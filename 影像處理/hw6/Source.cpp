#include<opencv2/opencv.hpp>
#include<iostream>
#include <fstream>
#include<string>
#include<iomanip>

using namespace cv;
using namespace std;

/*
	測資:
	 C:\Users\User\Desktop\影像處理\hw6\Assignment6\img1\img1.bmp
	 C:\Users\User\Desktop\影像處理\hw6\Assignment6\img2\img2.bmp
	 C:\Users\User\Desktop\影像處理\hw6\Assignment6\img3\img3.bmp
*/

/*
	 C:\Users\User\Desktop\影像處理\hw6\Assignment6\img1\img1_ColorDatabase.txt
	 C:\Users\User\Desktop\影像處理\hw6\Assignment6\img2\img2_ImageColor.txt
	 C:\Users\User\Desktop\影像處理\hw6\Assignment6\img3\img3_ColorDatabase.txt

*/


struct ColorData{

	int id = -1;
	int R = -1;
	int G = -1;
	int B = -1;

};

struct RLE {

	int id = -1;
	int count = 0;

};




void CreateColorDataBase_CompressImage(Mat img,vector<ColorData>&colors, vector<double>&total_compression_rate,string path)
{
	int index = path.rfind(".");
	string filepath =path.substr(0, index);

	ofstream outFile(filepath+"_" + "ColorDatabase.txt");
	ofstream outFile2(filepath + "_" "ImageColor.txt");


	if (!outFile||!outFile2)
		cout << "\n檔案未正確開啟\n\n";
	else
		cout << "\n開始建立顏色資料庫、壓縮圖片\n\n";

	outFile << img.rows << "," << img.cols<<endl;

	for (int row = 0; row < img.rows; row++) 
	{

		vector<RLE>rle;

		for (int col = 0; col < img.cols; col++)
		{
			int B = img.at<Vec3b>(row, col)[0]; 
			int G = img.at<Vec3b>(row, col)[1]; 
			int R = img.at<Vec3b>(row, col)[2]; 

			ColorData temp;
			temp.id = colors.size();
			temp.B = B; temp.G = G; temp.R = R;

			RLE replace;
			

			if (colors.empty())
			{
				outFile << colors.size() << "," << R << "," << G << "," << B << "\n";
				replace.id = colors.size();
				replace.count += 1;

				colors.push_back(temp);
				rle.push_back(replace);
			}
			else
			{
				for (int i = 0; i < colors.size(); i++)
				{
					if (colors[i].B == B && colors[i].G == G && colors[i].R == R)
					{
						replace.id = i;
						replace.count += 1;

						 if(rle.empty())
							 rle.push_back(replace);
						 else
							 if (i == rle[rle.size() - 1].id)
								rle[rle.size() - 1].count += 1;
							 else
								 rle.push_back(replace);
							 
						break;
					}

					if (i == (colors.size() - 1))
					{
						outFile << colors.size() << "," << R << "," << G << "," << B << "\n";
						replace.id = colors.size();
						replace.count += 1;
						colors.push_back(temp);
						rle.push_back(replace);
						break;
					}

				}
			}


		}

		for (int x = 0; x < rle.size(); x++)
			outFile2 << rle[x].id << " " << rle[x].count << " ";


	}


	cout << "建立顏色資料庫、壓縮圖片完成\n\n";

	outFile.seekp(0, ios::end);
	outFile2.seekp(0, ios::end);
	
	double compression_rate = double(img.total() * img.elemSize()) / (outFile.tellp() + outFile2.tellp());
	total_compression_rate.push_back(compression_rate);

	cout << "顏色總數: " << colors.size() << endl << endl;
	cout << "圖片的大小: " << img.total()*img.elemSize() << " bytes" << endl << endl;
	cout << "ColorDataBase.txt的檔案大小: " << outFile.tellp() <<" bytes" << endl << endl;
	cout << "ImageColor.txt的檔案大小: " << outFile2.tellp() << " bytes" << endl << endl;
	cout<<"圖片的壓縮率: " << fixed << setprecision(4) << compression_rate  << endl << endl;

	outFile.close();
	outFile2.close();

}


Mat DeCompressImage(vector<ColorData>& colors, string path,ifstream &inFile,ifstream &inFile2)
{

	cout << "\n===========================\n\n開始解壓縮圖片\n\n";

	string oneline, data;
	char delimiter = ',';
	vector<int>datas;

	getline(inFile, oneline);

	stringstream sstream(oneline);
	while (getline(sstream, data, delimiter))
		datas.push_back(stoi(data));

	int height = datas[0];int width = datas[1];

	Mat NewImage(height, width, CV_8UC3, Scalar(0, 0, 0));

	while (getline(inFile, oneline))
	{
		stringstream sstream(oneline);

		ColorData temp;
		char delimiter = ',';


		string data;
		vector<int>datas;

		while (getline(sstream, data, delimiter))
			datas.push_back(stoi(data));

		temp.id = datas[0]; temp.R = datas[1]; temp.G = datas[2]; temp.B = datas[3];

		colors.push_back(temp);
	}


	vector<RLE>rle;

	while (getline(inFile2, oneline))
	{
		stringstream sstream(oneline);

		char delimiter = ' ';
		string data;
		vector<int>datas;

		while (getline(sstream, data, delimiter))
			datas.push_back(stoi(data));

		for (int i = 0; i < (datas.size() - 1);)
		{
			RLE temp;
			temp.id = datas[i];
			temp.count = datas[i + 1];
			rle.push_back(temp);
			i += 2;
		}

	}

	for (int row = 0, times = 0, count = 1; row < NewImage.rows; row++)  // 檢查圖像中的每一個 pixel
		for (int col = 0; col < NewImage.cols; col++)
		{
			if (count > rle[times].count)
			{
				count = 1;
				times++;
			}

			NewImage.at<Vec3b>(row, col)[0] = colors[rle[times].id].B;
			NewImage.at<Vec3b>(row, col)[1] = colors[rle[times].id].G;
			NewImage.at<Vec3b>(row, col)[2] = colors[rle[times].id].R;
			count++;

		}

	inFile.close();
	inFile2.close();

	cout << "解壓縮圖片完成\n\n";

	return NewImage;

}



int main()
{

	vector<double>total_compression_rate;

	while (true)
	{
		cout << "\n請選擇模式(0:結束程式,1:壓縮圖片,2:解壓縮圖片,3:查看圖片平均壓縮率): ";

		string mode = "";

		getline(cin,mode);


		if (mode == "0")
			break;
		else if (mode == "1")
		{

			while (true)
			{
				string path = "";
				Mat img;

				cout << "\n請輸入圖片路徑(輸入:0是返回): ";

				getline(cin, path);

				if (path == "0")
					break;

				img = imread(path, IMREAD_COLOR); 

				if (img.empty())
				{
					cout << "\n圖片的路徑錯誤\n";
					continue;
				}
				else
				{
					vector<ColorData>colors;
					CreateColorDataBase_CompressImage(img, colors, total_compression_rate, path);
					break;
				}
			}

		}
		else if (mode == "2")
		{
			while (true)
			{
				string path = "";
				vector<ColorData>colors;

				cout << "\n請輸入檔案路徑(選擇一個檔案的路徑輸入即可,輸入:0是返回): ";

				getline(cin, path);
				
				if (path == "0")
					break;

				int index = path.rfind("_");
				if (index == string::npos)
				{
					cout << "\n檔名輸入錯誤\n";
					continue;
				}
				int length = path.size()- path.substr(index).size();
				string filepath = path.substr(0, length);


				ifstream inFile(filepath + "_" + "ColorDatabase.txt");
				ifstream inFile2(filepath + "_" + "ImageColor.txt");

				if (!inFile || !inFile2)
				{
					cout << "\n檔案未正確開啟\n\n";
					continue;
				}
				else
				{
					Mat NewImage = DeCompressImage(colors, path, inFile, inFile2);

					int index2 = filepath.rfind("\\") + 1;
					int length2 = filepath.size() - filepath.substr(index2).size();
					string filepath2 = filepath.substr(0, length2);
					int index3 = filepath.rfind("\\") + 1;
					string filepath3 = filepath.substr(index3);
					string fileName = filepath2 + "compress_" + filepath3 + ".bmp";

					imwrite(fileName, NewImage);

					namedWindow("DeCompressImage", WINDOW_AUTOSIZE);
					resize(NewImage, NewImage, Size(), 0.2, 0.2);  //改變圖片的大小，0.5:原圖的50%

					imshow("DeCompressImage", NewImage);
					waitKey(0);

					destroyWindow("DeCompressImage");

					break;
				}


			}

		}
		else if (mode == "3")
		{

			if (total_compression_rate.size() == 0)
				cout << "\n尚未壓縮過圖片\n";
			else
			{
				double average = 0;

				for (auto it : total_compression_rate)
					average += it;

				average /= total_compression_rate.size();

				cout << "\n圖片的平均壓縮率: " << fixed << setprecision(4) << average << endl;

			}

			continue;

		}

	}



}