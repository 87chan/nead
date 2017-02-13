#include "MyDrawNode.h"
#include "AppHeader.h"

USING_NS_CC;

MyDrawNode::MyDrawNode()
	: DrawData(nullptr)
{
}

MyDrawNode::~MyDrawNode()
{
}

void MyDrawNode::Initialize(b2World* world, cocos2d::Layer* parentLayer)
{
	MyNode::Initialize(world, parentLayer);

	DrawData = CCDrawNode::create();
	this->addChild(DrawData);
}

void MyDrawNode::Finalize(b2World* world, cocos2d::Layer* parentLayer)
{
	MyNode::Finalize(world, parentLayer);
}

void MyDrawNode::UpdateBody(float dt)
{
	MyNode::UpdateBody(dt);

	Vec2 position = Vec2(BodyData->GetPosition().x * PTM_RATIO, BodyData->GetPosition().y * PTM_RATIO);
	float rotation = -1 * CC_RADIANS_TO_DEGREES(BodyData->GetAngle());

	DrawData->setPosition(position);
	DrawData->setRotation(rotation);
}

/**************************************************************************************************
* EOF
**************************************************************************************************/
