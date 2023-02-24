#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

/*
	測資:
		C:\Users\User\Pictures\Saved Pictures\A.jpg
		C:\Users\User\Desktop\影像處理\hw2\Assignment2\yzu.bmp
*/


int height;  // 圖片的高度
int width;  // 圖片的寬度
int angle; // 控制 「旋轉整張圖片的圖」的角度
int angle2; // 控制 「旋轉中間的圓的圖」的角度
int MaxAngle = 359;
double radius;  // 圓形的半徑
 

Point center;
Mat image;
Mat image2;
Mat image3;
Mat rotated_image; // 存 「旋轉整張圖片的圖」

static void on_trackbar1(int, void*)  // 控制 「旋轉整張圖片的圖」
{

	Mat rotation_matix = getRotationMatrix2D(center, angle, 1.0);  // 使用此函式得到旋轉矩陣(以圖片為中心做旋轉,第三個參數代表圖片的放大倍率)
	
	warpAffine(image, rotated_image, rotation_matix, image.size());  // 利用旋轉矩陣，旋轉圖片

	imshow("旋轉整張圖片的圖", rotated_image);

}

static void on_trackbar2(int, void*)  // 控制 「旋轉中間的圓的圖」
{

	Mat rotation_matix = getRotationMatrix2D(center, angle2, 1.0);  // 使用此函式得到旋轉矩陣(以圖片為中心做旋轉,第三個參數代表圖片的放大倍率)
	Mat image4;  // 存 「旋轉完後的圓」
	warpAffine(image2, image4, rotation_matix, image.size());  // 利用旋轉矩陣，將圓形做旋轉，再存到 image4

	for (int x = 0; x < width; x++)  // 將 「旋轉完後的圓」 與 「切割完圖片後，剩下的背景」做合併
		for (int y = 0; y < height; y++)
		{
			int temp = (x - center.x) * (x - center.x) + (y - center.y) * (y - center.y);

			if (temp < (radius * radius))
			{
				image3.at<Vec3b>(Point(x, y))[0] = image4.at<Vec3b>(Point(x, y))[0];
				image3.at<Vec3b>(Point(x, y))[1] = image4.at<Vec3b>(Point(x, y))[1];
				image3.at<Vec3b>(Point(x, y))[2] = image4.at<Vec3b>(Point(x, y))[2];
			}

		}

	imshow("旋轉中間的圓的圖", image3);

}

int main()
{

	while (true)
	{
		string path = "";
		cout << "\n請輸入圖片路徑(若要退出,則輸入0): ";

		getline(cin, path);
		if (path == "0")
			break;

		image = imread(path, -1);  // -1 一定要打

		if (image.empty())
		{
			cout << "\n圖片的路徑錯誤\n";
			continue;
		}

		image2 = image.clone(); // 存「切割完圖片後，剩下的圓」
		image3 = image.clone();// 存 「切割完圖片後，剩下的背景」

		cout << "\n請輸入旋轉角度:";
		angle = 0;

		while (cin >> angle)
		{
			angle2 = angle;

			height = image.rows;  
			width = image.cols;	
			radius = min(height, width) / 2;  

			center = Point(width / 2, height / 2);

			for (int x = 0; x < width; x++)
				for (int y = 0; y < height; y++)
				{
					int temp = (x - center.x) * (x - center.x) + (y - center.y) * (y - center.y);  // 每個座標與圓心的距離

					if (temp < (radius * radius))  // 切割出圓的部分
					{
						image2.at<Vec3b>(Point(x, y))[0] = image.at<Vec3b>(Point(x, y))[0];
						image2.at<Vec3b>(Point(x, y))[1] = image.at<Vec3b>(Point(x, y))[1];
						image2.at<Vec3b>(Point(x, y))[2] = image.at<Vec3b>(Point(x, y))[2];

					}
					else  // 切割出背景的部分(不包括圓)
					{
						image3.at<Vec3b>(Point(x, y))[0] = image.at<Vec3b>(Point(x, y))[0];
						image3.at<Vec3b>(Point(x, y))[1] = image.at<Vec3b>(Point(x, y))[1];
						image3.at<Vec3b>(Point(x, y))[2] = image.at<Vec3b>(Point(x, y))[2];

					}

				}

			namedWindow("原圖", WINDOW_AUTOSIZE);
			namedWindow("旋轉整張圖片的圖", WINDOW_AUTOSIZE);
			namedWindow("旋轉中間的圓的圖", WINDOW_AUTOSIZE);

			imshow("原圖", image);
			
			//在視窗中建立一個滑動條
			char TranckbarName[50] = "旋轉角度";
			createTrackbar(TranckbarName, "旋轉整張圖片的圖", &angle, MaxAngle, on_trackbar1);
			createTrackbar(TranckbarName, "旋轉中間的圓的圖", &angle2, MaxAngle, on_trackbar2);

			on_trackbar1(angle, 0);
			on_trackbar2(angle2, 0);

			waitKey(0);

			destroyWindow("原圖");
			destroyWindow("旋轉整張圖片的圖");
			destroyWindow("旋轉中間的圓的圖");

			cout << "\n請輸入旋轉角度:";
		}
		cin.clear(); // 為了將 ^Z 輸入流,清除

	}

}
