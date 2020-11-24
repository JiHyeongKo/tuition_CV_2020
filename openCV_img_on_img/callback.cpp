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
	if (frame.empty()) { cout << "��� ���� �Է� ����\n "; exit(0); }
	imshow("frame", frame);

	input = imread(FileName, IMREAD_COLOR);
	if (input.empty()) { cout << "���� �Է� ����\n "; exit(0); }

	cout << "ȭ�鿡 �� ����Ʈ�� �����ϰ� Excute ��ư�� Ŭ���ϼ���.\n\n";
	setMouseCallback("frame", onMouse, &frame);
}

void callbackVideo(void)
{
	VideoCapture cap(FileName);	// ������ ������ ���
	if (!cap.isOpened())
		cerr << "ERROR! Unable to open video\n";
		
	frame = imread(frameName, IMREAD_COLOR);
	if (frame.empty()) { cout << "��� ���� �Է� ����\n "; exit(0); }
	imshow("frame", frame);

	cap.read(input);	// �����󿡼� �ϳ��� �������� �����Ѵ�. 
	if (input.empty()) { cout << "���� �Է� ����\n "; exit(0); }

	cout << "ȭ�鿡 �� ����Ʈ�� �����ϰ� Excute ��ư�� Ŭ���ϼ���.\n";
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
	if (frame.empty()) { cout << "��� ���� �Է� ����\n "; exit(0); }
	imshow("frame", frame);

	cout << "ȭ�鿡 �� ����Ʈ�� �����ϰ� Excute ��ư�� Ŭ���ϼ���.\n";
	setMouseCallback("frame", onMouse, &frame);

	return;
	
}
