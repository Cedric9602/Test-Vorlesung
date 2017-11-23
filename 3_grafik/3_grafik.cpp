// 3_grafik.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"

#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>


#include <cassert>
#include <cmath>
#include <cstdint>
#include <vector>
#include <forward_list>
#include <string>
#include <memory>
#include <iostream>
#include <algorithm>
#include <ctime>
using namespace std;


//--------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------ Deklarationen -----------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------
uint16_t FG_x = 750;	//Fenstergröße x
uint16_t FG_y = 1000;	//Fenstergröße y
uint16_t speed = 3;
int16_t zaehler = 0;
int16_t Leben = 3;
int16_t Score = 0;
Gosu::Font Scoreanzeige = 50;
bool Start = true;


class Input {
public:
	bool left_up = false;
	bool left;
	bool right_up = false;
	bool right;
	bool space_up = false;
	bool space;

	void taste_l(bool druck) {
		left = false;

		if (druck && !left_up) {
			left_up = true;
			left = true;
		}
		else if (!druck) { left_up = false; }
	}

	void taste_r(bool druck) {
		right = false;

		if (druck && !right_up) {
			right_up = true;
			right = true;
		}
		else if (!druck) { right_up = false; }
	}

	void taste_s(bool druck) {
		space = false;

		if (druck && !space_up) {
			space_up = true;
			space = true;
		}
		else if (!druck) { space_up = false; }
	}
};

class Player {
public:
	Gosu::Image bild;

	Player() : bild("Bilder/Panzer.png") {}

	int16_t x = 375;			// x-Koordinate
	int16_t y = 900;			// y-Koordinate
	int16_t Schusszahl = 2;

	void draw() {
		bild.draw_rot(x, y, 0.2,
			0,				// Rotationswinkel in Grad
			0.5, 0.5		// Position der "Mitte" relativ zu x, y
		);
	}

	void update(Input in) {
		if (in.left) 
		{
			if (x > 75) { x -= 150; }
		}
		
		if (in.right)
		{
			if (x < 675) { x += 150; }
		}
	}
};

class Gegner {
public:

	Gosu::Image bild;
	int16_t x = 375;
	int16_t y = -200;
	int16_t y1;
	int16_t y2;
	bool Kollision = false;

	Gegner(string n, uint16_t s) : bild(n) {
		x = s;
	}

	 void draw() {
		 bild.draw_rot(x, y, 0.1,
			 270,				// Rotationswinkel in Grad
			 0.5, 0.5	// Position der "Mitte" relativ zu x, y
		 ); 
	 }
};

class Shot {
public:
	Gosu::Image bild;
	int16_t x = 375;
	int16_t y = 850;
	bool Kollision = false;

	Shot(string n, int16_t s) : bild(n) {
		x = s;
	}

	void draw() {
		bild.draw_rot(x, y, 0.2,
			0,				// Rotationswinkel in Grad
			0.5, 0.5	// Position der "Mitte" relativ zu x, y
		);
	}
};


class Finish {
public:
	Gosu::Image bild;
	int16_t x = 375;
	int16_t y = 500;

	Finish() : bild("Bilder/Finish.png") { }

	void draw() {
		bild.draw_rot(x, y, 0.2,
			0,				// Rotationswinkel in Grad
			0.5, 0.5	// Position der "Mitte" relativ zu x, y
		);
	}
};


class Lebensanzeige {
public:

	Gosu::Image bild;
	int16_t x = 50;
	int16_t y = 30;
	int16_t Nr;

	Lebensanzeige() : bild("Bilder/MAGNUM.png") { }

	void draw() {
		bild.draw_rot(x, y, 0.3,
			0,				// Rotationswinkel in Grad
			0.5, 0.5	// Position der "Mitte" relativ zu x, y
		);
	}
};


//--------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------ GameWindow --------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------

class GameWindow : public Gosu::Window {
public:
	Gosu::Image street;
	
	GameWindow()
		: Window(FG_x, FG_y)
		, street("Bilder/street.png")
	{
		set_caption("Panzerspiel"); 
	}
	
	Player player;
	Finish Ende;
	Input in;
	vector<Gegner>  elem;
	vector<Gegner>  ersatz;

	vector<Shot> Schüsse;
	vector<Shot> Schüsse_ersatz;	

	uint32_t zaehler = 0;

	Lebensanzeige Leben3;
	Lebensanzeige Leben2;
	Lebensanzeige Leben1;

	

	void update() override {
		if (Leben > 0) {
			zaehler++;

			if (Start) {
				Start = false;

				Leben3.x = 250;
				Leben3.Nr = 3;

				Leben2.x = 150;
				Leben2.Nr = 2;

				Leben1.x = 50;
				Leben1.Nr = 1;
			}

			in.taste_l(input().down(Gosu::KB_LEFT));
			in.taste_r(input().down(Gosu::KB_RIGHT));
			in.taste_s(input().down(Gosu::KB_SPACE));
			player.update(in);

			if (in.space) {
				if (player.Schusszahl > 0) {
					Shot schuss("Bilder/Laser.png", player.x);
					Schüsse.push_back(schuss);
					player.Schusszahl--;
				}
			}

			if (zaehler % 120 == 0) {							//Alle 2s neues Element
				string Auto;
				int16_t Spur = round(Gosu::random(0.0, 4.1)) * 150 + 75;
				uint16_t typ = round(Gosu::random(0.0, 4.6));

				switch (typ) {
				case 0: Auto = "Bilder/LKW2.png"; break;
				case 1: Auto = "Bilder/Cabrio.png"; break;
				case 2: Auto = "Bilder/gruen2.png"; break;
				case 3: Auto = "Bilder/Oldtimer2.png"; break;
				case 4: Auto = "Bilder/the_white_one2.png"; break;
				default: Auto = "Bilder/Panzer.png";
				}

				Gegner gegner1(Auto, Spur);
				elem.push_back(gegner1);
			}

			if (zaehler % 300 == 0) {							//Alle 5s speed erhöhen
				speed += 1;
			}

			for (Gegner gegner : elem) {
				gegner.y1 = gegner.y + 150;
				gegner.y2 = gegner.y - 150;

				if (zaehler % 1 == 0) {
					gegner.y += speed;
				}

				if (gegner.y > 1200) {
					gegner.Kollision = true;
					Leben--;
					Score -= 2;
				}

				if ((gegner.x == player.x) && (((player.y >= gegner.y2) && (player.y <= gegner.y1)))) {
					gegner.Kollision = true;
					Leben--;
					Score -= 5;
				}


				for (auto shot = Schüsse.begin(); shot != Schüsse.end();shot++)
				{
					shot->y -= 10;

					if (shot->y < -100) {
						shot->Kollision = true;

						if (player.Schusszahl < 2) {
							player.Schusszahl++;
						}
					}

					if (shot->x == gegner.x) {
						if ((shot->y >= gegner.y2) && (shot->y <= gegner.y1)) {
							shot->Kollision = true;
							gegner.Kollision = true;
							Score += 10;

							if (player.Schusszahl < 2) {
								player.Schusszahl++;
							}
						}
					}

					if (shot->Kollision == false) {
						Schüsse_ersatz.push_back(*shot);
					}
				}

				if (gegner.Kollision == false) {
					ersatz.push_back(gegner);
				}

				Schüsse.clear();
				Schüsse = Schüsse_ersatz;
				Schüsse_ersatz.clear();
			}

			elem.clear();
			elem = ersatz;
			ersatz.clear();
		}


		if (Leben3.x < 800) {
			if (Leben3.Nr > Leben) { Leben3.x += 20; }
		}

		if (Leben2.x < 800) {
			if (Leben2.Nr > Leben) { Leben2.x += 20; }
		}

		if (Leben1.x < 800) {
			if (Leben1.Nr > Leben) { Leben1.x += 20; }
		}
		
	}

	void draw() override {
		street.draw_rot(0, 0, 0.1,
			0,				// Rotationswinkel in Grad
			0.0, 0.0		// Position der "Mitte" relativ zu x, y
		);

		Scoreanzeige.draw("Score: ", 500, 50, 1.0, 1.0, 1.0, Gosu::Color::RED);
		Scoreanzeige.draw(to_string(Score), 650, 50, 1.0, 1.0, 1.0, Gosu::Color::RED);

		player.draw();

		for (auto x : elem) {
			x.draw();
		}

		for (auto z : Schüsse) {
			z.draw();
		}
	
		if (Leben == 0) {
			Ende.draw();
		}

		Leben3.draw();
		Leben2.draw();
		Leben1.draw();
	}
};


//--------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------ Main --------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------

void main()
{
	GameWindow window;
	window.show();
}