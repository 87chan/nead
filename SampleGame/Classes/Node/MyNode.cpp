#include "MyNode.h"
#include "AppHeader.h"

USING_NS_CC;

int MyNode::UniqueIDCounter = 0;

MyNode::MyNode()
: WorldRef(nullptr)
, ParentRef(nullptr)
, BodyData(nullptr)
, UniqueID(0)
{
}

MyNode::~MyNode()
{
}

void MyNode::Initialize(b2World* world, cocos2d::CCNode* parentNode)
{
	WorldRef = world;
	ParentRef = parentNode;

	UniqueID = UniqueIDCounter;

	++UniqueIDCounter;

	// �e�Ɏ�����R�t����.
	parentNode->addChild(this);
}

void MyNode::Finalize(b2World* world, cocos2d::CCNode* parentNode)
{
	// �����̎q���O��.
	this->removeAllChildren();

	// ���������[���h����O��.
	if (BodyData)
	{
		world->DestroyBody(BodyData);
	}

	// �e���玩�����O��.
	parentNode->removeChild(this);
}

void MyNode::Remove()
{
	this->removeAllChildren();
}

/**************************************************************************************************
* EOF
**************************************************************************************************/