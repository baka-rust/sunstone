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
    int x, y;
    int speed = 2; //bigger the number, the slower the mouse, but the more jagged the movements
    sf::Texture texture;
	sf::Sprite crosshair;

};

struct GUIToolTip{

    int x, y;
	bool display;
	sf::Font font;
	sf::Text text;
	sf::RectangleShape background;
	int startDisplayIndex = 0; // Position on string where message beings displaying

};

struct GUIConsumableMonitor{//Ammo Monitor
    int x,y;
    sf::Texture texture;
    sf::Sprite monitor;
    int index; //texture Index
    int currentValue;
    int maxValue;

};

class GUITextArea{

public:



	std::vector<sf::String> inputMessage;
    float shiftx, shifty;
    int x, y;

	sf::Font font;
	sf::Text text;
	sf::RectangleShape background;
	int startDisplayIndex = 0; // Position on string where message beings displaying

	GUITextArea(int x, int y, int w, int h);
	void toggleDisplay(bool d);
	void addMessage(sf::String s);
	void draw(sf::RenderWindow* app);
	void setShift(float x, float y);
private:

    bool display = true;
};

class GUI {

public:



	GUIBar healthBar;
	GUICrosshair crosshair;
	GUIToolTip tooltip;
	GUIToolTip messageArea;
	GUIConsumableMonitor ammoBox;
	GUITextArea textArea;



	GUI(int w, int h);

	 //overlay creations
    void createToolTipArea(int x, int y, int w, int h, sf::String s);
	void setToolTipInfo(sf::String messages);
	void displayToolTip(bool bDisplay);
	void setHealth(float health);
	void toggleRecoil(bool recoil);
	void update(float elapsedTime, sf::Vector2i pos);
	void draw(sf::RenderWindow* app);
    void setCenter(float x, float y);
	//Commands
	void processCommand(sf::String command);
	void clearLastCommand();


private:
    void updateCrosshair(sf::Vector2i pos);
    void mouseRecoil();
	int height, width;
	float shiftx, shifty;
	char lastCommand = ' ';
	sf::String currentCommand = "";

/**
     std::map<std::string, AnimationSequence*>ammoAnimations;
    typedef std::map<std::string, AnimationSequence*>::iterator i_ammoAnimations;
**/
};
#endif
