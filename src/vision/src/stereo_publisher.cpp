#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "my_roscpp_library/my_stereofunction.h"
#include "my_roscpp_library/my_stereograb.h"

using namespace cv;
using namespace std;

char fpsr_string[10];
char fpsl_string[10];

StereoGrab* grab= new StereoGrab();
StereoFunction* stereoFunc = new StereoFunction();

int main(int argc, char **argv){
    ros::init(argc, argv, "img_stream_publisher");
    ros::NodeHandle nh;   

    grab->stereoGrabInitFrames();
	grab->stereGrabFrames();
	stereoFunc->stereoInit(grab); 

    //CvSize imageSize = { 0, 0 };

	IplImage *frame1 = grab->imageLeft;
	IplImage *frame2 = grab->imageRight;
	IplImage *immg1, *immg2;

	immg1 = cvCreateImage(cvSize(320, 240), IPL_DEPTH_8U, 1);
	immg2 = cvCreateImage(cvSize(320, 240), IPL_DEPTH_8U, 1);

	grab->stereGrabFrames();
	//frame1 = grab->imageLeft;
	//frame2 = grab->imageRight;

	cvCvtColor(grab->imageLeft, immg1, CV_RGB2GRAY);
	cvCvtColor(grab->imageRight, immg2, CV_RGB2GRAY);
			
	//if(cvWaitKey(15)==27) break;

    image_transport::ImageTransport it(nh);
    image_transport::Publisher pubr = it.advertise("camera/right/image_raw",1);
    image_transport::Publisher publ = it.advertise("camera/left/image_raw",1);

    sensor_msgs::ImagePtr msgr;// = cv_bridge::CvImage(std_msgs::Header(),"bgr8", framer).toImageMsg();
    sensor_msgs::ImagePtr msgl;// = cv_bridge::CvImage(std_msgs::Header(),"bgr8", framel).toImageMsg();
    
    ros::Rate loop_rate(10);

    while (ros::ok()) {
        grab->stereGrabFrames();
        unsigned int n;
        msgr = cv_bridge::CvImage(std_msgs::Header(),"bgr8", immg1).toImageMsg();
        msgl = cv_bridge::CvImage(std_msgs::Header(),"bgr8", immg2).toImageMsg();

        pubr.publish(msgr);
        publ.publish(msgl);

        ros::spinOnce();
        loop_rate.sleep();

        cvShowImage("camera left", immg1);
		cvShowImage("camera right", immg2);
        
        //ros::spinOnce();
        n++;
        cout<< "macet" << n << endl;
        cvReleaseImage(&immg1);
        cvReleaseImage(&immg2);
        if(waitKey(30) == 27){
            break;
        }
    }
    destroyAllWindows();
    grab->stereoGrabStopCam();
    return 0;
}


