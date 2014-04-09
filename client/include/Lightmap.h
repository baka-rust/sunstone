#ifndef LIGHTMAP_H
#define LIGHTMAP_H

#include <SFML/Graphics.hpp>

class Lightmap : public sf::Drawable {
    
    public:
    
    private:
  
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // You can draw other high-level objects
        target.draw(m_sprite, states);
        // ... or use the low-level API
        states.texture = &m_texture;
        target.draw(m_vertices, states);
        // ... or draw with OpenGL directly
        glBegin(GL_QUADS);

        
        
        
        
        
        glEnd();
    }
    sf::Sprite m_sprite;
    sf::Texture m_texture;
    sf::VertexArray m_vertices;
    
};

#endif // LIGHTMAP_H