#ifndef MAIN_H
#define MAIN_H
#define INPUT	0
#define EXECUTE	1
#define QUIT	-1

#define MP4_NAME	"test.mp4"
#define IMG_NAME	"lenna.jpg"
#define	FRAME_NAME	"frame.jpg"
#define CAM_NAME	0	// my computer: rear camera 0, front one 1

void onMouse(int event, int x, int y, int flags, void* param);
void go(void);
void callbackImg(void);
void callbackVideo(void);
void callbackCam(void);
void initialize(void);

#endif MAIN_H