;; Auto-generated. Do not edit!


(when (boundp 'telegram_ros::Options)
  (if (not (find-package "TELEGRAM_ROS"))
    (make-package "TELEGRAM_ROS"))
  (shadow 'Options (find-package "TELEGRAM_ROS")))
(unless (find-package "TELEGRAM_ROS::OPTIONS")
  (make-package "TELEGRAM_ROS::OPTIONS"))

(in-package "ROS")
;;//! \htmlinclude Options.msg.html


(defclass telegram_ros::Options
  :super ros::object
  :slots (_question _options ))

(defmethod telegram_ros::Options
  (:init
   (&key
    ((:question __question) "")
    ((:options __options) (let (r) (dotimes (i 0) (push "" r)) r))
    )
   (send-super :init)
   (setq _question (string __question))
   (setq _options __options)
   self)
  (:question
   (&optional __question)
   (if __question (setq _question __question)) _question)
  (:options
   (&optional __options)
   (if __options (setq _options __options)) _options)
  (:serialization-length
   ()
   (+
    ;; string _question
    4 (length _question)
    ;; string[] _options
    (apply #'+ (mapcar #'(lambda (x) (+ 4 (length x))) _options)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _question
       (write-long (length _question) s) (princ _question s)
     ;; string[] _options
     (write-long (length _options) s)
     (dolist (elem _options)
       (write-long (length elem) s) (princ elem s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _question
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _question (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string[] _options
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _options (make-list n))
     (dotimes (i n)
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setf (elt _options i) (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
     ))
   ;;
   self)
  )

(setf (get telegram_ros::Options :md5sum-) "95c5cf65731d4dcf4593661dbe57ef01")
(setf (get telegram_ros::Options :datatype-) "telegram_ros/Options")
(setf (get telegram_ros::Options :definition-)
      "string question
string[] options

")



(provide :telegram_ros/Options "95c5cf65731d4dcf4593661dbe57ef01")


