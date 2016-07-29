cmake_minimum_required(VERSION 2.8.3)
project(pub_sim)

find_package(catkin REQUIRED COMPONENTS roscpp std_msgs)

catkin_package()

include_directories(${catkin_INCLUDE_DIRS})

add_executable(pub_sim src/main.cpp)

target_link_libraries(pub_sim ${catkin_LIBRARIES})

