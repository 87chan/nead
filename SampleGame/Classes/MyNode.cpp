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

	// �e�Ɏ�����R�t����.
	parentLayer->addChild(this);
}

void MyNode::Finalize(b2World* world, cocos2d::Layer* parentLayer)
{
	// �����̎q���O��.
	this->removeAllChildren();

	// ���������[���h����O��.
	if (BodyData)
	{
		world->DestroyBody(BodyData);
	}

	// �e���玩�����O��.
	parentLayer->removeChild(this);
}

void MyNode::Remove()
{
	this->removeAllChildren();
}

/**************************************************************************************************
* EOF
**************************************************************************************************/