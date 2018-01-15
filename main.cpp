/********************************************************
This program is for the assignment in Sensor 2017 at CIT.
Using OpenCV to detect a face and calculate the distance 
of the face from the camera. 

Date  : 2018/01/19
Author: Masashi Kaneko
*********************************************************/

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
 
using namespace std;
using namespace cv;

float real_face_size=0.25;
float initial_face_size=170;
float initial_distance=1;
float f=initial_distance*initial_face_size/real_face_size;

Mat detectFaceInImage(Mat &image,string &cascade_file){
	CascadeClassifier cascade;
	cascade.load(cascade_file);

	vector<Rect> faces;
	cascade.detectMultiScale(image,faces,1.1,3,0,Size(20,20));
	for (int i = 0; i < faces.size(); i++){
		rectangle(image,Point(faces[i].x,faces[i].y),Point(faces[i].x+faces[i].width,faces[i].y+faces[i].height),Scalar(0,200,0),3,CV_AA);
		
		cout<<"face size (pixel) = "<<faces[i].width<<endl;
		
		// calculate the distance
		float real_distance=real_face_size*f/faces[i].width;	
		cout<<"distance (m)      = "<<real_distance<<"\n"<<endl;
	}
	return image;
}
 
int main(){
 
	// Create a VideoCapture object and open the input file
  	// If the input is the web camera, pass 0 instead of the video file name
  	VideoCapture cap("video.mp4"); 
  
 	// Check if camera opened successfully
	if(!cap.isOpened()){
		cout << "Error opening video stream or file" << endl;
    		return -1;
  	}

	// haarcascade classifier
	string filename="haarcascade_frontalface_alt.xml";

  	while(1){
		
		Mat frame;
 
    		// Capture frame-by-frame
    		cap >> frame;
  
    		// If the frame is empty, break immediately
    		if (frame.empty())
      			break;

		// face detection process
		Mat detectFaceImage=detectFaceInImage(frame,filename);
 
    		// Display the resulting frame
    		imshow("Display",detectFaceImage);
 
    		// Press ESC on keyboard to exit
    		char c=(char)waitKey(25);
    		if(c==27)
      			break;
		// Press s to take an image
    		else if(c==115){
      			imwrite("img.png",frame);
    		}	
  	}	
  
  	// When everything done, release the video capture object
  	cap.release();
 
  	// Closes all the frames
  	destroyAllWindows();
     
  	return 0;
}
