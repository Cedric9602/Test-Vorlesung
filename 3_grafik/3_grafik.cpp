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
		set_caption("Panzerspiel"); 
	}

	struct Position_obj {
		int16_t s = 3; //Spalte
		int16_t x = 375; //eig. Koordinaten
		int16_t y = 900;
	};

	
	
	Position_obj Player;


	void update() override {
		
		if (input().down(Gosu::KB_LEFT)) {
			if (Player.s > 1) {
				Player.s = Player.s - 1;
				Player.x = Player.x - 150; //Abfrage auf pos. Flanke
			}
		}

		if (input().down(Gosu::KB_RIGHT)) {
			if (Player.s < 5) {
				Player.s = Player.s + 1;
				Player.x = Player.x + 150;  //Abfrage auf pos. Flanke
			}
		}
		
	}

	void draw() override {
		street.draw_rot(0, 0, 0.0,
			0, // Rotationswinkel in Grad
			0.0, 0.0 // Position der "Mitte" relativ zu x, y
		);

		player.draw_rot(Player.x, Player.y, 0.1,
			0, // Rotationswinkel in Grad
			0.5, 0.5 // Position der "Mitte" relativ zu x, y
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

