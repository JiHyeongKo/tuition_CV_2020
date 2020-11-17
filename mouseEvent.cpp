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

void onMouse(int event, int x, int y, int flags, void* param)   // 마우스 이벤트가 발생하면 호출되는 콜백 함수이다. 
{
    if (event == EVENT_LBUTTONDOWN) 
    {  // 좌측 마우스버튼을 눌렀을 때
        Mat& img = *(Mat*)(param);
        if (i < 4)
        {
            circle(img, Point(x, y), 5, Scalar(255, 0, 0), 3);
            x_buffer[i] = x;
            y_buffer[i] = y;
            i++;
            imshow("frame", img);
        }

        if (i == 4) // 다하면 다시 불러와서 circle 삭제
        {
            img = imread("frame.jpg", IMREAD_COLOR);
        }

    }
}

void maskThreshold(Mat* mask, Mat* dst)
{
    Mat thr = Mat::zeros(mask->rows, mask->cols, CV_8U); // 마스크 복사 -> threshold로 사용
    Mat img = *dst; // 바깥 프레임 영상
    threshold(*mask, thr, 0, 255, THRESH_BINARY_INV);
    bitwise_and(thr, img, img);
    bitwise_or(img, *dst, *dst);
}

void warp(Mat* src, Mat* dst)
{
    Point2f inputp[4], outputp[4];

    inputp[0] = Point2f(0, 0);  //  좌측 맨위
    inputp[1] = Point2f(src->cols, 0);  // 우측 맨위
    inputp[2] = Point2f(0, src->rows);  // 좌측 맨밑
    inputp[3] = Point2f(src->cols, src->rows);  // 우측 맨밑

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

