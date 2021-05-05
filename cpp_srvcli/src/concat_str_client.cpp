// [
//         "/home/anni/sample_ws/src/ros_tutorials/turtlesim/include/**",
//         "/home/anni/sample_ws/src/srv_string/include/**",
//         "/opt/ros/foxy/include/**",
//         "/usr/include/**",
//         "/home/anni/sample_ws/install/cpp_srvcli/include/**"
//       ],


#include <chrono>
#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "cpp_srvcli/srv/concat_str.hpp"
//for test purpose only 
//#include "/home/anni/sample_ws/install/cpp_srvcli/include/cpp_srvcli/srv/concat_str.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

int main(int argc, char** argv){

    rclcpp::init(argc, argv);

    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_two_str_client");
    rclcpp::Client<cpp_srvcli::srv::ConcatStr>::SharedPtr client = node->create_client<cpp_srvcli::srv::ConcatStr>("add_two_str");
    auto request = std::make_shared<cpp_srvcli::srv::ConcatStr_Request>();
    std::string aa = "Hello";
    std::string bb = "World";
    //RCLCPP_WARN(rclcpp::get_logger("rclcpp"), "we are sending this %s %s",aa);
    request->aa = aa;
    request->bb = bb;
    int sys = 123;
    request->sys = sys;

while (!client->wait_for_service(1s)) {
        if (!rclcpp::ok()) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
        return 0;
        }
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
    }

    auto result_str = client->async_send_request(request);
    
    //wait for result
    if(rclcpp::spin_until_future_complete(node, result_str) == rclcpp::FutureReturnCode::SUCCESS){
        std::string rslt = result_str.get()->concatinated_aa_bb;
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Result: %s", rslt);
    } else {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service add_two_ints");
    }
    rclcpp::shutdown();
    return 0;
}

