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

class Element {
	Gosu::Image Bild;
	int16_t x = 375;
	int16_t y = 900;

public:

	Element(string n) : Bild(n) {}
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


	void update() override {

		in.taste_l(input().down(Gosu::KB_LEFT));
		in.taste_r(input().down(Gosu::KB_RIGHT));
		player.update(in);

	}


	void draw() override {
		street.draw_rot(0, 0, 0.1,
			0,				// Rotationswinkel in Grad
			0.0, 0.0		// Position der "Mitte" relativ zu x, y
		);

		player.draw();


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