#include"stdafx.h"
#include"ScreenDetection.h"
#include"PrintScreen.h"

using namespace std;
using namespace cv;
using namespace cv::dnn;

float confidenceThreshold = 0.9;
String modelConfiguration = "yolov2-tiny.cfg";//yolov2-tiny-voc.cfg
String modelBinary = "EnemyHeroPanel1.weights";
ifstream classNamesFile("voc.names");

int dnn_yolo_syx_Img();
int dnn_yolo_syx_Cam();

int dnn_yolo_syx_Img() {
	dnn::Net net = readNetFromDarknet(modelConfiguration, modelBinary);
	//判断是否读入成功
	if (net.empty())
	{
		printf("Could not load net...\n");
		return -1;
	}
	//定义一个string类的数组
	vector<string> classNamesVec;

	if (classNamesFile.is_open())
	{
		string className = "";
		while (std::getline(classNamesFile, className))
			classNamesVec.push_back(className);
	}

	// 加载图像
	Mat frame = imread("391.jpg");
	if (frame.empty())
	{
		printf("Could not load image...\n");
		return -1;
	}

	Mat inputBlob;
	inputBlob = blobFromImage(frame, 1 / 255.F, Size(416, 416), Scalar(), true, false);
	net.setInput(inputBlob, "data");

	// 检测
	Mat detectionMat = net.forward("detection_out");
	vector<double> layersTimings;
	double freq = getTickFrequency() / 1000;
	double time = net.getPerfProfile(layersTimings) / freq;
	ostringstream ss;
	ss << "detection time: " << time << " ms";
	putText(frame, ss.str(), Point(20, 20), 0, 0.5, Scalar(0, 0, 255));

	// 输出结果
	for (int i = 0; i < detectionMat.rows; i++)
	{
		const int probability_index = 5;
		const int probability_size = detectionMat.cols - probability_index;
		float *prob_array_ptr = &detectionMat.at<float>(i, probability_index);
		size_t objectClass = max_element(prob_array_ptr, prob_array_ptr + probability_size) - prob_array_ptr;
		float confidence = detectionMat.at<float>(i, (int)objectClass + probability_index);

		if (confidence > confidenceThreshold)
		{

			float x = detectionMat.at<float>(i, 0);
			float y = detectionMat.at<float>(i, 1);
			float width = detectionMat.at<float>(i, 2);
			float height = detectionMat.at<float>(i, 3);
			int xLeftBottom = static_cast<int>((x - width / 2) * frame.cols);
			int yLeftBottom = static_cast<int>((y - height / 2) * frame.rows);
			int xRightTop = static_cast<int>((x + width / 2) * frame.cols);
			int yRightTop = static_cast<int>((y + height / 2) * frame.rows);
			Rect object(xLeftBottom, yLeftBottom, xRightTop - xLeftBottom, yRightTop - yLeftBottom);

			rectangle(frame, object, Scalar(0, 0, 255), 2, 8);
			if (objectClass < classNamesVec.size())
			{
				ss.str("");
				ss << confidence;
				String conf(ss.str());
				String label = String(classNamesVec[objectClass]) + ": " + conf;
				int baseLine = 0;
				Size labelSize = getTextSize(label, CV_FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
				rectangle(frame, Rect(Point(xLeftBottom, yLeftBottom),
					Size(labelSize.width, labelSize.height + baseLine)),
					Scalar(255, 255, 255), CV_FILLED);
				putText(frame, label, Point(xLeftBottom, yLeftBottom + labelSize.height),
					CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0));

			}
		}
	}

	imshow("YOLO-Detections", frame);
	waitKey(0);
	return 0;
}


int dnn_yolo_syx_Cam() {
	dnn::Net net = readNetFromDarknet(modelConfiguration, modelBinary);
	//判断是否读入成功
	if (net.empty())
	{
		printf("Could not load net...\n");
		return -1;
	}
	//定义一个string类的数组
	vector<string> classNamesVec;

	if (classNamesFile.is_open())
	{
		string className = "";
		while (std::getline(classNamesFile, className))
			classNamesVec.push_back(className);
	}

	// 加载图像
	//------------ frame;
	//Mat fr;
	//将信息写到帧里
	Mat src;//截取屏幕Mat

	/*VideoCapture cap("2.mp4");
	if (!cap.isOpened())
	{
		cout << "could not open the camera";
		return -1;
	}*/

	Mat inputBlob;
	int xmouse = 0;//鼠标位置
	int ymouse = 0;
	int xrandom_number = 0;//随机数
	int yrandom_number = 0;
	srand((unsigned)time(NULL));


	//*****************************************************循环检测开始********************************************************
	while (true)//循环开始
	{
		src = initGDI();
		if (src.empty()) // 检查无效输入
		{
			std::cout << "Could not open or find the image" << std::endl;
			return 0;
		}
		inputBlob = blobFromImage(src, 1 / 255.F, Size(416, 416), Scalar(), true, false);
		net.setInput(inputBlob, "data");

		// 检测
		Mat detectionMat = net.forward("detection_out");
		vector<double> layersTimings;
		double freq = getTickFrequency() / 1000;
		double time = net.getPerfProfile(layersTimings) / freq;
		ostringstream ss;
		ss << "detection time: " << time << " ms";
		putText(src, ss.str(), Point(20, 20), 0, 0.5, Scalar(0, 0, 255));


		// 输出结果
		for (int i = 0; i < detectionMat.rows; i++)
		{
			const int probability_index = 5;
			const int probability_size = detectionMat.cols - probability_index;//detectionMat.cols = 6
			float *prob_array_ptr = &detectionMat.at<float>(i, probability_index);
			size_t objectClass = max_element(prob_array_ptr, prob_array_ptr + probability_size) - prob_array_ptr;
			float confidence = detectionMat.at<float>(i, (int)objectClass + probability_index);
			if (confidence > confidenceThreshold)
			{
				//画框
				float x = detectionMat.at<float>(i, 0);
				float y = detectionMat.at<float>(i, 1);
				float width = detectionMat.at<float>(i, 2);
				float height = detectionMat.at<float>(i, 3);
				int xLeftBottom = static_cast<int>((x - width / 2) * src.cols);
				int yLeftBottom = static_cast<int>((y - height / 2) * src.rows);
				int xRightTop = static_cast<int>((x + width / 2) * src.cols);
				int yRightTop = static_cast<int>((y + height / 2) * src.rows);
				Rect object(xLeftBottom, yLeftBottom, xRightTop - xLeftBottom, yRightTop - yLeftBottom);
				rectangle(src, object, Scalar(0, 0, 255), 2, 8);
				//模拟鼠标操作
				xrandom_number = -rand() % 51 + 25;
				yrandom_number = (rand() % (150 - 100 + 1)) + 100;
				xmouse = xLeftBottom + (xRightTop - xLeftBottom) / 2 + xrandom_number;
				ymouse = yLeftBottom + (yRightTop - yLeftBottom) / 2 + yrandom_number;
				SetCursorPos(xmouse, ymouse);
				mouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
				//画提示信息
				/*if (objectClass < classNamesVec.size())
				{
				ss.str("");
				ss << confidence;
				String conf(ss.str());
				String label = String(classNamesVec[objectClass]) + ": " + conf;
				int baseLine = 0;
				Size labelSize = getTextSize(label, CV_FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
				rectangle(src, Rect(Point(xLeftBottom, yLeftBottom),
				Size(labelSize.width, labelSize.height + baseLine)),
				Scalar(255, 255, 255), CV_FILLED);
				putText(src, label, Point(xLeftBottom, yLeftBottom + labelSize.height),
				CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0));
				}*/
			}
		}

		//imshow("YOLO-Detections", src);
		waitKey(20);
	}
	//*****************************************************循环检测结束********************************************************
	waitKey(0);
	return 0;
}