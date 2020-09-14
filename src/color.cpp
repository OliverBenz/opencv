#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>

using namespace cv;

// Functions
void detectAndDisplay(Mat frame);

int main(int argc, char** argv){
  namedWindow("standard");
  // namedWindow("mask");
  VideoCapture capture;

  capture.open(0);

  if(! capture.isOpened()) return -1;
  else{
    for(;;){
      Mat frame;
      capture >> frame;
      if(frame.empty()) break;
      
      detectAndDisplay(frame);

      if(waitKey(10) == 27) break;
    }
  }

  return 0;
}

void detectAndDisplay(Mat frame){
  Mat mask, cover;
  cvtColor(frame, mask, COLOR_BGR2HSV);
  // Yellow
  inRange(mask, Scalar(20, 100, 100), Scalar(30, 255, 255), mask);
  
  findNonZero(mask, cover);
  Rect rect = boundingRect(cover);

  rectangle(frame, rect.tl(), rect.br(), Scalar(255,0,0), 2);
  // cvtColor(frame, mask, COLOR_BGR2HLS);

  imshow("standard", frame);
}