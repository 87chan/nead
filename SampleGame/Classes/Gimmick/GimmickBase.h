#pragma once

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Node/MyDrawNode.h"

class GimmickManager;

class GimmickBase : public MyDrawNode
{
public:
	GimmickBase();
	virtual ~GimmickBase() {}

	virtual void Initialize(b2World* world, cocos2d::CCNode* parentNode, const cocos2d::Vec2& pos, float size);
	virtual void Finalize(b2World* world, cocos2d::CCNode* parentNode) override;
	virtual void UpdateBody(float delta) override;
	virtual void Update(float delta) override;

	// ‰½‚©‚ÉG‚ê‚ç‚ê‚½‚ÉŒÄ‚Î‚ê‚éˆ—.
	virtual void OnContactBegin(b2Body* body1, b2Body* body2) {}
	
	// ‰½‚©‚ª—£‚ê‚½‚ÉŒÄ‚Î‚ê‚éˆ—.
	virtual void OnContactEnd(b2Body* body1, b2Body* body2) {}
};

/**************************************************************************************************
*!	EOF
**************************************************************************************************/
