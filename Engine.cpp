#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

Engine::Engine() {
    // Set up the RenderWindow
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    m_Window.create(desktopMode, "Particle System", sf::Style::Close);
}

void Engine::run() {
    // Create a clock to track time per frame
    sf::Clock clock;

    // Unit tests for Particle
    std::cout << "Starting Particle unit tests..." << std::endl;
    Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
    p.unitTests();
    std::cout << "Unit tests complete. Starting engine..." << std::endl;

    // Main game loop
    while (m_Window.isOpen()) {
        // Time differential since the last frame
        sf::Time elapsed = clock.restart();
        float dtAsSeconds = elapsed.asSeconds();

        // Handle input, update, and draw
        input();
        update(dtAsSeconds);
        draw();
    }
}

void Engine::input() {
    sf::Event event;

    while (m_Window.pollEvent(event)) {
        // Handle window close
        if (event.type == sf::Event::Closed) {
            m_Window.close();
        }

        // Handle Escape key
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            m_Window.close();
        }

        // Handle left mouse button click
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            // Generate particles at the mouse click position
            sf::Vector2i mousePos = sf::Mouse::getPosition(m_Window);
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dist(25, 50); // Range for numPoints

            for (int i = 0; i < 5; ++i) { // Create 5 particles
                int numPoints = dist(gen);
                m_particles.emplace_back(m_Window, numPoints, mousePos);
            }
        }
    }
}

void Engine::update(float dtAsSeconds) {
    // Iterator-based loop for updating particles
    for (auto it = m_particles.begin(); it != m_particles.end();) {
        if (it->getTTL() > 0.0f) {
            it->update(dtAsSeconds);
            ++it; // Move to the next particle
        } else {
            it = m_particles.erase(it); // Erase and update iterator
        }
    }
}

void Engine::draw() {
    // Clear the window
    m_Window.clear();

    // Draw all particles
    for (const auto& particle : m_particles) {
        m_Window.draw(particle);
    }

    // Display the window
    m_Window.display();
}
