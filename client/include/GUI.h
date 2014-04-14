#ifndef GUI_H
#define GUI_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Terrain.h>



const int HEALTHBAR_Y = 10;

struct GUIBar{
	int posx=0;
	int posy=0;
	sf::RectangleShape barHandle;
	float max = 10;
	float curentValue = 1.f;
};

struct GUICrosshair{
    int x, y;
    int speed = 2; //bigger the number, the slower the mouse, but the more jagged the movements
    int tileType = 0;
    sf::RectangleShape crosshair;

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
    float shiftx = 0, shifty=0;
    float height;
    int x, w;
    float marginy = 4;

	sf::Font font;
	sf::Text currentText;
	sf::Text archivedText;
	bool displayArchivedText = true;

	sf::RectangleShape background;
	sf::Vector2f dimentions;
	int startDisplayIndex = 5; // Position on string where message beings displaying
    sf::String tempString;

	GUITextArea(int x, int windowHeight, int w, int h);
	GUITextArea();

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
	GUIConsumableMonitor ammoBox;
	GUITextArea textArea;
    GUITextArea tooltip;


	GUI(int w, int h, Terrain* d);

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

    int height, width;
	float shiftx, shifty;
	char lastCommand = ' ';
	sf::String currentCommand = "";
	Terrain* dungeon;

    void updateCrosshair(sf::Vector2i pos);
    void mouseClick();


/**
     std::map<std::string, AnimationSequence*>ammoAnimations;
    typedef std::map<std::string, AnimationSequence*>::iterator i_ammoAnimations;
**/
};
#endif
