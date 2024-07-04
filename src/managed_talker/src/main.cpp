
#include <chrono>
#include <cstdint>
#include <functional>
#include <iostream>
#include <lifecycle_msgs/msg/transition.hpp>
#include <memory>
#include <rclcpp/executors.hpp>
#include <rclcpp/executors/single_threaded_executor.hpp>
#include <rclcpp/logging.hpp>
#include <rclcpp/node_options.hpp>
#include <rclcpp/publisher.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/timer.hpp>
#include <rclcpp/utilities.hpp>
#include <rclcpp_lifecycle/lifecycle_node.hpp>
#include <rclcpp_lifecycle/lifecycle_publisher.hpp>
#include <rclcpp_lifecycle/node_interfaces/lifecycle_node_interface.hpp>
#include <rclcpp_lifecycle/state.hpp>
#include <std_msgs/msg/detail/string__struct.hpp>
#include <std_msgs/msg/string.hpp>
#include <string>
#include <thread>
#include <utility>

using namespace std::chrono_literals;

namespace managed_talker {
class Life_Talker : public rclcpp_lifecycle::LifecycleNode {
public:
  explicit Life_Talker(const rclcpp::NodeOptions &options)
      : rclcpp_lifecycle::LifecycleNode("LifeNode", options) {}

  // publisher that gets called by timer
  void publ() {

    RCLCPP_INFO(this->get_logger(), "Timer Callback Activated");

    auto msg = std::make_unique<std_msgs::msg::String>();

    msg->data = "Hello From Life " + std::to_string(count);

    if (publisher->is_activated()) {
      RCLCPP_INFO(this->get_logger(),
                  "Lifecycle publisher is active. Publishing: [%s]",
                  msg->data.c_str());
    } else {
      RCLCPP_INFO(this->get_logger(), "Lifecycle publisher is currently "
                                      "inactive. Messages are not published.");
    }

    publisher->publish(std::move(msg));

    count++;
  }

  // first callback, this is the initial state
  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
  on_configure(const rclcpp_lifecycle::State &) {
    publisher = this->create_publisher<std_msgs::msg::String>(
        "lifecycle_publisher", 10);

    timer = this->create_wall_timer(1s, std::bind(&Life_Talker::publ, this));

    RCLCPP_INFO(this->get_logger(), "on_configure() is called.");

    // SUCESS -> inactive , FAILURE -> unconfigured
    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::
        CallbackReturn::SUCCESS;
  }

  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
  on_activate(const rclcpp_lifecycle::State &state) {
    RCLCPP_INFO(this->get_logger(), "on_activate() is called.");

    rclcpp_lifecycle::LifecycleNode::on_activate(state);

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

    RCLCPP_INFO(this->get_logger(), "on_deactivate() is called.");

    // SUCESS -> Inactive , FAILURE -> Active
    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::
        CallbackReturn::SUCCESS;
  }

  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
  on_cleanup(const rclcpp_lifecycle::State &state) {
    timer.reset();
    publisher.reset();

    rclcpp_lifecycle::LifecycleNode::on_cleanup(state);

    RCLCPP_INFO(this->get_logger(), "on cleanup is called.");
    // SUCCESS -> unconfigured
    // FAILURE -> inactive
    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::
        CallbackReturn::SUCCESS;
  }

  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
  on_shutdown(const rclcpp_lifecycle::State &state) {
    timer.reset();
    publisher.reset();

    rclcpp_lifecycle::LifecycleNode::on_shutdown(state);

    RCLCPP_INFO(this->get_logger(), "shutdown called from state %s",
                state.label().c_str());

    // SUCCESS -> finalized (dead state i guess)
    // FAILURE -> <current state>

    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::
        CallbackReturn::SUCCESS;
  }

private:
  // publiser
  std::shared_ptr<rclcpp_lifecycle::LifecyclePublisher<std_msgs::msg::String>>
      publisher;
  // timer
  std::shared_ptr<rclcpp::TimerBase> timer;

  uint64_t count = 0;
};
}; // namespace managed_talker

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(managed_talker::Life_Talker);

// int main(int argc, char** argv) {
//   rclcpp::init(argc, argv);

//   auto options = rclcpp::NodeOptions().use_intra_process_comms(false);

//   rclcpp::spin(std::make_shared<Life_Talker>(options)->get_node_base_interface());

//   rclcpp::shutdown();

//   return 0;
// }
