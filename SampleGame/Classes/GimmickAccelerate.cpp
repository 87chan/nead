#include "GimmickAccelerate.h"

GimmickAccelerate::GimmickAccelerate()
{
}

GimmickAccelerate::~GimmickAccelerate()
{
}

void GimmickAccelerate::Initialize(b2World* world, cocos2d::CCNode* parentNode)
{
	GimmickBase::Initialize(world, parentNode);
}

void GimmickAccelerate::Finalize(b2World* world, cocos2d::CCNode* parentNode)
{
	GimmickBase::Finalize(world, parentNode);
}

void GimmickAccelerate::UpdateBody(float dt)
{
	GimmickBase::UpdateBody(dt);
}

void GimmickAccelerate::OnContactBegin()
{
	// ��������{�[����b2body���擾���A��x�����͂�������.
}

/**************************************************************************************************
*!	EOF
**************************************************************************************************/
