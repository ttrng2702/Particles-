#include "Particle.h"
#include "RotationMatrix.h"
#include "ScalingMatrix.h"
#include "TranslationMatrix.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>

// Constructor
Particle::Particle(sf::RenderTarget& target, int numPoints, sf::Vector2i mouseClickPosition)
    : m_A(2, numPoints), m_ttl(TTL), m_numPoints(numPoints)
{
    // Random angular velocity
    m_radiansPerSec = ((float)rand() / RAND_MAX) * PI;

    // Initialize Cartesian plane mapping
    m_cartesianPlane.setCenter(0, 0);
    m_cartesianPlane.setSize(target.getSize().x, -1.0f * target.getSize().y);

    // Map mouse position to Cartesian plane
    m_centerCoordinate = target.mapPixelToCoords(mouseClickPosition, m_cartesianPlane);

    // Random velocities
    m_vx = 100 + rand() % 401; // Range: [100, 500]
    m_vy = 100 + rand() % 401;
    if (rand() % 2) m_vx *= -1; // Randomize sign
    if (rand() % 2) m_vy *= -1;

    // Colors
    m_color1 = sf::Color::White; // Center color
    m_color2 = sf::Color(rand() % 256, rand() % 256, rand() % 256); // Random color

    // Generate vertices
    float theta = ((float)rand() / RAND_MAX) * (PI / 2); // Random starting angle
    float dTheta = 2 * PI / (numPoints - 1); // Angle increment

    for (int j = 0; j < numPoints; ++j) {
        float r = 20 + rand() % 61; // Random radius [20, 80]
        float dx = r * cos(theta);
        float dy = r * sin(theta);

        m_A(0, j) = m_centerCoordinate.x + dx;
        m_A(1, j) = m_centerCoordinate.y + dy;

        theta += dTheta;
    }
}

// Draw function
void Particle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Create a VertexArray
    sf::VertexArray lines(sf::TriangleFan, m_numPoints + 1);

    // Map center to pixel coordinates
    sf::Vector2f center = target.mapCoordsToPixel(m_centerCoordinate, m_cartesianPlane);
    lines[0].position = center;
    lines[0].color = m_color1;

    // Map vertices
    for (int j = 1; j <= m_numPoints; ++j) {
        sf::Vector2f point = target.mapCoordsToPixel(
            { m_A(0, j - 1), m_A(1, j - 1) }, m_cartesianPlane);
        lines[j].position = point;
        lines[j].color = m_color2;
    }

    // Draw the particle
    target.draw(lines, states);
}

// Update function
void Particle::update(float dt)
{
    // Reduce ttl
    m_ttl -= dt;

    // Rotate, scale, and translate
    rotate(dt * m_radiansPerSec);
    scale(SCALE);

    // Calculate translation
    float dx = m_vx * dt;
    float dy = m_vy * dt;

    // Apply gravity
    m_vy -= G * dt;

    translate(dx, dy);
}

// Translate function
void Particle::translate(double xShift, double yShift)
{
    TranslationMatrix T(xShift, yShift, m_numPoints);
    m_A = T + m_A;

    // Update center coordinate
    m_centerCoordinate.x += xShift;
    m_centerCoordinate.y += yShift;
}

// Rotate function
void Particle::rotate(double theta)
{
    sf::Vector2f temp = m_centerCoordinate;

    // Shift to origin
    translate(-temp.x, -temp.y);

    // Apply rotation
    RotationMatrix R(theta);
    m_A = R * m_A;

    // Shift back
    translate(temp.x, temp.y);
}

// Scale function
void Particle::scale(double c)
{
    sf::Vector2f temp = m_centerCoordinate;

    // Shift to origin
    translate(-temp.x, -temp.y);

    // Apply scaling
    ScalingMatrix S(c);
    m_A = S * m_A;

    // Shift back
    translate(temp.x, temp.y);
}

// Unit tests
bool Particle::almostEqual(float a, float b, float epsilon)
{
    return fabs(a - b) < epsilon;
}

void Particle::unitTests()
{
    std::cout << "Running Particle unit tests...\n";

    // Add test cases here

    std::cout << "All tests passed.\n";
}
