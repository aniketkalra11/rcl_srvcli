cmake_minimum_required(VERSION 3.5)
project(cpp_srvcli)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(cpp_srvcli REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(rosidl_default_generators REQUIRED)


rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/ConcatStr.srv"
 )


add_executable(server src/add_two_ints_server.cpp)
ament_target_dependencies(server rclcpp example_interfaces)

add_executable(client src/add_two_ints_client.cpp)
ament_target_dependencies(client rclcpp example_interfaces)


add_executable(server_str src/concat_str_server.cpp)
ament_target_dependencies(server_str rclcpp std_msgs cpp_srvcli)

add_executable(client_str src/concat_str_client.cpp)
ament_target_dependencies(client_str rclcpp std_msgs cpp_srvcli)

install(TARGETS 
    server
    client
    server_str
    client_str
    DESTINATION lib/${PROJECT_NAME}
)

ament_package()
