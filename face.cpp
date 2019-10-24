#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>

using namespace cv;

// Global variables
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;

// Functions
void detectAndDisplay(Mat frame);

int main(int argc, char** argv){
  VideoCapture capture;

  // Load Cascades
  if(!face_cascade.load("./data/haarcascade_frontalface_alt.xml")){
    std::cout << "Failed Faces";
    return -1;
  }
  if(!eyes_cascade.load("./data/haarcascade_eye_tree_eyeglasses.xml")){
    std::cout << "Failed Eyes";
    return -1;
  }

  capture.open(0);

  if(! capture.isOpened()) return -1;
  else{
    for(;;){
      Mat frame;
      capture >> frame;
      if(frame.empty()) break;

      // Rect rect = Rect(50,50,100,100);
      // rectangle(frame, rect, Scalar(255,0,0),1,8,0);

      // blur(frame, frame, Size(8, 8), Point(-1, -1));
      // imshow("Test", frame);
      detectAndDisplay(frame);

      if(waitKey(10) == 27) break;
    }
  }

  return 0;
}

void detectAndDisplay(Mat frame){
  Mat frame_gray;
  cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
  equalizeHist(frame_gray, frame_gray);

  std::vector<Rect> faces;
  face_cascade.detectMultiScale(frame_gray, faces);
  // std::cout << faces[0] << std::endl;

  for(size_t i = 0; i < faces.size(); i++){
    Point face_center(faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2);
    ellipse(frame, face_center, Size(faces[i].width/2, faces[i].height/2), 0, 0, 360, Scalar(255, 0, 255), 2);

    // Face Region of Interest -> Just the face part of the image
    Mat faceRoI = frame_gray(faces[i]);

    std::vector<Rect> eyes;
    eyes_cascade.detectMultiScale(faceRoI, eyes);

    for(size_t j = 0; j < eyes.size(); j++){
      Point eye_center(faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2);
      ellipse(frame, eye_center, Size(eyes[j].width/2, eyes[j].height/2), 0, 0, 360, Scalar(255, 0, 255), 2);
      // int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
      // circle(frame, eye_center, radius, Scalar( 255, 0, 0 ), 4 );      
    }
  }
  imshow("Face Detection", frame);
}