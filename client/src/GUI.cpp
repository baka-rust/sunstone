#include "GUI.h"

GUI::GUI(int h, int w){

    std::stringstream imagePath;

	healthBar.curentValue = 1.f;
    sf::Texture healthBarText;
	healthBarText.loadFromFile("resources/health.jpg");
	healthBar.barHandle = sf::Sprite(healthBarText);
	healthBar.max = healthBar.barHandle.getScale().x;
	healthBar.barHandle.setPosition(healthBar.posx, healthBar.posy);

    sf::Texture crosshairText;
	crosshairText.loadFromFile("resources/crosshairs.jpg");
	crosshair.crosshair = sf::Sprite(crosshairText);
    crosshair.crosshair.setPosition(sf::Vector2f(w/2,h/2));

    sf::Texture ammoBoxText;
    ammoBoxText.loadFromFile("resources/ammo.jpg");
    ammoBox.monitor = sf::Sprite(ammoBoxText);
    ammoBox.index = 0;
    ammoBox.maxValue = 9;
    ammoBox.currentValue = 0;

}

void GUI::createTextArea(float w, float h, sf::Vector2i position, sf::String message){

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

void GUI::setToolTipInfo(sf::String message){
    tooltip.message = message;
}

void GUI::displayToolTip(bool bDisplay){
	if(bDisplay == false){
        tooltip.message.clear();
	}
	tooltip.display = bDisplay;
}

void GUI::setHealth(int health){
    if(health > healthBar.max)
        health = healthBar.max;
    healthBar.curentValue = health;
    healthBar.barHandle.setScale((healthBar.curentValue/healthBar.max), 1);
}

void GUI::mouseRecoil(){
    if(crosshair.isRecoiling){
        float r = .5 + static_cast<float>(rand())/ static_cast<float>(RAND_MAX);
        crosshair.crosshair.setScale(r,r);
    }else
        crosshair.crosshair.setScale(1.f,1.f);
}

void GUI::updateGUI(float elapsedTime, sf::Vector2i mousePosition){

    crosshair.crosshair.setPosition(mousePosition.x * 1.0, mousePosition.y * 1.0);

}

void GUI::draw(sf::RenderWindow *app){
    healthBar.barHandle.setPosition(0,0);
    sf::RectangleShape shape(sf::Vector2f(10,10));
    shape.setFillColor(sf::Color::White);
    shape.setPosition(0,0);
    app->draw(shape);
    /**
     app.draw(healthBar.barHandle);
    app.draw(crosshair.crosshair);
    app.draw(ammoBox.monitor);
    */
}
