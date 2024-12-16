#include "Engine.h"

Engine::Engine() : m_Window(sf::VideoMode(800, 600), "Particle System") {
    m_Window.setFramerateLimit(60);
}

void Engine::run() {
    sf::Clock clock;

    while (m_Window.isOpen()) {
        input();
        float dt = clock.restart().asSeconds();
        update(dt);
        render();
    }
}

void Engine::input() {
    sf::Event event;
    while (m_Window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_Window.close();
        }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(m_Window);
        Particle p(m_Window, rand() % 26 + 25, mousePos); 
        m_particles.push_back(p);
    }
}

void Engine::update(float dt) {
    for (auto& p : m_particles) {
        p.update(dt);
    }
    
    // Remove particles that have expired
    m_particles.erase(
        std::remove_if(m_particles.begin(), m_particles.end(), [](const Particle& p) { return !p.isAlive(); }),
        m_particles.end()
    );
}

void Engine::render() {
    m_Window.clear();
    for (const auto& p : m_particles) {
        m_Window.draw(p);
    }
    m_Window.display();
}
