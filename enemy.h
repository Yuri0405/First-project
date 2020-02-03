#ifndef ENEMY
#define ENEMY
#include <SFML/Graphics.hpp>
#include <array>
#include <string>
#include <vector>
#include "map.h"



class Enemy
{
//private:
public:
bool is_alive = true;
int type;
int len; // ����� ����
int way_count = 0;
float herotime;
float delta;
int counter_of_steps = 0; // ������� �����
std::vector<bool> move_h;
std::array <int,20*20> px,py;
//public:
Plate unit;
Enemy(const std::__cxx11::string namefile);
Enemy() {};
void move(float time,int,float);
void lee(int ax, int ay, int bx, int by);
void make_time();
//bool check();
bool wayEnd();
~Enemy();

public:
    void CheckCollision(std::vector<Enemy> &gameEnemies);
};






#endif