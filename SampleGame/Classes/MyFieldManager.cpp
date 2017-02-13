#include "MyFieldManager.h"
#include "AppHeader.h"

USING_NS_CC;

MyFieldManager::MyFieldManager()
: FrameBody(nullptr)
{
}

MyFieldManager::~MyFieldManager()
{
}

void MyFieldManager::Initialize(b2World* world, cocos2d::Layer* parentLayer)
{
	MyNode::Initialize(world, parentLayer);

	this->CreateFrame(world);
}

void MyFieldManager::Finalize(b2World* world, cocos2d::Layer* parentLayer)
{
	MyNode::Finalize(world, parentLayer);
}

void MyFieldManager::CreateFrame(b2World* world)
{
	// ���̐ݒ�
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);
	groundBodyDef.type = b2_staticBody;

	//���̃{�f�B�쐬  
	FrameBody = world->CreateBody(&groundBodyDef);

	//����ӏ��쐬  
	b2EdgeShape edge;
	b2FixtureDef groundFixtureDef;
	groundFixtureDef.shape = &edge;
	groundFixtureDef.density = DEFAULT_DENSITY;
	groundFixtureDef.restitution = DEFAULT_RESTITUTION;
	groundFixtureDef.friction = DEFAULT_FRICTION;

	Size size = Director::getInstance()->getWinSize();

	//���̕�  
	edge.Set(b2Vec2(0, size.height / PTM_RATIO), b2Vec2(0, 0));
	FrameBody->CreateFixture(&groundFixtureDef);

	//��̕�  
	edge.Set(b2Vec2(0, 0), b2Vec2(size.width / PTM_RATIO, 0));
	FrameBody->CreateFixture(&groundFixtureDef);

	//�E�̕�  
	edge.Set(b2Vec2(size.width / PTM_RATIO, 0), b2Vec2(size.width / PTM_RATIO, size.height / PTM_RATIO));
	FrameBody->CreateFixture(&groundFixtureDef);

	//��̕�  
	edge.Set(b2Vec2(size.width / PTM_RATIO, size.height / PTM_RATIO), b2Vec2(0, size.height / PTM_RATIO));
	FrameBody->CreateFixture(&groundFixtureDef);
}

/**************************************************************************************************
* EOF
**************************************************************************************************/
