#include "MyContactListener.h"

std::shared_ptr<MyContactListener> MyContactListener::Instance;

void MyContactListener::BeginContact(b2Contact* contact)
{
	b2Body* data1 = static_cast<b2Body*>(contact->GetFixtureA()->GetBody());
	b2Body* data2 = static_cast<b2Body*>(contact->GetFixtureB()->GetBody());

	for (std::vector<ContactEntryParam>::iterator it = ParamList.begin(); it != ParamList.end(); ++it)
	{
		if (((data1 == it->body1 && data2 == it->body2)
			|| (data1 == it->body2 && data2 == it->body1))
			&& (*it).timing == ContactTiming::BEGIN)
		{
			it->callback->Execute();
		}
	}
}

void MyContactListener::EndContact(b2Contact* contact)
{
	b2Body* data1 = static_cast<b2Body*>(contact->GetFixtureA()->GetBody());
	b2Body* data2 = static_cast<b2Body*>(contact->GetFixtureB()->GetBody());

	for (std::vector<ContactEntryParam>::iterator it = ParamList.begin(); it != ParamList.end(); ++it)
	{
		if (((data1 == it->body1 && data2 == it->body2)
			|| (data1 == it->body2 && data2 == it->body1))
			&& (*it).timing == ContactTiming::END)
		{
			it->callback->Execute();
		}
	}
}

/**************************************************************************************************
* EOF
**************************************************************************************************/

