#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>

using namespace cv;

// Global variables
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;

int main(int argc, char** argv){
  VideoCapture capture;

  // if(!face_cascade.load("haarcascade_frontalface_alt.xml")) { std::cout << "Failed"; return -1; }
  // if(!eyes_cascade.load("haarcascade_eye_tree_eyeglasses.xml")) { std::cout << "Failed"; return -1; }

  capture.open(0);

  if(! capture.isOpened()) return -1;
  else{
    for(;;){
      Mat frame;
      capture >> frame;
      if(frame.empty()) break;

      Rect rect = Rect(50,50,100,100);
      rectangle(frame, rect, Scalar(255,0,0),1,8,0);

      // blur(frame, frame, Size(8, 8), Point(-1, -1));
      imshow("Test", frame);

      if(waitKey(10) == 27) break;
    }
  }

  return 0;
}