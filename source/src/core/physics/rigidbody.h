/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 24-08-2021 11:57:36                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 03-12-2021 10:32:03                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <glm/glm.hpp>

namespace Nocturn::core
{
    class Rigidbody
    {
    public:
        Rigidbody() noexcept;
        Rigidbody(float mass, const glm::vec3 &position, const glm::vec3 &velocity, const glm::vec3 &acceleration);
        Rigidbody(const Rigidbody &rigidbody) = default; /* default behaviour  */
        Rigidbody(Rigidbody &&) = delete;

        Rigidbody &operator=(const Rigidbody &) = delete;
        Rigidbody &operator=(Rigidbody &&) = delete;

        /* void setPosition(const glm::vec3 &position); */
        /* void setVelocity(const glm::vec3 &velocity); */
        /* void setAcceleration(const glm::vec3 &acceleration); */

        const glm::vec3 &getPosition() const;

        void update(float dt);
        void applyForce(const glm::vec3 &force);
        void applyForce(const glm::vec3 &direction, const float magnitude);
        void applyAcceleration(const glm::vec3 &acceleration);
        void applyAcceleration(const glm::vec3 &direction, const float magnitude);
        void applyImpulse(const glm::vec3 &force, float dt);
        void applyImpulse(const glm::vec3 &direction, const float magnitude, const float dt);
        void transferEnergy(float joule, glm::vec3 direction);

        ~Rigidbody() = default;

    private:
        float m_mass;

        glm::vec3 m_position;
        glm::vec3 m_velocity;
        glm::vec3 m_acceleration;
    };
}
#endif