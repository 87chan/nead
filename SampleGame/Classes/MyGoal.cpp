#include "MyGoal.h"
#include "AppHeader.h"

USING_NS_CC;

static const Vec2 GOAL_POS = Vec2(400.0f, 180.0f);
static const float GOAL_SIZE = 32.0f;

MyGoal::MyGoal()
{
}

MyGoal::~MyGoal()
{
}

void MyGoal::Initialize(b2World* world, cocos2d::Layer* parentLayer)
{
	MyDrawNode::Initialize(world, parentLayer);

	Size size = Director::getInstance()->getWinSize();

	DrawData = cocos2d::CCDrawNode::create();
	DrawData->drawCircle(GOAL_POS, GOAL_SIZE * 0.5f, 0.0f, 64, false, ccColor4F::RED);
	this->addChild(DrawData);

	/* 物理エンジン上の物質の定義 */
	b2BodyDef rectBodyDef;
	/*
	物体の力に対する属性
	b2_dynamicBody: 速度があり力に反応する
	b2_staticBody: 速度が無く力に反応しない
	b2_kinematicBody: 速度があり力に反応しない
	*/
	rectBodyDef.type = b2_staticBody;

	/* 物理エンジンの空間上の座標 */
	rectBodyDef.position.Set(
		GOAL_POS.x / PTM_RATIO,
		GOAL_POS.y / PTM_RATIO);
	rectBodyDef.userData = DrawData;

	/* 物理エンジン上の物質作成 */
	BodyData = world->CreateBody(&rectBodyDef);
	b2MassData massData = b2MassData();
	massData.center = BodyData->GetWorldCenter();
	massData.mass = DEFAULT_MASS;
	BodyData->SetMassData(&massData);

	/* 物理エンジン上の物質の形と大きさ */
	b2CircleShape spriteShape;
	spriteShape.m_radius = GOAL_SIZE * 0.5f / PTM_RATIO;

	/* 物質の性質定義（形、密度、摩擦） */
	b2FixtureDef spriteFixturedef;
	spriteFixturedef.shape = &spriteShape;
	spriteFixturedef.density = DEFAULT_DENSITY;
	spriteFixturedef.restitution = DEFAULT_RESTITUTION;
	spriteFixturedef.friction = DEFAULT_FRICTION;

	/* 物質の性質定義適用 */
	BodyData->CreateFixture(&spriteFixturedef);
}

void MyGoal::Finalize(b2World* world, cocos2d::Layer* parentLayer)
{
	MyDrawNode::Finalize(world, parentLayer);
}

/**************************************************************************************************
* EOF
**************************************************************************************************/
