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



	std::vector<sf::String> inputMessage;


	sf::Font font;
	sf::Text text;
	sf::RectangleShape background;
	int startDisplayIndex = 0; // Position on string where message beings displaying

	GUITextArea(int x, int y, int w, int h);
	void toggleDisplay(bool d);
	void addMessage(sf::String s);
	void draw(sf::RenderWindow* app);

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

    sf::Time recoilTime;

	GUI(int w, int h);

	 //overlay creations
    void createToolTipArea(int x, int y, int w, int h, sf::String s);
	void setToolTipInfo(sf::String messages);
	void displayToolTip(bool bDisplay);
	void setHealth(float health);
	void toggleRecoil(bool recoil);
	void updateGUI(float elapsedTime, sf::Vector2i pos);
	void draw(sf::RenderWindow* app);

	//Commands
	void processCommand(sf::String command);
	void clearLastCommand();

private:
    void mouseRecoil();
	int height, width;
	char lastCommand = ' ';
	sf::String currentCommand = "";

/**
     std::map<std::string, AnimationSequence*>ammoAnimations;
    typedef std::map<std::string, AnimationSequence*>::iterator i_ammoAnimations;
**/
};
#endif
