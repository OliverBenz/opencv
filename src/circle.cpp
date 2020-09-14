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
  Mat frame_gray;
  cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
  GaussianBlur(frame_gray, frame_gray, Size(9, 9), 2, 2);
  // medianBlur(frameHLS, frame_gray, 5);

  std::vector<Vec3f> circles;
  HoughCircles(frame_gray, circles, HOUGH_GRADIENT, 1, frame_gray.rows/16, 100, 30, 0, 50);
  for( size_t i = 0; i < circles.size(); i++ ){
      Vec3i c = circles[i];
      Point center = Point(c[0], c[1]);
      // circle center
      circle( frame, center, 1, Scalar(0,100,100), 3, LINE_AA);
      // circle outline
      int radius = c[2];
      circle( frame, center, radius, Scalar(255,0,255), 3, LINE_AA);
  }

  imshow("standard", frame);
  // imshow("mask", mask);
}