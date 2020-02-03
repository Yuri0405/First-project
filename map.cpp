#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <string>
#include <math.h>
#include "map.h"
#include "enemy.h"


using namespace sf;
using namespace std;


sf::Sprite Map:: make_plate(int i,int j,int type,std::__cxx11::string namefile)
{  
   a[i*20+j].img_plate.loadFromFile(namefile);
   a[i*20+j].texture_plate.loadFromImage(a[i*20+j].img_plate);
   sprites[i*20+j].setTexture(a[i*20+j].texture_plate);
   sprites[i*20+j].setPosition(i*40,j*40);
  // a[i*20+j].sprite_plate.setTexture(a[i*20+j].texture_plate);
  // a[i*20+j].sprite_plate.setPosition(i*40,j*40);
   if (type==1)
   {
      a[i*20+j].type = 1;
   }
   else if ( type == 0 )
   {
      a[i*20+j].type = 0;
   }
   else if (type == 1)
   {
      a[i*20+j].type = 1;
   }
   else if (type == 2)
   {
      a[i*20+j].type = 2;
   }
   
   
   
   return  sprites[i*20+j];
}

sf::Sprite Map::getPlate(int i,int j)
{
	//return sprites[i*20+j];
   return sprites[i*20+j];
}


void Map::nice_place()
{
   
   std::vector<int> numberRoad;
   std::vector<int> numberGrass;
   std::vector<int> value;
    float size = 0;
    int xR = 0;
    int yR = 0;
    int xG = 0;
    int yG = 0;
    int count = 0;
    for (int i = 0; i < 400; i++)
    {
        switch (a[i].type)
        {
        case 2:
            numberGrass.push_back(i);
            break;
        case 1:
            numberRoad.push_back(i);
            break;
        default:
            break;
        }
    }
    for(int n = 0; n < numberGrass.size(); n++)
    {
        value.push_back(0);
        value[n] = 0;
       for(int m = 0; m < numberRoad.size(); m++)
        {
            xG = numberGrass[n]%20;
            yG = (numberGrass[n] - numberGrass[n]%20)/20;
            xR = numberRoad[m]%20;
            yR = (numberRoad[m] - numberRoad[m]%20)/20;
            if(sqrt((xG-xR)*(xG-xR)+(yG-yR)*(yG-yR)) < 2.8)
            {
                value[n]++;
            }
        }    
    }
    for (int i = 0; i < numberGrass.size(); ++i) 
    {
        int help = 0;
        for (int j =  0; j < numberGrass.size()-1; j++) 
        {
            if (value[j] < value[j+1]) 
            {
                help = value[j];
                value[j] = value[j+1];
                value[j+1] = help;
                help = numberGrass[j];
                numberGrass[j] = numberGrass[j+1];
                numberGrass[j+1] = help;
            }
        }
    }
    for (int j = 0; j <  10; j++) 
    {
        sprites[numberGrass[j]].setColor(sf::Color(12*j,128+12*j,0,255));
        places.push_back(sprites[numberGrass[j]]);
    }
    
}


sf::RectangleShape Map::make_panel(const std::__cxx11::string path,sf::RectangleShape rectangle)
{
    //unit.img_plate.loadFromFile(path);
    //unit.texture_plate.loadFromImage(unit.img_plate);
    rectangle.setFillColor(sf::Color(15,200,0,255));
    rectangle.setTexture(&unit.texture_plate);
    rectangle.setPosition(sf::Vector2f(805, 0));
    return rectangle;
}






