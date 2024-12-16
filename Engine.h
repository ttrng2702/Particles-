#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include "Particle.h"
#include <vector>

class Engine {
public:
    Engine();
    void run();

private:
    void input();
    void update(float dt);
    void render();
    
    sf::RenderWindow m_Window;
    std::vector<Particle> m_particles;
};

#endif // ENGINE_H
