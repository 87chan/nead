#include "GimmickAccelerate.h"
#include "AppHeader.h"
#include "Ball/MyBall.h"

USING_NS_CC;

GimmickAccelerate::GimmickAccelerate()
{
}

void GimmickAccelerate::Initialize(b2World* world, cocos2d::CCNode* parentNode)
{
	GimmickBase::Initialize(world, parentNode);

	Size size = Director::getInstance()->getWinSize();

	float s = 32;
	Vec2 pos = Vec2(200.0f, 100.0f);

	DrawData = cocos2d::CCDrawNode::create();
	this->DrawRect(
		Vec2(-s * 0.5f, -s * 0.5f),
		Vec2(-s * 0.5f,s * 0.5f),
		Vec2(s * 0.5f, s * 0.5f),
		Vec2(s * 0.5f, -s * 0.5f),
		ccColor4F::BLUE);
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
	rectBodyDef.position.Set(
		pos.x / PTM_RATIO,
		pos.y / PTM_RATIO);
	rectBodyDef.userData = DrawData;

	/* �����G���W����̕����쐬 */
	BodyData = world->CreateBody(&rectBodyDef);
	b2MassData massData = b2MassData();
	massData.center = BodyData->GetWorldCenter();
	massData.mass = DEFAULT_MASS;
	BodyData->SetMassData(&massData);

	/* �����G���W����̕����̌`�Ƒ傫�� */
	b2CircleShape spriteShape;
	spriteShape.m_radius = s * 0.5f / PTM_RATIO;

	b2FixtureDef spriteFixturedef;
	spriteFixturedef.shape = &spriteShape;
	spriteFixturedef.isSensor = true; // ���m�̂ݍs��.

	/* �����̐�����`�K�p */
	BodyData->CreateFixture(&spriteFixturedef);
}

void GimmickAccelerate::Finalize(b2World* world, cocos2d::CCNode* parentNode)
{
	GimmickBase::Finalize(world, parentNode);
}

void GimmickAccelerate::UpdateBody(float dt)
{
	GimmickBase::UpdateBody(dt);
}

void GimmickAccelerate::OnContactBegin(b2Body* body1, b2Body* body2)
{
	GimmickBase::OnContactBegin(body1, body2);

	static float POWER = 1000;

	// ��������{�[����b2body���擾���A��x�����͂�������.
	MyBall* ball1 = static_cast<MyBall*>(body1->GetUserData());
	MyBall* ball2 = static_cast<MyBall*>(body2->GetUserData());
	if (ball1 && ball1->getTag() == TAG_BALL)
	{
		b2Vec2 power = body1->GetLinearVelocity();
		power.x *= POWER;
		power.y *= POWER;
		body1->SetLinearVelocity(power);
	}
	else if (ball2 && ball2->getTag() == TAG_BALL)
	{
		b2Vec2 power = body2->GetLinearVelocity();
		power.x *= POWER;
		power.y *= POWER;
		body2->SetLinearVelocity(power);
	}
}

/**************************************************************************************************
*!	EOF
**************************************************************************************************/
