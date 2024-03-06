cmake_minimum_required(VERSION 3.5)

project (marine_radio_tools)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(catkin REQUIRED COMPONENTS
  marine_radio_msgs
  roscpp
)

catkin_package(
  CATKIN_DEPENDS flite marine_radio_msgs
)

add_executable(send_text_service src/send_text_service.cpp)

target_include_directories(send_text_service PUBLIC ${catkin_INCLUDE_DIRS})
target_link_libraries(send_text_service ${catkin_LIBRARIES} flite_cmu_us_kal flite_usenglish flite_cmulex flite)
add_dependencies(send_text_service ${catkin_EXPORTED_TARGETS})


