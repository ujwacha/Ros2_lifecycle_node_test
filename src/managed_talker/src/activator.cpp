#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <future>
#include <lifecycle_msgs/msg/detail/transition__struct.hpp>
#include <lifecycle_msgs/srv/detail/change_state__struct.hpp>
#include <lifecycle_msgs/srv/detail/get_state__struct.hpp>
#include <memory>
#include <rclcpp/client.hpp>
#include <rclcpp/logging.hpp>
#include <rclcpp/node_options.hpp>
#include <rclcpp/parameter_value.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/subscription.hpp>
#include <rclcpp_lifecycle/lifecycle_node.hpp>

#include <rclcpp_lifecycle/transition.hpp>
#include <std_msgs/msg/detail/int16__struct.hpp>
#include <std_msgs/msg/int16.hpp>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>


namespace managed_talker {

  using namespace lifecycle_msgs::msg;
 
  
  
class LifeActivator : public rclcpp_lifecycle::LifecycleNode {
public:

  int lookup_table[10];
  LifeActivator(const rclcpp::NodeOptions &options)
      : rclcpp_lifecycle::LifecycleNode("AllActivator", options) {
    this->declare_parameter("lifecycles_list", rclcpp::PARAMETER_STRING_ARRAY);

    lifecycle_list = this->get_parameter("lifecycles_list").as_string_array();


    lookup_table[Transition::TRANSITION_CONFIGURE] = 2 << 8;
    lookup_table[Transition::TRANSITION_ACTIVATE] = 3 << 8;
    lookup_table[Transition::TRANSITION_DEACTIVATE] = 2 << 8;
    lookup_table[Transition::TRANSITION_UNCONFIGURED_SHUTDOWN] = 4 << 8;
    lookup_table[Transition::TRANSITION_CLEANUP] = 1 << 8;
    
 

    for (long unsigned int i = 0; i < lifecycle_list.size(); i++) {
      RCLCPP_INFO(this->get_logger(), "%s", lifecycle_list[i].c_str());

    };

  
  }

  // first callback, this is the initial state
  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
  on_configure(const rclcpp_lifecycle::State & state) {

    rclcpp_lifecycle::LifecycleNode::on_configure(state);

    RCLCPP_INFO(this->get_logger(), "on_configure(), BEFORE");

    bool val = to_all_change(lifecycle_msgs::msg::Transition::TRANSITION_CONFIGURE);

    
    
    RCLCPP_INFO(this->get_logger(), "on_configure() is called, transition suceeded in all: %i", val);

    
    sucide(val);
    
    // SUCESS -> inactive , FAILURE -> unconfigured
    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::
        CallbackReturn::SUCCESS;
  }

  ////////////////////////////

  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
  on_activate(const rclcpp_lifecycle::State &state) {

    rclcpp_lifecycle::LifecycleNode::on_activate(state);

    bool val = to_all_change(lifecycle_msgs::msg::Transition::TRANSITION_ACTIVATE);


    RCLCPP_INFO(this->get_logger(), "on_activate() is called, transition suceeded in all: %i", val);

    sucide(val);
    // SUCESS -> active, FAILURE->inactive
    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::
        CallbackReturn::SUCCESS;
  }

  /////////////////

  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
  on_deactivate(const rclcpp_lifecycle::State &state) {

    rclcpp_lifecycle::LifecycleNode::on_deactivate(state);

    // subscription_.reset();

    bool val = to_all_change(lifecycle_msgs::msg::Transition::TRANSITION_DEACTIVATE);

    RCLCPP_INFO(this->get_logger(), "on_deactivate() is called. sucess: %i", val);

    sucide(val);
    // SUCESS -> Inactive , FAILURE -> Active
    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::
        CallbackReturn::SUCCESS;
  }

  ///////////////////////////

  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
  on_cleanup(const rclcpp_lifecycle::State &state) {
    // subscription_.reset();

    rclcpp_lifecycle::LifecycleNode::on_cleanup(state);

    bool val = to_all_change(lifecycle_msgs::msg::Transition::TRANSITION_CLEANUP);
    RCLCPP_INFO(this->get_logger(), "on cleanup is called. sucess: %i", val);


    sucide(val);

    // SUCCESS -> unconfigured
    // FAILURE -> inactive
    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::
        CallbackReturn::SUCCESS;
  }

  ////////////////////////

  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
  on_shutdown(const rclcpp_lifecycle::State &state) {

    // subscription_.reset();

    rclcpp_lifecycle::LifecycleNode::on_shutdown(state);

    bool val = to_all_change(lifecycle_msgs::msg::Transition::TRANSITION_UNCONFIGURED_SHUTDOWN);
    RCLCPP_INFO(this->get_logger(), "shutdown called from state %s, sucess: %i",
                state.label().c_str(), val);

    sucide(val);

    // SUCCESS -> finalized (dead state i guess)
    // FAILURE -> <current state>

    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::
        CallbackReturn::SUCCESS;
  }

  ///////////////////

  bool change_state(std::uint8_t transition,  unsigned int index = 0) {
    std::string current = lifecycle_list[index];

    std::string send_command = "ros2 lifecycle set " + current + " ";

    switch (transition) {
    case lifecycle_msgs::msg::Transition::TRANSITION_ACTIVATE:
      send_command += "activate";
      break;
    case lifecycle_msgs::msg::Transition::TRANSITION_DEACTIVATE:
      send_command += "deactivate";
      break;
    case lifecycle_msgs::msg::Transition::TRANSITION_CONFIGURE:
      send_command += "configure";
      break;
    case lifecycle_msgs::msg::Transition::TRANSITION_UNCONFIGURED_SHUTDOWN:
      send_command += "shutdown";
      break;
    case lifecycle_msgs::msg::Transition::TRANSITION_CLEANUP:
      send_command += "cleanup";
      break;

    default:
      RCLCPP_INFO(this->get_logger(), "[ERROR] didn't get a proper transition id");
      break;
    }
    
    system(send_command.c_str());

    std::string get_command = "exit $(ros2 lifecycle  get " + current + " | grep -oP '(?<=\\[).*?(?=\\])')";


    int value = system(get_command.c_str());
    RCLCPP_INFO(this->get_logger(), "VALUE:::::: %i", value);


    if (transition > 9) { // because the array is 10 units long
      return false;
    }

    if ( value == lookup_table[transition]) {

      RCLCPP_INFO(this->get_logger(), "Transition Sucessful");

      return true;
    } else {
      return false;
    }
    
  }
  
  bool to_all_change(std::uint8_t transit) {
    bool retstate = true;
    bool val;
    RCLCPP_INFO(this->get_logger(), "to_all_change Entered, size: %li", lifecycle_list.size());

    for (long unsigned int i = 0; i < lifecycle_list.size() ;i++) {


      val = change_state(transit, i);
      
      RCLCPP_INFO(this->get_logger(), "to_all_change: %li, %i", i, val);

      if (retstate) {
	retstate = val;
      }
    };

    return retstate;
  };


  void sucide(bool result) {
    if (result) return;

    // kill everyting if false comes up

    RCLCPP_INFO(this->get_logger(), "One of the nodes Failled to transition, Killing Every Node");

    to_all_change(lifecycle_msgs::msg::Transition::TRANSITION_UNCONFIGURED_SHUTDOWN);
  };

  // rclcpp::Subscription<std_msgs::msg::Int16>::SharedPtr subscription_;

  std::vector<std::string> lifecycle_list;

};

}; // namespace managed_talker


#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(managed_talker::LifeActivator);
