// implement your program here

#include <iostream>
#include <string>
#include "region_grower.hpp"

using namespace std;

int checkNumbers(char* str)
{
	for (int i = 0; i < string(str).size(); i++)
	{
		if ((str[i] < '0') || (str[i] > '9'))
		{
			return -1;
		}
	}
	return std::atoi(str);
}

/*
* The main function()
*/
int main(int argc, char* argv[])
{
	if ((argc > 1) && (argc < 9) && (argc == 8))
	{
		// take values from terminal
		string origPic = string(argv[1]);
		int i = 2;
		do {
			if (checkNumbers(argv[i]) == -1)
			{
				cout << "Error: num not right\n";
				return EXIT_FAILURE;
			}
			if (((i == 4) || (i == 5) || (i == 6)) && ((checkNumbers(argv[i]) < 0) || (checkNumbers(argv[i]) > 255)))
			{
				cout << "Error: pixel not in range\n";
				return EXIT_FAILURE;
			}
			i++;
		} while (i < 7);
		ImagePos pos = ImagePos{ static_cast<std::size_t>(stoi(string(argv[2]))), static_cast<size_t>(std::stoi(string(argv[3]))) };
		Pixel fillColor = Pixel{ static_cast<unsigned char>(stoi(string(argv[4]))), static_cast<unsigned char>(stoi(string(argv[5]))), static_cast<unsigned char>(stoi(string(argv[6]))), 255 };
		string destPic = string(argv[7]);

		// region grower class object
		RegionGrower rg;

		if (!rg.SetImage(origPic))
		{
			cout << "Error: set image wrong\n";
			return EXIT_FAILURE;
		}
		rg.SetReplacement(fillColor);
		if (!rg.SetSeed(pos.x, pos.y))
		{
			cout << "Error: seed is wrong\n";
			return EXIT_FAILURE;
		}
		rg.Update();
		if (!rg.GetOutput(destPic))
		{
			cout << "Error: output not right\n";
			return EXIT_FAILURE;
		}

		// return 0
		return EXIT_SUCCESS;
	}

	//return 1 and output error
	cout << "Error: \n";
	return EXIT_FAILURE;
}
