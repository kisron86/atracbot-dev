
(cl:in-package :asdf)

(defsystem "telegram_ros-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :sensor_msgs-msg
)
  :components ((:file "_package")
    (:file "LabeledImage" :depends-on ("_package_LabeledImage"))
    (:file "_package_LabeledImage" :depends-on ("_package"))
    (:file "Options" :depends-on ("_package_Options"))
    (:file "_package_Options" :depends-on ("_package"))
  ))