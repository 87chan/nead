#include "MyContactListener.h"

std::shared_ptr<MyContactListener> MyContactListener::Instance;

void MyContactListener::BeginContact(b2Contact* contact)
{
	b2Body* body1 = static_cast<b2Body*>(contact->GetFixtureA()->GetBody());
	b2Body* body2 = static_cast<b2Body*>(contact->GetFixtureB()->GetBody());

	for (std::vector<ContactEntryParam>::iterator it = ParamList.begin(); it != ParamList.end(); ++it)
	{
		if (((body1 == it->body1 && body2 == it->body2)
			|| (body1 == it->body2 && body2 == it->body1))
			&& (*it).timing == ContactTiming::BEGIN)
		{
			it->callback(body1, body2);
		}
	}
}

void MyContactListener::EndContact(b2Contact* contact)
{
	b2Body* body1 = static_cast<b2Body*>(contact->GetFixtureA()->GetBody());
	b2Body* body2 = static_cast<b2Body*>(contact->GetFixtureB()->GetBody());

	for (std::vector<ContactEntryParam>::iterator it = ParamList.begin(); it != ParamList.end(); ++it)
	{
		if (((body1 == it->body1 && body2 == it->body2)
			|| (body1 == it->body2 && body2 == it->body1))
			&& (*it).timing == ContactTiming::END)
		{
			it->callback(body1, body2);
		}
	}
}

/**************************************************************************************************
* EOF
**************************************************************************************************/

