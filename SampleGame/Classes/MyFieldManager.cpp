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
	// 箱の設定
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);
	groundBodyDef.type = b2_staticBody;

	//箱のボディ作成  
	FrameBody = world->CreateBody(&groundBodyDef);

	//判定箇所作成  
	b2EdgeShape edge;
	b2FixtureDef groundFixtureDef;
	groundFixtureDef.shape = &edge;
	groundFixtureDef.density = DEFAULT_DENSITY;
	groundFixtureDef.restitution = DEFAULT_RESTITUTION;
	groundFixtureDef.friction = DEFAULT_FRICTION;

	Size size = Director::getInstance()->getWinSize();

	//左の壁  
	edge.Set(b2Vec2(0, size.height / PTM_RATIO), b2Vec2(0, 0));
	FrameBody->CreateFixture(&groundFixtureDef);

	//底の壁  
	edge.Set(b2Vec2(0, 0), b2Vec2(size.width / PTM_RATIO, 0));
	FrameBody->CreateFixture(&groundFixtureDef);

	//右の壁  
	edge.Set(b2Vec2(size.width / PTM_RATIO, 0), b2Vec2(size.width / PTM_RATIO, size.height / PTM_RATIO));
	FrameBody->CreateFixture(&groundFixtureDef);

	//上の壁  
	edge.Set(b2Vec2(size.width / PTM_RATIO, size.height / PTM_RATIO), b2Vec2(0, size.height / PTM_RATIO));
	FrameBody->CreateFixture(&groundFixtureDef);
}

/**************************************************************************************************
* EOF
**************************************************************************************************/
