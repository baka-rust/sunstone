#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <sstream>



const int HEALTHBAR_Y = 10;

struct GUIBar{
	int posx=0;
	int posy=0;
	sf::Sprite barHandle;
	float max = 10;
	float curentValue = 10;
};

struct GUICrosshair{
	sf::Sprite crosshair;
	bool isRecoiling;

};

struct GUITextArea{

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
    sf::Sprite monitor;
    int index; //texture Index
    int currentValue;
    int maxValue;

};


class GUI {

public:

    sf::RenderWindow* app;

	int height, width;

	GUIBar healthBar;
	GUICrosshair crosshair;
	GUITextArea tooltip;
	GUITextArea messageArea;
	GUIConsumableMonitor ammoBox;

    sf::Time recoilTime;

	GUI(int w, int h);

	 //overlay creations
	void createTextArea(float w, float h, sf::Vector2i poisition, sf::String message);
	void setToolTipInfo(sf::String messages);
	void displayToolTip(bool bDisplay);
	void setHealth(int health);
	void mouseRecoil();
	void updateGUI(float elapsedTime, sf::Vector2i mousePosition);
	void draw(sf::RenderWindow* app);

private:
/**
     std::map<std::string, AnimationSequence*>ammoAnimations;
    typedef std::map<std::string, AnimationSequence*>::iterator i_ammoAnimations;
**/
};
#endif
