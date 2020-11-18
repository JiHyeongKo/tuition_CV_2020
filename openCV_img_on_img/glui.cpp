#pragma warning(disable: 4996)
#include <opencv2/opencv.hpp>
#include <iostream>
#include <GL/glui.h>
#include <GL/glut.h>
#include "OpenFileDialog.h"
#include "SaveFileDialog.h"
#include "main.h"

using namespace cv;
using namespace std;

int main_window;
extern Mat input;
extern Mat frame;
extern int i;
extern int* x_buffer;
extern int* y_buffer;
String FileName;
GLUI_RadioGroup* inputGroup;
GLUI_RadioGroup* frameGroup;
void warp(Mat* src, Mat* dst);

const std::string TCHARToString(const TCHAR* ptsz)
{
	int len = wcslen((wchar_t*)ptsz);

	char* psz = new char[2 * len + 1];

	wcstombs(psz, (wchar_t*)ptsz, 2 * len + 1);
	std::string s = psz;

	delete[] psz;

	return s;
}

void control_rb(int control)
{
	if (control == INPUT)
	{
		if (inputGroup->get_int_val() != 2)	// 캠이 아닐 때
		{
			OpenFileDialog* openFileDialog = new OpenFileDialog();
			if (openFileDialog->ShowDialog())
				FileName = TCHARToString(openFileDialog->FileName);
		}
		initialize();	// 잘 못 눌렀을시..

		switch (inputGroup->get_int_val())
		{
		case 0: callbackImg(); break;
		case 1: callbackVideo(); break;
		case 2: callbackCam(); break;
		}
	}
}
void control_bt(int control)
{
	switch (control)
	{

	case QUIT: exit(0);	break;

	case EXECUTE:
	{
		if (i != 4)
		{
			printf("출력 포인트를 지정하세요.\n\n");
			break;
		}

		else if (i == 4)
		{
			switch (inputGroup->get_int_val())
			{
			case 0:
				printf("종료를 원하시면 QUIT을 클릭하세요.\n");
				printf("다른 Input을 사용하고 싶으시면 다른 라디오 버튼을 클릭 후 시도하세요.\n\n");
				input = imread(FileName, IMREAD_COLOR);
				//imshow("input", input);
				warp(&input, &frame);
				imshow("frame", frame);

				initialize();
				break;

			case 1:
			{
				printf("종료를 원하시면 아무 키보드 자판이나 누르고 QUIT을 클릭하세요.\n");
				printf("다른 Input을 사용하고 싶으시면 아무 키보드 자판이나 누르고 다른 라디오 버튼을 클릭 후 시도하세요.\n\n");
				VideoCapture cap(FileName);

				while (1)
				{
					frame = imread(FRAME_NAME, IMREAD_COLOR);
					cap >> input;	// 동영상에서 하나의 프레임을 추출한다. 

					//imshow("input", input);
					warp(&input, &frame);
					imshow("frame", frame);

					if (waitKey(30) > 0)
					{
						initialize();
						break;
					}
				}
				break;
			}

			case 2: 
			{
				printf("종료를 원하시면 아무 키보드 자판이나 누르고 QUIT을 클릭하세요.\n");
				printf("다른 Input을 사용하고 싶으시면 아무 키보드 자판이나 누르고 다른 라디오 버튼을 클릭 후 시도하세요.\n\n");
				VideoCapture cam;
				cam.open(CAP_NAME);

				while (1)
				{
					frame = imread(FRAME_NAME, IMREAD_COLOR);
					cam.read(input);

					//imshow("input", input);
					warp(&input, &frame);
					imshow("frame", frame);

					if (waitKey(30) > 0)
					{
						initialize();
						break;
					}
				}
				break;
			}

			default: break;
			}
		}
	}
	}
}

void go(void)
{
	cout << "Input을 선택하고, Read를 클릭하세요.\n";
	int obj = 0xff;
	GLUI* glui = GLUI_Master.create_glui("GLUI", 0L, 512, 512);
	main_window = glui->get_glut_window_id();
	GLUI_Master.set_glutIdleFunc(NULL);

	GLUI_Panel* inputPanel = new GLUI_Panel(glui, "Input Image");
	inputGroup = new GLUI_RadioGroup(inputPanel, &obj);

	new GLUI_RadioButton(inputGroup, "Image");
	new GLUI_RadioButton(inputGroup, "Video");
	new GLUI_RadioButton(inputGroup, "Cam");

	new GLUI_Button(inputGroup, "Read", INPUT, control_rb);
	new GLUI_Button(inputGroup, "Execute", EXECUTE, control_bt);
	new GLUI_Button(inputGroup, "Quit", QUIT, control_bt);

	glui->set_main_gfx_window(main_window);
	glutMainLoop();
}