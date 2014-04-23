#ifndef ANIMATIONSEQUENCE_H
#define ANIMATIONSEQUENCE_H

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

class AnimationSequence {

    public:

        float x, y;         // sprite locations

        int frameCount;     // number of frames
        float frameLength;  // speed of animation

        bool playing = true;

        AnimationSequence(std::string path, int frameNum, float speed);    // path starts at 0, steps up from there
        void update(float elapsedTime);
        void draw(sf::RenderWindow *app);
    
        void stop();
        void play();
        void restart();
        void playOnce();    // might use for attacks and the like

    private:

        int currentFrame = 0;   // current position in animation
        float frameTime;    // time on current frame

        sf::Texture texture;
        std::vector<sf::Sprite> sprites;


};

#endif // ANIMATIONSEQUENCE_H
