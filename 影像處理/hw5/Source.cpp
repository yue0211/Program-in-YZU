#include<opencv2/opencv.hpp>
#include<iostream>
#define PI 3.1415926

using namespace cv;
using namespace std;

/*
	測資:
	 C:\Users\User\Desktop\影像處理\hw5\Assignment5\flower.jpg
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

		Mat hsi(original.rows, original.cols, original.type());

		if (src.empty())
		{
			cout << "\n圖片的路徑錯誤\n";
			continue;
		}

		float r, g, b, H, S, I, num, den, theta, sum, min_RGB;

		for (int i = 0; i < original.rows; i++)   // 將 圖從 "RGB color space" 轉成 "HSI color space" 。如此圖形處理時，較不會有太多雜訊
		{
			for (int j = 0; j < original.cols; j++)
			{
				b = original.at<Vec3b>(i, j)[0];
				g = original.at<Vec3b>(i, j)[1];
				r = original.at<Vec3b>(i, j)[2];

				// 歸一化
				b = b / 255.0;
				g = g / 255.0;
				r = r / 255.0;



				num = 0.5 * ((r - g) + (r - b));
				den = sqrt((r - g) * (r - g) + (r - b) * (g - b));
				theta = acos(num / den);

				if (den == 0)
					H = 0; // 分母不能為0
				else
					if (b <= g)
						H = theta;
					else
						H = (2 * PI - theta);

				min_RGB = min(min(b, g), r);  // min(R,G,B)
				sum = b + g + r;

				if (sum == 0)
					S = 0;
				else
					S = 1 - 3 * min_RGB / sum;

				I = sum / 3.0;
				H = H / (2 * PI);

				//將S分量和H分量都擴充到[0,255]區間以便於顯示;
				//一般H分量在[0,2pi]之間，S在[0,1]之間
				hsi.at<Vec3b>(i, j)[0] = H * 255;
				hsi.at<Vec3b>(i, j)[1] = S * 255;
				hsi.at<Vec3b>(i, j)[2] = I * 255;

			}

		}

		Mat binaryImage;

		// 設定要偵測的顏色的數值範圍(此部分是要設定黃色)，第一個參數:設定顏色，第二個參數:設定飽和度，第三個參數:設定強度
		Scalar scalarL = Scalar(22, 150, 0);  //顏色範圍的下限
		Scalar scalarH = Scalar(40, 255, 255); //顏色範圍的上限

		inRange(hsi, scalarL, scalarH, binaryImage);  //根據設定的顏色範圍，生成一張二值化的圖(此圖會將目標顏色的區域，設成白色)
		
		Mat result = original.clone();

		for (int i = 0; i < result.rows; i++)
			for (int j = 0; j < result.cols; j++)
			{
				int temp = binaryImage.at<uchar>(i, j);

				if (temp ==0)
				{
					result.at<Vec3b>(i, j)[0] = 0;
					result.at<Vec3b>(i, j)[1] = 0;
					result.at<Vec3b>(i, j)[2] = 0;
				}

			}



		namedWindow("原圖", WINDOW_AUTOSIZE);
		namedWindow("HSI圖", WINDOW_AUTOSIZE);
		namedWindow("二值化的圖", WINDOW_AUTOSIZE);
		namedWindow("結果", WINDOW_AUTOSIZE);

		resize(original, original, Size(), 0.5, 0.5);  //改變圖片的大小，0.5:原圖的50%
		resize(hsi, hsi, Size(), 0.5, 0.5);
		resize(binaryImage, binaryImage, Size(), 0.5, 0.5);
		resize(result, result, Size(), 0.5, 0.5);

		imshow("原圖", original);
		imshow("HSI圖", hsi);
		imshow("二值化的圖", binaryImage);
		imshow("結果", result);


		waitKey(0);

		destroyWindow("原圖");
		destroyWindow("HSI圖");
		destroyWindow("二值化的圖");
		destroyWindow("結果");

		cin.clear();

	}

}