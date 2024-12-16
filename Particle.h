#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>
#include "Matrix.h"
#include "RotationMatrix.h"
#include "ScalingMatrix.h"
#include "TranslationMatrix.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

class Particle : public sf::Drawable {
public:
    Particle(sf::RenderTarget& target, int numPoints, sf::Vector2i mouseClickPosition);
    virtual ~Particle() {}

    void update(float dt);
    void unitTests();
    
    // Function to check if particle's TTL has expired
    bool isAlive() const { return m_ttl > 0.0f; }

private:
    // Matrix representing the particle's vertices (Cartesian coordinates)
    Matrix m_A;
    float m_ttl; // Time to live
    int m_numPoints;
    float m_radiansPerSec; // Angular velocity
    float m_vx, m_vy; // Initial velocities in x and y
    sf::Color m_color1, m_color2;
    sf::Vector2f m_centerCoordinate;
    sf::Transform m_cartesianPlane; // Transformation matrix for Cartesian to screen coordinates

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif
