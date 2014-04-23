#include "AnimationSequence.h"

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

AnimationSequence::AnimationSequence(std::string path, int frameNum, float speed) {
    
    frameCount = frameNum;
    frameLength = speed;
    
    texture = sf::Texture();
    texture.loadFromFile(path + ".png");
    
    int frameWidth = texture.getSize().x / frameCount;
    int frameHeight = texture.getSize().y;
  
    sprites = std::vector<sf::Sprite>(frameNum);

    for(int i=0; i<frameNum; i++) {
        sprites[i] = sf::Sprite(texture, sf::IntRect(frameWidth * i, 0, frameHeight, frameWidth));
    }
}

void AnimationSequence::update(float elapsedTime) {

    frameTime = frameTime + elapsedTime;

    if(playing == true) {
        if(frameCount > 0){
            if(frameTime >= frameLength) {
                if(currentFrame < frameCount - 1) {
                    currentFrame++;
                }
                else {
                    currentFrame = 0;
                }

                frameTime = 0.0;
            }
        }
    }

}

void AnimationSequence::draw(sf::RenderWindow *app) {
    sprites[currentFrame].setPosition(x, y);
    app->draw(sprites[currentFrame]);
}

void AnimationSequence::stop() {
    playing = false;
}

void AnimationSequence::play() {
    playing = true;
}

void AnimationSequence::restart() {
    currentFrame = 0;
    frameTime = 0;
    playing = true;
}

