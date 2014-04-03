#include "GUI.h"

GUI::GUI(int h, int w){
	
	healthBar.curentValue = 1.f;
	healthBar.max = 100;
	healthBar.size = sf::Vector2f(healthBar.max,HEALTHBAR_Y);
	healthBar.position = sf::Vector2f(0,0);
	healthBar.barHandle = sf::RectangleShape(healthBar.size);
	healthBar.barHandle.setPosition(healthBar.position);
	healthBar.barHandle.setFillColor(sf::Color::Blue);
	

	crosshair.position = sf::Vector2f(w/2,h/2);
	sf::Texture crosshairText;
	/**
	crosshairText.loadFromFile("Resource/crosshairs.png");
	crosshair.crosshair = sf::Sprite(crosshairText);
	*/
}

void GUI::createTextArea(float h, float w, sf::Vector2i position, sf::String message){
	
	tooltip.position.x = position.x;
	tooltip.position.y = position.y;
	tooltip.size = sf::Vector2f(w,h);
	tooltip.background = sf::RectangleShape(tooltip.size);
	tooltip.background.setPosition(tooltip.position);
	tooltip.background.setFillColor(sf::Color::White);
	displayToolTip(true);
	tooltip.message = message;

	/**	
	sf::Font font;
	
	
		text.setCharacterSize(30);
		text.setStyle(sf::Text::Bold);
		text.setColor(sf::Color::Red);
		
	tooltip.font.loadFromFile("Resource/sansation.ttf");
	//tooltip.text = sf::Text(tooltip.message, tooltip.font);
	*/
}

void GUI::displayToolTip(bool bDisplay){
	tooltip.display = bDisplay;
}

void GUI::setHealth(float health){
	healthBar.curentValue = health;
	healthBar.size.x = healthBar.max*healthBar.curentValue;
	healthBar.barHandle.setSize(healthBar.size);
}

