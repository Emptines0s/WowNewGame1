#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>
#include "Unit.h"
#include "Player.h"
#include "Enemy.h"
#include "Environment.h"
#include "Item.h"
#include "Projectile.h"
#include "Inventory.h"
#include "CollisionCheck.h"
#include "RenderLayers.h"
#include "RoomsGenerator.h"

int main()
{
	srand(time(0));
	//Create Window
	sf::View view(sf::FloatRect(800, 600, 800, 600));
	sf::RenderWindow window(sf::VideoMode(800, 600), "MYGAMES", sf::Style::Close);
	window.setFramerateLimit(180);
	sf::Clock clock;
	// Create Image/Texture for Objects
	sf::Image hero;
	hero.loadFromFile("images/Hero.png");
	hero.createMaskFromColor(sf::Color::White);
	sf::Image enemy1;
	enemy1.loadFromFile("images/Bullet2.png");
	sf::Image slime;
	slime.loadFromFile("images/Slime.png");
	slime.createMaskFromColor(sf::Color::White);
	sf::Image background;
	background.loadFromFile("images/background.jpg");
	sf::Texture bk;
	bk.loadFromImage(background);
	sf::Image inventory_image;
	inventory_image.loadFromFile("images/background.jpg");
	sf::Image slots_image;
	slots_image.loadFromFile("images/slots.png");
	sf::Image staff_image;
	staff_image.loadFromFile("images/EmeraldStaff.png");
	staff_image.createMaskFromColor(sf::Color::White);
	sf::Image EmeraldPr_image;
	EmeraldPr_image.loadFromFile("images/EmeraldPr.png");
	EmeraldPr_image.createMaskFromColor(sf::Color::White);
	sf::Image armor_image;
	armor_image.loadFromFile("images/Armor.png");
	armor_image.createMaskFromColor(sf::Color::White);
	sf::Image wall_image;
	wall_image.loadFromFile("images/Wall.png");
	sf::Image door_image;
	door_image.loadFromFile("images/Door.png");
	sf::Image ground_image;
	ground_image.loadFromFile("images/Ground.png");
	sf::Texture ground_texture;
	ground_texture.loadFromImage(ground_image);
	sf::Sprite ground_sprite;
	ground_sprite.setTexture(ground_texture);

	//Game modules
	RenderLayers renderlayers;
	CollisionCheck collisioncheck;
	RoomsGenerator roomsgenerator;
	
	sf::Vector2f player_position;
	int player_hp;

	// Objects containers
	vector < vector <char> > Room;
	list <Unit*> unit;
	list <Unit*>::iterator obj1;
	list <Unit*>::iterator obj2;
	unit.push_back(new Player ("player", 20, 50, sf::Vector2f(200, 200), hero));
	Inventory inventory(false, inventory_image, slots_image, unit.back());
	
	// Create start items and start Rooms variable
	unit.push_back(new Item("staff", 545, 1, sf::Vector2f(50, 50), staff_image, Item::WEAPON , 1, true));
	unit.push_back(new Item("helmet", 456, 5, sf::Vector2f(50, 100), enemy1, Item::HELMET, 2, true));
	unit.push_back(new Item("boots", 999, 5, sf::Vector2f(50, 150), enemy1, Item::BOOTS, 3, true));
	unit.push_back(new Item("armor", 999, 15, sf::Vector2f(50, 220), armor_image, Item::CHEAST, 4, true));
	bool nextRoom = true;
	int enemyCount = 0;
	
	// Game loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Game logic time lock
		sf::Time time = clock.getElapsedTime();
		clock.restart();

		sf::Vector2f c_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);
		//std::cout << c_pos.x << "  |  " << c_pos.y << "\n";
		//std::cout << player_position.x << "  p|p  " << player_position.y << "\n";

		view.setCenter(player_position);

		// Generate New Room
		if ( nextRoom == true )
		{
			for (obj1 = unit.begin(); obj1 != unit.end();)
			{
				Unit* b = *obj1;
				if ((*obj1)->name == "Wall" || (*obj1)->name == "Door" || (*obj1)->name == "Ground")
				{
					obj1 = unit.erase(obj1);
					delete b;
				}
				else obj1++;
			}

			Room.clear();

			roomsgenerator.Generate(Room);

			for (int i = 0; i < roomsgenerator.room_height; i++) {
				for (int j = 0; j < roomsgenerator.room_width; j++)
				{
					if (Room[i][j] == 'W') unit.push_back(new Environment("Wall", 0, 1, sf::Vector2f(50 * j, 50 * i), wall_image, false));
					if (Room[i][j] == 'G') unit.push_back(new Environment("Ground", 0, 1, sf::Vector2f(50 * j, 50 * i), ground_image, false));
					if (Room[i][j] == 'S')
					{
						unit.push_back(new Environment("Ground", 0, 1, sf::Vector2f(50 * j, 50 * i), ground_image, false));
						unit.push_back(new Slime("slime", 1, 2, sf::Vector2f(50 * j, 50 * i), slime, 1));
					}
					if (Room[i][j] == 'D') unit.push_back(new Environment("Door", 0, 1, sf::Vector2f(50 * j, 50 * i), door_image, false));
				}
			}
			nextRoom = false;
		}

		enemyCount = 0;
		
		// Unit Update
		for (obj1 = unit.begin(); obj1 != unit.end();)
		{
			Unit* b = *obj1;
			if ((*obj1)->name == "player")
			{
				player_position = (*obj1)->pos;
				player_hp = (*obj1)->hp;
			}
			if ((*obj1)->name == "slime") enemyCount += 1;
			(*obj1)->update(time);
			(*obj1)->update(time, player_position);
			if ((*obj1)->hp <= 0)
			{
				obj1 = unit.erase(obj1);
				delete b;
			}
			else obj1++;
		}

		// Using Items (Attack)
		for (auto item : inventory.InventoryItemList)
		{
			if (item->state == 5 && item->name == "staff") unit.push_back(new Projectile("EmeraldStaff_Projectile", 1, 1, player_position, EmeraldPr_image, c_pos));
		}

		// Game modules update
		inventory.update(time, window);
		window.setView(view);
		collisioncheck.Collision(inventory.InventoryItemList, unit, obj1, obj2, window, nextRoom, time, enemyCount);
		renderlayers.Render(inventory, inventory.InventoryItemList, unit, obj1, obj2, window, player_hp);
		window.display();
		window.clear();
	}
}