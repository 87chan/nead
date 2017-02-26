#pragma once

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "GimmickBase.h"

// �G�ꂽ��X�e�[�W�N���A.
// Todo:���E�ςɍ��킹�āA�z�����܂��悤�ȕ\�������������.

class GimmickGoal : public GimmickBase
{
public:
	GimmickGoal();
	~GimmickGoal() {}

	void Initialize(b2World* world, cocos2d::CCNode* parentNode, const cocos2d::Vec2& pos, float size) override;
	void Finalize(b2World* world, cocos2d::CCNode* parentNode) override;
	void UpdateBody(float dt) override;

	void OnContactBegin(b2Body* body1, b2Body* body2) override;
};

/**************************************************************************************************
*!	EOF
**************************************************************************************************/
