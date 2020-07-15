# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "telegram_ros: 2 messages, 0 services")

set(MSG_I_FLAGS "-Itelegram_ros:/home/kisron/catkin_workspace/src/telegram_ros/msg;-Isensor_msgs:/opt/ros/melodic/share/sensor_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/melodic/share/geometry_msgs/cmake/../msg;-Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(telegram_ros_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/kisron/catkin_workspace/src/telegram_ros/msg/Options.msg" NAME_WE)
add_custom_target(_telegram_ros_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "telegram_ros" "/home/kisron/catkin_workspace/src/telegram_ros/msg/Options.msg" ""
)

get_filename_component(_filename "/home/kisron/catkin_workspace/src/telegram_ros/msg/LabeledImage.msg" NAME_WE)
add_custom_target(_telegram_ros_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "telegram_ros" "/home/kisron/catkin_workspace/src/telegram_ros/msg/LabeledImage.msg" "sensor_msgs/Image:std_msgs/Header"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(telegram_ros
  "/home/kisron/catkin_workspace/src/telegram_ros/msg/Options.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/telegram_ros
)
_generate_msg_cpp(telegram_ros
  "/home/kisron/catkin_workspace/src/telegram_ros/msg/LabeledImage.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/sensor_msgs/cmake/../msg/Image.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/telegram_ros
)

### Generating Services

### Generating Module File
_generate_module_cpp(telegram_ros
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/telegram_ros
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(telegram_ros_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(telegram_ros_generate_messages telegram_ros_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/kisron/catkin_workspace/src/telegram_ros/msg/Options.msg" NAME_WE)
add_dependencies(telegram_ros_generate_messages_cpp _telegram_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/kisron/catkin_workspace/src/telegram_ros/msg/LabeledImage.msg" NAME_WE)
add_dependencies(telegram_ros_generate_messages_cpp _telegram_ros_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(telegram_ros_gencpp)
add_dependencies(telegram_ros_gencpp telegram_ros_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS telegram_ros_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(telegram_ros
  "/home/kisron/catkin_workspace/src/telegram_ros/msg/Options.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/telegram_ros
)
_generate_msg_eus(telegram_ros
  "/home/kisron/catkin_workspace/src/telegram_ros/msg/LabeledImage.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/sensor_msgs/cmake/../msg/Image.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/telegram_ros
)

### Generating Services

### Generating Module File
_generate_module_eus(telegram_ros
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/telegram_ros
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(telegram_ros_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(telegram_ros_generate_messages telegram_ros_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/kisron/catkin_workspace/src/telegram_ros/msg/Options.msg" NAME_WE)
add_dependencies(telegram_ros_generate_messages_eus _telegram_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/kisron/catkin_workspace/src/telegram_ros/msg/LabeledImage.msg" NAME_WE)
add_dependencies(telegram_ros_generate_messages_eus _telegram_ros_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(telegram_ros_geneus)
add_dependencies(telegram_ros_geneus telegram_ros_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS telegram_ros_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(telegram_ros
  "/home/kisron/catkin_workspace/src/telegram_ros/msg/Options.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/telegram_ros
)
_generate_msg_lisp(telegram_ros
  "/home/kisron/catkin_workspace/src/telegram_ros/msg/LabeledImage.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/sensor_msgs/cmake/../msg/Image.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/telegram_ros
)

### Generating Services

### Generating Module File
_generate_module_lisp(telegram_ros
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/telegram_ros
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(telegram_ros_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(telegram_ros_generate_messages telegram_ros_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/kisron/catkin_workspace/src/telegram_ros/msg/Options.msg" NAME_WE)
add_dependencies(telegram_ros_generate_messages_lisp _telegram_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/kisron/catkin_workspace/src/telegram_ros/msg/LabeledImage.msg" NAME_WE)
add_dependencies(telegram_ros_generate_messages_lisp _telegram_ros_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(telegram_ros_genlisp)
add_dependencies(telegram_ros_genlisp telegram_ros_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS telegram_ros_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(telegram_ros
  "/home/kisron/catkin_workspace/src/telegram_ros/msg/Options.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/telegram_ros
)
_generate_msg_nodejs(telegram_ros
  "/home/kisron/catkin_workspace/src/telegram_ros/msg/LabeledImage.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/sensor_msgs/cmake/../msg/Image.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/telegram_ros
)

### Generating Services

### Generating Module File
_generate_module_nodejs(telegram_ros
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/telegram_ros
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(telegram_ros_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(telegram_ros_generate_messages telegram_ros_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/kisron/catkin_workspace/src/telegram_ros/msg/Options.msg" NAME_WE)
add_dependencies(telegram_ros_generate_messages_nodejs _telegram_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/kisron/catkin_workspace/src/telegram_ros/msg/LabeledImage.msg" NAME_WE)
add_dependencies(telegram_ros_generate_messages_nodejs _telegram_ros_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(telegram_ros_gennodejs)
add_dependencies(telegram_ros_gennodejs telegram_ros_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS telegram_ros_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(telegram_ros
  "/home/kisron/catkin_workspace/src/telegram_ros/msg/Options.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/telegram_ros
)
_generate_msg_py(telegram_ros
  "/home/kisron/catkin_workspace/src/telegram_ros/msg/LabeledImage.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/sensor_msgs/cmake/../msg/Image.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/telegram_ros
)

### Generating Services

### Generating Module File
_generate_module_py(telegram_ros
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/telegram_ros
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(telegram_ros_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(telegram_ros_generate_messages telegram_ros_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/kisron/catkin_workspace/src/telegram_ros/msg/Options.msg" NAME_WE)
add_dependencies(telegram_ros_generate_messages_py _telegram_ros_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/kisron/catkin_workspace/src/telegram_ros/msg/LabeledImage.msg" NAME_WE)
add_dependencies(telegram_ros_generate_messages_py _telegram_ros_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(telegram_ros_genpy)
add_dependencies(telegram_ros_genpy telegram_ros_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS telegram_ros_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/telegram_ros)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/telegram_ros
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET sensor_msgs_generate_messages_cpp)
  add_dependencies(telegram_ros_generate_messages_cpp sensor_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/telegram_ros)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/telegram_ros
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET sensor_msgs_generate_messages_eus)
  add_dependencies(telegram_ros_generate_messages_eus sensor_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/telegram_ros)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/telegram_ros
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET sensor_msgs_generate_messages_lisp)
  add_dependencies(telegram_ros_generate_messages_lisp sensor_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/telegram_ros)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/telegram_ros
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET sensor_msgs_generate_messages_nodejs)
  add_dependencies(telegram_ros_generate_messages_nodejs sensor_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/telegram_ros)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/telegram_ros\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/telegram_ros
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET sensor_msgs_generate_messages_py)
  add_dependencies(telegram_ros_generate_messages_py sensor_msgs_generate_messages_py)
endif()
