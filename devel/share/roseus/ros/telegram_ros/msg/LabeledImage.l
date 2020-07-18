;; Auto-generated. Do not edit!


(when (boundp 'telegram_ros::LabeledImage)
  (if (not (find-package "TELEGRAM_ROS"))
    (make-package "TELEGRAM_ROS"))
  (shadow 'LabeledImage (find-package "TELEGRAM_ROS")))
(unless (find-package "TELEGRAM_ROS::LABELEDIMAGE")
  (make-package "TELEGRAM_ROS::LABELEDIMAGE"))

(in-package "ROS")
;;//! \htmlinclude LabeledImage.msg.html
(if (not (find-package "SENSOR_MSGS"))
  (ros::roseus-add-msgs "sensor_msgs"))


(defclass telegram_ros::LabeledImage
  :super ros::object
  :slots (_label _image ))

(defmethod telegram_ros::LabeledImage
  (:init
   (&key
    ((:label __label) "")
    ((:image __image) (instance sensor_msgs::Image :init))
    )
   (send-super :init)
   (setq _label (string __label))
   (setq _image __image)
   self)
  (:label
   (&optional __label)
   (if __label (setq _label __label)) _label)
  (:image
   (&rest __image)
   (if (keywordp (car __image))
       (send* _image __image)
     (progn
       (if __image (setq _image (car __image)))
       _image)))
  (:serialization-length
   ()
   (+
    ;; string _label
    4 (length _label)
    ;; sensor_msgs/Image _image
    (send _image :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _label
       (write-long (length _label) s) (princ _label s)
     ;; sensor_msgs/Image _image
       (send _image :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _label
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _label (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; sensor_msgs/Image _image
     (send _image :deserialize buf ptr-) (incf ptr- (send _image :serialization-length))
   ;;
   self)
  )

(setf (get telegram_ros::LabeledImage :md5sum-) "75484018036457751667104ffd54a14e")
(setf (get telegram_ros::LabeledImage :datatype-) "telegram_ros/LabeledImage")
(setf (get telegram_ros::LabeledImage :definition-)
      "string label
sensor_msgs/Image image

================================================================================
MSG: sensor_msgs/Image
# This message contains an uncompressed image
# (0, 0) is at top-left corner of image
#

Header header        # Header timestamp should be acquisition time of image
                     # Header frame_id should be optical frame of camera
                     # origin of frame should be optical center of camera
                     # +x should point to the right in the image
                     # +y should point down in the image
                     # +z should point into to plane of the image
                     # If the frame_id here and the frame_id of the CameraInfo
                     # message associated with the image conflict
                     # the behavior is undefined

uint32 height         # image height, that is, number of rows
uint32 width          # image width, that is, number of columns

# The legal values for encoding are in file src/image_encodings.cpp
# If you want to standardize a new string format, join
# ros-users@lists.sourceforge.net and send an email proposing a new encoding.

string encoding       # Encoding of pixels -- channel meaning, ordering, size
                      # taken from the list of strings in include/sensor_msgs/image_encodings.h

uint8 is_bigendian    # is this data bigendian?
uint32 step           # Full row length in bytes
uint8[] data          # actual matrix data, size is (step * rows)

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

")



(provide :telegram_ros/LabeledImage "75484018036457751667104ffd54a14e")


