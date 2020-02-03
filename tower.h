#include <SFML/Graphics.hpp>
#include "map.h"
#include "enemy.h"
#include <vector>

class Tower
{
    public:
    Tower(const std::__cxx11::string);
    ~Tower();
    void Draw(sf::RenderWindow &wd);
    void SetPosition(const sf::Vector2f &Pos);
    void Update();
    bool EnemyCheck();
    void Attack();
    Enemy getNearbyEnemy(Enemy& e) const;

    Plate unit;
    private:
    sf::Vector2f pos;


};

class Game_Object
{
public:
   Game_Object(int x, int y,int width, int height, std::string Image_Path);

public:
   sf::Sprite Object_Sprite;
   sf::Image Object_Image;
   sf::Texture Object_Texture;

   float timeElpased = 0;
};

struct single_bullet
{
   sf::Sprite Bullet_Sprite;
   sf::Vector2f dir;
};

class Bullet : public Game_Object
{
public:
   Bullet(int x, int y,int width, int height, std::string Image_Path);

   void Move(Tower &Tower, Enemy& Foe, std::vector<Enemy> &gameEnemies);
   void Draw(sf::RenderWindow& gameWindow);

public:
   std::vector <single_bullet> projectiles;

protected:
   static constexpr float speed = 10.f;
};

void click_check(sf::Event event,sf::Sprite,sf::Vector2f,bool);