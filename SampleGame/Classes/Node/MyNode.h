#pragma once

#include "cocos2d.h"
#include "Box2D/Box2D.h"

class MyNode : public cocos2d::CCNode
{
public:
	MyNode();
	virtual ~MyNode();

	virtual void Initialize(b2World* world, cocos2d::CCNode* parentNode);
	virtual void Finalize(b2World* world, cocos2d::CCNode* parentNode);
	virtual void UpdateBody(float dt) {}
	void Remove();

	b2Body*	GetBodyData() { return BodyData; }
	const b2Body* GetBodyData() const{ return BodyData; }

	int GetUniqueID() const { return UniqueID; }

	CREATE_FUNC(MyNode);

protected:
	b2Body*			BodyData;

private:
	int				UniqueID;

private:
	static int		UniqueIDCounter;
};

/**************************************************************************************************
* EOF
**************************************************************************************************/
