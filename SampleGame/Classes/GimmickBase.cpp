#include "GimmickBase.h"

GimmickBase::GimmickBase()
{}

void GimmickBase::Initialize(b2World* world, cocos2d::Layer* parentLayer)
{
	MyDrawNode::Initialize(world, parentLayer);
}

void GimmickBase::Finalize(b2World* world, cocos2d::Layer* parentLayer)
{
	MyDrawNode::Finalize(world, parentLayer);
}

void GimmickBase::UpdateBody(float dt)
{
	MyDrawNode::UpdateBody(dt);
}

/**************************************************************************************************
*!	EOF
**************************************************************************************************/
