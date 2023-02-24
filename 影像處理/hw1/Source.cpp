#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

/*
	測資:
	 C:\Users\User\Desktop\影像處理\hw1\lennaRGB.tif
	 C:\Users\User\Desktop\影像處理\hw1\bookGray.jpg
*/

int main() 
{
	/*Mat img = imread("C:\\Users\\User\\Desktop\\影像處理\\hw1\\bookGray.jpg", -1);  // 路徑要再多加一個反斜線

	if (img.empty())  
		return -1;*/

	while (true)
	{
		string path = "";
		Mat img;
		cout << "\n請輸入圖片路徑(若要退出,則輸入0): ";
		
		getline(cin, path);
		if (path == "0")
			break;

		img = imread(path,-1);  // -1 一定要打

		if (img.empty())
		{
			cout << "\n圖片的路徑錯誤\n";
			continue;
		}

		cout << "\n請輸入像素值:";
		int pixel = 0;
		while (cin >> pixel)
		{
			int high = img.rows;  // 圖片的高度
			int width = img.cols;	// 圖片的寬度

			//  Mat tempImg = img;    // 此種寫法, 更改 tempImg 時, img 的圖像也會被同時修改
			Mat tempImg = img.clone();  //  此種寫法, 更改 tempImg 時, img 的圖像不會被同時修改

			if (img.channels() == 1) // 讀取的圖像是灰階圖(R==G==B,相當於是一個值)
			{
				cout << "\n此圖是灰階圖\n";
				for (int row = 0; row < high; row++)  // 檢查圖像中的每一個 pixel
					for (int col = 0; col < width; col++)
					{
						int gray = img.at<uchar>(row, col);

						gray += pixel;

						if (gray < 0) // 此判斷是因為 RGB 的範圍是 0~255
							gray = 0;
						else if (gray > 255)  // 此判斷是因為 RGB 的範圍是 0~255
							gray = 255;
						
						tempImg.at<uchar>(row, col) = gray;

					}

			}
			else if (img.channels() == 3) // 讀取的圖像是彩色圖(R!=G!=B,相當於是三個值)
			{
				cout << "\n此圖是彩色圖\n";

				for (int row = 0; row < high; row++)  // 檢查圖像中的每一個 pixel
					for (int col = 0; col < width; col++)
					{
						int b = img.at<Vec3b>(row, col)[0]; //  一個像素的RGB 中的B
						int g = img.at<Vec3b>(row, col)[1]; //  一個像素的RGB 中的G
						int r = img.at<Vec3b>(row, col)[2]; //  一個像素的RGB 中的R

						r += pixel;

						if (r > 255)  // 此判斷是因為 RGB 的範圍是 0~255
							r = 255;

						if (r < 0) // 此判斷是因為 RGB 的範圍是 0~255
							r = 0;

						tempImg.at<Vec3b>(row, col)[2] = r;
					}

			}

			namedWindow("原圖", WINDOW_AUTOSIZE);  // 新增視窗，第一個參數 為視窗名稱
			namedWindow("修改後的圖", WINDOW_AUTOSIZE);
			imshow("原圖", img);
			imshow("修改後的圖", tempImg);

			waitKey(0);  // 有此行後，視窗不會馬上消失

			destroyWindow("原圖");
			destroyWindow("修改後的圖");

			cout << "\n請輸入像素值:";
		}
		cin.clear(); // 為了將 ^Z 輸入流,清除
		
	}

	return -1;
	
}
