#include "GUI.h"

GUITextArea::GUITextArea(int x, int y, int w, int h){


}



GUI::GUI(int h, int w){


	healthBar.curentValue = 1.f;
   healthBar.texture.loadFromFile("resources/health.jpg");
	healthBar.barHandle.setTexture(healthBar.texture);
	healthBar.barHandle.setPosition(healthBar.posx, healthBar.posy);
	healthBar.barHandle.setScale(healthBar.max,1);

   crosshair.texture.loadFromFile("resources/crosshairs.jpg");
	crosshair.crosshair.setTexture(crosshair.texture);
    crosshair.crosshair.setPosition(sf::Vector2f(w/2,h/2));
    int orgx = crosshair.texture.getSize().x;
	int orgy = crosshair.texture.getSize().y;
    crosshair.crosshair.setOrigin(sf::Vector2f(orgx/2, orgy/2));

    ammoBox.texture.loadFromFile("resources/ammo.jpg");
    ammoBox.monitor.setTexture(ammoBox.texture);
   // ammoBox.monitor.setPosition(w-ammoBox.texture.getSize().x, 0);
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

void GUI::setHealth(float health){
    if(health*healthBar.max > healthBar.max)
        health = 1.f;
    healthBar.curentValue = health;
    healthBar.barHandle.setScale((health*healthBar.max), 1);
}

void GUI::mouseRecoil(){
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){

        float r = .5 + static_cast<float>(rand())/ static_cast<float>(RAND_MAX);
        crosshair.crosshair.setScale(r,r);
    }else
        crosshair.crosshair.setScale(1.f,1.f);
}


void GUI::updateGUI(float elapsedTime, sf::Vector2i pos){
    float r = .5 + static_cast<float>(rand())/ static_cast<float>(RAND_MAX);
    setHealth(r);
    crosshair.crosshair.setPosition(pos.x,pos.y);
    mouseRecoil();
}

void GUI::draw(sf::RenderWindow *app){



     app->draw(healthBar.barHandle);
    app->draw(crosshair.crosshair);
    //app->draw(ammoBox.monitor);

}
