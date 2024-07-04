#include <chrono>
#include <functional>
#include <memory>
#include <rclcpp/node_options.hpp>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <rclcpp_components/register_node_macro.hpp>

namespace test_pubsub {

class NodeMsgNo : public rclcpp::Node {
public:
  NodeMsgNo(const rclcpp::NodeOptions & options) : rclcpp::Node("test_node", options) {
    publ = this->create_publisher<std_msgs::msg::String>("publ", 10);
    timer = this->create_wall_timer(std::chrono::milliseconds(500),
                                    std::bind(&NodeMsgNo::test, this));
  }

private:
  void test() {
    auto message = std_msgs::msg::String();
    message.data = "Hello World";
    RCLCPP_INFO(this->get_logger(), "Publishing");
    publ->publish(message);
  };

  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publ;
  rclcpp::TimerBase::SharedPtr timer;
};

} // namespace no_message


RCLCPP_COMPONENTS_REGISTER_NODE(test_pubsub::NodeMsgNo);

// int main(int argc, char * argv[]) // 
// {
//   rclcpp::init(argc, argv);

//   rclcpp::NodeOptions def = rclcpp::NodeOptions();

//   rclcpp::spin(std::make_shared<test_pubsub::NodeMsgNo>(def));

//   rclcpp::shutdown();
//   return 0;
// }

