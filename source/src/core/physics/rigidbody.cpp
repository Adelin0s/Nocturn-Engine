#include "rigidbody.h"

#include <cmath>

namespace Nocturn::core
{
    Rigidbody::Rigidbody() noexcept
    :   m_mass                               	(1.0f)
    ,   m_position								(0.0f)
    ,   m_velocity                            	(0.0f)
    ,   m_acceleration                        	(0.0f)
    { }

    Rigidbody::Rigidbody(float mass, const glm::vec3 &position, const glm::vec3 &velocity, const glm::vec3 &acceleration)
    :   m_mass									(mass)
    ,   m_position                              (position)
    ,   m_velocity                              (velocity)
    ,   m_acceleration                          (acceleration) 
    { }

    const glm::vec3 &Rigidbody::getPosition() const
    {
        return m_position;
    }

    void Rigidbody::update(float dt)
    {
        m_position += m_velocity * dt + 0.5f * m_acceleration * (dt * dt);
        m_velocity += m_acceleration * dt;
    }

    void Rigidbody::applyForce(const glm::vec3 &force)
    {
        m_acceleration += force / m_mass;
    }

    void Rigidbody::applyForce(const glm::vec3 &direction, const float magnitude)
    {
        applyForce(direction * magnitude);
    }

    void Rigidbody::applyAcceleration(const glm::vec3 &acceleration)
    {
        m_acceleration += acceleration;
    }

    void Rigidbody::applyAcceleration(const glm::vec3 &direction, const float magnitude)
    {
        applyForce(direction * magnitude);
    }

    void Rigidbody::applyImpulse(const glm::vec3 &force, const float dt)
    {
        m_velocity += force / m_mass * dt;
    }

    void Rigidbody::applyImpulse(const glm::vec3 &direction, const float magnitude, const float dt)
    {
        applyImpulse(direction * magnitude, dt);
    }

    void Rigidbody::transferEnergy(float joules, glm::vec3 direction)
    {
        if (joules == 0)
        {
            return;
        }

        // comes from formula: KE = 1/2 * m * v^2
        glm::vec3 deltaV = direction * (float)sqrt(2 * std::abs(joules) / m_mass);

        m_velocity += joules > 0 ? deltaV : -deltaV;
    }
}