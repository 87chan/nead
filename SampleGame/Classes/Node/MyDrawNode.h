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

	virtual void Initialize(b2World* world, cocos2d::CCNode* parentNode) override;
	virtual void Finalize(b2World* world, cocos2d::CCNode* parentNode) override;
	virtual void UpdateBody(float dt) override;

	void Clear() { DrawData->clear(); }
	void DrawLine(const cocos2d::Vec2 &origin, const cocos2d::Vec2 &destination, const cocos2d::Color4F &color){ DrawData->drawLine(origin, destination, color); }
	void DrawCirlce(const cocos2d::Vec2& center, float radius, float angle, unsigned int segments, bool drawLineToCenter, const cocos2d::Color4F& color) { DrawData->drawCircle(center, radius, angle, segments, drawLineToCenter, color); }
	void DrawRect(const cocos2d::Vec2& pos1, const cocos2d::Vec2& pos2, const cocos2d::Vec2& pos3, const cocos2d::Vec2& pos4, const cocos2d::Color4F& color) { DrawData->drawRect(pos1, pos2, pos3, pos4, color); }

	void SetDrawPos(cocos2d::Vec2 pos);
	cocos2d::Vec2 GetDrawPos()const { return DrawData->getPosition(); }

protected:
	cocos2d::CCDrawNode*	DrawData;
};

/**************************************************************************************************
* EOF
**************************************************************************************************/
