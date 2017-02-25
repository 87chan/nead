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

		BEGIN, // 触れた時.
		END,   // 離れた時.
	};
}

struct ContactEntryParam
{
	ContactEntryParam()
		: body1(nullptr)
		, body2(nullptr)
	{}

	template <class C, class T>
	void SetCallback(C& obj,T func)
	{
		callback = new MyCallback<C, T>(obj, func);
	}

	b2Body* body1;
	b2Body* body2;
	ContactTiming::CONTACT_TIMING timing;
	MyCallbackBase* callback;
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

	// 衝突が始まった時に実行.
	virtual void BeginContact(b2Contact* contact);

	// 衝突が終わった時に実行.
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
