#pragma once

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "AppHeader.h"
#include <vector>

namespace ContactTiming
{
	enum CONTACT_TIMING
	{
		NONE,

		BEGIN, // �G�ꂽ��.
		END,   // ���ꂽ��.
	};
}

typedef std::function<void(b2Body*, b2Body*)> ContactCallback;

struct ContactEntryParam
{
	ContactEntryParam()
		: body1(nullptr)
		, body2(nullptr)
		, timing(ContactTiming::NONE)
	{}

	b2Body* body1;
	b2Body* body2;
	ContactTiming::CONTACT_TIMING timing;
	ContactCallback callback;
};

class MyContactListener : public b2ContactListener
{
public:
	static MyContactListener* GetInstance()
	{
		if (!Instance)
		{
			Instance.reset(new MyContactListener());
		}

		return Instance.get();
	}

	void EntryContactCallBack(ContactEntryParam param) { ParamList.push_back(param); }
	void RemoveContactCallback() { ParamList.clear(); }

	// �Փ˂��n�܂������Ɏ��s.
	virtual void BeginContact(b2Contact* contact);

	// �Փ˂��I��������Ɏ��s.
	virtual void EndContact(b2Contact* contact);

private:
	MyContactListener() {}
	static std::shared_ptr<MyContactListener> Instance;

private:
	std::vector<ContactEntryParam> ParamList;
};

/**************************************************************************************************
* EOF
**************************************************************************************************/
