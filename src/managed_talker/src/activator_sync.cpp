#include <chrono>
#include <cstdlib>
#include <functional>
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

#include <std_msgs/msg/detail/int16__struct.hpp>
#include <std_msgs/msg/int16.hpp>
#include <string>
#include <vector>

namespace managed_talker {

class LifeActivator : public rclcpp_lifecycle::LifecycleNode {
public:
  LifeActivator(const rclcpp::NodeOptions &options)
      : rclcpp_lifecycle::LifecycleNode("AllActivator", options) {
    this->declare_parameter("lifecycles_list", rclcpp::PARAMETER_STRING_ARRAY);

    lifecycle_list = this->get_parameter("lifecycles_list").as_string_array();

    // if (lifecycle_list.size() > 0) to_continue = true;
    // else to_continue = false;

    to_continue = lifecycle_list.size() > 0 ? true : false;

    for (long unsigned int i = 0; i < lifecycle_list.size(); i++) {
      RCLCPP_INFO(this->get_logger(), "%s, %i", lifecycle_list[i].c_str(),
                  to_continue);

      get_state_topics.push_back(lifecycle_list[i] + "/get_state");
      change_state_topics.push_back(lifecycle_list[i] + "/change_state");

      RCLCPP_INFO(this->get_logger(), "%s, %i", get_state_topics[i].c_str(),
                  to_continue);
      RCLCPP_INFO(this->get_logger(), "%s, %i", change_state_topics[i].c_str(),
                  to_continue);
    };
  }

  void topic_callback(const std_msgs::msg::Int16 &msg) {

    RCLCPP_INFO(this->get_logger(), "Got Subscription");

  }

  // first callback, this is the initial state
  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
  on_configure(const rclcpp_lifecycle::State &) {


    for (long unsigned int i; i < get_state_topics.size(); i++) {
      state_clients.push_back(
          this->create_client<lifecycle_msgs::srv::GetState>(
              get_state_topics[i].c_str()));
    }

    for (long unsigned int i; i < get_state_topics.size(); i++) {
      change_clients.push_back(
          this->create_client<lifecycle_msgs::srv::ChangeState>(
              change_state_topics[i].c_str()));
    }


    bool val = to_all_change(lifecycle_msgs::msg::Transition::TRANSITION_CONFIGURE);
    
    
    RCLCPP_INFO(this->get_logger(), "on_configure() is called, transition suceeded in all: %i", val);

    

    // SUCESS -> inactive , FAILURE -> unconfigured
    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::
        CallbackReturn::SUCCESS;
  }

  ////////////////////////////

  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
  on_activate(const rclcpp_lifecycle::State &state) {

    rclcpp_lifecycle::LifecycleNode::on_activate(state);
    subscription_ = this->create_subscription<std_msgs::msg::Int16>(
        "get_stuff", 10,
        std::bind(&LifeActivator::topic_callback, this, std::placeholders::_1));

    bool val = to_all_change(lifecycle_msgs::msg::Transition::TRANSITION_ACTIVATE);


    RCLCPP_INFO(this->get_logger(), "on_activate() is called, transition suceeded in all: %i", val);

    // SUCESS -> active, FAILURE->inactive
    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::
        CallbackReturn::SUCCESS;
  }

  /////////////////

  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
  on_deactivate(const rclcpp_lifecycle::State &state) {

    rclcpp_lifecycle::LifecycleNode::on_deactivate(state);

    subscription_.reset();

    bool val = to_all_change(lifecycle_msgs::msg::Transition::TRANSITION_DEACTIVATE);

    RCLCPP_INFO(this->get_logger(), "on_deactivate() is called. sucess: %i", val);

    // SUCESS -> Inactive , FAILURE -> Active
    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::
        CallbackReturn::SUCCESS;
  }

  ///////////////////////////

  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
  on_cleanup(const rclcpp_lifecycle::State &state) {
    subscription_.reset();

    rclcpp_lifecycle::LifecycleNode::on_cleanup(state);

    bool val = to_all_change(lifecycle_msgs::msg::Transition::TRANSITION_CLEANUP);
    RCLCPP_INFO(this->get_logger(), "on cleanup is called. sucess: %i", val);
    // SUCCESS -> unconfigured
    // FAILURE -> inactive
    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::
        CallbackReturn::SUCCESS;
  }

  ////////////////////////

  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
  on_shutdown(const rclcpp_lifecycle::State &state) {

    subscription_.reset();

    rclcpp_lifecycle::LifecycleNode::on_shutdown(state);

    bool val = to_all_change(lifecycle_msgs::msg::Transition::TRANSITION_CLEANUP);
    RCLCPP_INFO(this->get_logger(), "shutdown called from state %s, sucess: %i",
                state.label().c_str(), val);

    // SUCCESS -> finalized (dead state i guess)
    // FAILURE -> <current state>

    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::
        CallbackReturn::SUCCESS;
  }

  ///////////////////

  bool change_state(std::uint8_t transition,  unsigned int index = 0)
  {
    auto request =
        std::make_shared<lifecycle_msgs::srv::ChangeState::Request>();
    request->transition.id = transition;

    if (!change_clients[index]->wait_for_service(time_out)) {
      RCLCPP_ERROR(get_logger(), "Service %s is not available.",
                   change_clients[index]->get_service_name());
      return false;
    }

    auto result = change_clients[index]->async_send_request();


    

  }


  bool to_all_change(std::uint8_t transit) {
    bool retstate = true;
    bool val;
    RCLCPP_INFO(this->get_logger(), "to_all_change");

    for (long unsigned int i = 0; i < change_clients.size(); i++) {

      RCLCPP_INFO(this->get_logger(), "to_all_change: %li", i);

      val = change_state(transit, i);
      
      if (retstate) {
	retstate = val;
      }
    };

    return retstate;
  };

  rclcpp::Subscription<std_msgs::msg::Int16>::SharedPtr subscription_;

  std::vector<std::string> lifecycle_list;
  std::vector<std::string> get_state_topics;
  std::vector<std::string> change_state_topics;

  std::vector<std::shared_ptr<rclcpp::Client<lifecycle_msgs::srv::GetState>>>
      state_clients;
  std::vector<std::shared_ptr<rclcpp::Client<lifecycle_msgs::srv::ChangeState>>>
      change_clients;

  bool to_continue;
};

}; // namespace managed_talker

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);

  auto options = rclcpp::NodeOptions().use_intra_process_comms(false);

  rclcpp::spin(std::make_shared<managed_talker::LifeActivator>(options)
                   ->get_node_base_interface());

  rclcpp::shutdown();

  return 0;
}
