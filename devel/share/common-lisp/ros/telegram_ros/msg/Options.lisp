; Auto-generated. Do not edit!


(cl:in-package telegram_ros-msg)


;//! \htmlinclude Options.msg.html

(cl:defclass <Options> (roslisp-msg-protocol:ros-message)
  ((question
    :reader question
    :initarg :question
    :type cl:string
    :initform "")
   (options
    :reader options
    :initarg :options
    :type (cl:vector cl:string)
   :initform (cl:make-array 0 :element-type 'cl:string :initial-element "")))
)

(cl:defclass Options (<Options>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Options>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Options)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name telegram_ros-msg:<Options> is deprecated: use telegram_ros-msg:Options instead.")))

(cl:ensure-generic-function 'question-val :lambda-list '(m))
(cl:defmethod question-val ((m <Options>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader telegram_ros-msg:question-val is deprecated.  Use telegram_ros-msg:question instead.")
  (question m))

(cl:ensure-generic-function 'options-val :lambda-list '(m))
(cl:defmethod options-val ((m <Options>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader telegram_ros-msg:options-val is deprecated.  Use telegram_ros-msg:options instead.")
  (options m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Options>) ostream)
  "Serializes a message object of type '<Options>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'question))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'question))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'options))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((__ros_str_len (cl:length ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) ele))
   (cl:slot-value msg 'options))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Options>) istream)
  "Deserializes a message object of type '<Options>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'question) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'question) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'options) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'options)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:aref vals i) __ros_str_idx) (cl:code-char (cl:read-byte istream))))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Options>)))
  "Returns string type for a message object of type '<Options>"
  "telegram_ros/Options")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Options)))
  "Returns string type for a message object of type 'Options"
  "telegram_ros/Options")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Options>)))
  "Returns md5sum for a message object of type '<Options>"
  "95c5cf65731d4dcf4593661dbe57ef01")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Options)))
  "Returns md5sum for a message object of type 'Options"
  "95c5cf65731d4dcf4593661dbe57ef01")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Options>)))
  "Returns full string definition for message of type '<Options>"
  (cl:format cl:nil "string question~%string[] options~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Options)))
  "Returns full string definition for message of type 'Options"
  (cl:format cl:nil "string question~%string[] options~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Options>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'question))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'options) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4 (cl:length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Options>))
  "Converts a ROS message object to a list"
  (cl:list 'Options
    (cl:cons ':question (question msg))
    (cl:cons ':options (options msg))
))
