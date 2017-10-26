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

	GameWindow()
		: Window(FG_x, FG_y)
		, street("Bilder/street.png")
	{
		set_caption("Panzerspiel"); 
	}

	double mouse_x = 0.0;
	double mouse_y = 0.0;
	bool shoot = false;
	uint16_t rot = 0;

	int16_t down1 = 0;
	int16_t down2 = -200;

	void update() override {
		mouse_x = input().mouse_x();
		mouse_y = input().mouse_y();
		if (input().down(Gosu::MS_LEFT)) {			// linke Maustaste
			shoot = true;
		}
		else if (input().down(Gosu::MS_RIGHT)) {	// rechte Maustaste
			
		}

		rot++;
		down1 = (down1 + 1) % 480;
		down2 = (down2 + 1) % 480;
	}

	void draw() override {
		street.draw_rot(0, 0, 0.0,
			0, // Rotationswinkel in Grad
			0.0, 0.0 // Position der "Mitte" relativ zu x, y
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
		

		// Fadenkreuz
		graphics().draw_line(
			mouse_x - 20, mouse_y, Gosu::Color::RED,
			mouse_x + 20, mouse_y, Gosu::Color::RED,
			0.1
		);
		graphics().draw_line(
			mouse_x, mouse_y - 20, Gosu::Color::RED,
			mouse_x, mouse_y + 20, Gosu::Color::RED,
			0.1
		);

		/*
		graphics().draw_triangle(
		20, 300, Gosu::Color::BLUE,
		mouse_x, mouse_y, Gosu::Color::RED,
		300, 300, Gosu::Color::GREEN,
		0.0
		);

		graphics().draw_line(
			20, 20, Gosu::Color::RED,
			200, 100, Gosu::Color::GREEN,
			0.1
		);

		graphics().draw_line(
			10, 100, Gosu::Color::RED,
			200, 20, Gosu::Color::GREEN,
			0.1
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

