// ConsoleApplication1111111.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//To-do list:
//Use key released to make it so player2 can only shoot in 1 direction at a time
//Use a clock function to make the bullets shoot slower
//Make it so the enemies cannot spawn in an area around the player (Maybe use an invisible circle and record its position?)
//Make it so the enemies follow player 1

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <vector>
#include <math.h>
#include <cstdlib>
using namespace std;
using namespace sf;

class Bullet {
public:
	CircleShape shape;
	Vector2f currVelocity;
	float maxSpeed;


	Bullet(float radius = 5.f)
		: currVelocity(0.f, 0.f), maxSpeed(15.f)
	{
		this->shape.setRadius(radius);
		this->shape.setFillColor(Color::Magenta);
	}
};

int main() {
	srand(time(NULL));
	//Anti-Aliasing
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	//Window
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML reeeet", sf::Style::Default, settings);
	//Variables
	bool up = false; 
	bool up1 = false;
	bool down = false;
	bool down1 = false;
	bool right = false;
	bool right1 = false;
	bool left = false;
	bool left1 = false;
	Clock bulletTime;
	Time bulletTimePassed;
	Clock enemyTime;
	Time enemyTimePassed;

	//Clock
	Time t1 = seconds(0.5);
	bulletTimePassed = bulletTime.getElapsedTime();
	Time t2 = seconds(0.5);
	enemyTimePassed = enemyTime.getElapsedTime();

	//Shapes
	//Player1
	CircleShape player(15.f);
	player.setFillColor(Color::Cyan);
	Vector2f playerCenter;
	Vector2f mousePosWindow;
	Vector2f aimDir;
	Vector2f aimDirNorm;

	//Player2
	sf::CircleShape player2;
	player2.setRadius(10);
	player2.setPosition(0, 0);
	Vector2f playerCenter2;
	Vector2f aimUp;
	Vector2f aimLeft;
	Vector2f aimDown;
	Vector2f aimRight;

	aimUp = Vector2f(0, -0.5f);
	aimLeft = Vector2f(-0.5f, 0.f);
	aimDown = Vector2f(0.f, 0.5f);
	aimRight = Vector2f(0.5f, 0.f);
	
	//Bullets
	Bullet b1;
	Bullet b2;

	vector<Bullet> bullets;
	bullets.push_back(Bullet(b1));
	bullets.push_back(Bullet(b2));

	//Enemy
	RectangleShape enemy;
	enemy.setFillColor(Color::Red);
	enemy.setSize(Vector2f(10.f, 10.f));

	vector<RectangleShape> enemies;
	int spawnCounter = 20;
	///Draw

	//Screen
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			//Player 1 and 2 keypressed
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::D) {
					if (event.key.code == sf::Keyboard::W) {
						up = true;
						//std::cout << "W has been pressed." << std::endl;
					}
					if (event.key.code == sf::Keyboard::A) {
						left = true;
					}
					if (event.key.code == sf::Keyboard::S) {
						down = true;
					}
					if (event.key.code == sf::Keyboard::D) {
						right = true;
					}
				}
				else
				{
					if (event.key.code == sf::Keyboard::Up) {
						up1 = true;
					}
					if (event.key.code == sf::Keyboard::Left) {
						left1 = true;
					}
					if (event.key.code == sf::Keyboard::Down) {
						down1 = true;
					}
					if (event.key.code == sf::Keyboard::Right) {
						right1 = true;
					}
				}
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::W) {
					up = false;
				}
				if (event.key.code == sf::Keyboard::A) {
					left = false;
				}
				if (event.key.code == sf::Keyboard::S) {
					down = false;
				}
				if (event.key.code == sf::Keyboard::D) {
					right = false;
				}
				if (event.key.code == sf::Keyboard::Up) {
					up1 = false;
				}
				if (event.key.code == sf::Keyboard::Left) {
					left1 = false;
				}
				if (event.key.code == sf::Keyboard::Down) {
					down1 = false;
				}
				if (event.key.code == sf::Keyboard::Right) {
					right1 = false;
				}
			}
		}
	//Player 1 movements
	sf::Vector2f movement1(0, 0);
		if (up1)
			movement1.y -= 0.5f;
		if (left1)
			movement1.x -= 0.5f;
		if (down1)
			movement1.y += 0.5f;
		if (right1)
			movement1.x += 0.5f;
	//Player 2 movements
	sf::Vector2f movement2(0, 0);
		if (up)
			movement2.y -= 0.8f;
		if (left)
			movement2.x -= 0.8f;
		if (down)
			movement2.y += 0.8f;
		if (right)
			movement2.x += 0.8f;


		//Update
			//Enemies
		if (spawnCounter < 20)
			spawnCounter++;

		if (spawnCounter >= 20 && enemies.size() < 50)
		{
			enemy.setPosition(Vector2f(rand() % window.getSize().x, rand() % window.getSize().y));
			enemies.push_back(RectangleShape(enemy));
		}

			//Shooting
		///Shooting Player2
		if (Keyboard::isKeyPressed(Keyboard::U))
		{
			if (bulletTimePassed.asSeconds() >= t1.asSeconds())
			{
				b1.shape.setPosition(playerCenter);
					
				b1.shape.setPosition(playerCenter2);
				b1.currVelocity = aimUp * b1.maxSpeed;

				bullets.push_back(Bullet(b1));
				bulletTime.restart();
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::H))
		{
			b1.shape.setPosition(playerCenter2);
			b1.currVelocity = aimLeft * b1.maxSpeed;

			bullets.push_back(Bullet(b1));

		}
		if (Keyboard::isKeyPressed(Keyboard::J))
		{
			b1.shape.setPosition(playerCenter2);
			b1.currVelocity = aimDown * b1.maxSpeed;

			bullets.push_back(Bullet(b1));

		}
		if (Keyboard::isKeyPressed(Keyboard::K))
		{
			b1.shape.setPosition(playerCenter2);
			b1.currVelocity = aimRight * b1.maxSpeed;

			bullets.push_back(Bullet(b1));

		}
		///Shooting Player1
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (bulletTimePassed.asSeconds() >= t1.asSeconds())
			{

				b1.shape.setPosition(playerCenter);
				b1.currVelocity = aimDirNorm * b1.maxSpeed;

				bullets.push_back(Bullet(b1));
				bulletTime.restart();
			}
		}

		for (size_t i = 0; i < bullets.size(); i++)
		{
			bullets[i].shape.move(bullets[i].currVelocity);

			//Out of bounds
			if ((bullets[i].shape.getPosition().x < 0 || bullets[i].shape.getPosition().x > window.getSize().x) || (bullets[i].shape.getPosition().y < 0 || bullets[i].shape.getPosition().y > window.getSize().y))
			{
				bullets.erase(bullets.begin() + i);
				
			}
			else
			{
				//Enemy collision
				for (size_t k = 0; k < enemies.size(); k++)
				{
					if (bullets[i].shape.getGlobalBounds().intersects(enemies[k].getGlobalBounds()))
					{
						bullets.erase(bullets.begin() + i);
						enemies.erase(enemies.begin() + k);
						break;
					}
					else if (player2.getGlobalBounds().intersects(enemies[k].getGlobalBounds()))
					{
						enemies.erase(enemies.begin() + k);
					}
					else if (player.getGlobalBounds().intersects(enemies[k].getGlobalBounds()))
					{
						window.close();
						cout << "lol get rekt" << "\n";
					}
				}
			}
		}

		//Vectors
		playerCenter = Vector2f(player.getPosition().x + player.getRadius(), player.getPosition().y + player.getRadius());
		playerCenter2 = Vector2f(player2.getPosition().x + player2.getRadius(), player2.getPosition().y + player2.getRadius());
		mousePosWindow = Vector2f(Mouse::getPosition(window));
		aimDir = mousePosWindow - playerCenter;
		aimDirNorm = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));

		cout << aimDirNorm.x << " " << aimDirNorm.y << '\n';

		//Player
		//if(Keyboard::isKeyPressed(Keyboard::A))
			//player.move(-10.f, 0f)
		
		//Draw
		window.clear();
		player2.move(movement2);
		player.move(movement1);
		window.draw(player2);
		window.draw(player);

		for (size_t i = 0; i < enemies.size(); i++)
		{
			window.draw(enemies[i]);
		}
		

		for (size_t i = 0; i < bullets.size(); i++)
		{
			window.draw(bullets[i].shape);
		}

		window.display();

		//cout << "Hello World!\n";
	}
	return 0;
}
	
		


		




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
