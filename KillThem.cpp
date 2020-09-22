#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cstdlib>
#include <vector>
#include <string>

int main() {
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(640, 400), "Shooting ball game");
	window.setFramerateLimit(80);

	sf::CircleShape enemy;
	enemy.setFillColor(sf::Color::White);
	enemy.setRadius(30);
	enemy.setPointCount(6);
	enemy.setPosition(sf::Vector2f(270, 0));
	std::vector<sf::CircleShape > enemies;
	int enemyTimer=80;
	int enemyspeed = 1;

	sf::RectangleShape gun(sf::Vector2f(40.f, 60.f));
	gun.setPosition(sf::Vector2f(320.f, 340.f));
	gun.setFillColor(sf::Color::White);
	sf::RectangleShape gunMouth(sf::Vector2f(20.f, 100.f));
	gunMouth.setPosition(sf::Vector2f(330.f,300.f));
	int gunSpeed = 8;


	sf::CircleShape bullet;
	bullet.setFillColor(sf::Color(150, 150, 255, 255));
	bullet.setRadius(12);
	bullet.setPointCount(3);
	bullet.setPosition(sf::Vector2f(328.f, 300.f));
	std::vector<sf::CircleShape> bullets;
	sf::Vector2f bulletpos;
	//bullets.push_back(sf::CircleShape(bullet));
	int shoottimer=60;
	int bulletSpeed=10;
	int points=0;

	sf::Font font;
	font.loadFromFile("Fonts/ponde.ttf");
	if (!font.loadFromFile("Fonts/ponde.ttf")) {
		std::cout << "no fonts" << std::endl;
	}
	sf::Text point;
	point.setFont(font);
	point.setFillColor(sf::Color::White);
	point.setCharacterSize(15);
	point.setString("Points: ");
	point.setPosition(10.f, 10.f);
	
	sf::Text pointss;
	pointss.setFont(font);
	pointss.setFillColor(sf::Color::White);
	pointss.setCharacterSize(15);
	pointss.setPosition(100.f, 9.f);
	pointss.setString(std::to_string(points));
	int gtimer=40;

	sf::Text health;
	health.setFont(font);
	health.setFillColor(sf::Color::White);
	health.setCharacterSize(15);
	health.setPosition(10.f, 380.f);
	health.setString("Health:");

	int health_ps=100;
	sf::Text health_p;
	health_p.setFont(font);
	health_p.setFillColor(sf::Color::White);
	health_p.setCharacterSize(15);
	health_p.setPosition(100.f, 380.f);
	health_p.setString(std::to_string(health_ps));
	int rtimer = 40;

	sf::RectangleShape GameOver(sf::Vector2f(640.f, 400.f));
	GameOver.setFillColor(sf::Color(255, 255, 255, 100));
	sf::Text gameOver;
	gameOver.setFont(font);
	gameOver.setFillColor(sf::Color::Black);
	gameOver.setCharacterSize(24);
	gameOver.setPosition(window.getSize().x/2-100, window.getSize().y/2-40);
	gameOver.setString("GAME OVER");


	sf::Text restart;
	restart.setFont(font);
	restart.setFillColor(sf::Color::Black);
	restart.setCharacterSize(24);
	restart.setPosition(window.getSize().x / 2 - 80, window.getSize().y / 2 );
	restart.setString("RESTART");

	sf::RectangleShape restart_box(sf::Vector2f(140.f,30.f));
	restart_box.setPosition(window.getSize().x / 2 - 85, window.getSize().y / 2);
	restart_box.setFillColor(sf::Color(10, 10, 10, 100));

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		//gun
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && gun.getPosition().x>0) {
			gun.move(-gunSpeed, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && gun.getPosition().x < window.getSize().x - gun.getSize().x) {
			gun.move(gunSpeed, 0);
		}
		gunMouth.setPosition(sf::Vector2f(gun.getPosition().x + 10, gunMouth.getPosition().y));

		//bullets
		bulletpos = sf::Vector2f(gun.getPosition().x + 8.f, 300.f);
		if (shoottimer <60) {
			shoottimer++;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&shoottimer>=10) {
			bullet.setPosition(bulletpos);
			bullets.push_back(sf::CircleShape(bullet));
			shoottimer = 0;
		}

		for (int i = 0; i < bullets.size(); i++) {
			bullets[i].move(0, -bulletSpeed);
			if (bullets[i].getPosition().y <-20) {
				bullets.erase(bullets.begin() + i);
			}
			
		}


		//enemy
		if (enemyTimer < 80) {
			enemyTimer++;
		}
		else {
			enemyTimer = 0;
			enemy.setPosition(rand() % (window.getSize().x)-60, -50.f);
			enemies.push_back(sf::CircleShape(enemy));
		}

		for (int i = 0; i < enemies.size(); i++) {
			enemies[i].move(0, enemyspeed);
			if (enemies[i].getPosition().y > window.getSize().y) {
				enemies.erase(enemies.begin() + i);
			}
		}


		//collosin
		if (gtimer < 40) {
			gtimer++;
		}
		else {
			pointss.setFillColor(sf::Color::White);
			health_p.setFillColor(sf::Color::White);
			gtimer = 0;
		}

		for (int i = 0; i < enemies.size(); i++) {
			if (enemies[i].getGlobalBounds().intersects(gunMouth.getGlobalBounds())) {
				health_ps -= 20;
				health_p.setString(std::to_string(health_ps));
				enemies.erase(enemies.begin() + i);
				health_p.setFillColor(sf::Color::Red);

				break;
			}
		}
		for (int i = 0; i < bullets.size(); i++) {
			for (int j = 0; j < enemies.size(); j++) {
				if (bullets[i].getGlobalBounds().intersects(enemies[j].getGlobalBounds())) {
					bullets.erase(bullets.begin() + i);
					enemies.erase(enemies.begin() + j);
					points++;
					pointss.setString(std::to_string(points));
					pointss.setFillColor(sf::Color::Green);

					
						
					

					break;
				}
			
			}

		}
		

		window.clear(sf::Color(10, 10, 10, 255));
		if (health_ps > 0) {
			for (int i = 0; i < bullets.size(); i++) {
				window.draw(bullets[i]);
			}
			for (int i = 0; i < enemies.size(); i++) {
				window.draw(enemies[i]);
			}
			window.draw(gun);
			window.draw(gunMouth);
			window.draw(point);
			window.draw(pointss);
			window.draw(health);
			window.draw(health_p);
		}
		else {
			window.draw(GameOver);
			window.draw(gameOver);
			window.draw(restart_box);
			window.draw(restart);
		}
		window.display();
	}



	return 0;
}