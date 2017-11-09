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



class Input {
public:
	bool left_up = false;
	bool left;
	bool right_up = false;
	bool right;

	void taste_l(bool druck) {
		left = false;

		if (druck && !left_up) {
			left_up = true;
			left = true;
		}
		else if (!druck) {
			left_up = false;
		}
	}

	void taste_r(bool druck) {
		right = false;

		if (druck && !right_up) {
			right_up = true;
			right = true;
		}
		else if (!druck) {
			right_up = false;
		}
	}
};

class Player {
public:
	Gosu::Image bild;

	Player() : bild("Bilder/Panzer.png") {}

	int16_t x = 375;			// x-Koordinate
	int16_t y = 900;			// y-Koordinate


	void draw() {
		bild.draw_rot(x, y, 0.2,
			0,				// Rotationswinkel in Grad
			0.5, 0.5		// Position der "Mitte" relativ zu x, y
		);
	}

	void update(Input in) {
		if (in.left) 
		{
			if (x > 75) {
				x -= 150;
			}
		}
		
		if (in.right)
		{
			if (x < 675) {
				x += 150;
			}
		}
	}
	
};

class Gegner {
public:

	Gosu::Image bild;
	int16_t x = 375;
	int16_t y = -200;
	bool Kollision = false;

	Gegner(string n, uint16_t s) : bild(n) {
		x = s;
	}




	 void draw() {
		 bild.draw_rot(x, y, 0.2,
			 270,				// Rotationswinkel in Grad
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
	Input in;
	vector<Gegner>  elem;
	vector<Gegner>  ersatz;

	uint32_t zaehler = 0;

	

	void update() override {
		zaehler++;

		in.taste_l(input().down(Gosu::KB_LEFT));
		in.taste_r(input().down(Gosu::KB_RIGHT));
		player.update(in);

		if (zaehler % 120 == 0) { //Alle 2s neues Element
			int16_t Spur = round(Gosu::random(0.0, 4.1)) * 150 + 75;
			string Auto;
			uint16_t typ = round(Gosu::random(0.0, 4.6));
			switch (typ) {
			case 0: Auto = "Bilder/LKW.jpg"; break;
			case 1: Auto = "Bilder/Cabrio.jpg"; break;
			case 2: Auto = "Bilder/gruen.jpg"; break;
			case 3: Auto = "Bilder/Oldtimer.jpg"; break;
			case 4: Auto = "Bilder/the_white_one.jpg"; break;
			default: Auto="Bilder/Panzer.png";
			}


			Gegner gegner1(Auto,Spur);
			elem.push_back(gegner1);
		}

		if (zaehler % 300 == 0) {		//Alle 5s speed erhöhen
			speed += 1;
		}

		for (Gegner i : elem) {
			if (zaehler % 1 == 0) {
				i.y += speed;
				}


			if (i.y > 1200) {
				i.Kollision = true;
			}

			if (i.Kollision == false) {
				ersatz.push_back(i);
			

			}


		}
		elem.clear();
		elem = ersatz;
		ersatz.clear();


	}


	void draw() override {
		street.draw_rot(0, 0, 0.1,
			0,				// Rotationswinkel in Grad
			0.0, 0.0		// Position der "Mitte" relativ zu x, y
		);

		player.draw();
		
		for (auto x : elem) {
			x.draw();
		}

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