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

	DrawData = cocos2d::CCDrawNode::create();
	DrawData->drawCircle(Vec2::ZERO, size, 0.0f, 64, false, ccColor4F::RED);
	this->addChild(DrawData);

	/* �����G���W����̕����̒�` */
	b2BodyDef rectBodyDef;
	/*
	���̗̂͂ɑ΂��鑮��
	b2_dynamicBody: ���x������͂ɔ�������
	b2_staticBody: ���x�������͂ɔ������Ȃ�
	b2_kinematicBody: ���x������͂ɔ������Ȃ�
	*/
	rectBodyDef.type = b2_staticBody;

	/* �����G���W���̋�ԏ�̍��W */
	rectBodyDef.userData = DrawData;

	/* �����G���W����̕����쐬 */
	BodyData = world->CreateBody(&rectBodyDef);
	b2MassData massData = b2MassData();
	massData.center = BodyData->GetWorldCenter();
	massData.mass = DEFAULT_MASS;
	BodyData->SetMassData(&massData);

	/* �����G���W����̕����̌`�Ƒ傫�� */
	b2CircleShape spriteShape;
	spriteShape.m_radius = size / PTM_RATIO;

	b2FixtureDef spriteFixturedef;
	spriteFixturedef.shape = &spriteShape;
	spriteFixturedef.isSensor = true; // ���m�̂ݍs��.

	/* �����̐�����`�K�p */
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

	// �X�e�[�W�N���A.
	if (SceneGameMain* sceneMain = static_cast<SceneGameMain*>(ParentRef))
	{
		sceneMain->ClearCallback();
	}
}

/**************************************************************************************************
*!	EOF
**************************************************************************************************/
