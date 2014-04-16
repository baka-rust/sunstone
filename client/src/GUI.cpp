#include "GUI.h"

GUIButton::GUIButton(int x, int y, std::string message, void (*cb)()){
    pos.x = x;
    pos.y = y;
    callback = cb;
    //For commit purposes

    if (!font.loadFromFile("resources/arial.ttf"))
    {
    // error...
    }

    text.setFont(font);
    text.setString(message);
    text.setCharacterSize(14);
    text.setColor(sf::Color::Yellow);
    text.setScale(.5,.5);
    text.scale(.5,.5);

    sf::Vector2f dimentions;
    dimentions.x = text.getGlobalBounds().width + margin;
    dimentions.y = text.getGlobalBounds().height + margin;
    background.setSize(dimentions);
    background.setFillColor(sf::Color::Blue);
    background.setOutlineThickness(1);
    background.setOutlineColor(sf::Color::Yellow);

}

void GUIButton::update(sf::RenderWindow* app){

     sf::FloatRect bounds = background.getGlobalBounds();
    sf::Vector2i mousePos = sf::Mouse::getPosition(*app);
    //std::cout << background.getPosition().y << "," << bounds.height << "," << app->mapPixelToCoords(mousePos).y << std::endl;
    if(bounds.contains(app->mapPixelToCoords(mousePos))){
        //std::cout << "hovering" <<std::endl;
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            buttonClicked();
       }
    }
}

void GUIButton::buttonClicked(){
    (*callback)();
    if(deleteOnClick){
        display = false;
    }

}

void GUIButton::draw(sf::RenderWindow* app){
    if(display){
        background.setPosition(app->mapPixelToCoords(pos));
        text.setPosition(background.getPosition().x + margin/2, background.getPosition().y + margin/2);
        app->draw(background);
        app->draw(text);
        update(app);
    }

}


GUITextArea::GUITextArea(int x, int y, int w, int h) {
    pos.x =x;
    pos.y = y;


    inputMessage = std::vector<std::string>(10," ");
    if (!font.loadFromFile("resources/arial.ttf"))
    {
    // error...
    }

    tempString = "Hi";
    addMessage(tempString);
    currentText.setFont(font);
    currentText.setString(inputMessage.back());
    currentText.setCharacterSize(14);
    currentText.setColor(sf::Color::Yellow);
    currentText.setScale(.5,.5);
    currentText.scale(.5,.5);

    archivedText.setFont(font);
    archivedText.setString(inputMessage.back());
    archivedText.setCharacterSize(14);
    archivedText.setColor(sf::Color::Yellow);
    archivedText.setScale(.5,.5);
    archivedText.scale(.5,.5);



    background.setPosition(x, y);
    dimentions.x = w;
    dimentions.y = h;
    background.setFillColor(sf::Color(0,0,255,100));//blue
    slider.setPosition(x,y);



}

GUITextArea::GUITextArea(){
    GUITextArea(0,0,1,1);
}

void GUITextArea::addMessage(std::string s){

    inputMessage.push_back(s);

     std::string str = "";
    for(int i = inputMessage.size()- startDisplayIndex; i < inputMessage.size(); i++){
        str += inputMessage[i];
        str += "\n";

    }
    archivedText.setString(str);

}

void GUITextArea::toggleDisplay(bool d){
    display = d;
    clock.restart();
}

void GUITextArea::draw(sf::RenderWindow* app){
   if(display){

    float textBounds;
    if(displayArchivedText)
        textBounds= archivedText.getGlobalBounds().height + currentText.getGlobalBounds().height + 2*marginy;
    else
    textBounds = currentText.getGlobalBounds().height + 2*marginy;

    if(dimentions.y < textBounds) dimentions.y = textBounds;
    float width;
    (archivedText.getGlobalBounds().width > currentText.getGlobalBounds().width)? width = archivedText.getGlobalBounds().width: width = currentText.getGlobalBounds().width;
    if(dimentions.x < width) dimentions.x = width;

    background.setSize(dimentions);

    sf::Vector2f worldPos = app->mapPixelToCoords(sf::Vector2i(pos.x, pos.y - dimentions.y));

    background.setPosition(worldPos);
    app->draw(background);
    sf::Vector2f backPos = background.getPosition();

    archivedText.setPosition(backPos);

    currentText.setPosition(archivedText.getPosition().x ,  archivedText.getPosition().y + marginy + archivedText.getGlobalBounds().height);
    currentText.setString(tempString);
    if(displayArchivedText)
        app->draw(archivedText);
    app->draw(currentText);
   }
   else{
        float closingPercent = clock.getElapsedTime().asSeconds()/closingTime;
        if(closingPercent <= 1 && closingPercent >= .1){
            slider.setPosition(background.getPosition());
            slider.setSize(background.getSize());
            slider.setScale(closingPercent, closingPercent);
            app->draw(slider);
        }

   }
}

void test(){
    std::cout << "Worked";
}

GUI::GUI(int w, int h): textArea(0,h-100,50,100), tooltip(1,1,3,3), testButton(30, 30, "Hi", test ){

    height = h;
    width = w;



    tooltip.toggleDisplay(false);
    tooltip.background.setFillColor(sf::Color::White);

    tooltip.displayArchivedText=false;

    healthBar.barHandle = sf::RectangleShape(sf::Vector2f(10, 5));
    healthBar.barHandle.setFillColor(sf::Color::Red);
	healthBar.curentValue = 1.f;
	healthBar.pos.x = 0;
	healthBar.pos.y = 0;
	setHealth(1.f);
    healthBar.barHandle.setPosition(healthBar.pos.x, healthBar.pos.y);

    crosshair.crosshair = sf::RectangleShape(sf::Vector2f(5, 5));

   crosshair.crosshair.setFillColor(sf::Color::Cyan);
    //crosshair.crosshair.setPosition(sf::Vector2f(w/2,h/2));
    int orgx = crosshair.crosshair.getSize().x;
	int orgy = crosshair.crosshair.getSize().y;
    crosshair.crosshair.setOrigin(sf::Vector2f(orgx/2, orgy/2));


    crosshair.crosshair.setOutlineThickness(5.f);
    crosshair.crosshair.setOutlineColor(sf::Color::Blue);

    switch(currentState){
        case MAIN:
        break;
        case LOGIN:
            textArea.addMessage(
                                "Welcome to SUNSTONE!\n To Start playing enter your name then a , Then your Port , and then your server address \n example:  John Doe, 84294, 12.121.12.12"
            );
    }



}



void GUI::createToolTipArea(int x, int y, int w, int h, std::string message){

    tooltip.pos.x = x;
    tooltip.pos.y = y;
    tooltip.dimentions.x  = w;
    tooltip.dimentions.y = h;
    tooltip.toggleDisplay(true);

    setToolTipInfo(message);

}

void GUI::setToolTipInfo(std::string message){
    tooltip.tempString = message;
}

void GUI::displayToolTip(bool bDisplay){
	tooltip.toggleDisplay(bDisplay);
}

void GUI::setHealth(float health){
    if(health*healthBar.max > healthBar.max)
        health = 1.f;
    healthBar.curentValue = health;
    healthBar.barHandle.setScale(.5*(health*healthBar.max), 1);
}

void GUI::mouseClick(){

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        if(crosshair.tileType < 3){
            float r = (static_cast<float>(rand())/ static_cast<float>(RAND_MAX))*3;
             crosshair.crosshair.setScale(r/3, r/3);
        }
    }else  if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
        createToolTipArea(crosshair.x, crosshair.y, 20, 20, "");
        std::cout << "\nCrosshair at " << crosshair.y;
        std::cout << "\n Tooltip at " << tooltip.background.getPosition().y;


    }else{
         crosshair.crosshair.setScale(.5, .5);
    }



}

void GUI::updateCrosshair(sf::RenderWindow *app){

   sf::Vector2i pixelPos = sf::Mouse::getPosition(*app);
    crosshair.x = pixelPos.x;
    crosshair.y = pixelPos.y;

    if(crosshair.x > width)
        crosshair.x = width;
    if(crosshair.x < 0)
        crosshair.x = 0;

    if(crosshair.y > height)
        crosshair.y = height;
    if(crosshair.y < 0)
        crosshair.y = 0;
/**
    ground = 0 ,
    wall ,
    door ,
    healthpack ,
    spawner
*/
    //divide by 15 since each tile is 16 wide
    sf::Vector2f worldPos = app->mapPixelToCoords(pixelPos);
    crosshair.crosshair.setPosition(worldPos);
  //  crosshair.tileType = dungeon->getTile(crosshair.x, crosshair.y, "low");
    switch(crosshair.tileType){
    case ground:
        setToolTipInfo("ground");
        break;
    case wall:
        setToolTipInfo("Wall");
        break;
    case door:
        setToolTipInfo("door");
        break;
    case healthpack:
        setToolTipInfo("Health pack");
        break;
    case spawner:
        setToolTipInfo("Spawner");
        break;
    }
    sf::Vector2f distance = crosshair.crosshair.getPosition() - tooltip.background.getPosition();
    float length = distance.x * distance.x + distance.y * distance.y;
    if(length > 100)
        tooltip.toggleDisplay(false);
    mouseClick();
}


void GUI::update(sf::RenderWindow *app){
    healthBar.barHandle.setPosition(app->mapPixelToCoords(healthBar.pos));
    updateCrosshair(app);

}

void GUI::draw(sf::RenderWindow *app){
   update(app);


    switch(currentState){
    case MAIN:

        app->draw(healthBar.barHandle);
        textArea.draw(app);
        tooltip.draw(app);
        app->draw(crosshair.crosshair);
    case LOGIN:
        textArea.draw(app);
        testButton.draw(app);
        app->draw(crosshair.crosshair);
        tooltip.draw(app);
    }

}


void GUI::processCommand(char command){
    //std::cout << command << " , " << static_cast<int>(command) <<std::endl;
    if(command == 13){//return
        clearLastCommand();
    }else{
        switch(currentState){
        case MAIN:
            switch(lastCommand){
                case ' ':
                    if(command != '?' && (command == '/'))
                    lastCommand = command;
                    break;
                case '/':
                     if(command == 8 && currentCommand.size() > 0){
                       currentCommand = currentCommand.substr(0, currentCommand.size() - 1 );
                    }else
                        currentCommand += command;
                    if(currentCommand.size() % 20 == 0)
                        currentCommand += "\n";
                    textArea.tempString =  "/: " +currentCommand;

                    textArea.toggleDisplay(true);
                    break;
            }
            break;
        case LOGIN:
                    lastCommand = '?';
                     if(command == 8 && currentCommand.size() > 0){
                       currentCommand = currentCommand.substr(0, currentCommand.size() - 1 );
                    }else
                    currentCommand += command;
                    textArea.tempString =  ": " +currentCommand;

        }
    }

}

void GUI::clearLastCommand(){
    switch(currentState){
        case MAIN:
            switch(lastCommand){
                case '/':
                    textArea.addMessage(currentCommand);
                    currentCommand = "";
                    lastCommand = ' ';
                    textArea.tempString = "";
                    textArea.toggleDisplay(false);
                    break;
                default:
                     currentCommand = "";
                    lastCommand = ' ';
                    textArea.tempString = "";
            }
            break;
        case LOGIN:
            switch(lastCommand){
            case '?':

                    int error = processLogin(currentCommand);
                    if(error == 1){
                        textArea.addMessage("Bad Port number");
                    }else if(error == 0){
                        textArea.addMessage("Good Login");
                        currentState = MAIN;
                        textArea.toggleDisplay(false);
                    }else{
                        std::ostringstream errorMessage(": Bad Login");
                        errorMessage << error;

                        textArea.addMessage(errorMessage.str());
                    }
                     currentCommand = "";
                    lastCommand = ' ';
                    textArea.tempString = "";

            }
            break;

    }


}

int GUI::processLogin(std::string input){
        std::string name;
        std::string portString;
        unsigned short port;
        std::string ip;
        int error = 0;

        std::istringstream ss(input);
        std::string token;

         std::getline(ss, token, ',');
         name = token;
        std::getline(ss, token, ',');
        portString = token;
        std::getline(ss, token, ',');
        ip = token;

        std::istringstream convert(portString);
        if(!(convert >> port)){
            error = 1;
        }

       error = network->login(name, port, ip);

        std::cout << name << " //" << portString << " //" << ip<< " //" <<std::endl;

        return error;
    }
