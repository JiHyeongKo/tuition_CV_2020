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
		if (inputGroup->get_int_val() != 2)	// ķ�� �ƴ� ��
		{
			OpenFileDialog* openFileDialog = new OpenFileDialog();
			if (openFileDialog->ShowDialog())
				FileName = TCHARToString(openFileDialog->FileName);
		}
		initialize();	// �� �� ��������..

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
			printf("��� ����Ʈ�� �����ϼ���.\n\n");
			break;
		}

		else if (i == 4)
		{
			switch (inputGroup->get_int_val())
			{
			case 0:
				printf("���Ḧ ���Ͻø� QUIT�� Ŭ���ϼ���.\n");
				printf("�ٸ� Input�� ����ϰ� �����ø� �ٸ� ���� ��ư�� Ŭ�� �� �õ��ϼ���.\n\n");
				input = imread(FileName, IMREAD_COLOR);
				//imshow("input", input);
				warp(&input, &frame);
				imshow("frame", frame);

				initialize();
				break;

			case 1:
			{
				printf("���Ḧ ���Ͻø� �ƹ� Ű���� �����̳� ������ QUIT�� Ŭ���ϼ���.\n");
				printf("�ٸ� Input�� ����ϰ� �����ø� �ƹ� Ű���� �����̳� ������ �ٸ� ���� ��ư�� Ŭ�� �� �õ��ϼ���.\n\n");
				VideoCapture cap(FileName);

				while (1)
				{
					frame = imread(FRAME_NAME, IMREAD_COLOR);
					cap >> input;	// �����󿡼� �ϳ��� �������� �����Ѵ�. 

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
				printf("���Ḧ ���Ͻø� �ƹ� Ű���� �����̳� ������ QUIT�� Ŭ���ϼ���.\n");
				printf("�ٸ� Input�� ����ϰ� �����ø� �ƹ� Ű���� �����̳� ������ �ٸ� ���� ��ư�� Ŭ�� �� �õ��ϼ���.\n\n");
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
	cout << "Input�� �����ϰ�, Read�� Ŭ���ϼ���.\n";
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