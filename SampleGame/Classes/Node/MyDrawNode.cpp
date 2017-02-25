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

void MyDrawNode::Initialize(b2World* world, cocos2d::CCNode* parentNode)
{
	MyNode::Initialize(world, parentNode);

	DrawData = CCDrawNode::create();
	this->addChild(DrawData);
}

void MyDrawNode::Finalize(b2World* world, cocos2d::CCNode* parentNode)
{
	MyNode::Finalize(world, parentNode);
}

void MyDrawNode::UpdateBody(float dt)
{
	MyNode::UpdateBody(dt);

	Vec2 position = Vec2(BodyData->GetPosition().x * PTM_RATIO, BodyData->GetPosition().y * PTM_RATIO);
	float rotation = -1 * CC_RADIANS_TO_DEGREES(BodyData->GetAngle());

	DrawData->setPosition(position);
	DrawData->setRotation(rotation);
}

void MyDrawNode::SetDrawPos(cocos2d::Vec2 pos)
{
	if (BodyData)
	{
		BodyData->SetTransform(b2Vec2(pos.x / PTM_RATIO, pos.y / PTM_RATIO), 0.0f);
	}
}

/**************************************************************************************************
* EOF
**************************************************************************************************/
