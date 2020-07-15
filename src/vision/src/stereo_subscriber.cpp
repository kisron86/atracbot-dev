#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "my_roscpp_library/my_stereofunction.h"
#include "my_roscpp_library/my_stereograb.h"

using namespace cv;
using namespace std;

IplImage *frame1;    
IplImage *frame2;

Mat imgl(320,240,CV_8UC1);
Mat imgr(320,240,CV_8UC1);

cv::Mat img2;
IplImage imgTmp = img2;
IplImage *input = cvCloneImage(&imgTmp);
IplImage tes_l, tes_r;
Mat showL(320,240,CV_8UC1);
Mat showR(320,240,CV_8UC1);

void r_imageCallback(const sensor_msgs::ImageConstPtr& msg){
    try {
        //cvShowImage("viewr", cv_bridge::toCvShare(msg, "mono8")->image);
        cv_bridge::toCvShare(msg, "bgr8")->image.copyTo(imgr);
        //tes_r = imgr;
        // cv_bridge::toCvShare(msg, "mono8")->image.
        //imshow("viewr", imgr);
        //waitKey(30);
    } catch (cv_bridge::Exception& e) {
        ROS_ERROR("Could not conver from '%s' to 'bgr8'.", msg->encoding.c_str());
    }
}

void l_imageCallback(const sensor_msgs::ImageConstPtr& msg){
    try {
        //cvShowImage("viewl", cv_bridge::toCvShare(msg, "mono8")->image);
        cv_bridge::toCvShare(msg, "bgr8")->image.copyTo(imgl);
        tes_l = imgl;
        //imshow("viewl", imgl);
        //waitKey(30);
    } catch (cv_bridge::Exception& e) {
        ROS_ERROR("Could not conver from '%s' to 'bgr8'.", msg->encoding.c_str());
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "stereo_subscriber");
    ros::NodeHandle nh;

    image_transport::ImageTransport it(nh);
    image_transport::Subscriber subr = it.subscribe("camera/right/image_raw", 1, r_imageCallback);
    image_transport::Subscriber subl = it.subscribe("camera/left/image_raw", 1, l_imageCallback);
        
    while(ros::ok()){
        //showL = Mat(&tes_l, true);
        //showR = Mat(&tes_r, true);
        //cout << showL.size().width << showL.size().height << endl;
        //cout << showR.empty() << endl;
        IplImage ipl_img_r = imgr.operator IplImage();
        IplImage ipl_img_l = imgr.operator IplImage();
        cvShowImage("camera right", &ipl_img_r);
        cvShowImage("camera left", &ipl_img_l);
        //imshow("kanan", imgr);
        //imshow("kiri", imgl);
        waitKey(10);
        ros::spinOnce();

        if(waitKey(30) == 27){
            break;
        }
    }
    return 0;
}
