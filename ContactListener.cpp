#include "ContactListener.hpp"

    void ContactListener::Add(const b2ContactPoint* point)
    {
        if (/*test->*/m_pointCount == k_maxContactPoints)
        {
            return;
        }

        ContactPoint* cp = /*test->*/m_points + /*test->*/m_pointCount;
        cp->shape1 = point->shape1;
        cp->shape2 = point->shape2;
        cp->position = point->position;
        cp->normal = point->normal;
        cp->id = point->id;
        cp->state = e_contactAdded;

        ++/*test->*/m_pointCount;
    }

    void ContactListener::Persist(const b2ContactPoint* point)
    {
        if (/*test->*/m_pointCount == k_maxContactPoints)
        {
            return;
        }

        ContactPoint* cp = /*test->*/m_points + /*test->*/m_pointCount;
        cp->shape1 = point->shape1;
        cp->shape2 = point->shape2;
        cp->position = point->position;
        cp->normal = point->normal;
        cp->id = point->id;
        cp->state = e_contactPersisted;

        ++/*test->*/m_pointCount;
    }

    void ContactListener::Remove(const b2ContactPoint* point)
    {
        if (/*test->*/m_pointCount == k_maxContactPoints)
        {
            return;
        }

        ContactPoint* cp = /*test->*/m_points + /*test->*/m_pointCount;
        cp->shape1 = point->shape1;
        cp->shape2 = point->shape2;
        cp->position = point->position;
        cp->normal = point->normal;
        cp->id = point->id;
        cp->state = e_contactRemoved;

        ++/*test->*/m_pointCount;
    }
