cmake_minimum_required(VERSION 2.8.3)
project(vision)

## Compile as C++11, supported in ROS Kinetic and newer
#add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  my_roscpp_library
  std_msgs
  image_transport
  sensor_msgs
  cv_bridge
)
set(OpenCV_INCLUDE_DIRS
  /usr/local/include
  /usr/local/include/opencv2
)

set(OpenCV_LIB_DIR
  /usr/local/lib
)


#set(OpenCV_DIR /home/kisron/opencv-2.4.13.5/release)
#find_package( OpenCV 2.4.13.5 EXACT REQUIRED )
find_package(OpenCV 2 REQUIRED)
#find_package(OpenCV COMPONENTS core highgui video imgproc REQUIRED)

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
#catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES vision
#  CATKIN_DEPENDS roscpp
#  DEPENDS system_lib
#)
catkin_package(
  INCLUDE_DIRS
  CATKIN_DEPENDS roscpp
                sensor_msgs
                std_msgs
                cv_bridge
                image_transport
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

include_directories(${OpenCV_INCLUDE_DIRS} ${catkin_INCLUDE_DIRS})

add_executable(trash_detection src/trash_detection.cpp)
target_link_libraries(trash_detection ${catkin_LIBRARIES} ${OpenCV_LIBS})

add_executable(target_detection src/target_detection.cpp)
add_dependencies(target_detection ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(target_detection ${catkin_LIBRARIES} ${OpenCV_LIBS})

add_executable(minoru_camera src/minoru_camera.cpp)
add_dependencies(minoru_camera ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(minoru_camera ${catkin_LIBRARIES} ${OpenCV_LIBS})

add_executable(img_subscriber src/img_subscriber.cpp)
add_dependencies(img_subscriber ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(img_subscriber ${catkin_LIBRARIES} ${OpenCV_LIBS})

add_executable(stereo_publisher src/stereo_publisher.cpp)
add_dependencies(stereo_publisher ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(stereo_publisher ${catkin_LIBRARIES} ${OpenCV_LIBS})

##add_executable(stereo_subscriber src/stereo_subscriber.cpp)
##add_dependencies(stereo_subscriber ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
##target_link_libraries(stereo_subscriber ${catkin_LIBRARIES} ${OpenCV_LIBS})