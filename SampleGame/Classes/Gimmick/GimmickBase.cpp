#include "GimmickBase.h"

GimmickBase::GimmickBase()
{}

void GimmickBase::Initialize(b2World* world, cocos2d::CCNode* parentNode)
{
	MyDrawNode::Initialize(world, parentNode);
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
