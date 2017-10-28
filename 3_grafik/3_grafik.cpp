// 3_grafik.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"

#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>


#include "assert.h"
#include "math.h"
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

class GameWindow : public Gosu::Window {
public:
	Gosu::Image street;
	Gosu::Image player;

	GameWindow()
		: Window(FG_x, FG_y)
		, street("Bilder/street.png")
		, player("Bilder/Panzer.png")
	{
		//set_caption("Panzerspiel"); 
	}
	
	
	struct Position_obj {
		int16_t s = 3; //Spalte
		int16_t x = 375; //eig. Koordinaten
		int16_t y = 900;
	};

	Position_obj Player;
	

	bool input_LEFT_up = false;
	bool input_RIGHT_up = false;
	

	/*TEST:
	PLAYER player;

	bool RIGHT_up = false;
	*/

	void update() override {
		//TEST:
		//player.r_step(player);
		
		if (input().down(Gosu::KB_LEFT) && !input_LEFT_up) {
			input_LEFT_up = true;

			if (Player.s > 1) {
				Player.s = Player.s - 1;
				Player.x = Player.x - 150;
			}
		}
		else if (!input().down(Gosu::KB_LEFT)) {
			input_LEFT_up = false;
		}


		if (input().down(Gosu::KB_RIGHT) && !input_RIGHT_up) {
			input_RIGHT_up = true;

			if (Player.s < 5) {
				Player.s = Player.s + 1;
				Player.x = Player.x + 150;
			}
		}
		else if (!input().down(Gosu::KB_RIGHT)) {
			input_RIGHT_up = false;
		}		
	}

	void draw() override {


		street.draw_rot(0, 0, 0.1,
			0,				// Rotationswinkel in Grad
			0.0, 0.0		// Position der "Mitte" relativ zu x, y
		);

		player.draw_rot(Player.x, Player.y, 0.2,							// für test müsste das hier stehen: player.get_x(), player.get_y(), 0.2,
			0,				// Rotationswinkel in Grad
			0.5, 0.5		// Position der "Mitte" relativ zu x, y
		);

		/*
		alien.draw_rot(200, down1, 0.1,
			rot, // Rotationswinkel in Grad
			0.0, 0.0 // Position der "Mitte" relativ zu x, y
		);

		alien.draw_rot(500, down2, 0.1,
			rot, // Rotationswinkel in Grad
			0.0, 0.0 // Position der "Mitte" relativ zu x, y
		);
		*/
	}
};

/*
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


class PLAYER : public GameWindow, public INPUT {
	int16_t x = 375;			// x-Koordinate
	int16_t y = 900;			// y-Koordinate

public:
	void set_x(int16_t x) { this->x = x; }
	int get_x() { return this->x; }

	void set_y(int16_t y) {	this->y = y; }
	int get_y() { return this->y; }
};


class ENEMY : public GameWindow {
public:

};


class ELEMENT : public GameWindow {
public:

};
*/


//--------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------ Main --------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------

void main()
{
	GameWindow window;
	window.show();
}



//--------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------ Definitionen ------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------

