#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

/*
	測資:
	 C:\Users\User\Desktop\影像處理\hw3\Assignment3\fig.jpg
	 C:\Users\User\Pictures\Saved Pictures\A.jpg
*/

int main()
{

	while (true)
	{
		string path = "";
		Mat original;
		Mat src;
		Mat img;
		cout << "\n請輸入圖片路徑(若要退出,則輸入0): ";

		getline(cin, path);
		if (path == "0")
			break;

		original = imread(path, IMREAD_COLOR);  // 原圖
		src = imread(path, IMREAD_GRAYSCALE);  // 將圖像以灰階圖的方式讀取

		if (src.empty())
		{
			cout << "\n圖片的路徑錯誤\n";
			continue;
		}

		GaussianBlur(src, img, Size(3, 3), 0, 0, BORDER_DEFAULT);  // 高斯模糊的功能: 將照片的雜訊去除，能讓我們找到更精準的輪廓

		Mat grad_x, grad_y;
		Mat abs_grad_x, abs_grad_y;
		Mat output;
		Mat edges_Image;

		// Sobel 主要用於邊緣偵測(只能作用於灰階圖)
		Sobel(img, grad_x, CV_64F, 1, 0,3);  // 對 x 方向計算梯度，所產生的圖
		Sobel(img, grad_y, CV_64F, 0, 1, 3); // 對 y 方向計算梯度，所產生的圖
		convertScaleAbs(grad_x, abs_grad_x);  //  convertScaleAbs 用於將圖片增強
		convertScaleAbs(grad_y, abs_grad_y);
		addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, edges_Image);   // 將 grad_x 和 grad_y 的圖 融合在一起


		const int EDGES_THRESHOLD = 65;  // 設定閾值
		const int max = 255;																			// THRESH_BINARY_INV  => 是一種 圖像二值化的規則
		threshold(edges_Image, output, EDGES_THRESHOLD, max, THRESH_BINARY_INV);  // threshold函數，能讓圖片白變黑 or 黑變白(將圖像上的像素點的灰度值，設置為0或255)

		namedWindow("原圖", WINDOW_AUTOSIZE);
		namedWindow("灰階圖(高斯模糊處理過)", WINDOW_AUTOSIZE);
		namedWindow("邊緣偵測的圖", WINDOW_AUTOSIZE);  
		namedWindow("素描圖", WINDOW_AUTOSIZE);

		imshow("原圖", original);
		imshow("灰階圖(高斯模糊處理過)", img);
		imshow("邊緣偵測的圖", edges_Image);
		imshow("素描圖", output);

		waitKey(0);  

		destroyWindow("原圖");
		destroyWindow("灰階圖(高斯模糊處理過)");
		destroyWindow("邊緣偵測的圖");
		destroyWindow("素描圖");

		cin.clear(); 

	 }

}