cmake_minimum_required(VERSION 3.5)
project(tuw2_example_pkg)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(std_msgs REQUIRED)

include_directories(include)

add_library(composition_nodes SHARED
            src/publisher_node.cpp
            src/subscriber_node.cpp)
target_compile_definitions(composition_nodes
  PRIVATE "TUW2_EXAMPLE_PACKAGE_DLL")
ament_target_dependencies(composition_nodes rclcpp rclcpp_components std_msgs)

# This package installs libraries without exporting them.
# Export the library path to ensure that the installed libraries are available.
if(NOT WIN32)
  ament_environment_hooks(
    "${ament_cmake_package_templates_ENVIRONMENT_HOOK_LIBRARY_PATH}")
endif()

add_executable(composition_publisher src/standalone_publisher.cpp)
target_link_libraries(composition_publisher composition_nodes)
ament_target_dependencies(composition_publisher
  rclcpp)

add_executable(composition_subscriber src/standalone_subscriber.cpp)
target_link_libraries(composition_subscriber composition_nodes)
ament_target_dependencies(composition_subscriber
  rclcpp)

add_executable(composition_composed src/composed.cpp)
target_link_libraries(composition_composed composition_nodes)
ament_target_dependencies(composition_composed rclcpp class_loader)

install(TARGETS
  composition_nodes
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)

install(TARGETS
  composition_publisher
  composition_subscriber
  composition_composed
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()

  find_package(ament_cmake_gtest REQUIRED)
  ament_add_gtest(pub_test test/test_subscriber.cpp)  # Need to link .cpp file under test
  target_include_directories(pub_test PUBLIC src/)  # Need to specify directories in order to #include from them in the test
  target_link_libraries(pub_test composition_nodes)
  ament_target_dependencies(pub_test rclcpp rclcpp_components std_msgs)  # Gtest requires rclcpp to instantiate the Node

endif()

ament_package()
