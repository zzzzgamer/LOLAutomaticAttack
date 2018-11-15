// LoL_Automatic_attack.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"PrintScreen.h"
#include"ScreenDetection.h"
using namespace std;

int main()
{
	dnn_yolo_syx_Cam();
	//cv::Mat src;
	//while (1)
	//{
	//	src = initGDI();
	//	if (src.empty()) // 检查无效输入
	//	{
	//		std::cout << "Could not open or find the image" << std::endl;
	//		return 0;
	//	}
	//	cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE); // 重新显示一个窗口
	//	cv::imshow("Display window", src);
	//	cv::waitKey(0);
	//}
	//SetCursorPos(1000, 1000);
	
	return 0;
}
//SetCursorPos(50,50);
//mouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);

