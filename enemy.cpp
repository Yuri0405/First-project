#include <SFML/Graphics.hpp>
#include <string>
#include "enemy.h"
#include "map.h"
#include <math.h>
#include <iostream>
using namespace std;




Enemy::Enemy(const std::__cxx11::string  namefile)
{


	unit.img_plate.loadFromFile(namefile);
	unit.texture_plate.loadFromImage(unit.img_plate);
	unit.sprite_plate.setTexture(unit.texture_plate);
	is_alive = true;
};

void Enemy::move(float time_delta,int i,float hero_time)
{  
	delta = time_delta;
	herotime = hero_time;

	if (herotime > 1000)
	{
		unit.sprite_plate.setPosition(40*py[way_count],40*px[way_count]);
		herotime = 0;
		way_count++;
	}
		
	    //cout<<px[3]<<" "<<py[3];
}
/* 
bool Enemy::check()
{
	return is_alive;
}
*/
void Enemy::lee(int ax, int ay, int bx, int by)   // ����� ���� �� ������ (ax, ay) � ������ (bx, by)
{

	const int W = 20;         // ������ �������� ����
	const int H = 20;         // ������ �������� ����
	const int WALL = -1;         // ������������ ������
	const int BLANK = -2;         // ��������� ������������ ������
	//void ggg();
	//int px[W * H], py[W * H];      // ���������� �����, �������� � ����
	int grid[H][W] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0},
		{0,1,0,2,2,2,0,1,0,0,0,0,0,0,0,0,0,0,1,0},
		{0,1,0,2,2,2,0,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,1,0,2,2,2,0,1,0,0,0,0,0,0,0,0,0,0,1,0},
		{0,1,0,2,2,2,0,1,0,2,2,2,2,2,2,2,2,0,1,0},
		{0,1,0,2,2,2,0,1,0,2,2,2,2,2,2,2,2,0,1,0},
		{0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0},
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,2,2,2,2,0,1,0,2,2,2,2,2,2,2,2,2,2,0},
		{0,0,2,2,2,2,0,1,0,2,2,2,2,2,2,2,2,2,2,0},
		{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		{0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,1,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	};               // ������� ����

	for (int i = 0; i < W; ++i)
	{
		for (int j = 0; j < H; ++j)
		{
			if (grid[i][j] == 1)
				grid[i][j] = BLANK;
			else
				grid[i][j] = WALL;
		}
	}
	int dx[4] = { 1, 0, -1, 0 };   // ��������, ��������������� ������� ������
	int dy[4] = { 0, 1, 0, -1 };   // ������, �����, ����� � ������
	int d, x, y, k;
	bool stop;

	if (grid[ay][ax] == WALL || grid[by][bx] == WALL) exit(1);  // ������ (ax, ay) ��� (bx, by) - �����
	//std::cout << "cc";
	// ��������������� �����
	d = 0;
	grid[ay][ax] = 0;            // ��������� ������ �������� 0
	do {
		stop = true;               // ������������, ��� ��� ��������� ������ ��� ��������
		for (y = 0; y < H; ++y)
			for (x = 0; x < W; ++x)
				if (grid[y][x] == d)                         // ������ (x, y) �������� ������ d
				{
					for (k = 0; k < 4; ++k)                    // �������� �� ���� ������������ �������
					{
						int iy = y + dy[k], ix = x + dx[k];
						if (iy >= 0 && iy < H && ix >= 0 && ix < W &&
							grid[iy][ix] == BLANK)
						{
							stop = false;              // ������� ������������ ������
							grid[iy][ix] = d + 1;      // �������������� �����
						}
					}
				}
		d++;
	} while (!stop && grid[by][bx] == BLANK);

	if (grid[by][bx] == BLANK) exit(1);  // ���� �� ������

	// �������������� ����
	len = grid[by][bx];            // ����� ����������� ���� �� (ax, ay) � (bx, by)
	x = bx;
	y = by;
	d = len;
	while (d > 0)
	{
		px[d] = x;
		py[d] = y;                   // ���������� ������ (x, y) � ����
		d--;
		for (k = 0; k < 4; ++k)
		{
			int iy = y + dy[k], ix = x + dx[k];
			if (iy >= 0 && iy < H && ix >= 0 && ix < W &&
				grid[iy][ix] == d)
			{
				x = x + dx[k];
				y = y + dy[k];           // ��������� � ������, ������� �� 1 ����� � ������
				break;
			}
		}
	}
	px[0] = ax;
	py[0] = ay;                    // ������ px[0..len] � py[0..len] - ���������� ����� ����
	
    


	int  temp_x = px[0];
	int temp_y = py[0];
	for (int i = 0; i < len; ++i)
	{
		if (px[i] != temp_x)
			move_h.push_back(true);
		else if (py[i] != temp_y)
			move_h.push_back(false);
		temp_x = px[i];
		temp_y = py[i];
	}
	move_h.push_back(0);
}


bool Enemy::wayEnd()
{    
	sf::Vector2f pos = unit.sprite_plate.getPosition();
	 
	if (pos.x== (40*px[len]) &&pos.y == (40*py[len]))
	{
		return true;
	}
	else
	{
		return false;
	}
	

}






void Enemy::make_time()
{

}




Enemy::~Enemy()
{

}

