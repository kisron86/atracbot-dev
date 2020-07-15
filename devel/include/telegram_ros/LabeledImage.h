// Generated by gencpp from file telegram_ros/LabeledImage.msg
// DO NOT EDIT!


#ifndef TELEGRAM_ROS_MESSAGE_LABELEDIMAGE_H
#define TELEGRAM_ROS_MESSAGE_LABELEDIMAGE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <sensor_msgs/Image.h>

namespace telegram_ros
{
template <class ContainerAllocator>
struct LabeledImage_
{
  typedef LabeledImage_<ContainerAllocator> Type;

  LabeledImage_()
    : label()
    , image()  {
    }
  LabeledImage_(const ContainerAllocator& _alloc)
    : label(_alloc)
    , image(_alloc)  {
  (void)_alloc;
    }



   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _label_type;
  _label_type label;

   typedef  ::sensor_msgs::Image_<ContainerAllocator>  _image_type;
  _image_type image;





  typedef boost::shared_ptr< ::telegram_ros::LabeledImage_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::telegram_ros::LabeledImage_<ContainerAllocator> const> ConstPtr;

}; // struct LabeledImage_

typedef ::telegram_ros::LabeledImage_<std::allocator<void> > LabeledImage;

typedef boost::shared_ptr< ::telegram_ros::LabeledImage > LabeledImagePtr;
typedef boost::shared_ptr< ::telegram_ros::LabeledImage const> LabeledImageConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::telegram_ros::LabeledImage_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::telegram_ros::LabeledImage_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::telegram_ros::LabeledImage_<ContainerAllocator1> & lhs, const ::telegram_ros::LabeledImage_<ContainerAllocator2> & rhs)
{
  return lhs.label == rhs.label &&
    lhs.image == rhs.image;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::telegram_ros::LabeledImage_<ContainerAllocator1> & lhs, const ::telegram_ros::LabeledImage_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace telegram_ros

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::telegram_ros::LabeledImage_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::telegram_ros::LabeledImage_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::telegram_ros::LabeledImage_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::telegram_ros::LabeledImage_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::telegram_ros::LabeledImage_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::telegram_ros::LabeledImage_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::telegram_ros::LabeledImage_<ContainerAllocator> >
{
  static const char* value()
  {
    return "75484018036457751667104ffd54a14e";
  }

  static const char* value(const ::telegram_ros::LabeledImage_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x7548401803645775ULL;
  static const uint64_t static_value2 = 0x1667104ffd54a14eULL;
};

template<class ContainerAllocator>
struct DataType< ::telegram_ros::LabeledImage_<ContainerAllocator> >
{
  static const char* value()
  {
    return "telegram_ros/LabeledImage";
  }

  static const char* value(const ::telegram_ros::LabeledImage_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::telegram_ros::LabeledImage_<ContainerAllocator> >
{
  static const char* value()
  {
    return "string label\n"
"sensor_msgs/Image image\n"
"\n"
"================================================================================\n"
"MSG: sensor_msgs/Image\n"
"# This message contains an uncompressed image\n"
"# (0, 0) is at top-left corner of image\n"
"#\n"
"\n"
"Header header        # Header timestamp should be acquisition time of image\n"
"                     # Header frame_id should be optical frame of camera\n"
"                     # origin of frame should be optical center of camera\n"
"                     # +x should point to the right in the image\n"
"                     # +y should point down in the image\n"
"                     # +z should point into to plane of the image\n"
"                     # If the frame_id here and the frame_id of the CameraInfo\n"
"                     # message associated with the image conflict\n"
"                     # the behavior is undefined\n"
"\n"
"uint32 height         # image height, that is, number of rows\n"
"uint32 width          # image width, that is, number of columns\n"
"\n"
"# The legal values for encoding are in file src/image_encodings.cpp\n"
"# If you want to standardize a new string format, join\n"
"# ros-users@lists.sourceforge.net and send an email proposing a new encoding.\n"
"\n"
"string encoding       # Encoding of pixels -- channel meaning, ordering, size\n"
"                      # taken from the list of strings in include/sensor_msgs/image_encodings.h\n"
"\n"
"uint8 is_bigendian    # is this data bigendian?\n"
"uint32 step           # Full row length in bytes\n"
"uint8[] data          # actual matrix data, size is (step * rows)\n"
"\n"
"================================================================================\n"
"MSG: std_msgs/Header\n"
"# Standard metadata for higher-level stamped data types.\n"
"# This is generally used to communicate timestamped data \n"
"# in a particular coordinate frame.\n"
"# \n"
"# sequence ID: consecutively increasing ID \n"
"uint32 seq\n"
"#Two-integer timestamp that is expressed as:\n"
"# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n"
"# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n"
"# time-handling sugar is provided by the client library\n"
"time stamp\n"
"#Frame this data is associated with\n"
"string frame_id\n"
;
  }

  static const char* value(const ::telegram_ros::LabeledImage_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::telegram_ros::LabeledImage_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.label);
      stream.next(m.image);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct LabeledImage_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::telegram_ros::LabeledImage_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::telegram_ros::LabeledImage_<ContainerAllocator>& v)
  {
    s << indent << "label: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.label);
    s << indent << "image: ";
    s << std::endl;
    Printer< ::sensor_msgs::Image_<ContainerAllocator> >::stream(s, indent + "  ", v.image);
  }
};

} // namespace message_operations
} // namespace ros

#endif // TELEGRAM_ROS_MESSAGE_LABELEDIMAGE_H