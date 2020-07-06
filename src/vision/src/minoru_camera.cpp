/*#include "ros/ros.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "my_roscpp_library/my_stereofunction.h"
#include "my_roscpp_library/my_stereograb.h"

StereoGrab* grab= new StereoGrab();
StereoFunction* stereoFunc = new StereoFunction();

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "minoru_camera");
  ros::NodeHandle n;

  ros::Rate loop_rate(10);

  int count = 0;
  while (ros::ok())
  {
    int count = 0;

	grab->stereoGrabInitFrames();
	grab->stereGrabFrames();
	IplImage *frame1 = grab->imageLeft;
	IplImage *frame2 = grab->imageRight;

	char choice = 'z';
    ros::NodeHandle nh;
    image_transport::ImageTransport it(nh);
    image_transport::Publisher pub = it.advertise("camera/image", 1);

    cv::Mat image = cv::imread(argv[1], cv::IMREAD_COLOR);
    sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame1).toImageMsg();

    ros::Rate loop_rate(5);
	while(nh.ok()){
		grab->stereGrabFrames();
		frame1 = grab->imageLeft;
		cvShowImage("camera left", frame1);
		frame2 = grab->imageRight;
		cvShowImage("camera right", frame2);
        pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
		/*if (choice == 'z') {
			//save files at proper locations if user presses 'c'
			stringstream l_name, r_name;
			l_name << "left" << setw(2) << setfill('0') << count << ".jpg";
			r_name << "right" << setw(2) << setfill('0') << count << ".jpg";
			imwrite(l_name.str(), cvarrToMat(grab->imageLeft));
			//imwrite(r_name.str(), cvarrToMat(grab->imageRight));
			cout << "Saved set " << count << endl;
			count++;
		}

		if(cvWaitKey(30)==27) break;
	}
  }
  return 0;
}

*/

/*#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_publisher");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);
  image_transport::Publisher pub = it.advertise("camera/image", 1);

  cv::Mat image = (cv:VideoCapture(2), cv::IMREAD_COLOR);
  sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();

  ros::Rate loop_rate(5);
  while (nh.ok()) {
    pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
  }
}
*/

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

char fpsr_string[10];
char fpsl_string[10];

int main(int argc, char **argv){
    ros::init(argc, argv, "minoru_camera");
    ros::NodeHandle nh;    

    VideoCapture capr(4);  // kamera kanan
    VideoCapture capl(2);  // kamera kiri

    capr.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
    capr.set(CV_CAP_PROP_FRAME_WIDTH, 320);
    capl.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
    capl.set(CV_CAP_PROP_FRAME_WIDTH, 320);

    if(!capr.isOpened()) {
        cout << "Cannot open the video file. \n";
        return -1;
      }

    if(!capl.isOpened()) {
        cout << "Cannot open the video file. \n";
        return -1;
    }

    Mat framer;
    Mat framel;

    image_transport::ImageTransport it(nh);
    image_transport::Publisher pubr = it.advertise("camera/right/image_raw",1);
    image_transport::Publisher publ = it.advertise("camera/left/image_raw",1);
    //image_transport::Publisher pub = it.advertise("camera/image",1);

    //cv::Mat image = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);

    //cv::waitKey(30);    

    sensor_msgs::ImagePtr msgr;// = cv_bridge::CvImage(std_msgs::Header(),"bgr8", framer).toImageMsg();
    sensor_msgs::ImagePtr msgl;// = cv_bridge::CvImage(std_msgs::Header(),"bgr8", framel).toImageMsg();
    //sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(),"bgr8", image).toImageMsg();
    
    ros::Rate loop_rate(10);

    while (ros::ok()) {
        if (!capr.read(framer)){
              cout<<"\n Cannot read the video file. \n";
              break;
            }
        if (!capl.read(framel)){
              cout<<"\n Cannot read the video file. \n";
              break;
        }

        msgr = cv_bridge::CvImage(std_msgs::Header(),"bgr8", framer).toImageMsg();
        msgl = cv_bridge::CvImage(std_msgs::Header(),"bgr8", framel).toImageMsg();

        pubr.publish(msgr);
        publ.publish(msgl);
        //pub.publish(msg);

        ros::spinOnce();
        loop_rate.sleep();

        imshow("Kamera_Kanan", framer);
        imshow("Kamera_Kiri", framel);

        if(waitKey(30) == 27){
            break;
        }
    }

    if(capr.isOpened())
        capr.release();

    if(capl.isOpened())
        capl.release();
  }




