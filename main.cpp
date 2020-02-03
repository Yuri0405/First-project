#include <iostream>
#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <string>
#include "map.h"
#include "enemy.h"
#include "tower.h"
using namespace std;
using namespace sf;



int main()
{
	
	int scheme[20][20] = {
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
	};

    Map field;
	string namefile = "Textures/Enemy.png";
	string plate_wall = "Textures/Plate_wall.png";
	string plate_way = "Textures/Plate_way.png";
	string plate_tower = "Textures/Plate_tower.png";
    
    int way_count;
	int enim_count;
	bool isMove;
	bool stand;
	float dx = 0;
	float dy = 0;
	float dx1 = 0;
	float dy1 = 0;
	float sx;
	float sy;

sf::RenderWindow window(sf::VideoMode(1430, 850), "laba");

	window.setFramerateLimit(60);


	  
    Enemy creep(namefile);
	creep.unit.sprite_plate.setPosition(40,40); 
	creep.lee(1, 1, 18, 18);

    std::vector<Enemy> creeps;
	std::vector<Tower> towers;
	

    Bullet bullet(0, 0, 40, 40, "textures/Bullet.png");//// construct bullet
	Tower twr("textures/tower.png");
	twr.SetPosition({520,360});
    

    

		
	float herotime = 0;
	float spawn_time = 0;
	Clock clock;
	Clock enim_clock;	
	
	while (window.isOpen())
	{
		
		//tower_menu(window,"textures/tower.png");
		float time = clock.getElapsedTime().asMicroseconds();
		float enim_time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		enim_clock.restart();
		time = time/800;
		enim_time = enim_time/800;

		herotime += time;
		spawn_time += enim_time;



		sf::Image image;
    	sf::Texture texture;
    	sf::Sprite sprite;


		image.loadFromFile("textures/tower.png");
    	texture.loadFromImage(image);
    	sprite.setTexture(texture);
    	sprite.setPosition(920,200);

       
		
		
		Vector2i pixelPos = Mouse::getPosition(window);
		Vector2f pos = window.mapPixelToCoords(pixelPos);

		
        

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed){
				window.close();
			}
            /* 
            if (event.type == sf::Event::MouseButtonPressed)//если нажата клавиша мыши
    		{
				if (event.key.code == sf::Mouse::Left)//а именно левая
					if (sprite.getGlobalBounds().contains(pos.x, pos.y))//и при этом координата курсора попадает в спрайт
						{
		
							dx = pos.x - sprite.getPosition().x;//делаем разность между позицией курсора и спрайта.для корректировки нажатия
							dy = pos.y - sprite.getPosition().y;//тоже самое по игреку
							isMove = true;//можем двигать спрайт
        							
						}    
      
    		
			}
             */
			if (event.type == sf::Event::MouseButtonPressed)//если нажата клавиша мыши
    		{
				if (event.key.code == sf::Mouse::Left)//а именно левая
					{
						for(auto& it : field.places)
						{
							if (it.getGlobalBounds().contains(pos.x, pos.y))//и при этом координата курсора попадает в спрайт
							{
		
								dx1 = pos.x - it.getPosition().x;//делаем разность между позицией курсора и спрайта.для корректировки нажатия
								dy1 = pos.y - it.getPosition().y;//тоже самое по игреку
							    sx = it.getPosition().x;
								sy = it.getPosition().y;
                                
                                twr.SetPosition({sx,sy});

                                towers.push_back(twr);
									
								


								stand = true;
        							
							}
							
						}
					}
      
    		
			}
			
            
            
			
		}
        if (isMove)
		{
			sprite.setColor(Color::Green);
			
		}
    
		
		

		window.clear();
        
        //tower_menu(window,"textures/tower.png",event,pos);


        if (spawn_time>1000)
			{
				creeps.push_back(creep);
				//cout<<"FUCK";
				spawn_time = 0;
			}
  

        for (int i = 0; i < 20; i++)
        {
			for (int j = 0; j < 20; j++)
			{  
               
				if (scheme[i][j] == 0)
				{
					field.make_plate(i, j, scheme[i][j], plate_wall);
				}

				if (scheme[i][j] == 1)
				{
					field.make_plate(i, j, scheme[i][j], plate_way);
				}

				if (scheme[i][j] == 2)
				{
					field.make_plate(i, j, scheme[i][j], plate_tower);
				}
                 
				
			     window.draw(field.getPlate(i,j));
			   }
               	
			}  
           
		   field.nice_place();
		   window.draw(sprite);
		
		 for(auto& it : creeps)
        	{   //cout<<"I’m working"<<endl;
            	if(it.wayEnd())
            		{   
                		creeps.erase(creeps.begin());
					
            		}
        	}
				
                
		for(auto& it : creeps)
			{
				it.move(time,way_count,herotime);
				window.draw(it.unit.sprite_plate);
			}
			

	    for(auto& it : towers)
		{
				it.Draw(window);
			//TOWERS
			if (it.EnemyCheck()) //make enemy check func
			{
				bullet.Move(it, creeps[0], creeps);
				bullet.Draw(window);
			}
		}

				
			/* 	
			twr.Draw(window);
			//TOWERS
			if (twr.EnemyCheck()) //make enemy check func
			{
				bullet.Move(twr, creeps[0], creeps);
				bullet.Draw(window);
			}
			*/
            
		

			window.display();
        }
		


		return 0;
	}

