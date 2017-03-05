#include "GimmickGravity.h"
#include "AppHeader.h"
#include "Ball/MyBall.h"

USING_NS_CC;

GimmickGravity::GimmickGravity()
{
}

void GimmickGravity::Initialize(b2World* world, cocos2d::CCNode* parentNode, const cocos2d::Vec2& pos, float size)
{
	GimmickBase::Initialize(world, parentNode, pos, size);

	this->DrawRect(
		Vec2(-size, -size),
		Vec2(-size, size),
		Vec2(size, size),
		Vec2(size, -size),
		ccColor4F::GRAY);

	/* 物理エンジン上の物質の形と大きさ */
	b2PolygonShape polyShape;
	polyShape.SetAsBox(size / PTM_RATIO, size / PTM_RATIO);

	b2FixtureDef spriteFixturedef;
	spriteFixturedef.shape = &polyShape;
	spriteFixturedef.isSensor = true; // 検知のみ行う.

	 /* 物質の性質定義適用 */
	BodyData->CreateFixture(&spriteFixturedef);

	this->SetDrawPos(pos);
}

void GimmickGravity::Finalize(b2World* world, cocos2d::CCNode* parentNode)
{
	GimmickBase::Finalize(world, parentNode);
}

void GimmickGravity::UpdateBody(float dt)
{
	GimmickBase::UpdateBody(dt);
}

void GimmickGravity::OnContactBegin(b2Body* body1, b2Body* body2)
{
	GimmickBase::OnContactBegin(body1, body2);

	WorldRef->SetGravity(WorldRef->GetGravity() * -1.0f);
}

/**************************************************************************************************
*!	EOF
**************************************************************************************************/
