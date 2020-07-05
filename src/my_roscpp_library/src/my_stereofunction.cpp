#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/contrib/contrib.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/types_c.h> //cxtypes.h
#include <stdio.h>
#include <iomanip>
#include "math.h" 
#include <iostream>
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/ml.hpp"

#include <my_roscpp_library/my_stereofunction.h>
#include <my_roscpp_library/my_stereograb.h>
#include <my_roscpp_library/my_hog.h>
#include <my_roscpp_library/my_glcm.h>


// #if defined(_MSC_VER)
// #include <tchar.h>
// #include <strsafe.h>
// #include <windows.h>
// #pragma comment(lib, "Ws2_32.lib")
// #elif defined(__GNUC__) || defined(__GNUG__)
// #include <dirent.h>
// #endif

string window_name = "Deteksi Manusia";
//VideoCapture cap(0);

#define DEPTHSETCOLOUR_PATH "./savedepth/colour/"
#define DEPTHSETRGB_PATH "./savedepth/rgb/"
#define DEPTHSET_PATH "./savedepth/biasa/"
#define HARDEXAMPLE_PATH "./savedepth/hardexample/"
#define FILEPATH "/home/kisron/catkin_workspace/TrainingHOG/"

#define CETAK 1
#define SAVEDATADEPT 0
#define SAVEHARDEXAMPLE 0

std::string cascadeName = "/home/kisron/catkin_workspace/bismillah20.xml";
cv::CascadeClassifier cascade;
int scale = 1;
int i;
float meas_dist = 0.0;

#define CETAK 1

int fileNO = 0;
IplImage *r_detect, *g_detect, *b_detect, *r_detect_r, *g_detect_r, *b_detect_r ;
int threshold, blobArea;
CvFont font;
int col = 0;
int column[320];
cv::Point p_center;

using namespace std;
using namespace cv;

/// Global variables
int threshold_value = 30;
int threshold_type = 0;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;

Mat src, src_gray, dst;
string window_name2 = "Threshold Demo";
string trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
string trackbar_value = "Value";

/// Function headers
void Threshold_Demo(int, void*);

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
char flag = 0;
static cv::HOGDescriptor hog;

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

bool kalmanIsSetup()
{
	return kalmanHasBeenSetup;
}
void setupKalman(float x_coord, float y_coord, float x_size, float y_size);
void setupKalman(float x_coord, float y_coord, float x_size, float y_size)
{
	printf("Setup Kalman filter");

	KF.init(4, 2, 0);
	KF.transitionMatrix = *(Mat_<float>(4, 4) << 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1);
	measurement.create(2, 1);
	KF.init(8, 4, 0);
	KF.transitionMatrix = *(Mat_<float>(8, 8) << 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1);
	measurement.create(4, 1);
	measurement.setTo(Scalar(0));

	KF.statePre.at<float>(0) = x_coord;
	KF.statePre.at<float>(1) = y_coord;
	KF.statePre.at<float>(2) = 0;
	KF.statePre.at<float>(3) = 0;
	KF.statePre.at<float>(2) = x_size;
	KF.statePre.at<float>(3) = y_size;
	setIdentity(KF.measurementMatrix);
	setIdentity(KF.processNoiseCov, Scalar::all(1e-2)); // Bigger number => faster update
	setIdentity(KF.processNoiseCov, Scalar::all(1e-1)); // Bigger number => faster update
	setIdentity(KF.measurementNoiseCov, Scalar::all(10));
	setIdentity(KF.errorCovPost, Scalar::all(.1));

	kalmanv.clear();
	kalmanCounter = 0;
	kalmanHasBeenSetup = true;

}

void StereoFunction::stereoInit(StereoGrab* grabb)
{
	cvInitFont(&font, CV_FONT_HERSHEY_PLAIN, 1, 1, 0, 1.4f, CV_AA);
	
	_M1 = (CvMat *)cvLoad("/home/kisron/catkin_workspace/CalibFile_thoriq/M1.yml");
	_M2 = (CvMat *)cvLoad("/home/kisron/catkin_workspace/CalibFile_thoriq/M2.yml");
	_T  = (CvMat *)cvLoad("/home/kisron/catkin_workspace/CalibFile_thoriq/T.yml");
	mx1 = (CvMat *)cvLoad("/home/kisron/catkin_workspace/CalibFile_thoriq/mx1.yml");
	my1 = (CvMat *)cvLoad("/home/kisron/catkin_workspace/CalibFile_thoriq/my1.yml");
	mx2 = (CvMat *)cvLoad("/home/kisron/catkin_workspace/CalibFile_thoriq/mx2.yml");
	my2 = (CvMat *)cvLoad("/home/kisron/catkin_workspace/CalibFile_thoriq/my2.yml");
	//_Q = (CvMat *)cvLoad("CalibFile/Q.yml");
	_CamData = (CvMat *)cvLoad("/home/kisron/catkin_workspace/CalibFile_thoriq/CamData.yml");

	//READ In FOCAL LENGTH, SENSOR ELEMENT SIZE, XFOV, YFOV
	//0: fx(pixel), 1: fy(pixel), 2: B (baseline), 3: f(mm), 4: sensor element size, 5: baseline in mm
		/*reprojectionVars[0] = cvmGet(_M1,0,0);
		reprojectionVars[1] = cvmGet(_M1,0,0);
		reprojectionVars[2] = (-1)*cvmGet(_T,0,0);
		reprojectionVars[3] = cvmGet(_CamData, 0, 0);
		reprojectionVars[4] = cvmGet(_CamData, 0, 1);
		reprojectionVars[5] = cvmGet(_CamData, 0, 2);*/


		//Loading images
		img1 = cvCreateImage(cvSize(320,240), IPL_DEPTH_8U, 1);		
		img2 = cvCreateImage(cvSize(320,240), IPL_DEPTH_8U, 1);
		imageSize = cvSize(img1 -> width,img1 ->height);
		
		img1r = cvCreateMat( imageSize.height,imageSize.width, CV_8U );		//rectified left image
		img2r = cvCreateMat( imageSize.height,imageSize.width, CV_8U );		//rectified right image
		disp  = cvCreateMat( imageSize.height,imageSize.width, CV_16S );	//disparity map
		vdisp = cvCreateMat( imageSize.height,imageSize.width, CV_8U );
		depthM = cvCreateMat(imageSize.height, imageSize.width, CV_32F);
				
		
		thres_img = cvCreateImage( imageSize, img1->depth, 1);
		blobs_img = cvCreateImage( imageSize, img1->depth, 3);
		
		img_detect = cvCreateImage(imageSize, IPL_DEPTH_8U, 3);
		r_detect = cvCreateImage(imageSize,8,1);//subpixel
		r_detect_r = cvCreateImage(imageSize,8,1);
		g_detect = cvCreateImage(imageSize,8,1);//subpixel
		g_detect_r = cvCreateImage(imageSize,8,1);
		b_detect = cvCreateImage(imageSize,8,1);//subpixel
		b_detect_r = cvCreateImage(imageSize,8,1);
		
		pair = cvCreateMat( imageSize.height, imageSize.width*2,CV_8UC3 ); 
}

void StereoFunction::stereoCalibration(StereoGrab* grabb){

	int  nx=11, ny=7, frame = 0, n_boards =30, N;
	int count1 = 0,count2 = 0, result1=0, result2=0;	
    int  successes1 = 0,successes2 = 0;
   	const int maxScale = 1;
	const float squareSize = 2.0f;		//Set this to your actual square size
	CvSize imageSize = {0,0};
	CvSize board_sz = cvSize( nx,ny );

	int i, j, n = nx*ny, N1 = 0, N2 = 0;
	
    vector<CvPoint2D32f> points[2];
	vector<int> npoints;
	vector<CvPoint3D32f> objectPoints;
	vector<CvPoint2D32f> temp1(n); 
	vector<CvPoint2D32f> temp2(n);
    
    double M1[3][3], M2[3][3], D1[5], D2[5];
    double R[3][3], T[3], E[3][3], F[3][3];
	double Q[4][4];
	CvMat _Qcalib  = cvMat(4, 4, CV_64F, Q);
    CvMat _M1calib = cvMat(3, 3, CV_64F, M1 );
    CvMat _M2calib = cvMat(3, 3, CV_64F, M2 );
    CvMat _D1 	   = cvMat(1, 5, CV_64F, D1 );
    CvMat _D2      = cvMat(1, 5, CV_64F, D2 );
    CvMat _R       = cvMat(3, 3, CV_64F, R );
    CvMat _Tcalib  = cvMat(3, 1, CV_64F, T );
    CvMat _E       = cvMat(3, 3, CV_64F, E );
    CvMat _F       = cvMat(3, 3, CV_64F, F );
	
	//Start webcam
		printf("\nWebcams are starting ...\n");
		grabb->stereoGrabInitFrames();
		grabb->stereGrabFrames();
		IplImage *frame1 = grabb->imageLeft;
		IplImage* gray_fr1 = cvCreateImage( cvGetSize(frame1), 8, 1 );
		IplImage *frame2 = grabb->imageRight;
		IplImage* gray_fr2 = cvCreateImage( cvGetSize(frame2), 8, 1 );
		imageSize = cvGetSize(frame1);
		
	
		printf("\nWant to capture %d chessboards for calibrate:", n_boards);	
		while((successes1<n_boards)||(successes2<n_boards))						
		{
			//------------- cari & drw chessboard-------------///
			if((frame++ % 20) == 0){
				//---------------- CAM KIRI-------------------------//
				result1 = cvFindChessboardCorners( frame1, board_sz,&temp1[0], &count1,CV_CALIB_CB_ADAPTIVE_THRESH|CV_CALIB_CB_FILTER_QUADS);
				cvCvtColor( frame1, gray_fr1, CV_BGR2GRAY );
				//----------------CAM KANAN--------------------------------------------------------------------------------------------------------
				result2 = cvFindChessboardCorners( frame2, board_sz,&temp2[0], &count2,CV_CALIB_CB_ADAPTIVE_THRESH|CV_CALIB_CB_FILTER_QUADS);
				cvCvtColor( frame2, gray_fr2, CV_BGR2GRAY );

				if(count1==n&&count2==n&&result1&&result2){
					cvFindCornerSubPix( gray_fr1, &temp1[0], count1,cvSize(11, 11), cvSize(-1,-1),cvTermCriteria(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS,30, 0.01) );
					cvDrawChessboardCorners( frame1, board_sz, &temp1[0], count1, result1 );
					cvShowImage( "Scan corners cam KI", frame1 );
					N1 = points[0].size();
					points[0].resize(N1 + n, cvPoint2D32f(0,0));
					copy( temp1.begin(), temp1.end(), points[0].begin() + N1 );
					++successes1;
					
					cvFindCornerSubPix( gray_fr2, &temp2[0], count2,cvSize(11, 11), cvSize(-1,-1),cvTermCriteria(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS,30, 0.01) );
					cvDrawChessboardCorners( frame2, board_sz, &temp2[0], count2, result2 );
					cvShowImage( "Scan corners cam KA", frame2 );
					N2 = points[1].size();
					points[1].resize(N2 + n, cvPoint2D32f(0,0));
					copy( temp2.begin(), temp2.end(), points[1].begin() + N2 );
					++successes2;
					printf("\nNumber Chessboards ditemukan: %d", successes2);
					//cvWaitKey(3000);
					//Sleep(3000);
				}else{
					cvShowImage( "corners camera2", frame2 );	
					cvShowImage( "corners camera1", frame1 );
					
				}
				grabb->stereGrabFrames();
				frame1 = grabb->imageLeft;
				cvShowImage("camera KI", frame1);
				frame2 = grabb->imageRight;
				cvShowImage("camera KA", frame2);
				
			if(cvWaitKey(1)==27) break;
			
			}
		}

		grabb->stereoGrabStopCam();
		cvDestroyWindow("camera KI");
		cvDestroyWindow("camera KA");
		cvDestroyWindow("corners camera1");
		cvDestroyWindow("corners camera2");	
		printf("\nSelesai Capture!");
		
		
		//--------------Compute for calibration-------------------
		N = n_boards*n;
		objectPoints.resize(N);
		for( i = 0; i < ny; i++ )
			for(j = 0; j < nx; j++ )   objectPoints[i*nx + j] = cvPoint3D32f(i*squareSize, j*squareSize, 0);
		for( i = 1; i < n_boards; i++ ) copy( objectPoints.begin(), objectPoints.begin() + n, objectPoints.begin() + i*n );
		npoints.resize(n_boards,n);
		
		CvMat _objectPoints = cvMat(1, N, CV_32FC3, &objectPoints[0] );
		CvMat _imagePoints1 = cvMat(1, N, CV_32FC2, &points[0][0] );
		CvMat _imagePoints2 = cvMat(1, N, CV_32FC2, &points[1][0] );
		CvMat _npoints = cvMat(1, npoints.size(), CV_32S, &npoints[0] );
		cvSetIdentity(&_M1calib);
		cvSetIdentity(&_M2calib);
		cvZero(&_D1);
		cvZero(&_D2);
		
		printf("\nRunning stereo calibration ...");
		fflush(stdout);
		cvStereoCalibrate( &_objectPoints, &_imagePoints1, &_imagePoints2, &_npoints,&_M1calib, &_D1, &_M2calib, &_D2,imageSize, &_R, &_Tcalib, &_E, &_F,
		cvTermCriteria(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS, 100, 1e-5),
        CV_CALIB_FIX_ASPECT_RATIO+CV_CALIB_ZERO_TANGENT_DIST + CV_CALIB_SAME_FOCAL_LENGTH );


		printf("\nDone Calibration");
		//-------------UNDISTORTION------------------------------------------
		cvUndistortPoints( &_imagePoints1, &_imagePoints1,&_M1calib, &_D1, 0, &_M1calib );
		cvUndistortPoints( &_imagePoints2, &_imagePoints2,&_M2calib, &_D2, 0, &_M2calib );
		//COMPUTE AND DISPLAY RECTIFICATION and find disparities
		CvMat* mx1calib = cvCreateMat( imageSize.height,imageSize.width, CV_32F );
        CvMat* my1calib = cvCreateMat( imageSize.height,imageSize.width, CV_32F );
        CvMat* mx2calib = cvCreateMat( imageSize.height,imageSize.width, CV_32F );
        CvMat* my2calib = cvCreateMat( imageSize.height,imageSize.width, CV_32F );

        double R1[3][3], R2[3][3], P1[3][4], P2[3][4];
        CvMat _R1 = cvMat(3, 3, CV_64F, R1);
        CvMat _R2 = cvMat(3, 3, CV_64F, R2);
	
            CvMat _P1 = cvMat(3, 4, CV_64F, P1);
            CvMat _P2 = cvMat(3, 4, CV_64F, P2);
			//compute variables needed for rectification using camera matrices, distortion vectors, rotation matrix, and translation vector
            cvStereoRectify( &_M1calib, &_M2calib, &_D1, &_D2, imageSize,&_R, &_Tcalib,&_R1, &_R2, &_P1, &_P2, &_Qcalib,0/*CV_CALIB_ZERO_DISPARITY*/ );
			//Precompute maps for cvRemap()
            cvInitUndistortRectifyMap(&_M1calib,&_D1,&_R1,&_P1,mx1calib,my1calib);
            cvInitUndistortRectifyMap(&_M2calib,&_D2,&_R2,&_P2,mx2calib,my2calib);
		
			

			printf("\nSaving matries for later use ...\n");
			cvSave("/home/kisron/catkin_workspace/CalibFile_thoriq/M1.yml",&_M1calib);
			cvSave("/home/kisron/catkin_workspace/CalibFile_thoriq/D1.yml",&_D1);
			cvSave("/home/kisron/catkin_workspace/CalibFile_thoriq/R1.yml",&_R1);
			cvSave("/home/kisron/catkin_workspace/CalibFile_thoriq/P1.yml",&_P1);
			cvSave("/home/kisron/catkin_workspace/CalibFile_thoriq/M2.yml",&_M2calib);
			cvSave("/home/kisron/catkin_workspace/CalibFile_thoriq/D2.yml",&_D2);
			cvSave("/home/kisron/catkin_workspace/CalibFile_thoriq/R2.yml",&_R2);
			cvSave("/home/kisron/catkin_workspace/CalibFile_thoriq/P2.yml",&_P2);
			cvSave("/home/kisron/catkin_workspace/CalibFile_thoriq/Q.yml",&_Qcalib);
			cvSave("/home/kisron/catkin_workspace/CalibFile_thoriq/T.yml",&_Tcalib);
			cvSave("/home/kisron/catkin_workspace/CalibFile_thoriq/mx1.yml",mx1calib);
			cvSave("/home/kisron/catkin_workspace/CalibFile_thoriq/my1.yml",my1calib);
			cvSave("/home/kisron/catkin_workspace/CalibFile_thoriq/mx2.yml",mx2calib);
			cvSave("/home/kisron/catkin_workspace/CalibFile_thoriq/my2.yml",my2calib);
}

void meas_distance(vector<float>& distance) {
	distance.push_back(meas_dist);
}


void StereoFunction::stereoCorrelation(StereoGrab* grabb){
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

	cvSplit(grabb->imageLeft,r_detect,g_detect,b_detect, NULL); 
	cvRemap( r_detect, r_detect_r, mx1, my1 ); // Undistort image
	cvRemap( g_detect, g_detect_r, mx1, my1 ); // Undistort image
	cvRemap( b_detect, b_detect_r, mx1, my1 ); // Undistort image
	cvMerge( r_detect_r, g_detect_r, b_detect_r, NULL, img_detect);


	IplImage* eq_gray = cvCreateImage(cvGetSize(img1), 8, 1);

	CvHistogram *hist;
	int hist_size = 256;
	float range[] = { 0, 256 };
	float* ranges[] = { range };

	float max_value = 0.0;
	float w_scale = 0.0;

	/* Convert the image to gray */
	cvCvtColor(grabb->imageLeft, img1, CV_RGB2GRAY);
	cvCvtColor(grabb->imageRight, img2, CV_RGB2GRAY);

	//rectification
	cvRemap( img1, img1r, mx1, my1);
	cvRemap( img2, img2r, mx2, my2);
	sgbm(cvarrToMat(img1r), cvarrToMat(img2r), cvarrToMat(disp));
	cvNormalize( disp, vdisp, 0, 256, CV_MINMAX );

	//view data
	//cvNamedWindow( "Rectified", 1);
	//cvNamedWindow( "Disparity Map",1 );
	//membuat line
	CvMat part;
	cvGetCols( pair, &part, 0, imageSize.width );
	cvCvtColor( img1r, &part, CV_GRAY2BGR );
	cvGetCols( pair, &part, imageSize.width, imageSize.width*2 );
	cvCvtColor( img2r, &part, CV_GRAY2BGR );
	for( int j = 0; j < imageSize.height; j += 16 )
	cvLine( pair, cvPoint(0,j), cvPoint(imageSize.width*2,j),CV_RGB(0,255,0));
	//ending line

	//cvLine(vdisp, cvPoint(0, 120), cvPoint(320,120), CV_RGB(255, 0, 0)); //horizontal
	//cvLine(vdisp, cvPoint(160, 0), cvPoint(160, 240), CV_RGB(255, 0, 0));// vertical

	Mat dst = Mat(vdisp, true);
	//imshow("tes", dst);
	//cvShowImage("Rectified", pair);
	//cvShowImage("Disparity Map", vdisp);
		

	//jarak
	stereoSavePointCloud();
}
void StereoFunction::stereoCorrelation_deteksi(StereoGrab* grabb){
	Mat img;
	FILE* f = 0;
	char _filename[1024];
	//////////////////////////////////////////////////////////////HOG KONFIGURASI//////////////////////////////////////////////////////
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
	////////////////////////////////////////////////////////////// KONFIGURASI ENDD//////////////////////////////////////
	//cout << "NOFLAG" << endl;
	
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

	cvSplit(grabb->imageLeft,r_detect,g_detect,b_detect, NULL); 
	cvRemap( r_detect, r_detect_r, mx1, my1 ); // Undistort image
	cvRemap( g_detect, g_detect_r, mx1, my1 ); // Undistort image
	cvRemap( b_detect, b_detect_r, mx1, my1 ); // Undistort image
	cvMerge( r_detect_r, g_detect_r, b_detect_r, NULL, img_detect);


	IplImage* eq_gray = cvCreateImage(cvGetSize(img1), 8, 1);

	CvHistogram *hist;
	int hist_size = 256;
	float range[] = { 0, 256 };
	float* ranges[] = { range };

	float max_value = 0.0;
	float w_scale = 0.0;

	/* Convert the image to gray */
	cvCvtColor(grabb->imageLeft, img1, CV_RGB2GRAY);
	cvCvtColor(grabb->imageRight, img2, CV_RGB2GRAY);
	//	
	////histogram equalisasi
	//cvEqualizeHist(img1, img1);
	//cvEqualizeHist(img2, img2);

	//cvNormalize(img1,img1,0,150,)
	//rectification
	cvRemap( img1, img1r, mx1, my1);
	cvRemap( img2, img2r, mx2, my2);
	sgbm(cvarrToMat(img1r), cvarrToMat(img2r), cvarrToMat(disp));
	cvNormalize( disp, vdisp, 0, 256, CV_MINMAX );
	
	//double min;
	//double max;
	//cv::minMaxIdx(cvarrToMat(vdisp), &min, &max);
	//cv::Mat adjMap;
	//// expand your range to 0..255. Similar to histEq();
	//cvarrToMat(vdisp).convertTo(adjMap, CV_8UC1, 255 / (max - min), -min);
	//cv::Mat falseColorsMap;
	//applyColorMap(adjMap, falseColorsMap, cv::COLORMAP_BONE);

	//cv::imshow("Out", falseColorsMap);
	if (SAVEDATADEPT){
		if (counter != 3000) {
				//save files at proper locations if user presses 'c'
				stringstream deptcolour, depth;
				deptcolour << "tinggirama150v1" << setw(2) << setfill('0') << counter << ".png";
				imwrite(DEPTHSET_PATH + deptcolour.str(), cvarrToMat(vdisp));
				
				depth << "tinggirama150v1" << setw(2) << setfill('0') << counter << ".jpg";
				imwrite(DEPTHSETRGB_PATH + depth.str(), cvarrToMat(grabb->imageLeft));
				
				cout << "Saved set " << counter << endl;
				counter++;
		}
	}

	//view data
	//cvNamedWindow( "Rectified", 1);
	//cvNamedWindow( "Disparity Map",1 );
	//membuat line
	CvMat part;
	cvGetCols( pair, &part, 0, imageSize.width );
	cvCvtColor( img1r, &part, CV_GRAY2BGR );
	cvGetCols( pair, &part, imageSize.width, imageSize.width*2 );
	cvCvtColor( img2r, &part, CV_GRAY2BGR );
	for( int j = 0; j < imageSize.height; j += 16 )
	cvLine( pair, cvPoint(0,j), cvPoint(imageSize.width*2,j),CV_RGB(0,255,0));
	//ending line

	//cvLine(vdisp, cvPoint(0, 120), cvPoint(320,120), CV_RGB(255, 0, 0)); //horizontal
	//cvLine(vdisp, cvPoint(160, 0), cvPoint(160, 240), CV_RGB(255, 0, 0));// vertical

	//---------------------------------------------------DETEKSI----------------------------------------------------//
		double precTick = ticks;
		ticks = (double)cv::getTickCount();
		double dT = (ticks - precTick) / cv::getTickFrequency(); //seconds


		Mat deteksi(vdisp);
		double t = (double)getTickCount();
		//konfigurasi matriks  
		std::vector<cv::Rect> found, found_1, found_filtered;
		//Deteksi multi-skala gambar  
		hog.detectMultiScale(deteksi, found, 0, cv::Size(8, 8), cv::Size(16, 16), 1.2, 2);
		
		//jika deteksi manusia mengeluarkan suara
		if (flagtread == 1 && flagStep==0){
			//aksi thread
		}
		else if (flagTrashIn == 'i'){
			//cout << "terima kasih telah membuang sampah" << endl;
			flagStep = 2;
		}
		else if (flagTrashIn == 'o'){
			//cout << "terima kasih telah membuang sampah" << endl;
			//HANDLE h2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread2, 0, 0, &threadID2);
			flagStep = 0;
		}flagTrashIn = char(waitKey(1));

		if (finded){
			// >>>> Matrix A
			kf.transitionMatrix.at<float>(2) = dT;
			kf.transitionMatrix.at<float>(9) = dT;
			// <<<< Matrix A

			//cout << "dT:" << endl << dT << endl;

			state = kf.predict();
			//cout << "State post:" << endl << state << endl;

			cv::Rect predRect;
			predRect.width = state.at<float>(4);
			predRect.height = state.at<float>(5);
			predRect.x = state.at<float>(0) - predRect.width / 2;
			predRect.y = state.at<float>(1) - predRect.height / 2;

			cv::Point center;
			center.x = state.at<float>(0);
			center.y = state.at<float>(1);

			if (SAVEDATADEPT == 0){
			cv::rectangle(deteksi, predRect, cv::Scalar(255, 0, 0), 3);
			//threadFinished = true;
			//cout << "flag__" << flagtread << endl;
			flagtread++;
			if (flagtread > 50)flagtread = 0; //suara loop jika ketemu terus

			}
		}

		for (int i = 0; i<found.size(); i++)
		{
			if (found[i].x > 0 && found[i].y > 0 && (found[i].x + found[i].width)< deteksi.cols
				&& (found[i].y + found[i].height)< deteksi.rows)
				found_1.push_back(found[i]);
		}

		// Cari semua rectangular non-nested r dan letakkan di found_filtered, jika tersarang
		// Ambil persegi panjang luar terbesar ke found_filtered   
		for (int i = 0; i < found_1.size(); i++)
		{
			cv::Rect r = found_1[i];
			int j = 0;
			for (; j < found_1.size(); j++)
			if (j != i && (r & found_1[j]) == found_1[j])
				break;
			if (j == found_1.size())
				found_filtered.push_back(r);
		}

		//Gambar kotak persegi panjang, karena kotak yang dideteksi oleh hog sedikit lebih besar dari kotak target sebenarnya, jadi beberapa penyesuaian harus dilakukan di sini, yang dapat disesuaikan sesuai dengan situasi aktual.    
		for (int i = 0; i<found_filtered.size(); i++)
		{
			cv::Rect r = found_filtered[i];
			//Setelah persegi panjang deteksi dikurangi, itu ditarik dan disesuaikan sesuai dengan situasi aktual  
			r.x += cvRound(r.width*0.1);
			r.width = cvRound(r.width*0.8);
			r.y += cvRound(r.height*0.1);
			r.height = cvRound(r.height*0.8);
		}

		for (int i = 0; i<found_filtered.size(); i++)
		{
			cv::Rect r = found_filtered[i];
			cv::rectangle(deteksi, r.tl(), r.br(), cv::Scalar(0, 255, 255), 2);

			//Simpan persegi panjang sebagai gambar Hard Example  
			if (HARDEXAMPLE_PATH){
				Mat hardExampleImg = deteksi(r);//Intercept gambar ukuran persegi panjang dari aslinya
				resize(hardExampleImg, hardExampleImg, Size(64, 64));//Buat skala gambar yang dipotong menjadi ukuran 64 * 64
				stringstream hardexample;
				hardexample << "hardexample" << setw(2) << setfill('0') << hardExampleCount << ".jpg";
				imwrite(HARDEXAMPLE_PATH + hardexample.str(), hardExampleImg);
				//cout << "Saved set " << hardExampleImg << endl;
				hardExampleCount++;
			}
		}
		//cout << "f_size: " << found_filtered.size();
		// >>>>> Kalman Update
		if (found_filtered.size() == 0)
		{
			notFoundCount++;
			cout << "notFoundCount:" << notFoundCount << endl;
		
			if (notFoundCount >= 25)
			{
				flagtread = 0;
				finded = false;
			}
			/*else
			kf.statePost = state;*/
		}
		else
		{
			notFoundCount = 0;
			meas.at<float>(0) = found_filtered[0].x + found_filtered[0].width / 2;
			meas.at<float>(1) = found_filtered[0].y + found_filtered[0].height / 2;
			meas.at<float>(2) = (float)found_filtered[0].width;
			meas.at<float>(3) = (float)found_filtered[0].height;

			if (!finded) // First detection!
			{
				// >>>> Initialization
				kf.errorCovPre.at<float>(0) = 1; // px
				kf.errorCovPre.at<float>(7) = 1; // px
				kf.errorCovPre.at<float>(14) = 1;
				kf.errorCovPre.at<float>(21) = 1;
				kf.errorCovPre.at<float>(28) = 1; // px
				kf.errorCovPre.at<float>(35) = 1; // px

				state.at<float>(0) = meas.at<float>(0);
				state.at<float>(1) = meas.at<float>(1);
				state.at<float>(2) = 0;
				state.at<float>(3) = 0;
				state.at<float>(4) = meas.at<float>(2);
				state.at<float>(5) = meas.at<float>(3);
				// <<<< Initialization

				kf.statePost = state;

				finded = true;
			}else
			kf.correct(meas); // Kalman Correction
			//cout << "Measure matrix:" << endl << meas << endl;
		}

		t = (double)getTickCount() - t;
		//printf("detection time = %gms\n", t*1000. / cv::getTickFrequency());
		//--------------------------------------------------- END DETEKSI ----------------------------------------------------//


		//save video
		//oVideoWriter.write(falseColorsMap);

		imshow("deteksi", deteksi);
		//cvShowImage("Rectified", pair);
		//cvShowImage("Disparity Map", vdisp);

		//jarak
		stereoSavePointCloud();
}

void PointCenter(cv::Point center) {
	//cout << "Center: " << center << endl;
	p_center = center;
}

void StereoFunction::stereoSavePointCloud()
{
		//0: fx(pixel), 1: fy(pixel), 2: base line (pixel), 3: f(mm), 4: sensor element size, 5: baseline (mm)
	double	focal = 4.2; //mm reprojectionVars[0]; //4.2126730429010615
	double	baseline = 30;	
	double 	depth = 0;

	double vk[10] = { 2.097815, 3.411168, 4.489978, 5.250000, 5.826590, 6.300000, 6.675497, 7.024390, 7.578947, 7.875000 };
	double jk[10]= {50, 100, 150, 200, 250, 300, 350, 400, 450, 500};
	double j1=0, j2=0;
	double v1=0, v2=0;
	double jarak;
	real_disparity= cvCreateImage( imageSize, IPL_DEPTH_32F, 1 );
	cvConvertScale( disp, real_disparity, 1.0/16, 0 );
	// min 1.27 29 cm
	// max 8.16 400 cm
	depth = (double)((baseline*focal)/((double)(cvGet2D(disp,120,160).val[0]/16)));
	//printf("%f\n",depth);
	

	int ok=0;
	for(int i=0; i<8; i++){
		if(depth>=vk[i] && depth<vk[i+1]){
			v1 = vk[i+1]-vk[i];
			j1 = jk[i+1]-jk[i];

			v2=depth-vk[i];
			j2 = j1*v2/v1;
			j2 = j2 + jk[i];
			ok=1;
			break;
		}
	}
	if(ok==1){
		//printf("%f__jarak: %f\n",depth,j2);
	}

	//if(CETAK ==0){

	//	for (int y = 0; y < vdisp->rows; y++){
	//		for (int x = 0; x < vdisp->cols ; x++){	
	//				printf("%d %d %f %f", y,x,(float)cvmGet(depthM,y,x),(float)cvGet2D(real_disparity,y,x).val[0]);
	//				//fprintf(distanceFile, "%d %d %f %f\n",y,x,(float)cvmGet(depthM,y,x),(float)cvGet2D(real_disparity,y,x).val[0]);
	//			}
	//	}
	////fclose(distanceFile);
	//}
}