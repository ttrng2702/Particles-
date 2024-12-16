#include "Particle.h"

Particle::Particle(sf::RenderTarget& target, int numPoints, sf::Vector2i mouseClickPosition)
    : m_A(2, numPoints), m_ttl(5.0f), m_numPoints(numPoints), m_radiansPerSec(rand() % 314 / 100.0f), 
      m_vx(rand() % 401 + 100), m_vy(rand() % 401 + 100), m_color1(sf::Color::White), m_color2(sf::Color::Green) {

    srand(static_cast<unsigned>(time(0))); // Initialize random number generator

    // Initialize the transformation matrix for Cartesian to screen coordinates
    m_cartesianPlane = sf::Transform();
    m_cartesianPlane.scale(target.getSize().x, -target.getSize().y); // Invert Y-axis
    
    // Map mouse click position to Cartesian plane (screen center -> origin)
    m_centerCoordinate = target.mapPixelToCoords(mouseClickPosition, m_cartesianPlane);
    setCenter(0, 0); // Set particle's center to the origin of the Cartesian plane
    
    // Generate numPoints for the particle's shape (vertices in Cartesian coordinates)
    float theta = static_cast<float>(rand() % 100) / 100.0f * 3.14159f / 2;  // Random angle between 0 and PI/2
    float dTheta = 2 * 3.14159f / (numPoints - 1);

    for (int j = 0; j < numPoints; ++j) {
        float r = rand() % 61 + 20; // Random radius between 20 and 80
        float dx = r * cos(theta);
        float dy = r * sin(theta);
        
        m_A(0, j) = m_centerCoordinate.x + dx; // X coordinate
        m_A(1, j) = m_centerCoordinate.y + dy; // Y coordinate
        
        theta += dTheta;
    }
}

void Particle::update(float dt) {
    m_ttl -= dt; // Decrease TTL with each frame

    if (isAlive()) {
        // Apply rotation, scaling, and translation transformations
        RotationMatrix rotation(m_radiansPerSec * dt);
        ScalingMatrix scaling(0.5f); // Scale by 0.5
        TranslationMatrix translation(10.0f, 5.0f); // Translate by (10, 5)
        
        m_A = translation * m_A;   // Apply translation
        m_A = scaling * m_A;       // Apply scaling
        m_A = rotation * m_A;      // Apply rotation

        // Apply velocity for movement (falling with gravity)
        m_vy -= 9.8f * dt;  // Apply gravity (simple physics)
        float dx = m_vx * dt;
        float dy = m_vy * dt;

        m_centerCoordinate.x += dx;
        m_centerCoordinate.y += dy;

        // Update particle's position by translating it
        TranslationMatrix move(dx, dy);
        m_A = move * m_A;
    }
}

void Particle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Create a VertexArray (TriangleFan) to draw the particle
    sf::VertexArray lines(sf::TrianglesFan, m_numPoints + 1);

    // Map Cartesian coordinates to screen coordinates
    sf::Vector2f center = target.mapCoordsToPixel(m_centerCoordinate, m_cartesianPlane);
    lines[0].position = center;
    lines[0].color = m_color1; // Center color is m_color1

    for (int j = 1; j <= m_numPoints; ++j) {
        sf::Vector2f vertex = target.mapCoordsToPixel(sf::Vector2f(m_A(0, j - 1), m_A(1, j - 1)), m_cartesianPlane);
        lines[j].position = vertex;
        lines[j].color = m_color2; // Outer points are m_color2
    }

    target.draw(lines, states);
}

void Particle::unitTests() {
    std::cout << "Running unit tests for Particle..." << std::endl;
    // Add specific unit test cases here.
    std::cout << "Unit tests completed!" << std::endl;
}
