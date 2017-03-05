#include "GimmickGoal.h"
#include "AppHeader.h"
#include "Scene/SceneGameMain.h"

USING_NS_CC;

GimmickGoal::GimmickGoal()
{
}

void GimmickGoal::Initialize(b2World* world, cocos2d::CCNode* parentNode, const cocos2d::Vec2& pos, float size)
{
	GimmickBase::Initialize(world, parentNode, pos, size);

	DrawData->drawCircle(Vec2::ZERO, size, 0.0f, 64, false, ccColor4F::RED);

	/* 物理エンジン上の物質の形と大きさ */
	b2CircleShape spriteShape;
	spriteShape.m_radius = size / PTM_RATIO;

	b2FixtureDef spriteFixturedef;
	spriteFixturedef.shape = &spriteShape;
	spriteFixturedef.isSensor = true; // 検知のみ行う.

	/* 物質の性質定義適用 */
	BodyData->CreateFixture(&spriteFixturedef);

	this->SetDrawPos(pos);
}

void GimmickGoal::Finalize(b2World* world, cocos2d::CCNode* parentNode)
{
	GimmickBase::Finalize(world, parentNode);
}

void GimmickGoal::UpdateBody(float dt)
{
	GimmickBase::UpdateBody(dt);
}

void GimmickGoal::OnContactBegin(b2Body* body1, b2Body* body2)
{
	GimmickBase::OnContactBegin(body1, body2);

	// ステージクリア.
	if (SceneGameMain* sceneMain = static_cast<SceneGameMain*>(this->getParent()))
	{
		sceneMain->ClearCallback();
	}
}

/**************************************************************************************************
*!	EOF
**************************************************************************************************/
