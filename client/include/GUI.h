#ifndef GUI_H
#define GUI_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>



const int HEALTHBAR_Y = 10;

struct GUIBar{
	int posx=0;
	int posy=0;
	sf::Texture texture;
	sf::Sprite barHandle;
	float max = 10;
	float curentValue = 1.f;
};

struct GUICrosshair{
    sf::Texture texture;
	sf::Sprite crosshair;

};

struct GUIToolTip{


	bool display;
	sf::Vector2f position;
	sf::String message;
	sf::Vector2f size;
	sf::Font font;
	sf::Text text;
	sf::RectangleShape background;
	int startDisplayIndex = 0; // Position on string where message beings displaying

};

struct GUIConsumableMonitor{//Ammo Monitor
    sf::Texture texture;
    sf::Sprite monitor;
    int index; //texture Index
    int currentValue;
    int maxValue;

};

class GUITextArea{

public:

	bool display;
	std::vector<sf::String> inputMessage;

	sf::Vector2f size;
	sf::Font font;
	sf::Text text;
	sf::RectangleShape background;
	int startDisplayIndex = 0; // Position on string where message beings displaying

	GUITextArea(int x, int y, int w, int h);
};

class GUI {

public:


	int height, width;

	GUIBar healthBar;
	GUICrosshair crosshair;
	GUIToolTip tooltip;
	GUIToolTip messageArea;
	GUIConsumableMonitor ammoBox;

    sf::Time recoilTime;

	GUI(int w, int h);

	 //overlay creations
	void createTextArea(float w, float h, sf::Vector2i poisition, sf::String message);
	void setToolTipInfo(sf::String messages);
	void displayToolTip(bool bDisplay);
	void setHealth(float health);
	void toggleRecoil(bool recoil);
	void updateGUI(float elapsedTime, sf::Vector2i pos);
	void draw(sf::RenderWindow* app);

private:
    void mouseRecoil();

/**
     std::map<std::string, AnimationSequence*>ammoAnimations;
    typedef std::map<std::string, AnimationSequence*>::iterator i_ammoAnimations;
**/
};
#endif
