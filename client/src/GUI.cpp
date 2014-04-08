#include "GUI.h"

GUITextArea::GUITextArea(int x, int y, int w, int h) {
    this->x = x;
    this->y = y;

    inputMessage = std::vector<sf::String>(10,"");
    if (!font.loadFromFile("resources/arial.ttf"))
    {
    // error...
    }
    addMessage("text");
    text.setFont(font);
    text.setString(inputMessage.back());
    text.setCharacterSize(14);
    text.setColor(sf::Color::Red);
    text.setScale(.5,.5);

    background.setPosition(x, y);
    background.setSize(sf::Vector2f(w,h));
    background.setFillColor(sf::Color(0,0,0,150));//white



}

void GUITextArea::addMessage(sf::String s){
    inputMessage.erase(inputMessage.begin());
    inputMessage.push_back(s);
}

void GUITextArea::toggleDisplay(bool d){
    display = d;
}

void GUITextArea::draw(sf::RenderWindow* app){
    background.setPosition(x+shiftx,y+shifty);
    app->draw(background);
    text.setPosition(background.getPosition());
    text.setString(inputMessage.back());
    app->draw(text);
}

void GUITextArea::setShift(float x, float y){
    shiftx = x;
    shifty = y;
}


GUI::GUI(int w, int h, Terrain* d): textArea(0,3*h/4,w/2,h/4){

    height = h;
    width = w;
    dungeon = d;

	healthBar.curentValue = 1.f;
   healthBar.texture.loadFromFile("resources/health.png");
	healthBar.barHandle.setTexture(healthBar.texture);
	healthBar.barHandle.setPosition(healthBar.posx, healthBar.posy);
	healthBar.barHandle.setScale(.5, .5);

   crosshair.texture.loadFromFile("resources/crosshairs.png");
	crosshair.crosshair.setTexture(crosshair.texture);
    crosshair.crosshair.setColor(sf::Color::Cyan);
    //crosshair.crosshair.setPosition(sf::Vector2f(w/2,h/2));
    int orgx = crosshair.texture.getSize().x;
	int orgy = crosshair.texture.getSize().y;
    crosshair.crosshair.setOrigin(sf::Vector2f(orgx/2, orgy/2));
    crosshair.crosshair.setScale(.5,.5);

    ammoBox.texture.loadFromFile("resources/ammo.jpg");
    ammoBox.monitor.setTexture(ammoBox.texture);
    ammoBox.x = w-ammoBox.texture.getSize().x;
    ammoBox.y = 0;
    ammoBox.monitor.setPosition(ammoBox.x, ammoBox.y);
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
    healthBar.barHandle.setScale(.5*(health*healthBar.max), .5);
}

void GUI::mouseClick(){
      crosshair.crosshair.setScale(.5,.5);

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        if(crosshair.tileType == 0){
            float r = static_cast<float>(rand())/ static_cast<float>(RAND_MAX);
            crosshair.crosshair.setScale(r,r);
        }
    }
}

void GUI::updateCrosshair(sf::Vector2i pos){

    crosshair.x = (pos.x)/crosshair.speed + shiftx;
    crosshair.y = (pos.y)/crosshair.speed + shifty;

    if(crosshair.x > shiftx + width)
        crosshair.x = shiftx + width;
    if(crosshair.x < shiftx)
        crosshair.x = shiftx;

    if(crosshair.y > shifty + height)
        crosshair.y = shifty + height;
    if(crosshair.y < shifty)
        crosshair.y = shifty;
/**
    ground = 0 ,
    wall ,
    door ,
    healthpack ,
    spawner
*/
    //divide by 15 since each tile is 16 wide
    crosshair.tileType = dungeon->getTile(crosshair.x/16, crosshair.y/16, "");

    crosshair.crosshair.setPosition(crosshair.x,crosshair.y);
    mouseClick();
}


void GUI::update(float elapsedTime, sf::Vector2i pos){
    float r = .5 + static_cast<float>(rand())/ static_cast<float>(RAND_MAX);
    setHealth(r);

    updateCrosshair(pos);
}

void GUI::draw(sf::RenderWindow *app){
    healthBar.barHandle.setPosition(shiftx + healthBar.posx, shifty + healthBar.posy);
    ammoBox.monitor.setPosition(shiftx + ammoBox.x, shifty + ammoBox.y);
     app->draw(healthBar.barHandle);
    app->draw(ammoBox.monitor);

    textArea.setShift(shiftx, shifty);
    textArea.draw(app);
    app->draw(crosshair.crosshair);


}

void GUI::setCenter(float x, float y){
    shiftx = x;
    shifty = y;
}

void GUI::processCommand(sf::String command){
    switch(lastCommand){
        case ' ':
            lastCommand = command[0];
            break;
        case '/':
            currentCommand += command;
            std::cout<<currentCommand.toAnsiString();
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
