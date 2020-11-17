#ifndef MAIN_H
#define MAIN_H
#define INPUT	0
#define EXCUTE	1
#define QUIT	-1

#define MP4_NAME	"test.mp4"
#define IMG_NAME	"lenna.jpg"
#define	FRAME_NAME	"frame.jpg"
#define CAP_NAME	1	// my computer: rear camera 0, front one 1

void onMouse(int event, int x, int y, int flags, void* param);
void go(void);
void callbackImg(int id);
void callbackVideo(int id);
void callbackCam(int id);
void initialize(void);

#endif MAIN_H

/*
해야할것:
사진, 영상, 카메라 불러오는 GLUI 구성
어파인, 마우스로 좌표받기
*/