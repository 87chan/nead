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
	rectBodyDef.position.Set(
		pos.x / PTM_RATIO,
		pos.y / PTM_RATIO);
	rectBodyDef.userData = DrawData;

	/* 物理エンジン上の物質作成 */
	BodyData = world->CreateBody(&rectBodyDef);
	b2MassData massData = b2MassData();
	massData.center = BodyData->GetWorldCenter();
	massData.mass = DEFAULT_MASS;
	BodyData->SetMassData(&massData);

	/* 物理エンジン上の物質の形と大きさ */
	b2CircleShape spriteShape;
	spriteShape.m_radius = s * 0.5f / PTM_RATIO;

	b2FixtureDef spriteFixturedef;
	spriteFixturedef.shape = &spriteShape;
	spriteFixturedef.isSensor = true; // 検知のみ行う.

	/* 物質の性質定義適用 */
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

	// 引数からボールのb2bodyを取得し、一度だけ力を加える.
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
