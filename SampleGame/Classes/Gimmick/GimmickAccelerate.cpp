#include "GimmickAccelerate.h"
#include "AppHeader.h"
#include "Ball/MyBall.h"

USING_NS_CC;

GimmickAccelerate::GimmickAccelerate()
{
}

void GimmickAccelerate::Initialize(b2World* world, cocos2d::CCNode* parentNode, const cocos2d::Vec2& pos, float size)
{
	GimmickBase::Initialize(world, parentNode, pos, size);

	this->DrawRect(
		Vec2(-size, -size),
		Vec2(-size, size),
		Vec2(size, size),
		Vec2(size, -size),
		ccColor4F::BLUE);

	/* �����G���W����̕����̌`�Ƒ傫�� */
	b2PolygonShape polyShape;
	polyShape.SetAsBox(size / PTM_RATIO, size / PTM_RATIO);

	b2FixtureDef spriteFixturedef;
	spriteFixturedef.shape = &polyShape;
	spriteFixturedef.isSensor = true; // ���m�̂ݍs��.

	/* �����̐�����`�K�p */
	BodyData->CreateFixture(&spriteFixturedef);

	this->SetDrawPos(pos);
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
