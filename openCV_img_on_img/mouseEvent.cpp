#include <opencv2/opencv.hpp>
#include <iostream>
#include "main.h"
using namespace cv;
using namespace std;

int x_buffer[4];
int y_buffer[4];
int i = 0;

void initialize(void)
{
    i = 0;
    memset(x_buffer, 0, sizeof(x_buffer));
    memset(y_buffer, 0, sizeof(y_buffer));
}

void onMouse(int event, int x, int y, int flags, void* param)   // ���콺 �̺�Ʈ�� �߻��ϸ� ȣ��Ǵ� �ݹ� �Լ��̴�. 
{
    if (event == EVENT_LBUTTONDOWN) 
    {  // ���� ���콺��ư�� ������ ��
        Mat& img = *(Mat*)(param);
        if (i < 4)
        {
            circle(img, Point(x, y), 5, Scalar(255, 0, 0), 3);
            x_buffer[i] = x;
            y_buffer[i] = y;
            i++;
            imshow("frame", img);
        }

        if (i == 4) // ���ϸ� �ٽ� �ҷ��ͼ� circle ����
        {
            img = imread("frame.jpg", IMREAD_COLOR);
        }

    }
}

void maskThreshold(Mat* mask, Mat* dst)
{
    Mat thr = Mat::zeros(mask->rows, mask->cols, CV_8U); // ����ũ ���� -> threshold�� ���
    Mat img = *dst; // �ٱ� ������ ����
    threshold(*mask, thr, 0, 255, THRESH_BINARY_INV);
    bitwise_and(thr, img, img);
    bitwise_or(img, *dst, *dst);
}

void warp(Mat* src, Mat* dst)
{
    Point2f inputp[4], outputp[4];

    inputp[0] = Point2f(0, 0);  //  ���� ����
    inputp[1] = Point2f(src->cols, 0);  // ���� ����
    inputp[2] = Point2f(0, src->rows);  // ���� �ǹ�
    inputp[3] = Point2f(src->cols, src->rows);  // ���� �ǹ�

    outputp[0] = Point2f(x_buffer[0], y_buffer[0]);
    outputp[1] = Point2f(x_buffer[1], y_buffer[1]);
    outputp[2] = Point2f(x_buffer[2], y_buffer[2]);
    outputp[3] = Point2f(x_buffer[3], y_buffer[3]);

    Mat mask;
    Mat dst_buffer = *dst;
    Mat cut = getPerspectiveTransform(inputp, outputp);

    warpPerspective(*src, mask, cut, dst->size());
    maskThreshold(&mask, dst);
    bitwise_or(mask, dst_buffer, *dst);
}

