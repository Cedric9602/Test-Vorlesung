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


class Player {
public:
	Gosu::Image bild;

	Player()
		: bild("Bilder/Panzer.png") { }

	int16_t x = 375;			// x-Koordinate
	int16_t y = 900;			// y-Koordinate


	void draw() {
		bild.draw_rot(x, y, 0.2,
			0,				// Rotationswinkel in Grad
			0.5, 0.5		// Position der "Mitte" relativ zu x, y
		);
	}

	void move_l() {
		if (x > 75) {
			x -= 150;
		}
	}
};

class Input {
	bool LEFT_up = false;
	bool RIGHT_up = false;

public:
	bool taste_l(bool druck) {
		if (druck && !LEFT_up) {
			LEFT_up = true;
			return true;
		}
		else if (!druck) {
			LEFT_up = false;
		}
		return false;
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


	bool input_LEFT_up = false;
	bool input_RIGHT_up = false;


	
	
	bool RIGHT_up = false;

	void update() override {

		if (in.taste_l(input().down(Gosu::KB_LEFT))) {
			player.move_l();
		}

		

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

















//--------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------ shit ------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------

/*
alien.draw_rot(200, down1, 0.1,
rot, // Rotationswinkel in Grad
0.0, 0.0 // Position der "Mitte" relativ zu x, y
);

alien.draw_rot(500, down2, 0.1,
rot, // Rotationswinkel in Grad
0.0, 0.0 // Position der "Mitte" relativ zu x, y
);



class ENEMY : public GameWindow {
public:

};


class ELEMENT : public GameWindow {
public:

};

class INPUT : public GameWindow {
bool LEFT_up = false;
bool RIGHT_up = false;

public:
void r_step(PLAYER player) {
if (input().down(Gosu::KB_RIGHT) && !RIGHT_up) {
RIGHT_up = true;

if (player.get_x() < 675) {
player.set_x(player.get_x() + 150);
}
}
else if (!input().down(Gosu::KB_RIGHT)) {
RIGHT_up = false;
}
}

void l_step(PLAYER player) {
if (input().down(Gosu::KB_LEFT) && !LEFT_up) {
LEFT_up = true;

if (player.get_x() > 75) {
player.set_x(player.get_x() - 150);
}
}
else if (!input().down(Gosu::KB_LEFT)) {
LEFT_up = false;
}
}
};

*/