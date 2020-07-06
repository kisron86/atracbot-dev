#include <ros/ros.h>
#include "my_roscpp_library/my_super_roscpp_library.h"

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include "opencv2/ml.hpp"

#include <time.h> 
#include <limits.h> 

#include <iomanip>
#include <iostream>
#include <stdlib.h>

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdio.h>
#include <ctype.h>

#include <math.h>
#include <string.h>
#include <fstream>
#include <sstream>

#include "my_roscpp_library/my_stereofunction.h"
#include "my_roscpp_library/my_stereograb.h"
#include <cv_bridge/cv_bridge.h>

#define CALIBRATION 0

using namespace std;
using namespace cv;

StereoGrab* grab= new StereoGrab();
StereoFunction* stereoFunc = new StereoFunction();

char flag = 0;
static cv::HOGDescriptor hog;

Mat img;
FILE* f = 0;
char _filename[1024];


int stereoPreFilterSize,
    stereoPreFilterCap,
    stereoDispWindowSize,
    stereoNumDisparities,
    stereoDispTextureThreshold,
    stereoDispUniquenessRatio,
    stereoSavePointCloudValue,
    stereoSaveOriginal;

IplImage *r_detect, *g_detect, *b_detect, *r_detect_r, *g_detect_r, *b_detect_r;
struct StereoFunction{
  CvMat* _M1;
  CvMat* _M2;
  CvMat* _T;
  CvMat* mx1;
  CvMat* mx2;
  CvMat* my1;
  CvMat* my2;
  CvMat* _Q;			//reprojection matrix
  CvMat* _CamData;

  CvSize imageSize;
  IplImage *img1,
       *img2,
       *img_detect,
       *thres_img,
       *blobs_img,
       *real_disparity;
  CvMat	 *cvma,
       *img1r,
       *img2r,
       *disp,
       *vdisp,
       *pair,
       *depthM;
};
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

#define FILEPATH "/home/kisron/catkin_workspace/TrainingHOG/"
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


int counter = 0;
char choice = 'd';

Size frame_size(320, 240);
int frames_per_second = 10;

//Create and initialize the VideoWriter object 
//VideoWriter oVideoWriter("MyVideo.avi", CV_FOURCC('M', 'J', 'P', 'G'), frames_per_second, frame_size, true);
//char flag = 0;
//static cv::HOGDescriptor hog;

// >>>> Kalman Filter
int stateSize = 6;
int measSize = 4;
int contrSize = 0;
unsigned int type = CV_32F;
cv::KalmanFilter kf(stateSize, measSize, contrSize, type);

cv::Mat state(stateSize, 1, type);  // [x,y,v_x,v_y,w,h]
cv::Mat meas(measSize, 1, type);    // [z_x,z_y,z_w,z_h]

double ticks = 0;
bool finded = false;

int notFoundCount = 0;
int hardExampleCount = 0; //hard example
CvMat *img1r;

Mat imgl(320,240,CV_8UC4);
Mat imgr(320,240,CV_8UC4);

int main(int argc, char **argv)
{
    ros::init(argc, argv, "deteksi_target");
    ros::NodeHandle nh;

	loadcorrelation();
	grab->stereoGrabInitFrames();
	grab->stereGrabFrames();
	
	
	while(ros::ok()){
        stereoFunc->stereoInit(grab);
		//stereoFunc->stereoCorrelation_deteksi(grab);
        if (flag == 0){
		//Muat parameter fungsi diskriminan terlatih (berbeda dari classifier yang disimpan oleh svm-> save)
		
		ifstream fileIn(string(FILEPATH) + "HOG_SVM0.txt", ios::in);
		vector<double> detector;
		cout << "file ok" << endl;
		double val;
		while (!fileIn.eof())
		{
			fileIn >> val;
			detector.push_back(val);
		}
		fileIn.close();

		//Pengaturan HOG		
		hog.winSize = Size(64, 64);
		cout << "Deklarasi Mulai" << endl; //error disini, boleh saya lihat program ketika di run ?
		cout << hog.winSize << endl;
		
		hog.setSVMDetector(detector);// Gunakan penggolong train sendiri
		cout << "Deklarasi Lewat" << endl;
		
		//cv::Mat procNoise(stateSize, 1, type)
		// [E_x,E_y,E_v_x,E_v_y,E_w,E_h]

		// Transition State Matrix A
		// Note: set dT at each processing step!
		// [ 1 0 dT 0  0 0 ]
		// [ 0 1 0  dT 0 0 ]
		// [ 0 0 1  0  0 0 ]
		// [ 0 0 0  1  0 0 ]
		// [ 0 0 0  0  1 0 ]
		// [ 0 0 0  0  0 1 ]
		cv::setIdentity(kf.transitionMatrix);

		// Measure Matrix H
		// [ 1 0 0 0 0 0 ]
		// [ 0 1 0 0 0 0 ]
		// [ 0 0 0 0 1 0 ]
		// [ 0 0 0 0 0 1 ]
		kf.measurementMatrix = cv::Mat::zeros(measSize, stateSize, type);
		kf.measurementMatrix.at<float>(0) = 1.0f;
		kf.measurementMatrix.at<float>(7) = 1.0f;
		kf.measurementMatrix.at<float>(16) = 1.0f;
		kf.measurementMatrix.at<float>(23) = 1.0f;

		// Process Noise Covariance Matrix Q
		// [ Ex   0   0     0     0    0  ]
		// [ 0    Ey  0     0     0    0  ]
		// [ 0    0   Ev_x  0     0    0  ]
		// [ 0    0   0     Ev_y  0    0  ]
		// [ 0    0   0     0     Ew   0  ]
		// [ 0    0   0     0     0    Eh ]
		//cv::setIdentity(kf.processNoiseCov, cv::Scalar(1e-2));
		kf.processNoiseCov.at<float>(0) = 1e-2;
		kf.processNoiseCov.at<float>(7) = 1e-2;
		kf.processNoiseCov.at<float>(14) = 5.0f;
		kf.processNoiseCov.at<float>(21) = 5.0f;
		kf.processNoiseCov.at<float>(28) = 1e-2;
		kf.processNoiseCov.at<float>(35) = 1e-2;

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
	int cn = cvarrToMat(img1r).channels();

    sgbm.preFilterCap = stereoPreFilterCap;//63; //stereoPreFilterSize;
	sgbm.SADWindowSize = stereoDispWindowSize;//3; //stereoDispWindowSize;
	sgbm.P1 = 8*cn*sgbm.SADWindowSize*sgbm.SADWindowSize;
	sgbm.P2 = 32*cn*sgbm.SADWindowSize*sgbm.SADWindowSize;
	sgbm.minDisparity =10;// -39; //0
	sgbm.numberOfDisparities =  stereoNumDisparities; //144;
	sgbm.uniquenessRatio =  stereoDispUniquenessRatio; //10;
	sgbm.speckleWindowSize = 200; //200
	sgbm.speckleRange = 32;		//32
	sgbm.disp12MaxDiff = 1;		//2

    cvSplit(imgl,r_detect,g_detect,b_detect, NULL); 
	cvRemap( r_detect, r_detect_r, mx1, my1 ); // Undistort image
	cvRemap( g_detect, g_detect_r, mx1, my1 ); // Undistort image
	cvRemap( b_detect, b_detect_r, mx1, my1 ); // Undistort image
	cvMerge( r_detect_r, g_detect_r, b_detect_r, NULL, img_detect);

		grab->stereGrabFrames();
		if(waitKey(30) == 27){
            break;
        }
	}
	destroyAllWindows();
	grab->stereoGrabStopCam();
	return 0;
}
