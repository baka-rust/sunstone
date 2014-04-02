#include "AnimationSequence.h"

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

AnimationSequence::AnimationSequence(std::string path, int frameNum, float speed) {

    frameCount = frameNum;
    frameLength = speed;

    frames.resize(frameNum);
    std::stringstream imagePath;

    for(int i=0; i<frameNum; i++) {
        imagePath << path << i << ".png";
        frames[i] = new sf::Texture();
        frames[i]->loadFromFile(imagePath.str());
        frames[i]->setSmooth(false);
        imagePath.str("");
    }

    sprite.setTexture(*frames[0]);

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

                sprite.setTexture(*frames[currentFrame]);
                frameTime = 0.0;
            }
        }
    }

}

void AnimationSequence::draw(sf::RenderWindow *app) {
    sprite.setPosition(x, y);
    app->draw(sprite);
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

