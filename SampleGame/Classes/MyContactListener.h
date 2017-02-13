#pragma once

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "AppHeader.h"
#include <vector>

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
	MyCallbackBase* callback;
};

class MyContactListener : public b2ContactListener
{
public:
	MyContactListener();
	~MyContactListener();

	void EntryContactCallBack(ContactEntryParam param) { ParamList.push_back(param); }
	void RemoveContactCallback() { ParamList.clear(); }

	// 衝突が始まった時に実行
	virtual void BeginContact(b2Contact* contact);

	std::vector<ContactEntryParam> ParamList;
};

/**************************************************************************************************
* EOF
**************************************************************************************************/
