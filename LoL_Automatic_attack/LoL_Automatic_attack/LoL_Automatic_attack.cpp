// LoL_Automatic_attack.cpp : �������̨Ӧ�ó������ڵ㡣
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
	//	if (src.empty()) // �����Ч����
	//	{
	//		std::cout << "Could not open or find the image" << std::endl;
	//		return 0;
	//	}
	//	cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE); // ������ʾһ������
	//	cv::imshow("Display window", src);
	//	cv::waitKey(0);
	//}
	//SetCursorPos(1000, 1000);
	
	return 0;
}
//SetCursorPos(50,50);
//mouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);

