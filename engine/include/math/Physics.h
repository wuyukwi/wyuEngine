#include"math/Vector.h"


struct stPointMass
{
    stPointMass() : m(0) {}
    float m;
    Vector3f pos;
    Vector3f velocity;
    Vector3f force;
};


inline void ApplyForce(Vector3f force, stPointMass* m)
{
    if (m != 0) m->force += force;
}


inline void SimulateMass(float dt, stPointMass* m)
{
    // Calculate new velocity and position.
    if (m != 0)
    {
        m->velocity += (m->force / m->m) * dt;
        m->pos += m->velocity * dt;
    }
}

#endif