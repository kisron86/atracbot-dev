#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include "my_roscpp_library/my_stereograb.h"

CvCapture *capture1=NULL, *capture2=NULL;
Mat imgl_s(320,240,CV_8UC4);
Mat imgr_s(320,240,CV_8UC4);

void r_imageCallback(const sensor_msgs::ImageConstPtr& msg){
    try {
        //cvShowImage("viewr", cv_bridge::toCvShare(msg, "mono8")->image);
        cv_bridge::toCvShare(msg, "mono8")->image.copyTo(imgr_s);
        //imshow("viewr", imgr);
        //waitKey(30);
    } catch (cv_bridge::Exception& e) {
        ROS_ERROR("Could not conver from '%s' to 'bgr8'.", msg->encoding.c_str());
    }
}

void l_imageCallback(const sensor_msgs::ImageConstPtr& msg){
    try {
        //cvShowImage("viewl", cv_bridge::toCvShare(msg, "mono8")->image);
        cv_bridge::toCvShare(msg, "mono8")->image.copyTo(imgl_s);
        //imshow("viewl", imgl);
        //waitKey(30);
    } catch (cv_bridge::Exception& e) {
        ROS_ERROR("Could not conver from '%s' to 'bgr8'.", msg->encoding.c_str());
    }
}


void StereoGrab::stereoGrabInitFrames(){

  capture1=cvCaptureFromCAM(4);
  assert(capture1!=NULL);
  cvWaitKey(100);
  capture2=cvCaptureFromCAM(0);
  assert(capture2!=NULL);

  cvSetCaptureProperty(capture1,CV_CAP_PROP_FRAME_WIDTH,WIDTH);
  cvSetCaptureProperty(capture1,CV_CAP_PROP_FRAME_HEIGHT,HEIGHT);
  cvSetCaptureProperty(capture2,CV_CAP_PROP_FRAME_WIDTH,WIDTH);
  cvSetCaptureProperty(capture2,CV_CAP_PROP_FRAME_HEIGHT,HEIGHT);
}

void StereoGrab::stereGrabFrames(){
	imageLeft = cvQueryFrame(capture1);
	imageRight = cvQueryFrame(capture2);
  cvSaveImage("/home/kisron/catkin_workspace/cam_left.jpg", imageLeft);
}

void StereoGrab::stereoGrabStopCam(){
  cvReleaseCapture( &capture1 );
  cvReleaseCapture( &capture2 );
}

void StereoGrab::stereoGrabGetSubscribeFrame()
{
  ros::init(argc, argv, "stereo_subscriber_test");
  ros::NodeHandle nh;

  image_transport::ImageTransport it(nh);
  image_transport::Subscriber subr = it.subscribe("camera/right/image_raw", 1, r_imageCallback);
  image_transport::Subscriber subl = it.subscribe("camera/left/image_raw", 1, l_imageCallback);

  imageLeftSubs = imgl_s;
  imageLeftSubs = IplImage(imgl_s);
  imageRightSubs = imgr_s;
  imageRightSubs = IplImage(imgr_s);
}