#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include "my_roscpp_library/my_super_roscpp_library.h"
#include <stdio.h>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include "opencv2/ml.hpp"
#include <opencv2/core/types_c.h>

#include <time.h> // to calculate time needed
#include <limits.h> // to get INT_MAX, to protect against overflow

#include <iomanip>
#include <iostream>
#include <stdlib.h>

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "my_roscpp_library/my_stereofunction.h"
#include "my_roscpp_library/my_stereograb.h"
#include <cv_bridge/cv_bridge.h>

#define CALIBRATION 0

using namespace std;
using namespace cv;

StereoGrab* grab= new StereoGrab();
StereoFunction* stereoFunc = new StereoFunction();
// StereoGrab* grab;
// StereoFunction* stereoFunc;

char flag = 0;
static cv::HOGDescriptor hog;

// Kalman-related variables
bool kalmanHasBeenSetup;
KalmanFilter KF;
vector<Point> kalmanv;
int kalmanCounter;
Mat_<float> measurement;
bool threadFinished = false;
int flagtread=0;
char flagTrashIn = 'm';
int flagStep=0;

// >>>> Kalman Filter
int stateSize = 6;
int measSize = 4;
int contrSize = 0;
unsigned int type = CV_32F;
cv::KalmanFilter kf(stateSize, measSize, contrSize, type);

//Mat imgl(320,240,CV_8UC4);
//Mat imgr(320,240,CV_8UC4);

#define FILEPATH "/home/kisron/catkin_workspace/TrainingHOG/"
using namespace gpu;

void playcal(){
	stereoFunc->stereoCalibration(grab);
}

void loadcorrelation(){
		ifstream params;
	params.open("/home/kisron/catkin_workspace/Correlation.txt");
	if(!params){
		cout << "file gak isok!";
		exit(1);
	}else{
		string temp;
		int value;
		while(params>>temp){
		params>>value;
		stereoFunc->stereoDispWindowSize = value;
		params>>temp;
		params>>value;
		stereoFunc->stereoDispTextureThreshold = value;
		params>>temp;
		params>>value;
		stereoFunc->stereoDispUniquenessRatio = value;
		params>>temp;
		params>>value;
		stereoFunc->stereoNumDisparities = value;
		params>>temp;
		params>>value;
		stereoFunc->threshold = value;
		params>>temp;
		params>>value;
		stereoFunc->blobArea = value;
		}
		stereoFunc->stereoPreFilterSize = 63;
		stereoFunc->stereoPreFilterCap = 12;//32;//63; 
		stereoFunc->stereoSavePointCloudValue = 0;

		params.close();
	}

}

void onWindowBarSlide(int pos)
{
	stereoFunc->stereoDispWindowSize = cvGetTrackbarPos("SADSize", "Stereo Controls");
	if(stereoFunc->stereoDispWindowSize < 5)
		{	stereoFunc->stereoDispWindowSize = 5;
			stereoFunc->stereoCorrelation(grab);
		}	
	else if ( stereoFunc->stereoDispWindowSize%2 == 0) 	  
		{
			stereoFunc->stereoDispWindowSize += 1;
			stereoFunc->stereoCorrelation(grab);
		}
	else stereoFunc->stereoCorrelation(grab); 
}

void onTextureBarSlide(int pos)
{
	stereoFunc->stereoDispTextureThreshold = cvGetTrackbarPos("Texture th", "Stereo Controls");
	if(stereoFunc->stereoDispTextureThreshold) 
		stereoFunc->stereoCorrelation(grab);
}

void onUniquenessBarSlide(int pos)
{
	stereoFunc->stereoDispUniquenessRatio = cvGetTrackbarPos("Uniqueness", "Stereo Controls");
	if(stereoFunc->stereoDispUniquenessRatio>=0)
		stereoFunc->stereoCorrelation(grab);
}

void onNumDisparitiesSlide(int pos)
{
	stereoFunc->stereoNumDisparities = cvGetTrackbarPos("Num.Disp", "Stereo Controls");
	while(stereoFunc->stereoNumDisparities%16!=0 || stereoFunc->stereoNumDisparities==0)
		stereoFunc->stereoNumDisparities++;

	stereoFunc->stereoCorrelation(grab);
}

void onPreFilterSizeBarSlide(int pos)
{
	stereoFunc->stereoPreFilterSize = cvGetTrackbarPos("PrFil.Size", "Stereo Controls");
	if(stereoFunc->stereoPreFilterSize>=5)
		if(stereoFunc->stereoPreFilterSize%2!=0)
				stereoFunc->stereoCorrelation(grab);
		else {
				++(stereoFunc->stereoPreFilterSize);
				stereoFunc->stereoCorrelation(grab);}
	else {
				stereoFunc->stereoPreFilterSize = 5;
				stereoFunc->stereoCorrelation(grab);}
		
} 

void onPreFilterCapBarSlide(int pos)
{
	stereoFunc->stereoPreFilterCap = cvGetTrackbarPos("PrFil.Cap", "Stereo Controls");
	if(stereoFunc->stereoPreFilterCap == 0) 
		{	stereoFunc->stereoPreFilterCap = 1;
			stereoFunc->stereoCorrelation(grab);
		}
	else if( stereoFunc->stereoPreFilterCap > 63)		
		{	stereoFunc->stereoPreFilterCap = 63;
			stereoFunc->stereoCorrelation(grab);
		}
	else 	stereoFunc->stereoCorrelation(grab);
}

void stereoCorrelationControl(){
	cvNamedWindow("Stereo Controls",0);
	cvResizeWindow("Stereo Controls", 350,	350);
	cvCreateTrackbar("SADSize", "Stereo Controls", &stereoFunc->stereoDispWindowSize,255, onWindowBarSlide);
	cvCreateTrackbar("Uniqueness", "Stereo Controls", &stereoFunc->stereoDispUniquenessRatio,25, onUniquenessBarSlide);
	cvCreateTrackbar("PrFil.Size", "Stereo Controls", &stereoFunc->stereoPreFilterSize,101, onPreFilterSizeBarSlide);
	cvCreateTrackbar("PrFil.Cap", "Stereo Controls", &stereoFunc->stereoPreFilterCap,63, onPreFilterCapBarSlide);
	cvCreateTrackbar("Num.Disp", "Stereo Controls", &stereoFunc->stereoNumDisparities,640, onNumDisparitiesSlide);
}

void mouseHandler(int event, int x, int y, int flags, void *param){

	switch(event){
	case CV_EVENT_LBUTTONDOWN:
	//l = cvGet2D(stereoFunc->depthM, x, y);
	printf("Distance to this object is: %f cm \n",(float)cvGet2D(stereoFunc->depthM, x, y).val[0]);
	break;
	}
}

void deteksi(){
	Mat img;
	FILE* f = 0;
	char _filename[1024];
	string line;
	//////////////////////////////////////////////////////////////HOG KONFIGURASI//////////////////////////////////////////////////////
	if (flag == 0){
		//Muat parameter fungsi diskriminan terlatih (berbeda dari classifier yang disimpan oleh svm-> save)
		vector<float> detector;

		ifstream fileIn(string(FILEPATH) + "HOG_SVM0.txt", ios::in);
		float val = 0.0f;
		
		while (getline(fileIn, line))
		{
			val = stof(line);
			detector.push_back(val);
			//n++;
		}
		fileIn.close();

		//Pengaturan HOG		
		hog.winSize = Size(64, 64);
		hog.HOGDescriptor::setSVMDetector(detector);

		cv::setIdentity(kf.transitionMatrix);
		
		kf.measurementMatrix = cv::Mat::zeros(measSize, stateSize, type);
		kf.measurementMatrix.at<float>(0) = 1.0f;
		kf.measurementMatrix.at<float>(7) = 1.0f;
		kf.measurementMatrix.at<float>(16) = 1.0f;
		kf.measurementMatrix.at<float>(23) = 1.0f;
		// Measures Noise Covariance Matrix R
		cv::setIdentity(kf.measurementNoiseCov, cv::Scalar(1e-1));
		// <<<< Kalman Filter

		//HANDLE h1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread1, 0, 0, &threadID1);
		//HANDLE h2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread2, 0, 0, &threadID2);

		flag = 1;
		cout << "Deklarasi Sukses" << endl;
	}
	int SADWindowSize = 0;
	StereoSGBM sgbm;
	//int cn = cvarrToMat(img1r).channels();
}	

/*
Mat imgl, imgr;
void r_imageCallback(const sensor_msgs::ImageConstPtr& msg){
    try {
        //cvShowImage("viewr", cv_bridge::toCvShare(msg, "mono8")->image);
        cv_bridge::toCvShare(msg, "mono8")->image.copyTo(imgr); // ditampung nang kene
		//grab->imageR = imgr.operator IplImage();
		//grab->imageRight  = cvCloneImage(&grab->imageR);
    } catch (cv_bridge::Exception& e) {
        ROS_ERROR("Could not conver from '%s' to 'bgr8'.", msg->encoding.c_str());
    }
}

void l_imageCallback(const sensor_msgs::ImageConstPtr& msg){
    try {
        //cvShowImage("viewl", cv_bridge::toCvShare(msg, "mono8")->image);
        cv_bridge::toCvShare(msg, "mono8")->image.copyTo(imgl);
		//grab->imageL = imgl.operator IplImage();
		//grab->imageLeft = cvCloneImage(&grab->imageL);
    } catch (cv_bridge::Exception& e) {
        ROS_ERROR("Could not conver from '%s' to 'bgr8'.", msg->encoding.c_str());
    }
}
*/

void r_imageCallback(const sensor_msgs::ImageConstPtr& msg);
void l_imageCallback(const sensor_msgs::ImageConstPtr& msg);



int main(int argc, char **argv)
{
    ros::init(argc, argv, "target_detection");
    ros::NodeHandle nh;

	// iki fungsi subscriber gambar
    image_transport::ImageTransport it(nh);
    image_transport::Subscriber subr = it.subscribe("camera/right/image_raw", 1, r_imageCallback);
    image_transport::Subscriber subl = it.subscribe("camera/left/image_raw", 1, l_imageCallback);
	
	if(CALIBRATION) playcal();
	loadcorrelation();
	//grab->stereoGrabInitFrames();// diganti
	//grab->stereGrabFrames();
	// cout << grab->imageLeft->width << " imageLeft " << grab->imageLeft->height << endl;
	stereoFunc->stereoInit_coba(grab);
	cout << "next" << endl;
	int count = 0;
	char choice='z';
	int itung=0;

	while(ros::ok()){
		stereoFunc->cobafung(grab);
        ros::spinOnce();
		if(waitKey(30) == 27){ break; }   //27 ASCII Esc
	}
	//Flush and close the video file
	//oVideoWriter.release();
	destroyAllWindows();
	cvDestroyAllWindows(); 
    //cvReleaseImage(&ipl_img_r);
	// grab->stereoGrabStopCam();
	return 0;
}
