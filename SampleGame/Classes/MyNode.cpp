#include "MyNode.h"
#include "AppHeader.h"

USING_NS_CC;

int MyNode::UniqueIDCounter = 0;

MyNode::MyNode()
: BodyData(nullptr)
, UniqueID(0)
{
}

MyNode::~MyNode()
{
}

void MyNode::Initialize(b2World* world, cocos2d::Layer* parentLayer)
{
	UniqueID = UniqueIDCounter;

	++UniqueIDCounter;

	// 親に自分を紐付ける.
	parentLayer->addChild(this);
}

void MyNode::Finalize(b2World* world, cocos2d::Layer* parentLayer)
{
	// 自分の子を外す.
	this->removeAllChildren();

	// 物理をワールドから外す.
	if (BodyData)
	{
		world->DestroyBody(BodyData);
	}

	// 親から自分を外す.
	parentLayer->removeChild(this);
}

void MyNode::Remove()
{
	this->removeAllChildren();
}

/**************************************************************************************************
* EOF
**************************************************************************************************/