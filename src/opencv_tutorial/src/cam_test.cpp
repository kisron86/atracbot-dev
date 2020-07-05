#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// class cam_test(){
// public:
//     cam_test(){
//         VideoCapture cap(0);
//         if(!cap.isOpened()){
//             cout << "cannot connect camera" << endl;
//         }

//         double dwidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
//         double dheight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
//         cout << "Frame size : " << dwidth << " x " << dheight << endl;

//         namedWindows("myVideo", CV_WINDOWS_AUTOSIZE);

//         while(1){
//             Mat frame;
//             bool bsuccess = cap.read(frame);
//             if(!bsuccess){
//                 cout << "cannot read a frame from video stream" << endl;
//                 break;
//             }
//             imshow("myVideo", frame);
//             if(waitKey(30) == 27){
//                 cout << "esc key pressed by user" << endl;
//                 break;
//             }
//         }

//     }
//     ~cam_test(){
//         cvDestroywindows("Camera_Output");
//     }
// };

int main(int argc, char **argv){
    ros::init(argc, argv, "cam_test");
    //cam_test cam_object;
    VideoCapture cap(0);
        if(!cap.isOpened()){
            cout << "cannot connect camera" << endl;
        }

        double dwidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
        double dheight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
        cout << "Frame size : " << dwidth << " x " << dheight << endl;

        namedWindow("myVideo", CV_WINDOW_AUTOSIZE);

        while(1){
            Mat frame;
            bool bsuccess = cap.read(frame);
            if(!bsuccess){
                cout << "cannot read a frame from video stream" << endl;
                break;
            }
            imshow("myVideo", frame);
            if(waitKey(30) == 27){
                cout << "esc key pressed by user" << endl;
                break;
            }
        }

    ROS_INFO("Camera Tested!");
} 