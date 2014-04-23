#ifndef GUI_H
#define GUI_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Terrain.h>
#include <Network.h>



const int HEALTHBAR_Y = 10;

struct GUIBar{
	sf::Vector2i pos;
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

class GUIButton{
public:
    sf::Vector2i pos;
    sf::RectangleShape background;
    sf::Font font;
    sf::Text text;

    int margin= 4;

    bool deleteOnClick = true;

    void (*callback)();

    GUIButton(int x, int y, std::string message, void (*callback)());
    void draw(sf::RenderWindow* app);
    void update(sf::RenderWindow* app);

private:
    bool display = true;
    void buttonClicked();
};



class GUITextArea{

public:



	std::vector<std::string> inputMessage;
    sf::Vector2i pos;
    float marginy = 4;

	sf::Font font;
	sf::Text currentText;
	sf::Text archivedText;
	bool displayArchivedText = true;

	sf::RectangleShape background;
	sf::RectangleShape slider; //closing and opening animation
	float closingTime = 1;
	sf::Clock clock;

	sf::Vector2f dimentions;
	int startDisplayIndex = 5; // Position on string where message beings displaying
    std::string tempString;

    bool hasOutputStream = false;


	GUITextArea(int x, int windowHeight, int w, int h);
	GUITextArea();

	void toggleDisplay(bool d);
	void addMessage(std::string s);
	void draw(sf::RenderWindow* app);
	bool getDisplay(){return display;}

private:

    bool display = true;
    bool openDisplay = true;
};

class GUI {

public:

    enum GameStates{
        LOGIN,
        MAIN
    };

    GameStates currentState = LOGIN;

	GUIBar healthBar;
	GUICrosshair crosshair;
	GUITextArea textArea;
    GUITextArea tooltip;

    Terrain* dungeon;
    Network* network;

	GUI(int w, int h);
	~GUI();

	 //overlay creations
    void createToolTipArea(int x, int y, int w, int h, std::string s);
	void setToolTipInfo(std::string messages);
	void displayToolTip(bool bDisplay);
	void setHealth(float health);
	void toggleRecoil(bool recoil);
	void update(sf::RenderWindow* app);
	void draw(sf::RenderWindow* app);
	void drawButtons(sf::RenderWindow* app);
	GUIButton* instanciateButton(int x,int y,std::string message, void (*callback)());
	bool IsIPAddress(std::string & ipaddr);
  //Commands
	void processCommand(char command);
	void clearLastCommand();




private:

    int height, width;
	char lastCommand = ' ';
	std::string currentCommand = "";
	std::vector<GUIButton*> buttons;


    void updateCrosshair(sf::RenderWindow* app);
    void mouseClick();
    int processLogin(std::string);


/**
     std::map<std::string, AnimationSequence*>ammoAnimations;
    typedef std::map<std::string, AnimationSequence*>::iterator i_ammoAnimations;
**/
};
#endif
