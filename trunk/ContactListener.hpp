#ifndef CONTACTLISTENER_HPP
#define CONTACTLISTENER_HPP

#include "..\Box2D_v2.0.1\Box2D\Include\Box2D.h"

enum ContactState
{
	e_contactAdded,
	e_contactPersisted,
	e_contactRemoved,
};

struct ContactPoint
{
	b2Shape* shape1;
	b2Shape* shape2;
	b2Vec2 normal;
	b2Vec2 position;
	b2Vec2 velocity;
	b2ContactID id;
	ContactState state;
};

const int32 k_maxContactPoints = 2048;

class ContactListener : public b2ContactListener
{
public:
	void Add(const b2ContactPoint* point);
	void Persist(const b2ContactPoint* point);
	void Remove(const b2ContactPoint* point);

	//Test* test;
	ContactPoint m_points[k_maxContactPoints];
	int32 m_pointCount;
};


#endif
