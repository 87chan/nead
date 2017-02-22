#include "GimmickAccelerate.h"

GimmickAccelerate::GimmickAccelerate()
{
}

GimmickAccelerate::~GimmickAccelerate()
{
}

void GimmickAccelerate::Initialize(b2World* world, cocos2d::Layer* parentLayer)
{
	GimmickBase::Initialize(world, parentLayer);
}

void GimmickAccelerate::Finalize(b2World* world, cocos2d::Layer* parentLayer)
{
	GimmickBase::Finalize(world, parentLayer);
}

void GimmickAccelerate::UpdateBody(float dt)
{
	GimmickBase::UpdateBody(dt);
}

void GimmickAccelerate::OnContactBegin()
{
	// 引数からボールのb2bodyを取得し、一度だけ力を加える.
}

/**************************************************************************************************
*!	EOF
**************************************************************************************************/
