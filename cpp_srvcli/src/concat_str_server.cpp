#include "rclcpp/rclcpp.hpp"
#include "cpp_srvcli/srv/concat_str.hpp"
#include "std_msgs/msg/string.hpp"

#include <memory>
#include <string>
void add(const std::shared_ptr<cpp_srvcli::srv::ConcatStr::Request> request, std::shared_ptr<cpp_srvcli::srv::ConcatStr::Response> response){


    std::string aa_r = request.get()->aa;
    std::string bb_r = request.get()->bb;
    int sys = request.get()->sys;
    RCLCPP_WARN(rclcpp::get_logger("rclcpp"), "this is what i am receiving %d", sys);

     std::string aa_bb_con = request.get()->aa + request.get()->bb;

     response->concatinated_aa_bb = aa_bb_con;
    
    // RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "we received  %c", aa_r);
    // RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "we received  %d", sys);
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request\na: %s b: %s",
    aa_r, bb_r);
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response: [%s]", response.get()->concatinated_aa_bb);

}

int main(int argc, char **argv){

    rclcpp::init(argc, argv);
    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_two_str_server");
    rclcpp::Service<cpp_srvcli::srv::ConcatStr>::SharedPtr service = node->create_service<cpp_srvcli::srv::ConcatStr>("add_two_str", &add);
    
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add two string.");

  rclcpp::spin(node);
  rclcpp::shutdown();
}