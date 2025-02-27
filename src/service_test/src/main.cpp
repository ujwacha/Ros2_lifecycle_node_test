#include <chrono>
#include <cstdint>
#include <functional>
#include <future>
#include <lifecycle_msgs/msg/detail/transition__struct.hpp>
#include <lifecycle_msgs/srv/detail/change_state__struct.hpp>
#include <memory>
#include <rclcpp/client.hpp>
#include <rclcpp/executors.hpp>
#include <rclcpp/logger.hpp>
#include <rclcpp/logging.hpp>
#include <rclcpp/node.hpp>
#include <rclcpp/node_options.hpp>
#include <rclcpp/rclcpp.hpp>
#include <lifecycle_msgs/srv/change_state.hpp>
#include <rclcpp/timer.hpp>
#include <rclcpp/utilities.hpp>
#include <string>


const char* service_name_global = "lifetalker/change_state";
// const char* another_service_name = "talker/change_state";

class ServiceNode: public rclcpp::Node {

public:
  ServiceNode(std::string nodename,
	      std::string service_name,
	      char t)
    : rclcpp::Node(nodename.c_str())
  {

    client = this->create_client<lifecycle_msgs::srv::ChangeState>(service_name);
    timer = this->create_wall_timer(std::chrono::milliseconds(1000),
				    std::bind(&ServiceNode::timer_callback, this));

    tra = t;
  }


  bool first_take = true;

  bool service_result = false;
private:

  void timer_callback() {
 
    RCLCPP_INFO(
		this->get_logger(),
		"*********HITMAN********");
    
    if (!first_take) {
        RCLCPP_INFO(
		    this->get_logger(),
		    "*********SHUTTING DOWN********");
	

	//      rclcpp::shutdown();
      return;
    }


    while (!client->wait_for_service(std::chrono::milliseconds(1000))) {
      if (rclcpp::ok()) {
        RCLCPP_INFO(
		     this->get_logger(),
		     "Client interrupted while waiting for service. Terminating...");
        return;
      }
      RCLCPP_INFO(this->get_logger(),
                  "Service Unavailable. Waiting for Service...");
    }


    auto request = std::make_shared<lifecycle_msgs::srv::ChangeState::Request>();

    request->transition.id = lifecycle_msgs::msg::Transition::TRANSITION_CONFIGURE;

    
    auto request_future = client->async_send_request(request,
						     std::bind(&ServiceNode::request_callback,
							       this,
							       std::placeholders::_1));


  }


  void request_callback(rclcpp::Client<lifecycle_msgs::srv::ChangeState>::SharedFuture future) {

    RCLCPP_INFO(this->get_logger(),
		"CALLBACK CALLED");

    auto status = future.wait_for(std::chrono::milliseconds(1000));

    if (status == std::future_status::ready) {
      std::shared_ptr<lifecycle_msgs::srv::ChangeState_Response_<std::allocator<void>>> data = future.get();
      RCLCPP_INFO(this->get_logger(),
		  "Result Success: %i",
		  data->success);

      // if (data->success > 0) this->service_result = true ;

      this->service_result = (data->success > 0)? true : false ;

      this->first_take = false;

    } else {
      RCLCPP_INFO(this->get_logger(),
		  "Service In-Progress...");

    }
  }

  rclcpp::Client<lifecycle_msgs::srv::ChangeState>::SharedPtr client;
  rclcpp::TimerBase::SharedPtr timer;
  char tra;

};


int main(int argc, char** argv) {
  rclcpp::init(argc, argv);


  auto node = std::make_shared<ServiceNode>(std::string("ServeNode"),
					     std::string(service_name_global),
					     lifecycle_msgs::msg::Transition::TRANSITION_CONFIGURE);

  while (node->first_take) {
    rclcpp::spin_some(node);
  }

  if (node->service_result) {
    RCLCPP_INFO(rclcpp::get_logger("OutMain"), "IT WAS TRUE");
  } else {
    RCLCPP_INFO(rclcpp::get_logger("OutMain"), "IT WAS TRUE");
  }


  rclcpp::shutdown();
  

}
