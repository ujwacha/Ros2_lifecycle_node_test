#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <rclcpp_lifecycle/lifecycle_node.hpp>

namespace listener_com {
using std::placeholders::_1;

class MinimalSubscriber : public rclcpp_lifecycle::LifecycleNode {
public:
  MinimalSubscriber(const rclcpp::NodeOptions &options)
      : rclcpp_lifecycle::LifecycleNode("minimal_subscriber", options) {}

  // first callback, this is the initial state
  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
  on_configure(const rclcpp_lifecycle::State &) {

    activated = false;

    RCLCPP_INFO(this->get_logger(), "on_configure() is called.");

    // SUCESS -> inactive , FAILURE -> unconfigured
    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::
        CallbackReturn::SUCCESS;
  }

  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
  on_activate(const rclcpp_lifecycle::State &state) {
    RCLCPP_INFO(this->get_logger(), "on_activate() is called.");

    rclcpp_lifecycle::LifecycleNode::on_activate(state);
    subscription_ = this->create_subscription<std_msgs::msg::String>(
        "chat_here", 10,
        std::bind(&MinimalSubscriber::topic_callback, this, _1));

    activated = true;

    // Let's sleep for 2 seconds.
    // We emulate we are doing important
    // work in the activating phase.
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    // SUCESS -> active, FAILURE->inactive
    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::
        CallbackReturn::SUCCESS;
  }

  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
  on_deactivate(const rclcpp_lifecycle::State &state) {

    rclcpp_lifecycle::LifecycleNode::on_deactivate(state);

    subscription_.reset();

    RCLCPP_INFO(this->get_logger(), "on_deactivate() is called.");

    // SUCESS -> Inactive , FAILURE -> Active
    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::
        CallbackReturn::SUCCESS;
  }

  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
  on_cleanup(const rclcpp_lifecycle::State &state) {
    subscription_.reset();

    rclcpp_lifecycle::LifecycleNode::on_cleanup(state);

    RCLCPP_INFO(this->get_logger(), "on cleanup is called.");
    // SUCCESS -> unconfigured
    // FAILURE -> inactive
    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::
        CallbackReturn::SUCCESS;
  }

  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
  on_shutdown(const rclcpp_lifecycle::State &state) {

    subscription_.reset();

    rclcpp_lifecycle::LifecycleNode::on_shutdown(state);

    RCLCPP_INFO(this->get_logger(), "shutdown called from state %s",
                state.label().c_str());

    // SUCCESS -> finalized (dead state i guess)
    // FAILURE -> <current state>

    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::
        CallbackReturn::SUCCESS;
  }

private:
  void topic_callback(const std_msgs::msg::String &msg) const {
    RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
  }
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
  bool activated = false;
};
}; // namespace listener_com

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(listener_com::MinimalSubscriber)

// int main(int argc, char * argv[])
// {
//   rclcpp::init(argc, argv);
//   rclcpp::spin(std::make_shared<MinimalSubscriber>());
//   rclcpp::shutdown();
//   return 0;
// }
