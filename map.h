#ifndef MAP
#define MAP
#include <SFML/Graphics.hpp>
#include <array>
#include <string>
#include <vector>
//#include "enemy.h"



class Plate
{
public:
int type;
int val = 0;
sf::Image img_plate;
sf::Texture texture_plate;
sf::Sprite sprite_plate;
//Tile(std::__cxx11::string,int);
//sf::Texture make_texture(std::__cxx11::string);
};


class Map
{
private:
    int height = 20;
    int weight = 20;
    //std::array<Plate,20*20> a;
    std::array<int,20*20> scheme;
    std::array<sf::Sprite,20*20> sprites;
    Plate unit;
public:
    std::array<Plate,20*20> a;
    std::vector<sf::Sprite> places;
    sf::Sprite make_plate(int,int,int,std::__cxx11::string);
    sf::Sprite getPlate(int,int);
    bool short_way(int,int,int,int);
    sf::Sprite set_pos(sf::Sprite,float,int);
    //void make_map(int*,std::__cxx11::string,std::__cxx11::string,std::__cxx11::string);
    void nice_place();
    sf::RectangleShape make_panel( const std::__cxx11::string,sf::RectangleShape);
};



#endif