#include "GUI.h"

GUITextArea::GUITextArea(int x, int y, int w, int h) {

    inputMessage = std::vector<sf::String>(10,"");
    if (!font.loadFromFile("resources/arial.ttf"))
    {
    // error...
    }
    addMessage("text");
    text.setFont(font);
    text.setString(inputMessage.back());
    text.setCharacterSize(24);
    text.setColor(sf::Color::Red);

    background.setPosition(x, y);
    background.setSize(sf::Vector2f(w,h));
    background.setFillColor(sf::Color::White);


}

void GUITextArea::addMessage(sf::String s){
    inputMessage.erase(inputMessage.begin());
    inputMessage.push_back(s);
}

void GUITextArea::toggleDisplay(bool d){
    display = d;
}

void GUITextArea::draw(sf::RenderWindow* app){

    app->draw(background);
    text.setPosition(background.getPosition());
    text.setString(inputMessage.back());
    app->draw(text);
}




GUI::GUI(int h, int w): textArea(0,h/2,w/2,h/2){


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

void GUI::createToolTipArea(int x, int y, int w, int h, sf::String message){


	tooltip.background.setSize(sf::Vector2f(w,h));
	tooltip.background.setPosition(x, y);
	tooltip.background.setFillColor(sf::Color::White);
	displayToolTip(true);

    if(!tooltip.font.loadFromFile("resources/arial.ttf")){
    //error
    }

    tooltip.text.setFont(tooltip.font);
    tooltip.text.setCharacterSize(14);
    tooltip.text.setColor(sf::Color::Red);
    tooltip.text.setString(message);


}

void GUI::setToolTipInfo(sf::String message){
    tooltip.text.setString(message);
}

void GUI::displayToolTip(bool bDisplay){
	if(bDisplay == false){
        tooltip.text.setString("");
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
    app->draw(ammoBox.monitor);
    textArea.draw(app);

}

void GUI::processCommand(sf::String command){
    switch(lastCommand){
        case ' ':
            lastCommand = command[0];
            break;
        case '/':
            currentCommand += command;
            std::cout<<currentCommand.toAnsiString();
            lastCommand = ' ';
            break;
    }

}

void GUI::clearLastCommand(){
    switch(lastCommand){
        case '/':
            textArea.addMessage(currentCommand);
            lastCommand = ' ';
            break;
    }
}
