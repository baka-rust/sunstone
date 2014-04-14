#include "GUI.h"

GUITextArea::GUITextArea(int x, int windowHeight, int w, int h) {
    this->x = x;
    this->w = w;
    height = windowHeight;

    inputMessage = std::vector<sf::String>(10," ");
    if (!font.loadFromFile("resources/arial.ttf"))
    {
    // error...
    }

    tempString = "";
    addMessage("text");
    currentText.setFont(font);
    currentText.setString(inputMessage.back());
    currentText.setCharacterSize(14);
    currentText.setColor(sf::Color::Yellow);
    currentText.setScale(.5,.5);

    archivedText.setFont(font);
    archivedText.setString(inputMessage.back());
    archivedText.setCharacterSize(14);
    archivedText.setColor(sf::Color::Yellow);
    archivedText.setScale(.5,.5);

    background.setPosition(x, height-20);
    dimentions = sf::Vector2f(w,h);
    background.setSize(dimentions);
    background.setFillColor(sf::Color(0,0,255,150));//blue



}

GUITextArea::GUITextArea(){
    GUITextArea(0,0,1,1);
}

void GUITextArea::addMessage(sf::String s){
    inputMessage.erase(inputMessage.begin());
    inputMessage.push_back(s);

     sf::String str = "";
    for(int i = inputMessage.size()- startDisplayIndex; i < inputMessage.size(); i++){
        str += inputMessage[i];
        str += "\n";

    }
     std::cout << str.toAnsiString();
    archivedText.setString(str);

}

void GUITextArea::toggleDisplay(bool d){
    display = d;
}

void GUITextArea::draw(sf::RenderWindow* app){
   if(display){
    float textBounds = archivedText.getGlobalBounds().height + currentText.getLocalBounds().height + 2*marginy;
    (height/3 > textBounds)? dimentions.y = height/3: dimentions.y = textBounds;
    background.setSize(dimentions);
    background.setPosition(shiftx + x,shifty + height - background.getGlobalBounds().height);
    app->draw(background);
    sf::Vector2f pos = background.getPosition();



    archivedText.setPosition(pos);

    currentText.setPosition(pos.x, pos.y + background.getGlobalBounds().height - currentText.getGlobalBounds().height - marginy);
    currentText.setString(tempString);
    if(displayArchivedText)
        app->draw(archivedText);
    app->draw(currentText);
   }
}

void GUITextArea::setShift(float x, float y){
    shiftx = x;
    shifty = y;
}


GUI::GUI(int w, int h, Terrain* d): textArea(0,h,w/2,h/4), tooltip(1,1,3,3){

    height = h;
    width = w;
    dungeon = d;

    tooltip.toggleDisplay(false);
    tooltip.background.setFillColor(sf::Color::White);
    tooltip.setShift(0,0);
    tooltip.displayArchivedText=false;

    healthBar.barHandle = sf::RectangleShape(sf::Vector2f(10, 2));
	healthBar.curentValue = 1.f;
    healthBar.barHandle.setPosition(healthBar.posx, healthBar.posy);

    crosshair.crosshair = sf::RectangleShape(sf::Vector2f(5, 5));

   crosshair.crosshair.setFillColor(sf::Color::Cyan);
    //crosshair.crosshair.setPosition(sf::Vector2f(w/2,h/2));
    int orgx = crosshair.crosshair.getSize().x;
	int orgy = crosshair.crosshair.getSize().y;
    crosshair.crosshair.setOrigin(sf::Vector2f(orgx/2, orgy/2));


    crosshair.crosshair.setOutlineThickness(5.f);
    crosshair.crosshair.setOutlineColor(sf::Color::Blue);

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


    tooltip.x = x;
    tooltip.height = y;
    tooltip.toggleDisplay(true);
    tooltip.background.setSize(sf::Vector2f(w,h));

    setToolTipInfo(message);

}

void GUI::setToolTipInfo(sf::String message){
    tooltip.tempString = message;
}

void GUI::displayToolTip(bool bDisplay){
	tooltip.toggleDisplay(bDisplay);
}

void GUI::setHealth(float health){
    if(health*healthBar.max > healthBar.max)
        health = 1.f;
    healthBar.curentValue = health;
    healthBar.barHandle.setScale(.5*(health*healthBar.max), .5);
}

void GUI::mouseClick(){

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        if(crosshair.tileType == 0){
            float r = (static_cast<float>(rand())/ static_cast<float>(RAND_MAX))*3;
             crosshair.crosshair.setOutlineThickness(r);
             crosshair.crosshair.setScale(r/3, r/3);
        }
    }else{
         crosshair.crosshair.setOutlineThickness(3.f);
         crosshair.crosshair.setScale(.5, .5);
    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
        createToolTipArea(crosshair.x, crosshair.y, 20, 20, "test");

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

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
        clearLastCommand();
    }

    updateCrosshair(pos);

}

void GUI::draw(sf::RenderWindow *app){
    healthBar.barHandle.setPosition(shiftx + healthBar.posx, shifty + healthBar.posy);
    ammoBox.monitor.setPosition(shiftx + ammoBox.x, shifty + ammoBox.y);
     app->draw(healthBar.barHandle);
    app->draw(ammoBox.monitor);

    textArea.draw(app);

    tooltip.draw(app);

    app->draw(crosshair.crosshair);


}

void GUI::setCenter(float x, float y){
    shiftx = x;
    shifty = y;

      textArea.setShift(shiftx, shifty);
}

void GUI::processCommand(sf::String command){
    switch(lastCommand){
        case ' ':
            lastCommand = command[0];
            break;
        case '/':
            currentCommand += command;

            textArea.tempString = lastCommand + ": " +currentCommand;
            break;
    }

}

void GUI::clearLastCommand(){
    switch(lastCommand){
        case '/':
            textArea.addMessage(currentCommand);
            currentCommand = "";
            lastCommand = ' ';
            textArea.tempString = "";

            break;
    }
}
