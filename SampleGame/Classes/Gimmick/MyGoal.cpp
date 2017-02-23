#include "MyGoal.h"
#include "AppHeader.h"

USING_NS_CC;

//static const Vec2 GOAL_POS = Vec2(400.0f, 180.0f);
//static const float GOAL_SIZE = 32.0f;

MyGoal::MyGoal()
    : GoalPos()
    , GoalSize(0.0f)
{
}

MyGoal::~MyGoal()
{
}

void MyGoal::InitParamInfo(const Vec2& pos, float size)
{
    this->GoalPos = pos;
    this->GoalSize = size;
}

void MyGoal::Initialize(b2World* world, cocos2d::CCNode* parentNode)
{
	MyDrawNode::Initialize(world, parentNode);

	Size size = Director::getInstance()->getWinSize();

	DrawData = cocos2d::CCDrawNode::create();
    DrawData->drawCircle(GoalPos, GoalSize * 0.5f, 0.0f, 64, false, ccColor4F::RED);
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
	rectBodyDef.position.Set(
        GoalPos.x / PTM_RATIO,
        GoalPos.y / PTM_RATIO);
	rectBodyDef.userData = DrawData;

	/* �����G���W����̕����쐬 */
	BodyData = world->CreateBody(&rectBodyDef);
	b2MassData massData = b2MassData();
	massData.center = BodyData->GetWorldCenter();
	massData.mass = DEFAULT_MASS;
	BodyData->SetMassData(&massData);

	/* �����G���W����̕����̌`�Ƒ傫�� */
	b2CircleShape spriteShape;
    spriteShape.m_radius = GoalSize * 0.5f / PTM_RATIO;

	/* �����̐�����`�i�`�A���x�A���C�j */
	b2FixtureDef spriteFixturedef;
	spriteFixturedef.shape = &spriteShape;
	spriteFixturedef.density = DEFAULT_DENSITY;
	spriteFixturedef.restitution = DEFAULT_RESTITUTION;
	spriteFixturedef.friction = DEFAULT_FRICTION;

	/* �����̐�����`�K�p */
	BodyData->CreateFixture(&spriteFixturedef);
}

void MyGoal::Finalize(b2World* world, cocos2d::CCNode* parentNode)
{
	MyDrawNode::Finalize(world, parentNode);
}

/**************************************************************************************************
* EOF
**************************************************************************************************/