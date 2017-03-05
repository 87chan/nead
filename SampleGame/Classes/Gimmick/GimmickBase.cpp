#include "GimmickBase.h"
#include "AppHeader.h"

GimmickBase::GimmickBase()
{}

void GimmickBase::Initialize(b2World* world, cocos2d::CCNode* parentNode, const cocos2d::Vec2& pos, float size)
{
	MyDrawNode::Initialize(world, parentNode);

	DrawData = cocos2d::CCDrawNode::create();
	this->addChild(DrawData);

	/* �����G���W����̕����̒�` */
	b2BodyDef rectBodyDef;

	/*
	���̗̂͂ɑ΂��鑮��
	b2_dynamicBody: ���x������͂ɔ�������
	b2_staticBody: ���x�������͂ɔ������Ȃ�
	b2_kinematicBody: ���x������͂ɔ������Ȃ�
	*/
	rectBodyDef.type = b2_staticBody;

	/* �����G���W���̋�ԏ�̍��W */
	rectBodyDef.userData = DrawData;

	/* �����G���W����̕����쐬 */
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
