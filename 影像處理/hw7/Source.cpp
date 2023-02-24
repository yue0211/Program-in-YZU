#include<opencv2/opencv.hpp>
#include<iostream>
#define PI 3.1415926

using namespace cv;
using namespace std;

/*
	測資:
	 C:\Users\User\Desktop\影像處理\hw7\Assignment7\IMG_5702.JPG
	 C:\Users\User\Desktop\影像處理\hw7\Assignment7\IMG_5703.JPG
	 C:\Users\User\Desktop\影像處理\hw7\Assignment7\IMG_5704.JPG
*/

int main()
{

	while (true)
	{
		string path = "";
		Mat img,original;
		cout << "\n請輸入圖片路徑(若要退出,則輸入0): ";

		getline(cin, path);
		if (path == "0")
			break;


		img = imread(path, IMREAD_GRAYSCALE); 
		original = imread(path);

		if (img.empty())
		{
			cout << "\n圖片的路徑錯誤\n";
			continue;
		}

		resize(img, img, Size(), 0.1, 0.1);
		resize(original, original, Size(), 0.1, 0.1);

		Mat BinaryImage, result;

		threshold(img, BinaryImage, 35, 255, THRESH_BINARY);  //圖片二值化

		erode(BinaryImage, result, Mat());  // erode 只能用於經過二值化運算的灰階圖片
		dilate(result, result, Mat()); // dilate 只能用於經過二值化運算的灰階圖片

		vector<Vec3f> circles;
		HoughCircles(result, circles,HOUGH_GRADIENT, 1, 20, 100, 8, 15, 24);  //偵測圖上的圓形

		for (size_t i = 0; i < circles.size(); i++)
		{
			Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));  //找出圓心
			int radius = cvRound(circles[i][2]);	// 找出圓的半徑
			circle(original, center, radius, Scalar(155, 50, 255), 3, 8, 0);  // 根據圓心及半徑 畫圓
		}

		cout <<"\n圍棋總數: " << circles.size() << endl;

		namedWindow("經過影像侵蝕及膨脹的圖", WINDOW_AUTOSIZE);
		namedWindow("偵測的結果", WINDOW_AUTOSIZE);
		
		imshow("經過影像侵蝕及膨脹的圖", result);
		imshow("偵測的結果", original);
		waitKey(0);

		destroyWindow("經過影像侵蝕及膨脹的圖");
		destroyWindow("偵測的結果");
		cin.clear();

	}

}