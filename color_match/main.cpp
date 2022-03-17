#include <iostream>
#include <vector>
#include <fstream>

struct RGB
{
double r = 0; //0 - 1
double g = 0; //0 - 1
double b = 0; //0 - 1
};

struct Box
{
	RGB  rgb;

int left_up_x = 0;
int left_up_y = 0;
int right_down_x = 0;
int right_down_y = 0;
};

int main(int ac, char** av)
{

	std::cout<<"hello world"<<std::endl;
	std::vector<std::vector<RGB>> board;

	for (int i = 0 ; i < 100 ; i++)
	{
		std::vector<RGB> row;
		for(int j = 0 ; j < 100 ; j++)
		{
			row.push_back(RGB());
		}
		board.push_back(row);
	}	

	
	Box box;
	box.rgb.r = 0.3;
	box.rgb.g = 0;
	box.rgb.b = 0;
	box.left_up_x = 10;
	box.left_up_y = 10;
	box.right_down_x = 40;
	box.right_down_y = 60;


	for(int i = box.left_up_y ; i<= box.right_down_y ; i++)
	{
		for(int j = box.left_up_x ; j<= box.right_down_x ; j++)
		{
			board[i][j].r += box.rgb.r;
			board[i][j].g += box.rgb.g;
			board[i][j].b += box.rgb.b;
		}
	}


	box.rgb.r = 0;
	box.rgb.g = 0;
	box.rgb.b = 0.5;
	box.left_up_x = 30;
	box.left_up_y = 30;
	box.right_down_x = 80;
	box.right_down_y = 80;

	for(int i = box.left_up_y ; i<= box.right_down_y ; i++)
	{
		for(int j = box.left_up_x ; j<= box.right_down_x ; j++)
		{
			board[i][j].r += box.rgb.r;
			board[i][j].g += box.rgb.g;
			board[i][j].b += box.rgb.b;
		}
	}



	// write out image
	std::ofstream myfile;
	myfile.open ("example.txt");
	for (int i = 0 ; i < 100 ; i++)
	{
		for(int j = 0 ; j < 100 ; j++)
		{
			myfile << i<<","<<j<<","<<board[i][j].r<<","<<board[i][j].g<<","<<board[i][j].b<<"\n";
		}
	}	

	myfile.close();





	return 0;
};
