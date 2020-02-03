#include <SFML/Graphics.hpp>
#include "tower.h"
#include "enemy.h"
#include <cmath>
#include <math.h>



using namespace std;




Tower::Tower(const std::__cxx11::string path)
{
    unit.img_plate.loadFromFile(path);
    unit.texture_plate.loadFromImage(unit.img_plate);
    unit.sprite_plate.setTexture(unit.texture_plate);
    //unit.sprite_plate.setTextureRect(sf::IntRect(0, 0, 64, 64));
    //unit.sprite_plate.setColor(sf::Color::Red);

}

Tower::~Tower()
{
    
}

void Tower::Draw(sf::RenderWindow &wd)
{
    unit.sprite_plate.setPosition(pos);
    wd.draw(unit.sprite_plate);
}

void Tower::SetPosition(const sf::Vector2f &Pos)
{
    this->pos = Pos;
}

void Tower::Update()
{

}

bool Tower::EnemyCheck()
{
    return true;
}

void Tower::Attack()
{

}

Enemy Tower::getNearbyEnemy(Enemy& e) const
{
    return  e;
}


Game_Object::Game_Object(int x, int y,int width, int height, std::string Image_Path)
{
    Object_Image.loadFromFile(Image_Path);
    Object_Texture.loadFromImage(Object_Image);
    Object_Sprite.setTexture(Object_Texture);
    Object_Sprite.setTextureRect(sf::IntRect(x,y,width,height));
}

Bullet::Bullet(int x, int y,int width, int height, std::string Image_Path) : Game_Object(x, y, width, height, Image_Path)
{
    Object_Sprite.setOrigin(sf::Vector2f(6, 6));
}

void Bullet::Move(Tower& Tower, Enemy& Foe, std::vector<Enemy> &gameEnemies)
{
    if (timeElpased < 10)
        timeElpased++;

    if (timeElpased >= 10)
    {
        Object_Sprite.setPosition(Tower.unit.sprite_plate.getPosition());
        projectiles.push_back({sf::Sprite(Object_Sprite), sf::Vector2f(1, 1)});

        sf::Vector2f bulletPosition = projectiles.back().Bullet_Sprite.getPosition();
        sf::Vector2f CursorPosition = Foe.unit.sprite_plate.getPosition();
        sf::Vector2f aimDir = CursorPosition - bulletPosition;
        sf::Vector2f aimDirNorm = aimDir / float(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));
        projectiles.back().dir = aimDirNorm;

        timeElpased = 0;

        if (projectiles.size() > 10)
        {
            projectiles.erase(projectiles.begin());
        }
    }

    for (int i = 0; i < projectiles.size(); i++)
    {
        projectiles[i].Bullet_Sprite.move(projectiles[i].dir.x * speed, projectiles[i].dir.y * speed);

        for (int j = 0; j < gameEnemies.size(); j++)
        {
            if (projectiles[i].Bullet_Sprite.getGlobalBounds().intersects(gameEnemies[j].unit.sprite_plate.getGlobalBounds()))
            {
                projectiles.erase(projectiles.begin() + i);
                gameEnemies.erase(gameEnemies.begin() + j);
            }
            
        }
    }
}

void Bullet::Draw(sf::RenderWindow& gameWindow)
{
    for (int i = 0; i < projectiles.size(); i++)
    {
        gameWindow.draw(projectiles[i].Bullet_Sprite);
    }
}


void click_check(sf::Event event,sf::Sprite sprite,sf::Vector2f pos,bool isMove)
{   
   float dx = 0;
   float dy = 0;

   if (event.type == sf::Event::MouseButtonPressed)//если нажата клавиша мыши
    		{
				if (event.key.code == sf::Mouse::Left)//а именно левая
					if (sprite.getGlobalBounds().contains(pos.x, pos.y))//и при этом координата курсора попадает в спрайт
						{
		
							dx = pos.x - sprite.getPosition().x;//делаем разность между позицией курсора и спрайта.для корректировки нажатия
							dx = pos.y - sprite.getPosition().y;//тоже самое по игреку
							isMove = true;//можем двигать спрайт
        							
						}    
      
    		}
}



