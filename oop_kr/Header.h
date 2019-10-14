#pragma once
#pragma warning(disable : 4996)

#define WW 1180		//������ ������
#define WH 664		//������ ������
#define BGW 2360	//������ ����
#define BFS 1		//�������� ���� 

using namespace sf;	//������������� ������������ ���� sf

bool collision = false;	//���� �������
bool show_ship = true;	//���� ������ ������
bool isGame = true;		//���� ���
bool isMenu = true;		//���� ����
bool isCaption = true;	//���� �����
bool show_info = false;	//���� ����������
bool isClose = false;	//���� �������� ���

class Ship;			//���� �������� ������
class Pilot;		//����� �����

class Player		//���� ������
{
public:
	int score = 0;	//�������
	int health = 2;	//ʳ������ �����
};

class Graphics		//���� �������
{
public:
	float current_Frame = 0;	//����� �����
	Texture texture;			//��������
	Sprite sprite;				//������
	virtual void update(Player &player, Ship &ship, Pilot &pilot, float time, float speed, float fspeed) = 0;	//��������� ������� �������� �����
};

class Ship : public Graphics	//���� �������� ������
{
public:
	int x;						//���������� �
	int y;						//���������� �
	int width;					//������ �������
	int heith;					//������ �������
	Texture booster_texture;	//�������� �������
	Sprite booster1_sprite;		//������ ������� �������
	Sprite booster2_sprite;		//������ ������� �������
	void update(Player &player, Ship &ship, Pilot &pilot, float time, float speed, float fspeed)		//������� �������� �����
	{
		x = sprite.getPosition().x;					//��������� ��������� �
		y = sprite.getPosition().y;					//��������� ��������� �
		//�������
		if (Keyboard::isKeyPressed(Keyboard::Down))	//���������� ����
		{
			if (y < WH - heith - 40)				//�������� ���������� ������� �������� ����
			{
				sprite.move(0, 0.2*time);			//���������� ������� �������
				booster1_sprite.move(0, 0.2*time);	//���������� ������� �������
				booster2_sprite.move(0, 0.2*time);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))	//���������� ����
		{
			if (y > 80)								//�������� ���������� ������� �������� ����
			{
				sprite.move(0, -0.2*time);			//���������� ������� �������
				booster1_sprite.move(0, -0.2*time);	//���������� ������� �������
				booster2_sprite.move(0, -0.2*time);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Left))	//���������� ����
		{	
			if (x > 100 - heith)					//�������� ���������� ������� �������� ����
			{

				sprite.move(-0.2*time, 0);			//���������� ������� �������
				booster1_sprite.move(-0.2*time, 0);	//���������� ������� �������
				booster2_sprite.move(-0.2*time, 0);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))//���������� ����
		{
			if (x < WW - width - 300)				//�������� ���������� ������� �������� ����
			{
				sprite.move(0.2*time, 0);			//���������� ������� �������
				booster1_sprite.move(0.2*time, 0);	//���������� ������� �������
				booster2_sprite.move(0.2*time, 0);
			}
		}

		current_Frame += 0.005*time;				//���� �����
		booster1_sprite.setTextureRect(IntRect(30 * int(current_Frame), 0, 30, 11));	//���� ������� �������
		booster2_sprite.setTextureRect(IntRect(30 * int(current_Frame), 11, 30, -11));
		if (current_Frame > 4)						//���� �����
		{
			current_Frame -= 4;						//�� ��������� ��������
		}
	}
	
	Ship()						//����������� �������
	{
		x = 100;												//��������� ���������� �
		y = 292;												//��������� ���������� �
		width = 70;												//������ �������
		heith = 50;												//������ �������
		texture.loadFromFile("images/ship.png");				//�������� �������� � �����
		sprite.setTexture(texture);								//������������ �������� �� ������
		sprite.setTextureRect(IntRect(0, 0, width, heith));		//������� �������
		sprite.setPosition(x, y);								//���������� �������
		booster_texture.loadFromFile("images/booster.png");		//�������� �������� � �����
		booster1_sprite.setTexture(booster_texture);			//������������ �������� �� ������
		booster1_sprite.setTextureRect(IntRect(0, 0, 30, 11));	//������� �������
		booster1_sprite.setPosition(x - 18, y + 14);			//���������� �������
		booster2_sprite.setTexture(booster_texture);			//������������ �������� �� ������
		booster2_sprite.setTextureRect(IntRect(0, 11, 30, -11));//������� �������
		booster2_sprite.setPosition(x - 18, y + 25);			//���������� �������
	}
};

class Pilot : public Ship		//����� �����
{
public:
	Pilot()
	{
		width = 34;										//������ �������
		heith = 50;										//������ �������
		texture.loadFromFile("images/pilot.png");		//�������� �������� � �����
		sprite.setTexture(texture);						//������������ �������� �� ������
		sprite.setTextureRect(IntRect(0, 0, 34, 50));	//������� �������
	}
};

class Backgound : public Graphics	//����� ����
{
public:
	Backgound(std::string source)	//����������� ����
	{
		texture.loadFromFile(source);					//�������� �������� � �����
		sprite.setTexture(texture);						//������������ �������� �� ������
		sprite.setTextureRect(IntRect(0, 0, BGW, WH));	//������� �������
		sprite.setPosition(0, 0);						//���������� �������
	}
	void update(Player &player, Ship &ship, Pilot &pilot, float time, float speed, float fspeed)	//��������� ����� ����
	{
		sprite.move(-speed * time * fspeed, 0);			//������ ����
		if (sprite.getPosition().x < -WW)				//�������� ���� �������
			sprite.setPosition(0, 0);					//�� ������� �������
	}
};

class Asteroids : public Graphics	//����� ��������
{
public:
	int width;												//������ �������
	int heith;												//������ �������
	Asteroids()												//����������� �������
	{
		width = 100;										//������ �������
		heith = 100;										//������ �������
		texture.loadFromFile("images/Asteroid.png");		//�������� �������� � �����
		sprite.setTexture(texture);							//������������ �������� �� ������
		sprite.setTextureRect(IntRect(0, 0, width, heith));	//���������� �������
	}
};

class Asteroid : public Asteroids	//����� �������
{
public:
	int x;											//��������� �
	int y;											//��������� �
	Asteroid(int y)									//����������� ��������
	{
		sprite.setPosition(1180, y);				//������������ �� ���������� �
	}
	void update(Player &player, Ship &ship, Pilot &pilot, float time, float speed, float fspeed)						//��������� �����
	{
		x = sprite.getPosition().x;					//��������� ���������� �
		y = sprite.getPosition().y;					//��������� ���������� �
		sprite.move(-1*time, 0);					//�������
		if (x < -width)					//�������� ���� �������
		{
			sprite.setPosition(1180, rand() % 564);	//���� ������� ��������
			player.score++;							//��������� ������� ������ 
		}
	}
};

class Explosion : public Graphics, Player	//����� ������
{
public:
	Explosion()											//����������� ������
	{
		texture.loadFromFile("images/explosion.png");	//�������� �������� � �����
		sprite.setTexture(texture);						//������������ �������� �� ������
		sprite.setTextureRect(IntRect(0, 0, 100, 100));	//���������� �������
	}
	void update(Player &player, Ship &ship, Pilot &pilot, float time, float speed, float fspeed)		//��������� �����
	{

		current_Frame += 0.005*time;							//���� �����
		if (collision == 1)										//�������� �� �������� ������������
		{
			ship.sprite.setTexture(pilot.texture);				//������������ ���� �������� �������
			ship.sprite.setTextureRect(IntRect(0, 0, 34, 50));	//
		}

		if (current_Frame > 3 && player.health)					//�������� �� ����� �������� ��������
		{
			show_ship = true;
		}

		if (current_Frame > 11 && collision == true)			//�������� ���� ������� ������
		{
			collision = false;									//����� �������
			if (player.health == 0)								//�������� ���� ���
			{
				isGame = false;
			}
		}
		sprite.setTextureRect(IntRect(100 * int(current_Frame), 0, 100, 100));	//���� �����
	}
};

bool manage_collision(Ship &ship, Asteroid &asteroid)	//�������� �����������
{
	//�������� �� �� ������������ ������� ������� � ��������
	return ((ship.y > (asteroid.y + asteroid.heith) || (ship.y + ship.heith) < asteroid.y) || ((ship.x + ship.width - 40) < asteroid.x || ship.x > (asteroid.x + asteroid.width)));
}

void update_version(Graphics &derived, Player &player, Ship &ship, Pilot &pilot, float time = 0, float speed = 0, float fspeed = 0)	//������� ����� ��� ��������� ������ update ���� �������� 
{
	derived.update(player, ship, pilot, time, speed, fspeed);
}

int game(RenderWindow &window)
{
	//��������� �����������
	Font font;								//��'��� �����
	font.loadFromFile("fonts/ARIALUNI.TTF");//������������ ������ � �����
	//���������� ��� ������� �����
	Text health("", font, 20);				//��'��� �����
	health.setColor(Color::White);			//���� ������ ����
	health.setStyle(Text::Bold);			//����� ������ ������
	health.setPosition(10, 10);				//������� ������
	//���������� ��� �������
	Text score("", font, 20);				//��'��� �����
	score.setColor(Color::White);			//���� ������ ����
	score.setStyle(Text::Bold);				//����� ������ ������
	score.setPosition(150, 10);				//������� ������

	//����� ��'����
	Player player;									//����������� ������
	Backgound background("images/background.png");	//����������� ���� � ���������� ���� � ����� ����� ������������� ��������
	Ship ship;										//����������� �������
	Asteroid asteroid(rand() % 564);				//����������� �������� � ���������� ���������� �
	Explosion explosion;							//����������� ������
	Pilot pilot;									//����������� �����
	Clock clock;									//����������� ��������

	while (isGame)	//���� ���
	{
		//��� �� ������� �����
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		//�������� ���
		time = time / 1000;

		//���� ��������� ����� ��'����
		update_version(background, player, ship, pilot, time, 0.1, 5);	//��������� ���� ����
		update_version(ship, player, ship, pilot, time);		//��������� ���� ������
		update_version(asteroid, player, ship, pilot, time);	//��������� ���� ��������
		update_version(explosion, player, ship, pilot, time);	//��������� ���� ������
		//����� ����� ��������� ����� ��'����

		//���� ������� �� �����
		window.clear();					//�������� �����
		window.draw(background.sprite);	//������� ���
		window.draw(asteroid.sprite);	//������� �������

		if (show_ship)					//�������� �� ����� �������� ������
			window.draw(ship.sprite);	//�������� ��������, ���� �����

		if (!manage_collision(ship, asteroid) || collision == 1) //�������� �������
		{
			if (collision == 0)		//���� ������� �� �� ����������
			{
				player.health--;			//�������� ����� ����������
				show_ship = 0;				//�� ������� ������
				explosion.current_Frame = 0;//���� ������ �������� 
			}
			collision = 1;											//�������� �������� 
			explosion.sprite.setPosition(ship.x - 40, ship.y - 25); //��������� ������
			window.draw(explosion.sprite);							//������� �����
		}
		else if (show_ship)//���� �������� �� �������� � ������� ����������
		{
			window.draw(ship.booster1_sprite);					//������� ���� �� �������
			window.draw(ship.booster2_sprite);					//������� ���� �� �������
		}

		//�������� ���������� ��� ������
		std::ostringstream player_health;								//����� ���������� ��� ������
		player_health << player.health;									//�������� ���������� � �����
		health.setString("Health: " + player_health.str());				//������� ������
		window.draw(health);

		std::ostringstream player_score;					//����� ���������� ��� �������
		player_score << player.score;						//�������� ���������� � �����
		score.setString("Score: " + player_score.str());	//������� ������
		window.draw(score);									//�������� �������
		window.display();									//�������� ����
		//����� ����� ������� �� �����
	}
	return player.score;	//��������� ��������� �������
}

void menu(RenderWindow &window)
{
	Player player; 
	Ship ship;
	Pilot pilot1;
	Clock clock;																	//����������� ��������
	Texture menuTexture1, menuTexture2, menuTexture3, infoTexture, pilotTexture;	//�������� ����� ���� � �����
	menuTexture1.loadFromFile("images/111.png");									//����������� �������� � �����
	menuTexture2.loadFromFile("images/222.png");									//����������� �������� � �����
	menuTexture3.loadFromFile("images/333.png");									//����������� �������� � �����
	infoTexture.loadFromFile("images/info.png");									//����������� �������� � �����
	pilotTexture.loadFromFile("images/pilot_menu.png");								//����������� �������� � �����
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), info(infoTexture), pilot(pilotTexture);	//������������ ������� � ����������� ����������
	Backgound background("images/background_menu.png");								//����������� ���� � ���������� ���� � ����� ����� ������������� ��������
	int menuNum = 0;					//����� ���� �� ��� �������� ������
	menu1.setPosition(440, 200);		//������� ����� 
	menu2.setPosition(270, 300);		//������� ����� 
	menu3.setPosition(510, 400);		//������� ����� 
	info.setPosition(265, 132);			//������� ���������� ��� ������
	pilot.setPosition(100, 200);		//������� �����
	while (isMenu)		//���� ����
	{
		//��� �� ������� �����
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		//�������� ���
		time = time / 1000;


		menu1.setColor(Color::White);	//���� ������� �� ���������� ����
		menu2.setColor(Color::White);	//���� ������� �� ���������� ����
		menu3.setColor(Color::White);	//���� ������� �� ���������� ����
		menuNum = 0;					//�������� �������� ������ �� ���������� 

		window.clear();						//�������� �����
		update_version(background, player, ship, pilot1, time, 0.1, BFS);	//��������� ���� ����
		window.draw(background.sprite);		//������� ���
		if (!show_info)		//�������� �� �� ����� �������� ���������� ��� ������
		{
			//���� ������ �� ����� ���� �������� ��� ����� ���� � ������� �������� �������� �����
			if (IntRect(440, 200, 299, 54).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }	
			if (IntRect(270, 300, 640, 53).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }
			if (IntRect(510, 400, 149, 51).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }

			if (Mouse::isButtonPressed(Mouse::Left))	//���� ��������� ��� ������ ���� 
			{
				//���������� �� ��� ��� ����� ������� ������ ����� ����
				if (menuNum == 1) isMenu = false;						//���� ������� ������ �����, ��������� ����		
				if (menuNum == 2) show_info = true;						//���� ������� ������ �����, �������� ���������� ��� ������
				if (menuNum == 3) { isClose = true; isMenu = false; }	//���� ������� ����� �����, ��������� ����
			}

			window.draw(pilot);		//������� ������ �����

			//������� ������� ����� ����
			window.draw(menu1);		
			window.draw(menu2);
			window.draw(menu3);
		}
		else	//���� ����� �������� ���������� ��� ������
		{
			if (Keyboard::isKeyPressed(Keyboard::Escape))	//���� ��������� ������ Esc, �� �������� ���������� ��� ������
				show_info = false;						
			window.draw(info);								//�������� ���������� ��� ������
		}
		window.display();									//�������� ����
	}
}

void caption(RenderWindow &window, int player_score)
{
	Player player;
	Ship ship;
	Pilot pilot;
	Clock clock;												//����������� ��������
	Font font;													//����������� ������
	font.loadFromFile("fonts/ARIALUNI.TTF");					//����������� ����� �� �����
	Text score("", font, 50);									//����������� ������ � ����������� ����������, ������ � ������ ����

	Color color(41,112,61,255);									//����������� ������� � ����������� RGBA
	score.setColor(color);										//������������ ���� ������
	score.setStyle(Text::Bold);									//������������ ����� ������
	score.setPosition(395, 330);								//������������ ������� ������
	std::ostringstream player_score_stream;						//����� ���������� ��� �������
	player_score_stream << player_score;						//�������� ���������� � �����
	score.setString("Score: " + player_score_stream.str());		//������� ������

	Texture infoTexture;										//����������� �������� ���������� ��� ������
	infoTexture.loadFromFile("images/info.png");				//����������� �������� � �����
	Sprite info(infoTexture);									//����������� ������� � ���������� ���������
	info.setPosition(265, 132);									//������� �������

	Backgound background("images/background_menu.png");			//����������� ���� � ���������� ���� � ����� ����� ������������� ��������

	while (isCaption)	//���� ��������
	{
		//��� �� ������� �����
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		//�������� ���
		time = time / 1000;

		window.clear();									//�������� �����
		update_version(background, player, ship, pilot, time, 0.1, BFS);				//��������� ���� ����
		window.draw(background.sprite);					//�������� ���
		window.draw(info);								//�������� ���������� ��� ������
		window.draw(score);								//�������� ��������� �������
		window.display();								//�������� ����

		if (Keyboard::isKeyPressed(Keyboard::Escape))	//���� ��������� ������ Esc �������� � ��������
			isCaption = false;
	}
}