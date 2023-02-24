#include <iostream>
#include <string>
#include <time.h> 
#include <vector>
# include <fstream>

using namespace std;

int main()
{
	string filename("input.txt");
	fstream file_out;

	file_out.open(filename, std::ios_base::out);
	if (!file_out.is_open()) {
		cout << "failed to open " << filename << '\n';
	}
	/*else {
		file_out << "Some random text to write." << endl;
		cout << "Done Writing!" << endl;
	}*/
	srand(time(NULL));
	int time_t = 0;

	while (time_t < 100)
	{
		int num = 20;
		int left = rand();
		int right = rand();
		left = (left % num) + 1;
		right = (right % num) + 1;
		int count = 0;
		cout << left << " " << right << endl;
		file_out << left << " " << right << endl;
		int left_e = rand();
		int right_e = rand();
		left_e = (left_e % left) + 1;
		right_e = (right_e % right) + 1;
		for (int i = 1; i <= left_e; i++)
		{
			for (int j = 1; j <= right_e; j++)
			{
				int x = rand();
				int y = rand();
				x = (x % left) + 1;
				y = (y % right) + 1;
				cout << x << " " << y << endl;
				file_out << x << " " << y << endl;

				count++;
				//cout << i << " " << i << endl;
			}
		}
		cout << "-1" << " " << "-1" << endl;
		cout << endl;
		file_out << "-1" << " " << "-1" << endl;
		file_out << endl;
		//cout << count << endl;
		time_t++;
	}

	file_out.close();
	/*srand(time(NULL));

	int x = rand();
	int y = rand();

	cout << x%5 << endl;
	cout << y % 5 << endl;*/
	return 0;
}