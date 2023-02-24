#include<opencv2/opencv.hpp>
#include<iostream>
#include<cmath>

using namespace cv;
using namespace std;

/*
	測資:
	 C:\Users\User\Desktop\影像處理\hw3\Assignment3\fig.jpg
	 C:\Users\User\Pictures\Saved Pictures\A.jpg
	 C:\Users\User\Desktop\影像處理\hw4\mizuho480.jpg
*/


Mat GaussianLowPassFunction(Mat src, float sigma)  // sigma是高斯函數的參數。此參數越小，則頻率高斯濾波器越窄、濾除高頻的成分越多、圖像就越平滑。
{
	//此部分為計算GaussianLowPass的濾波器函數

	Mat gaussianBlur(src.size(), CV_32FC1);

	int high = gaussianBlur.rows;  // 新尺寸的圖片的高度

	int width = gaussianBlur.cols;	// 新尺寸的圖片的寬度

	float d0 = 2 * sigma * sigma; 


	for (int i = 0; i < high; i++)
		for (int j = 0; j < width; j++)
		{
			float d = pow(float(i - high / 2), 2) + pow(float(j - width / 2), 2);
			gaussianBlur.at<float>(i, j) = expf(-d / d0);
		}

	namedWindow("高斯濾波器函數", WINDOW_AUTOSIZE);
	imshow("高斯濾波器函數", gaussianBlur);
	waitKey(0);
	destroyWindow("高斯濾波器函數");

	return gaussianBlur;
}

Mat FrequencyFilt(Mat src, Mat blur)  // blur是濾波器函數。src是新尺寸的圖片。此部分是利用濾波器函數，將頻域中想要過濾的數值過濾掉。
{
	Mat plane[] = { Mat_<float>(src), Mat::zeros(src.size(), CV_32FC1) };  // 創建通道(必須是單通道)，儲存 傅立葉轉換後的複數的 實部、虛部
	
	Mat compleximg;
	merge(plane, 2, compleximg);  //將實部(單通道)、虛部(單通道)通道合併成一個具有雙通道的容器()
	dft(compleximg, compleximg);  // 將傅立葉轉換完的結果存進"雙通道的容器"


	split(compleximg, plane);  //將雙通道分離成"2個單通道"

	/*      由於已經在padded的部分將每個piexl都乘上(-1)^(x+y)，因此已經將零頻移動到中心，所以不需要以下的所有操作。
	
			// 此部分的操作是: 移動影象(將零頻移到中心)
			int cx = plane[0].cols / 2;  // 圖的座標 =>將 (cx,cy) 思考成圖的中心點
			int cy = plane[0].rows / 2;

			//此部分是移動實數,part1_r~part4_r與plane[0]共享資料
			// Rect(0, 0, cx, cy)  => 矩形 ，原點:(0,0)，矩形的寬:cx，矩形的高:cy
			Mat part1_r(plane[0], Rect(0, 0, cx, cy));  // 整張圖的第二象限的圖片
			Mat part2_r(plane[0], Rect(cx, 0, cx, cy));// 整張圖的第一象限的圖片
			Mat part3_r(plane[0], Rect(0, cy, cx, cy));// 整張圖的第三象限的圖片
			Mat part4_r(plane[0], Rect(cx, cy, cx, cy));// 整張圖的第四象限的圖片

			// 此操作，part 1的內容和 part 4的內容會互相交換
			Mat temp;   
			part1_r.copyTo(temp);  // copyto()，複製內容，且不會共享記憶體
			part4_r.copyTo(part1_r); 
			temp.copyTo(part4_r);

			// 此操作，part 2的內容和 part 3的內容會互相交換
			part2_r.copyTo(temp);
			part3_r.copyTo(part2_r);
			temp.copyTo(part3_r);

	
			//此部分是移動虛數，目的與概念都和移動實數相同。part1_i~part4_i與plane[1]共享資料
			Mat part1_i(plane[1], Rect(0, 0, cx, cy));
			Mat part2_i(plane[1], Rect(cx, 0, cx, cy));
			Mat part3_i(plane[1], Rect(0, cy, cx, cy));
			Mat part4_i(plane[1], Rect(cx, cy, cx, cy));

			part1_i.copyTo(temp);
			part4_i.copyTo(part1_i);
			temp.copyTo(part4_i);

			part2_i.copyTo(temp);
			part3_i.copyTo(part2_i);
			temp.copyTo(part3_i);

	*/

	//此為原圖的頻譜圖
	Mat amplitude, angle, Spectrum, Phase;
	phase(plane[0], plane[1], angle); //將複數的圖像轉換成相位
	magnitude(plane[0], plane[1], amplitude);  //將複數的圖像轉換成振幅值
	amplitude += Scalar::all(1); // 傅立葉轉換後的圖片不好分析，因此要將振幅值轉成對數，數據的結果較好看
	log(amplitude, amplitude); 
	normalize(amplitude, Spectrum, 1, 0, NORM_MINMAX);
	normalize(angle, Phase, 0, 1, NORM_MINMAX);

	namedWindow("原圖的頻譜大小", WINDOW_AUTOSIZE);
	imshow("原圖的頻譜大小", Spectrum);
	waitKey(0);
	destroyWindow("原圖的頻譜大小");

	namedWindow("原圖的相位角度", WINDOW_AUTOSIZE);
	imshow("原圖的相位角度", Phase);
	waitKey(0);
	destroyWindow("原圖的相位角度");


	Mat blur_r, blur_i, BLUR,BlurAndOriginalSpectrum ,amplitude2;   // "濾波器函數"與"傅立葉轉換後的結果"做乘積
	multiply(plane[0], blur, blur_r);  // 實數與濾波器函數中的對應元素做相乘。
	multiply(plane[1], blur, blur_i);// 虛數與濾波器函數中的對應元素做相乘。
	Mat plane2[] = { blur_r, blur_i };
	merge(plane2, 2, BLUR);  // 將實部與虛部(兩個單通道:plane2[0],plane2[1])合併成一個單通道(BLUR)。

	magnitude(blur_r, blur_i, amplitude2);//將複數的圖像轉換成振幅值
	amplitude2 += Scalar::all(1); // 傅立葉轉換後的圖片不好分析，因此要將振幅值轉成對數，數據的結果較好看
	log(amplitude2, amplitude2);
	normalize(amplitude2, BlurAndOriginalSpectrum, 1, 0, NORM_MINMAX);
	namedWindow("原圖與濾波器函數相乘的頻譜大小", WINDOW_AUTOSIZE);
	imshow("原圖與濾波器函數相乘的頻譜大小", BlurAndOriginalSpectrum);
	waitKey(0);
	destroyWindow("原圖與濾波器函數相乘的頻譜大小");


	Mat amplitude3;
	idft(BLUR, BLUR);  //  離散傅立葉逆轉換。此結果也是複數。
	split(BLUR, plane); //將雙通道分離成"2個單通道"
	magnitude(plane[0], plane[1], amplitude3);  //將複數的圖像轉換成振幅值
	//因為已經有"離散傅立葉逆轉換"過了，因此不需要將振幅值轉成對數
	//normalize的目的是為了顯示圖片。因為圖片的幅度值仍然超過可顯示的範圍[0,1]，因此利用normalize()將數值限制在[0,1]
	normalize(amplitude3, amplitude3, 1,0 , NORM_MINMAX);
	return amplitude3;

}



void LowPassFilter(Mat gray,float clear)
{
	int M = getOptimalDFTSize(gray.rows);               //獲得最佳DFT尺寸(尺寸是2的次方)
	int N = getOptimalDFTSize(gray.cols);				//	離散傅立葉變換的運行速度與圖片的尺寸息息相關。當圖像的尺寸是2， 3，5的整數倍時，計算速度最快。

	Mat padded; // 儲存新尺寸的圖像
	copyMakeBorder(gray, padded, 0, gray.rows, 0, gray.cols, BORDER_CONSTANT, Scalar::all(0)); //爲了達到快速計算的目的，經常通過添加新的邊緣像素的方法獲取最佳圖像尺寸
	
	namedWindow("zero-padded image", WINDOW_AUTOSIZE);
	imshow("zero-padded image", padded);
	waitKey(0);
	destroyWindow("zero-padded image");

	padded.convertTo(padded, CV_32FC1);  // 將padded的型態轉成 CV_32 float ，1是指通道數。
																				// 此部分要轉成 CV_32 float 的原因:因為下面的運算會需要乘上(-1)，負數的範圍不在0~255便會報錯

	for (int i = 0; i < padded.rows; i++)   // padded 中的每一個pixel 都與 (-1)^(x+y) 做相乘
		for (int j = 0; j < padded.cols; j++)
			padded.at<float>(i, j) *= pow((-1), (i + j));

	padded.convertTo(padded, CV_8UC1);  // 將 padded 的型態轉回原本的型態，便能將padded中的負數篩掉。

	namedWindow("zero-padded image multiply by (-1)^(x+y)", WINDOW_AUTOSIZE);
	imshow("zero-padded image multiply by (-1)^(x+y)", padded);
	waitKey(0);
	destroyWindow("zero-padded image multiply by (-1)^(x+y)");

	Mat gaussianKernel = GaussianLowPassFunction(padded, clear);

	Mat Result = FrequencyFilt(padded, gaussianKernel);  //在頻率域濾波

	namedWindow("Gaussian filter(未調整為原尺寸)", WINDOW_AUTOSIZE);
	imshow("Gaussian filter(未調整為原尺寸)", Result);
	waitKey(0);
	destroyWindow("Gaussian filter(未調整為原尺寸)");

	Result = Result(Rect(0, 0, gray.cols, gray.rows));   // 將 圖片裁切為原尺寸

	namedWindow("Gaussian filter(已調整為原尺寸)", WINDOW_AUTOSIZE);
	imshow("Gaussian filter(已調整為原尺寸)", Result);
	waitKey(0);
	destroyWindow("Gaussian filter(已調整為原尺寸)");

}

int main()
{

	while (true)
	{
		string path = "";
		float clear;
		Mat img;
		Mat gray;
		
		
		cout << "\n請輸入圖片路徑(若要退出,則輸入0): ";
		
		getline(cin, path);
		if (path == "0")
			break;

		img = imread(path, IMREAD_COLOR);  // 原圖

		gray = imread(path, IMREAD_GRAYSCALE);  // 將圖像以灰階圖的方式讀取

		if (gray.empty())
		{
			cout << "\n圖片的路徑錯誤\n";
			continue;
		}

		namedWindow("原圖", WINDOW_AUTOSIZE);
		imshow("原圖", img);
		waitKey(0);
		destroyWindow("原圖");


		namedWindow("灰階圖", WINDOW_AUTOSIZE);
		imshow("灰階圖", gray);
		waitKey(0);
		destroyWindow("灰階圖");

		cout << "\n請輸入數值(圖片的模糊程度，數值越小代表越模糊):";

		while (cin >> clear)
		{
			LowPassFilter(gray, clear);
			cout << "\n請輸入數值:";
		}

		cin.clear();

	}

}