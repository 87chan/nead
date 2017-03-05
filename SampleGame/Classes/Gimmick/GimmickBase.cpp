#include "GimmickBase.h"
#include "AppHeader.h"

GimmickBase::GimmickBase()
{}

void GimmickBase::Initialize(b2World* world, cocos2d::CCNode* parentNode, const cocos2d::Vec2& pos, float size)
{
	MyDrawNode::Initialize(world, parentNode);

	DrawData = cocos2d::CCDrawNode::create();
	this->addChild(DrawData);

	/* 物理エンジン上の物質の定義 */
	b2BodyDef rectBodyDef;

	/*
	物体の力に対する属性
	b2_dynamicBody: 速度があり力に反応する
	b2_staticBody: 速度が無く力に反応しない
	b2_kinematicBody: 速度があり力に反応しない
	*/
	rectBodyDef.type = b2_staticBody;

	/* 物理エンジンの空間上の座標 */
	rectBodyDef.userData = DrawData;

	/* 物理エンジン上の物質作成 */
	BodyData = world->CreateBody(&rectBodyDef);
}

void GimmickBase::Finalize(b2World* world, cocos2d::CCNode* parentNode)
{
	MyDrawNode::Finalize(world, parentNode);
}

void GimmickBase::UpdateBody(float delta)
{
	MyDrawNode::UpdateBody(delta);
}

void GimmickBase::Update(float delta)
{
	this->UpdateBody(delta);
}

/**************************************************************************************************
*!	EOF
**************************************************************************************************/
