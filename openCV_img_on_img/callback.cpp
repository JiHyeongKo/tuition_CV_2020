#include <opencv2/opencv.hpp>
#include <iostream>
#include "main.h"
using namespace cv;
using namespace std;

Mat input;
Mat frame;

void callbackImg(int id)
{
	if (id == INPUT)
	{
		input = imread(IMG_NAME, IMREAD_COLOR);
		if (input.empty()) { cout << "���� �Է� ����\n "; exit(0); }
		
		frame = imread(FRAME_NAME, IMREAD_COLOR);
		if (frame.empty()) { cout << "���� �Է� ����\n "; exit(0); }
		imshow("frame", frame);

		cout << "ȭ�鿡 �� ����Ʈ�� �����ϰ� Excute ��ư�� Ŭ���ϼ���.\n\n";
		setMouseCallback("frame", onMouse, &frame);
	}
}

void callbackVideo(int id)
{
	if (id == INPUT)
	{
		VideoCapture cap(MP4_NAME);	// ������ ������ ���
		if (!cap.isOpened())
			cerr << "ERROR! Unable to open video\n";
		
		frame = imread(FRAME_NAME, IMREAD_COLOR);
		if (frame.empty()) { cout << "���� �Է� ����\n "; exit(0); }
		imshow("frame", frame);

		cap >> input;	// �����󿡼� �ϳ��� �������� �����Ѵ�. 
		if (input.empty()) { cout << "���� �Է� ����\n "; exit(0); }

		cout << "ȭ�鿡 �� ����Ʈ�� �����ϰ� Excute ��ư�� Ŭ���ϼ���.\n";
		setMouseCallback("frame", onMouse, &frame);
	
		return;
	}
}

void callbackCam(int id)
{
	if (id == INPUT)
	{
		VideoCapture cam;
		cam.open(CAP_NAME);
		if (!cam.isOpened()) {
			cerr << "ERROR! Unable to open camera\n";
			return;
		}
	
		cam.read(input);
		if (input.empty()) {
			cerr << "ERROR! blank frame grabbed\n";
			exit(0);
		}

		frame = imread(FRAME_NAME, IMREAD_COLOR);
		if (frame.empty()) { cout << "���� �Է� ����\n "; exit(0); }
		imshow("frame", frame);

		cout << "ȭ�鿡 �� ����Ʈ�� �����ϰ� Excute ��ư�� Ŭ���ϼ���.\n";
		setMouseCallback("frame", onMouse, &frame);

		return;
	}
}
