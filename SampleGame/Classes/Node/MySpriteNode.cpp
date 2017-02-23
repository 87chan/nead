#include "MySpriteNode.h"
#include "AppHeader.h"

USING_NS_CC;

MySpriteNode::MySpriteNode()
: SpriteData(nullptr)
{
}

MySpriteNode::~MySpriteNode()
{
}

void MySpriteNode::Initialize(b2World* world, cocos2d::CCNode* parentNode)
{
	MyNode::Initialize(world, parentNode);
}

void MySpriteNode::Finalize(b2World* world, cocos2d::CCNode* parentNode)
{
	MyNode::Finalize(world, parentNode);
}

void MySpriteNode::UpdateBody(float dt)
{
	MyNode::UpdateBody(dt);

	Vec2 position = Vec2(BodyData->GetPosition().x * PTM_RATIO, BodyData->GetPosition().y * PTM_RATIO);
	float rotation = -1 * CC_RADIANS_TO_DEGREES(BodyData->GetAngle());

	SpriteData->setPosition(position);
	SpriteData->setRotation(rotation);
}

/**************************************************************************************************
* EOF
**************************************************************************************************/
