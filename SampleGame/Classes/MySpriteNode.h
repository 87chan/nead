#pragma once

#include "MyNode.h"
#include "cocos2d.h"
#include "Box2D/Box2D.h"

class MySpriteNode : public MyNode
{
public:
	MySpriteNode();
	~MySpriteNode();

	CREATE_FUNC(MySpriteNode);

	virtual void Initialize(b2World* world, cocos2d::Layer* parentLayer) override;
	virtual void Finalize(b2World* world, cocos2d::Layer* parentLayer) override;
	virtual void UpdateBody(float dt) override;

	void initWithTexture(cocos2d::Texture2D* tex) { SpriteData->initWithTexture(tex); }

	cocos2d::Sprite* GetSprite() { return SpriteData; }
	const cocos2d::Sprite* GetSprite() const { return SpriteData; }

	float GetSpriteWidth() const { return SpriteData->getContentSize().width; }
	float GetSpriteHeight() const { return SpriteData->getContentSize().height; }
	cocos2d::Vec2 GetSpritePos()const { return SpriteData->getPosition(); }

protected:
	cocos2d::CCSprite*	SpriteData;
};

/**************************************************************************************************
* EOF
**************************************************************************************************/
