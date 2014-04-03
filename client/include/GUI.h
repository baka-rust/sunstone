#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <iostream>



const int HEALTHBAR_Y = 10;

struct GUIBar{
	sf::Vector2f position;
	sf::Vector2f size;
	sf::RectangleShape barHandle;
	int max; 
	float curentValue;
};

struct GUICrosshair{
	sf::Vector2f position;
	sf::Sprite crosshair;
};

struct GUITextArea{
	
	bool display;
	sf::Vector2f position;
	sf::String message;
	sf::Vector2f size;
	sf::Font font;
	sf::Text text;
	sf::RectangleShape background;
};

class GUI {

public:
	
	int height, width;

	GUIBar healthBar;
	GUICrosshair crosshair;
	GUITextArea tooltip;

	GUI(int, int);

	 //overlay creations
	void createTextArea(float, float, sf::Vector2i, sf::String);
	void displayToolTip(bool bDisplay);
	void setHealth(float);

};
#endif