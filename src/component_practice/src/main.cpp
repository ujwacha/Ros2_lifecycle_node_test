#include <chrono>
#include <functional>
#include <memory>
#include <rclcpp/executors.hpp>
#include <rclcpp/logging.hpp>
#include <rclcpp/node.hpp>
#include <rclcpp/node_options.hpp>
#include <rclcpp/publisher.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/timer.hpp>
#include <rclcpp/utilities.hpp>
#include <rclcpp_lifecycle/lifecycle_publisher.hpp>
#include <rclcpp_lifecycle/node_interfaces/lifecycle_node_interface.hpp>
#include <std_msgs/msg/detail/string__struct.hpp>
#include <std_msgs/msg/string.hpp>
#include <rclcpp_lifecycle/lifecycle_node.hpp>

namespace component_practice {
  class PraPub: public rclcpp_lifecycle::LifecycleNode {
  public:
    PraPub(const rclcpp::NodeOptions & options ) : rclcpp_lifecycle::LifecycleNode("PraNode", options)
    {}

    rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
    on_configure(const rclcpp_lifecycle::State &) {
      
      publisher = this->create_publisher<std_msgs::msg::String>("chat_here", 10);
      timer = this->create_wall_timer(std::chrono::milliseconds(500),
				      std::bind(&PraPub::publish, this));


      return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;

    }
 

    void publish() {
      auto message = std_msgs::msg::String();
      message.data = "Hi Everyone";

      if (publisher->is_activated()) {
	RCLCPP_INFO(this->get_logger(), "sent Message");
      } else {
	RCLCPP_INFO(this->get_logger(), "NOT sent Message");
      }
      
      publisher->publish(message);
    }

    rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
    on_activate(const rclcpp_lifecycle::State & state) {
      RCLCPP_INFO(this->get_logger(), "on_activate() is called.");
      
      rclcpp_lifecycle::LifecycleNode::on_activate(state);
      
      //SUCESS -> active, FAILURE->inactive
    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
    }
    
    rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
    on_deactivate(const rclcpp_lifecycle::State & state) {
      
      rclcpp_lifecycle::LifecycleNode::on_deactivate(state);
      
      RCLCPP_INFO(this->get_logger(), "on_deactivate() is called.");
      
      // SUCESS -> Inactive , FAILURE -> Active
      return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
    }


    rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
    on_cleanup(const rclcpp_lifecycle::State & state) {
      timer.reset();
      publisher.reset();
      
      rclcpp_lifecycle::LifecycleNode::on_cleanup(state);
      
      RCLCPP_INFO(this->get_logger(), "on cleanup is called.");
      // SUCCESS -> unconfigured
      // FAILURE -> inactive
      return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
    }

    
    rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
    on_shutdown(const rclcpp_lifecycle::State & state) {
      timer.reset();
      publisher.reset();
      
      rclcpp_lifecycle::LifecycleNode::on_shutdown(state);
      
      RCLCPP_INFO(this->get_logger(), "shutdown called from state %s", state.label().c_str());
      
      // SUCCESS -> finalized (dead state i guess)
      // FAILURE -> <current state>
      
      
      return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
    }
    
    
    
    
    

  private:

    std::shared_ptr<rclcpp_lifecycle::LifecyclePublisher<std_msgs::msg::String>> publisher;

    rclcpp::TimerBase::SharedPtr timer;
  };
};

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(component_practice::PraPub)
