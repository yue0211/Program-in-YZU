#include<iostream>
#include<vector>
#include<queue>
#include <fstream>
#include <sstream>
#include <string>
#include<windows.h>
#include <stdio.h>
#include <ctime>
#include <sys/timeb.h>
#include <climits>
#include <time.h>

using namespace std;

/*
測資:

(1)
		男生個數: 4
		女生個數: 4

		配對狀況:
			男			女
			1				1
			1				3
			2				1
			3				3
			4				1
			4				2
			4				3
			-1			-1


------------


*/

const int INF = (int)1e9;

bool HungarianMethod_arg(const vector<vector<int>>& grid, int i, vector<bool>& visited, vector<int>& girls,int nowboy, int nowgirl)
{
	for (int j = 0; j < girls.size(); j++)   // 幫 i (男生)找一個女生配對，所以對每個女生跑迴圈
	{
		if (grid[i][j] == 0 || visited[j]) // 如果 i (男生) 和 j (女生) 之間沒有配對，或是 i 已經找過 j 了，則不需要再管 j 了，換成找下一個女生
			continue;

		visited[j] = true;

		if (girls[j] < 0 || HungarianMethod_arg(grid, girls[j], visited, girls,i,j))  // 如果 j(女生) 沒配對過，則此女生可以直接拿來用。
		{																										//  或是 如果	j(女生) 有和其他男生配對過，所以如果將 j(女生) 配給 i(男生) ，可能會影響之前和 j 配對的男生 (girls[j]) 
																											// ，所以利用遞迴，幫girls[j](男生)再找一個新的女生配對，如果能找到新的女生和 girls[j](男生) 配對，則代表 i (男生) 和 j (女生) 可以互相配對
			girls[j] = i;
			girls[nowgirl] = nowboy;
			return true;
		}

	}

	return false;

}

bool HungarianMethod(const vector<vector<int>>& grid, int i, vector<bool>& visited, vector<int>& girls)
{
	for (int j = 0; j < girls.size(); j++)   // 幫 i (男生)找一個女生配對，所以對每個女生跑迴圈
	{
		if (grid[i][j] == 0 || visited[j]) // 如果 i (男生) 和 j (女生) 之間沒有配對，或是 i 已經找過 j 了，則不需要再管 j 了，換成找下一個女生
			continue;

		visited[j] = true;

		if (girls[j] < 0 || HungarianMethod_arg(grid, girls[j], visited, girls,i,j))  // 如果 j(女生) 沒配對過，則此女生可以直接拿來用。
		{																										//  或是 如果	j(女生) 有和其他男生配對過，所以如果將 j(女生) 配給 i(男生) ，可能會影響之前和 j 配對的男生 (girls[j]) 
																											// ，所以利用遞迴，幫girls[j](男生)再找一個新的女生配對，如果能找到新的女生和 girls[j](男生) 配對，則代表 i (男生) 和 j (女生) 可以互相配對
			girls[j] = i ;
			//girls[i] = j ;
			return true;  
		}

	}

	return false;

}

int augment(int u, int v, int bottleNeck, vector<vector<int>>& grid,vector<int>& p,int source)
{
	if (v == source)                                  
		return bottleNeck;		
	bottleNeck = augment(p[u], u, min(grid[u][v], bottleNeck), grid,p, source);
	grid[u][v] -= bottleNeck;
	grid[v][u] += bottleNeck;
	return bottleNeck;
}


// Edmonds-Karp  (找最短路徑用BFS)
int maxiumFlow(vector<vector<int>>& grid, vector<bool>& vis, vector<int>& p,int source,int sink)
{
	int maxiumflow = 0;

	while (true)
	{
		fill(vis.begin(), vis.end(),0);

		queue<int> q;
		q.push(source);
		vis[source] = true;

		while (!q.empty() && !vis[sink])
		{
			int u = q.front();
			q.pop();

			for (int v = 0; v < (sink + 1); v++)
			{
				if (vis[v] || !grid[u][v])
					continue;
				q.push(v);
				vis[v] = true;
				p[v] = u;
			}

		}

		if (!vis[sink])
			break;
		maxiumflow += augment(p[sink], sink, INF, grid,p, source);
	}

	return maxiumflow;
}


void DFS(vector<vector<int>>& grid, vector<bool>& vis, vector<int>& p, int source, int sink)
{
	vis[source] = true;
	int temp = source;

	for (int v = 0; v < (sink + 1); v++)
	{
		if (!vis[v] && grid[source][v])
		{
			vis[v] = true;
			p[v] = source;
			source = v;
			DFS(grid, vis, p, source, sink);
			source = temp;
		}

		if (vis[sink])
			break;
	}

}


// Edmonds-Karp  (找最短路徑用DFS)
int maxiumFlowDFS(vector<vector<int>>& grid, vector<bool>& vis, vector<int>& p, int source, int sink)
{
	int maxiumflow = 0;

	while (true)
	{
		fill(vis.begin(), vis.end(), 0);

		DFS(grid, vis, p, source, sink);

		if (!vis[sink])
			break;
		maxiumflow += augment(p[sink], sink, INF, grid, p, source);
	}

	return maxiumflow;
}



int main()
{
	/********/
	fstream file;
	file.open("C:\\Users\\User\\Desktop\\元智資工\\大學專題(Maximum bipartite matching)\\專題海報與code\\專題測資\\input.txt", ios::in);
	if (!file)
	{
		cout << "error" << endl;
		return 0;
	}
	/********/ 
	int choice = 0;
	cout << "請選擇解決Bipartite Matching問題,要使用的演算法(1.HungarianMethod 2.Edmonds Karp(BFS) 3.Edmonds Karp(DFS)  4.結束程式): ";
	cin >> choice;
	cout << endl;

	double sum_average = 0;

	int oooo = 0;
	while (true)
	{
		LARGE_INTEGER cpuFreq;
		LARGE_INTEGER startTime;
		LARGE_INTEGER endTime;
		double rumTime = 0.0;
		//struct timeb startTime, endTime;
		stringstream string_to_int;
		string temp;
		string temp1;
		int m = 0;  // 男生個數
		int n = 0;  // 女生個數
		int tempBoy, tempGirl;

		/********/
		//cout << "請選擇解決Bipartite Matching問題,要使用的演算法(1.HungarianMethod 2.Edmonds Karp(BFS) 3.Edmonds Karp(DFS)  4.結束程式): "; 
		//cin >> choice;
		//choice = 2;       //1  2  3 /////////////////////////////////////////////////////
		/********/
		//cout << endl;
		
		if (choice == 4)
			break;

		//cout << "請輸入男生個數:"; 
		file >> temp;
		string_to_int << temp;	string_to_int >> m;
		string_to_int.str("");	string_to_int.clear();
		
		//cout << endl;
		//cout << "請輸入女生個數:";
		file >> temp;
		string_to_int << temp;	string_to_int >> n;
		string_to_int.str("");	string_to_int.clear();
		
		//cout << endl;
		//cout << "請輸入男女的配對狀況(輸入完成時,輸入兩個-1):\n"; cout << endl;

		if (file.eof())
		{
			double res = sum_average / 100;
			cout << "average time ： " << res << " ms" << endl;
			return 0;
		}


		if (choice == 1)   // HungarianMethod
		{
			QueryPerformanceFrequency(&cpuFreq);
			QueryPerformanceCounter(&startTime);
			//ftime(&startTime);
			//DWORD startTime = GetTickCount();

			vector<vector<int>>grid(m, vector<int>(n, 0));
			
			int like = 0;
			while (file >> temp >> temp1)
			{
				string_to_int << temp;	string_to_int >> tempBoy;
				string_to_int.str("");	string_to_int.clear();

				string_to_int << temp1;	string_to_int >> tempGirl;
				string_to_int.str("");	string_to_int.clear();

				if (tempBoy == -1 && tempGirl == -1)
					break;
				grid[(tempBoy - 1)][(tempGirl - 1)] = 1;
				like++;
			}

			vector<int>girls(n, -1);  // 紀錄女生和哪個男生配對
			int matches = 0;// 最大的配對數

			for (int i = 0; i < m; i++)   // 對每個男生跑迴圈
			{
				vector<bool>visited(n, false);
				if (HungarianMethod(grid, i, visited, girls))  // 檢查男生是否能找到適合的女生配對，且不影響到原本已經配對好的男生
					matches++;
			}

			/*for (int i = 0; i < girls.size(); i++)
				cout << girls[i]+1 << " " << endl;
			cout << "#########\n";*/


			cout << "Max matches: " << matches << endl;// << endl;

			QueryPerformanceCounter(&endTime);
			//DWORD endTime = GetTickCount();
			//ftime(&endTime);

			rumTime = (((endTime.QuadPart - startTime.QuadPart) * 1000.0f) / cpuFreq.QuadPart);
			sum_average += rumTime;
			cout << "Hungarian Method演算法的執行時間:" << rumTime << " ms" << endl << endl;


		}
		else if (choice == 2|| choice == 3)  // Edmonds Karp   (BFS)  , Edmonds Karp   (DFS)
		{
			QueryPerformanceFrequency(&cpuFreq);
			QueryPerformanceCounter(&startTime);
			//DWORD startTime = GetTickCount64();

			int source = 0;
			int sink = m + n + 1;

			vector<vector<int>>grid((m+n+2), vector<int>((m + n + 2), 0));
			vector<bool>vis((m + n + 2), 0);
			vector<int>p((m + n + 2), 0);

			while (file >> temp >> temp1)
			{
				string_to_int << temp;	string_to_int >> tempBoy;
				string_to_int.str("");	string_to_int.clear();

				string_to_int << temp1;	string_to_int >> tempGirl;
				string_to_int.str("");	string_to_int.clear();

				if (tempBoy == -1 && tempGirl == -1)
					break;
				grid[tempBoy][m+ tempGirl] = 1;
			}


			for (int i = 1; i <= m; i++)
				grid[source][i] = 1;

			for (int i = (m+1); i <= (m+n); i++)
				grid[i][sink] = 1;

			if(choice==2)
				cout << "Max matches: " << maxiumFlow(grid,vis,p,source,sink) << endl;//<< endl;
			else if(choice==3)
				cout << "Max matches: " << maxiumFlowDFS(grid, vis, p, source, sink) << endl;// << endl;

			QueryPerformanceCounter(&endTime);
			//DWORD endTime = GetTickCount64();

			rumTime = (((endTime.QuadPart - startTime.QuadPart) * 1000.0f) / cpuFreq.QuadPart);
			sum_average += rumTime;

			if(choice == 2)
				cout << "Edmonds Karp(BFS)演算法的執行時間:";
			else
				cout << "Edmonds Karp(DFS)演算法的執行時間:";
			cout<< rumTime << " ms" << endl << endl;


		}
		oooo++;


	}
	

}