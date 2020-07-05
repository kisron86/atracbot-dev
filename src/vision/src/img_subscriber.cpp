#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui/highgui.hpp>
#include "my_roscpp_library/my_stereofunction.h"
#include "my_roscpp_library/my_stereograb.h"

using namespace cv;

Mat imgl(320,240,CV_8UC4);
Mat imgr(320,240,CV_8UC4);
    

void r_imageCallback(const sensor_msgs::ImageConstPtr& msg){
    try {
        //imshow("viewr", cv_bridge::toCvShare(msg, "bgr8")->image);
        cv_bridge::toCvShare(msg, "bgr8")->image.copyTo(imgr);
        //imshow("viewr", imgr);
        //waitKey(30);
    } catch (cv_bridge::Exception& e) {
        ROS_ERROR("Could not conver from '%s' to 'bgr8'.", msg->encoding.c_str());
    }
}

void l_imageCallback(const sensor_msgs::ImageConstPtr& msg){
    try {
        //imshow("viewl", cv_bridge::toCvShare(msg, "bgr8")->image);
        cv_bridge::toCvShare(msg, "bgr8")->image.copyTo(imgl);
        //imshow("viewl", imgl);
        //waitKey(30);
    } catch (cv_bridge::Exception& e) {
        ROS_ERROR("Could not conver from '%s' to 'bgr8'.", msg->encoding.c_str());
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "img_subscriber");
    ros::NodeHandle nh;

    image_transport::ImageTransport it(nh);
    image_transport::Subscriber subr = it.subscribe("camera/right/image_raw", 1, r_imageCallback);
    image_transport::Subscriber subl = it.subscribe("camera/left/image_raw", 1, l_imageCallback);
        
    while(ros::ok()){
        imshow("kanan", imgr);
        imshow("kiri", imgl);
        waitKey(10);
        ros::spinOnce();

        if(waitKey(30) == 27){
            break;
        }
    }
    return 0;
}