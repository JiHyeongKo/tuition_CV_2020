#include <opencv2/opencv.hpp>
#include <iostream>
#include "main.h"
using namespace cv;
using namespace std;

Mat input;
Mat frame;
extern String FileName;
extern String frameName;

void callbackImg(void)
{
	frame = imread(frameName, IMREAD_COLOR);
	if (frame.empty()) { cout << "배경 영상 입력 오류\n "; exit(0); }
	imshow("frame", frame);

	input = imread(FileName, IMREAD_COLOR);
	if (input.empty()) { cout << "영상 입력 오류\n "; exit(0); }

	cout << "화면에 네 포인트를 선택하고 Excute 버튼을 클릭하세요.\n\n";
	setMouseCallback("frame", onMouse, &frame);
}

void callbackVideo(void)
{
	VideoCapture cap(FileName);	// 동영상 파일인 경우
	if (!cap.isOpened())
		cerr << "ERROR! Unable to open video\n";
		
	frame = imread(frameName, IMREAD_COLOR);
	if (frame.empty()) { cout << "배경 영상 입력 오류\n "; exit(0); }
	imshow("frame", frame);

	cap.read(input);	// 동영상에서 하나의 프레임을 추출한다. 
	if (input.empty()) { cout << "영상 입력 오류\n "; exit(0); }

	cout << "화면에 네 포인트를 선택하고 Excute 버튼을 클릭하세요.\n";
	setMouseCallback("frame", onMouse, &frame);
	
	return;
}

void callbackCam(void)
{
	VideoCapture cam;
	cam.open(CAM_NAME);
	if (!cam.isOpened()) {
		cerr << "ERROR! Unable to open camera\n";
		return;
	}
	
	cam.read(input);
	if (input.empty()) {
		cerr << "ERROR! blank frame grabbed\n";
		exit(0);
	}

	frame = imread(frameName, IMREAD_COLOR);
	if (frame.empty()) { cout << "배경 영상 입력 오류\n "; exit(0); }
	imshow("frame", frame);

	cout << "화면에 네 포인트를 선택하고 Excute 버튼을 클릭하세요.\n";
	setMouseCallback("frame", onMouse, &frame);

	return;
	
}
