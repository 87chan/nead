#pragma once

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "MyDrawNode.h"

class GimmickBase : public MyDrawNode
{
public:
	GimmickBase();
	virtual ~GimmickBase() {}

	virtual void Initialize(b2World* world, cocos2d::Layer* parentLayer) override;
	virtual void Finalize(b2World* world, cocos2d::Layer* parentLayer) override;
	virtual void UpdateBody(float dt) override;

	// ‰½‚©‚ÉG‚ê‚ç‚ê‚½‚ÉŒÄ‚Î‚ê‚éˆ—.
	virtual void OnContactBegin() {};
	
	// ‰½‚©‚ª—£‚ê‚½‚ÉŒÄ‚Î‚ê‚éˆ—.
	virtual void OnContactEnd() {};
};

/**************************************************************************************************
*!	EOF
**************************************************************************************************/
