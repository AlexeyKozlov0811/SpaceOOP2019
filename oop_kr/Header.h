#pragma once
#pragma warning(disable : 4996)

#define WW 1180		//Ширина екрана
#define WH 664		//Висота екрана
#define BGW 2360	//Ширина фону
#define BFS 1		//швидкість фону 

using namespace sf;	//використовуємо пространство імен sf

bool collision = false;	//флаг зіткнень
bool show_ship = true;	//флаг виводу гравця
bool isGame = true;		//флаг гри
bool isMenu = true;		//флаг меню
bool isCaption = true;	//флаг титрів
bool show_info = false;	//флаг інформації
bool isClose = false;	//флаг закриття гри

class Ship;			//клас корабель гравця
class Pilot;		//класс пілота

class Player		//клас гравця
{
public:
	int score = 0;	//Рахунок
	int health = 2;	//Кількість спроб
};

class Graphics		//клас графіки
{
public:
	float current_Frame = 0;	//Номер кадру
	Texture texture;			//Текстура
	Sprite sprite;				//Спрайт
	virtual void update(Player &player, Ship &ship, Pilot &pilot, float time, float speed, float fspeed) = 0;	//віртуальна функція оновленя стану
};

class Ship : public Graphics	//клас корабель гравця
{
public:
	int x;						//координата х
	int y;						//координата у
	int width;					//ширина корабля
	int heith;					//висота корабля
	Texture booster_texture;	//текстура двигуна
	Sprite booster1_sprite;		//спрайт першого двигуна
	Sprite booster2_sprite;		//спрайт другого двигуна
	void update(Player &player, Ship &ship, Pilot &pilot, float time, float speed, float fspeed)		//функція оновленя стану
	{
		x = sprite.getPosition().x;					//оновлення кординати х
		y = sprite.getPosition().y;					//оновлення кординати у
		//зміщення
		if (Keyboard::isKeyPressed(Keyboard::Down))	//переміщення вниз
		{
			if (y < WH - heith - 40)				//перевірка досягнення границі ігрового поля
			{
				sprite.move(0, 0.2*time);			//переміщення спрайту корабля
				booster1_sprite.move(0, 0.2*time);	//переміщення спрайту двигунів
				booster2_sprite.move(0, 0.2*time);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))	//переміщення вниз
		{
			if (y > 80)								//перевірка досягнення границі ігрового поля
			{
				sprite.move(0, -0.2*time);			//переміщення спрайту корабля
				booster1_sprite.move(0, -0.2*time);	//переміщення спрайту двигунів
				booster2_sprite.move(0, -0.2*time);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Left))	//переміщення вниз
		{	
			if (x > 100 - heith)					//перевірка досягнення границі ігрового поля
			{

				sprite.move(-0.2*time, 0);			//переміщення спрайту корабля
				booster1_sprite.move(-0.2*time, 0);	//переміщення спрайту двигунів
				booster2_sprite.move(-0.2*time, 0);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))//переміщення вниз
		{
			if (x < WW - width - 300)				//перевірка досягнення границі ігрового поля
			{
				sprite.move(0.2*time, 0);			//переміщення спрайту корабля
				booster1_sprite.move(0.2*time, 0);	//переміщення спрайту двигунів
				booster2_sprite.move(0.2*time, 0);
			}
		}

		current_Frame += 0.005*time;				//зміна кадру
		booster1_sprite.setTextureRect(IntRect(30 * int(current_Frame), 0, 30, 11));	//зміна спрайту двигунів
		booster2_sprite.setTextureRect(IntRect(30 * int(current_Frame), 11, 30, -11));
		if (current_Frame > 4)						//цикл кадрів
		{
			current_Frame -= 4;						//на початкове значення
		}
	}
	
	Ship()						//конструктор корабля
	{
		x = 100;												//початкова координата х
		y = 292;												//початкова координата у
		width = 70;												//ширина спрайту
		heith = 50;												//висота спрайту
		texture.loadFromFile("images/ship.png");				//загрузка текстури с файлу
		sprite.setTexture(texture);								//встановлення текстури на спрайт
		sprite.setTextureRect(IntRect(0, 0, width, heith));		//границі спрайту
		sprite.setPosition(x, y);								//координати спрайту
		booster_texture.loadFromFile("images/booster.png");		//загрузка текстури с файлу
		booster1_sprite.setTexture(booster_texture);			//встановлення текстури на спрайт
		booster1_sprite.setTextureRect(IntRect(0, 0, 30, 11));	//границі спрайту
		booster1_sprite.setPosition(x - 18, y + 14);			//координати спрайту
		booster2_sprite.setTexture(booster_texture);			//встановлення текстури на спрайт
		booster2_sprite.setTextureRect(IntRect(0, 11, 30, -11));//границі спрайту
		booster2_sprite.setPosition(x - 18, y + 25);			//координати спрайту
	}
};

class Pilot : public Ship		//класс пілота
{
public:
	Pilot()
	{
		width = 34;										//ширина спрайту
		heith = 50;										//висота спрайту
		texture.loadFromFile("images/pilot.png");		//загрузка текстури с файлу
		sprite.setTexture(texture);						//встановлення текстури на спрайт
		sprite.setTextureRect(IntRect(0, 0, 34, 50));	//границі спрайту
	}
};

class Backgound : public Graphics	//класс фону
{
public:
	Backgound(std::string source)	//конструктор фону
	{
		texture.loadFromFile(source);					//загрузка текстури с файлу
		sprite.setTexture(texture);						//встановлення текстури на спрайт
		sprite.setTextureRect(IntRect(0, 0, BGW, WH));	//границі спрайту
		sprite.setPosition(0, 0);						//координати спрайту
	}
	void update(Player &player, Ship &ship, Pilot &pilot, float time, float speed, float fspeed)	//оновлення стану фону
	{
		sprite.move(-speed * time * fspeed, 0);			//зміщеня фону
		if (sprite.getPosition().x < -WW)				//перевірка кінця анімації
			sprite.setPosition(0, 0);					//на початок анімації
	}
};

class Asteroids : public Graphics	//класс астероїдів
{
public:
	int width;												//ширина спрайту
	int heith;												//висота спрайту
	Asteroids()												//конструктор спрайту
	{
		width = 100;										//ширина спрайту
		heith = 100;										//висота спрайту
		texture.loadFromFile("images/Asteroid.png");		//загрузка текстури с файлу
		sprite.setTexture(texture);							//встановлення текстури на спрайт
		sprite.setTextureRect(IntRect(0, 0, width, heith));	//координати спрайту
	}
};

class Asteroid : public Asteroids	//класс астероїд
{
public:
	int x;											//кордината х
	int y;											//кордината у
	Asteroid(int y)									//конструктор астероїду
	{
		sprite.setPosition(1180, y);				//встановлення по координати у
	}
	void update(Player &player, Ship &ship, Pilot &pilot, float time, float speed, float fspeed)						//оновлення стану
	{
		x = sprite.getPosition().x;					//оновлення координати х
		y = sprite.getPosition().y;					//оновлення координати у
		sprite.move(-1*time, 0);					//зміщення
		if (x < -width)					//перевірка кінця анімації
		{
			sprite.setPosition(1180, rand() % 564);	//нова позиція астероїду
			player.score++;							//інкремент рахунку гравця 
		}
	}
};

class Explosion : public Graphics, Player	//класс вибуху
{
public:
	Explosion()											//конструктор вибуху
	{
		texture.loadFromFile("images/explosion.png");	//загрузка текстури с файлу
		sprite.setTexture(texture);						//встановлення текстури на спрайт
		sprite.setTextureRect(IntRect(0, 0, 100, 100));	//координати спрайту
	}
	void update(Player &player, Ship &ship, Pilot &pilot, float time, float speed, float fspeed)		//оновлення стану
	{

		current_Frame += 0.005*time;							//зміна кадру
		if (collision == 1)										//перевірка чи відбулось зіштовхування
		{
			ship.sprite.setTexture(pilot.texture);				//встановлення нової текстури спрайту
			ship.sprite.setTextureRect(IntRect(0, 0, 34, 50));	//
		}

		if (current_Frame > 3 && player.health)					//перевірка чи треба виводити корабель
		{
			show_ship = true;
		}

		if (current_Frame > 11 && collision == true)			//перевірка кінця анімації вибуху
		{
			collision = false;									//кінець анімації
			if (player.health == 0)								//перевірка кінця гри
			{
				isGame = false;
			}
		}
		sprite.setTextureRect(IntRect(100 * int(current_Frame), 0, 100, 100));	//зміна кадру
	}
};

bool manage_collision(Ship &ship, Asteroid &asteroid)	//перевірка зіштовхувань
{
	//перевірка чи не перетинаются спрайти корабля і астероїда
	return ((ship.y > (asteroid.y + asteroid.heith) || (ship.y + ship.heith) < asteroid.y) || ((ship.x + ship.width - 40) < asteroid.x || ship.x > (asteroid.x + asteroid.width)));
}

void update_version(Graphics &derived, Player &player, Ship &ship, Pilot &pilot, float time = 0, float speed = 0, float fspeed = 0)	//функція обирає яку реалізацію функциї update буде виконано 
{
	derived.update(player, ship, pilot, time, speed, fspeed);
}

int game(RenderWindow &window)
{
	//Інтерфейс користувача
	Font font;								//об'єкт шрифт
	font.loadFromFile("fonts/ARIALUNI.TTF");//завантаження шрифта з файлу
	//Інформація про кількість спроб
	Text health("", font, 20);				//об'єкт текст
	health.setColor(Color::White);			//колір тексту білий
	health.setStyle(Text::Bold);			//стиль тектсу жирний
	health.setPosition(10, 10);				//позиція тексту
	//Інформація про рахунок
	Text score("", font, 20);				//об'єкт текст
	score.setColor(Color::White);			//колір тексту білий
	score.setStyle(Text::Bold);				//стиль тектсу жирний
	score.setPosition(150, 10);				//позиція тексту

	//Ігрові об'єкти
	Player player;									//конструктор гравця
	Backgound background("images/background.png");	//конструктор фону з параметром файл з якого треба завантажувати текстуру
	Ship ship;										//конструктор корабля
	Asteroid asteroid(rand() % 564);				//конструктор астероїду с параметром коортината у
	Explosion explosion;							//конструктор вибуху
	Pilot pilot;									//конструктор пілота
	Clock clock;									//конструктор годинник

	while (isGame)	//цикл гри
	{
		//Час на ітеріцію циклу
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		//Швидкість гри
		time = time / 1000;

		//блок оновлення стану об'єктів
		update_version(background, player, ship, pilot, time, 0.1, 5);	//оновлюємо стан фону
		update_version(ship, player, ship, pilot, time);		//оновлюємо стан гравця
		update_version(asteroid, player, ship, pilot, time);	//оновлюємо стан астероїдів
		update_version(explosion, player, ship, pilot, time);	//оновлюємо стан вибуху
		//кінець блоку оновлення станів об'єктів

		//блок ввиводу на екран
		window.clear();					//відчищаємо екран
		window.draw(background.sprite);	//малюємо фон
		window.draw(asteroid.sprite);	//малюємо астроїди

		if (show_ship)					//перевірка чи треба виводити гравця
			window.draw(ship.sprite);	//виводимо корабель, якщо треба

		if (!manage_collision(ship, asteroid) || collision == 1) //перевірка зіткнень
		{
			if (collision == 0)		//якщо зіткненя ще не відбувалось
			{
				player.health--;			//лічільник спроб зменшується
				show_ship = 0;				//не малюємо гравця
				explosion.current_Frame = 0;//кадр вибуху нульовий 
			}
			collision = 1;											//зіткнення відбулося 
			explosion.sprite.setPosition(ship.x - 40, ship.y - 25); //кординати вибуху
			window.draw(explosion.sprite);							//малюємо вибух
		}
		else if (show_ship)//якщо зіткнення не відбулося і гравець виводиться
		{
			window.draw(ship.booster1_sprite);					//малюємо вогні від двигунів
			window.draw(ship.booster2_sprite);					//малюємо вогні від двигунів
		}

		//Виводимо інформацію для гравця
		std::ostringstream player_health;								//поток інформації про спроби
		player_health << player.health;									//заносимо інформацію в поток
		health.setString("Health: " + player_health.str());				//Поєднуємо строки
		window.draw(health);

		std::ostringstream player_score;					//поток інформації про рахунок
		player_score << player.score;						//заносимо інформацію в поток
		score.setString("Score: " + player_score.str());	//Поєднуємо строки
		window.draw(score);									//виводимо рахунок
		window.display();									//виводимо вікно
		//кінець блоку ввиводу на екран
	}
	return player.score;	//повертаємо фінальний рахунок
}

void menu(RenderWindow &window)
{
	Player player; 
	Ship ship;
	Pilot pilot1;
	Clock clock;																	//конструктор годинник
	Texture menuTexture1, menuTexture2, menuTexture3, infoTexture, pilotTexture;	//текстури опцій меню і пілоту
	menuTexture1.loadFromFile("images/111.png");									//завантажуємо текстуру з файлу
	menuTexture2.loadFromFile("images/222.png");									//завантажуємо текстуру з файлу
	menuTexture3.loadFromFile("images/333.png");									//завантажуємо текстуру з файлу
	infoTexture.loadFromFile("images/info.png");									//завантажуємо текстуру з файлу
	pilotTexture.loadFromFile("images/pilot_menu.png");								//завантажуємо текстуру з файлу
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), info(infoTexture), pilot(pilotTexture);	//конструктори спрайтів з параметрами текстурами
	Backgound background("images/background_menu.png");								//конструктор фону з параметром файл з якого треба завантажувати текстуру
	int menuNum = 0;					//опція меню на яку наведено курсор
	menu1.setPosition(440, 200);		//позиція опцій 
	menu2.setPosition(270, 300);		//позиція опцій 
	menu3.setPosition(510, 400);		//позиція опцій 
	info.setPosition(265, 132);			//позиція інформації про проект
	pilot.setPosition(100, 200);		//позиція пілоту
	while (isMenu)		//цикл меню
	{
		//Час на ітеріцію циклу
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		//Швидкість гри
		time = time / 1000;


		menu1.setColor(Color::White);	//колір спрайту по замовченню білий
		menu2.setColor(Color::White);	//колір спрайту по замовченню білий
		menu3.setColor(Color::White);	//колір спрайту по замовченню білий
		menuNum = 0;					//значення обраного пункта по замовченню 

		window.clear();						//відчищаємо екран
		update_version(background, player, ship, pilot1, time, 0.1, BFS);	//оновлюємо стан фону
		window.draw(background.sprite);		//малюємо фон
		if (!show_info)		//перевірка чи не треба виводити інформацію про проект
		{
			//якщо курсор на пункті меню підсвічуємо цей пункт синім і ставимо відповідне значення змінної
			if (IntRect(440, 200, 299, 54).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }	
			if (IntRect(270, 300, 640, 53).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }
			if (IntRect(510, 400, 149, 51).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }

			if (Mouse::isButtonPressed(Mouse::Left))	//якщо натиснута ліва кнопка миші 
			{
				//перевіряємо чи був при цьому обраний деякий пункт меню
				if (menuNum == 1) isMenu = false;						//якщо обраний перший пункт, закриваємо меню		
				if (menuNum == 2) show_info = true;						//якщо обраний другий пункт, виводимо інформацію про проект
				if (menuNum == 3) { isClose = true; isMenu = false; }	//якщо обраний третій пункт, закриваємо вікно
			}

			window.draw(pilot);		//малюємо спрайт пілота

			//малюємо спрайти опцій меню
			window.draw(menu1);		
			window.draw(menu2);
			window.draw(menu3);
		}
		else	//якщо треба виводити інформацію про проект
		{
			if (Keyboard::isKeyPressed(Keyboard::Escape))	//якщо натиснемо клавішу Esc, не виводимо інформацію про проект
				show_info = false;						
			window.draw(info);								//виводимо інформацію про проект
		}
		window.display();									//виводимо вікно
	}
}

void caption(RenderWindow &window, int player_score)
{
	Player player;
	Ship ship;
	Pilot pilot;
	Clock clock;												//конструктор годинник
	Font font;													//конструктор шрифту
	font.loadFromFile("fonts/ARIALUNI.TTF");					//завантажуємо шрифт із файлу
	Text score("", font, 50);									//конструктор тексту с параметрами інформації, шрифта і розміру літер

	Color color(41,112,61,255);									//конструктор кольору з параметрами RGBA
	score.setColor(color);										//встановлюємо колір тексту
	score.setStyle(Text::Bold);									//встановлюємо стиль тексту
	score.setPosition(395, 330);								//встановлюємо позицію тексту
	std::ostringstream player_score_stream;						//поток інформації про рахунок
	player_score_stream << player_score;						//заносимо інформацію в поток
	score.setString("Score: " + player_score_stream.str());		//Поєднуємо строки

	Texture infoTexture;										//конструктор текстури інформації про проект
	infoTexture.loadFromFile("images/info.png");				//завантажуємо текстуру з файлу
	Sprite info(infoTexture);									//конструктор спрайту з параметром текстурою
	info.setPosition(265, 132);									//позиція спрайту

	Backgound background("images/background_menu.png");			//конструктор фону з параметром файл з якого треба завантажувати текстуру

	while (isCaption)	//цикл заставки
	{
		//Час на ітеріцію циклу
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		//Швидкість гри
		time = time / 1000;

		window.clear();									//відчищаємо екран
		update_version(background, player, ship, pilot, time, 0.1, BFS);				//оновлюємо стан фону
		window.draw(background.sprite);					//виводимо фон
		window.draw(info);								//виводимо інформацію про проект
		window.draw(score);								//виводимо фінальний рахунок
		window.display();								//виводимо вікно

		if (Keyboard::isKeyPressed(Keyboard::Escape))	//якщо натиснемо клавішу Esc виходимо з програми
			isCaption = false;
	}
}