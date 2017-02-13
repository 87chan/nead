#pragma once

#include "MyNode.h"
#include "cocos2d.h"
#include "Box2D/Box2D.h"

class MyDrawNode : public MyNode
{
public:
	MyDrawNode();
	virtual ~MyDrawNode();

	CREATE_FUNC(MyDrawNode);

	virtual void Initialize(b2World* world, cocos2d::Layer* parentLayer) override;
	virtual void Finalize(b2World* world, cocos2d::Layer* parentLayer) override;
	void UpdateBody(float dt) override;

	void clear() { DrawData->clear(); }
	void drawLine(const cocos2d::Vec2 &origin, const cocos2d::Vec2 &destination, const cocos2d::Color4F &color){ DrawData->drawLine(origin, destination, color); }
	void drawCirlce(const cocos2d::Vec2 &center, float radius, float angle, unsigned int segments, bool drawLineToCenter, const cocos2d::Color4F &color) { DrawData->drawCircle(center, radius, angle, segments, drawLineToCenter, color); }

	cocos2d::Vec2 GetDrawPos()const { return DrawData->getPosition(); }

protected:
	cocos2d::CCDrawNode*	DrawData;
};

/**************************************************************************************************
* EOF
**************************************************************************************************/
