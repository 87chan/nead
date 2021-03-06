#include "MyBall.h"
#include "AppHeader.h"
#include "MyBallManager.h"
#include "Scene/SceneGameMain.h"

USING_NS_CC;

static const Vec2	SHOT_NUM_OFFSET = Vec2(0.0f, 20.0f);
static const float	NEXT_STANDBY_TIME = 3.0f;
static const float	SELECTED_CIRCLE_RADUIS_OFFSET = 3.0f;
static const float	STOPPED_VELOCITY_LENGTH = 0.1f;

MyBall::MyBall()
: BallMgrRef(nullptr)
, SpriteBatchNode(nullptr)
, LabelShotNum(nullptr)
, CircleSelected(nullptr)
, bSelected(false)
, bStandby(true)
, LeftShotNum(1)
, ShotMode(SHOT_MODE::SHOT_DEFAULT)
{
}

MyBall::~MyBall()
{
}

void MyBall::Initialize(b2World* world, cocos2d::CCNode* parentNode, MyBallManager* ballMgr, const cocos2d::Vec2& pos, int shotNum)
{
	MySpriteNode::Initialize(world, parentNode);

    LeftShotNum = shotNum;
	BallMgrRef = ballMgr;

	SpriteBatchNode = cocos2d::CCSpriteBatchNode::create("ball_16.png");
	this->addChild(SpriteBatchNode);

	LabelShotNum = cocos2d::LabelTTF::create("", "Arial", 24);
	LabelShotNum->setLocalZOrder(UI_LAYER);
	LabelShotNum->setVisible(true);
	this->addChild(LabelShotNum);

	CircleSelected = MyDrawNode::create();
	CircleSelected->setLocalZOrder(UI_LAYER);
	CircleSelected->Initialize(world, parentNode);

	Size size = Director::getInstance()->getWinSize();

	/* 画像の表示 */
	SpriteData = CCSprite::create();
	SpriteData->initWithTexture(SpriteBatchNode->getTexture());
	SpriteData->setPosition(pos);
	SpriteData->setTag(TAG_BALL);
	this->addChild(SpriteData);

	/* 物理エンジン上の物質の定義 */
	b2BodyDef spriteBodyDef;
	/*
	物体の力に対する属性
	b2_dynamicBody: 速度があり力に反応する
	b2_staticBody: 速度が無く力に反応しない
	b2_kinematicBody: 速度があり力に反応しない
	*/
	spriteBodyDef.type = b2_dynamicBody;

	/* 物理エンジンの空間上の座標 */
	spriteBodyDef.position.Set(
		SpriteData->getPositionX() / PTM_RATIO,
		SpriteData->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = SpriteData;

	/* 物理エンジン上の物質作成 */
	BodyData = world->CreateBody(&spriteBodyDef);
	b2MassData massData = b2MassData();
	massData.center = BodyData->GetWorldCenter();
	massData.mass = DEFAULT_MASS;
	BodyData->SetMassData(&massData);
	BodyData->SetLinearDamping(DEFAULT_LINEAR_DAMPLING);
	BodyData->SetAngularDamping(DEFAULT_ANGULAR_DAMPLING);

	/* 物理エンジン上の物質の形と大きさ */
	b2CircleShape spriteShape;
	spriteShape.m_radius = SpriteData->getContentSize().width * 0.5f / PTM_RATIO;

	/* 物質の性質定義（形、密度、摩擦） */
	b2FixtureDef spriteFixturedef;
	spriteFixturedef.shape = &spriteShape;
	spriteFixturedef.density = DEFAULT_DENSITY;
	spriteFixturedef.restitution = DEFAULT_RESTITUTION;
	spriteFixturedef.friction = DEFAULT_FRICTION;

	/* 物質の性質定義適用 */
	BodyData->CreateFixture(&spriteFixturedef);
}

void MyBall::Finalize(b2World* world, cocos2d::CCNode* parentNode)
{
	CircleSelected->Finalize(world, parentNode);

	MySpriteNode::Finalize(world, parentNode);
}

void MyBall::Update(float dt)
{
	if (!bStandby)
	{
		if(this->IsStopped())
		{
			bStandby = true;

			this->ConsumeLeftShotNum();

			if (BallMgrRef->CheckAllFinish())
			{
				// ゲームオーバー.
				if (SceneGameMain* sceneMain = static_cast<SceneGameMain*>(this->getParent()))
				{
					sceneMain->GameOverCallback();
				};
			}
		}
	}

	MySpriteNode::UpdateBody(dt);

	this->UpdateShotNum();

	Vec2 pos = this->GetSpritePos();
	CircleSelected->Clear();

	ccColor4F color;
	if (bSelected)
	{
		switch (ShotMode)
		{
		case SHOT_MODE::TOP_SPIN:
			color = ccColor4F::BLUE;
			break;

		case SHOT_MODE::BACK_SPIN:
			color = ccColor4F::RED;
			break;

		case SHOT_MODE::SHOT_DEFAULT:
			color = ccColor4F::GREEN;
		default:

			break;
		}

		CircleSelected->DrawCirlce(
			pos,
			this->GetSpriteWidth() * 0.5f + SELECTED_CIRCLE_RADUIS_OFFSET,
			0.0f,
			DEFAULT_SEGMENTS,
			false,
			color);
	}
}

void MyBall::UpdateShotNum()
{
	char sNum[32];
	sprintf_s(sNum, "%d", LeftShotNum);

	LabelShotNum->setString(sNum);
	LabelShotNum->setPosition(this->GetSpritePos() + SHOT_NUM_OFFSET);
}

void MyBall::OnShot(const b2Vec2& force, float torque)
{
	if (b2Body* body = this->GetBodyData())
	{
		body->ApplyLinearImpulse(force, body->GetWorldCenter(), true);
		body->ApplyAngularImpulse(torque, true);

		bStandby = false;
	}
}

bool MyBall::IsStopped()
{
	if (BodyData)
	{
		float length = BodyData->GetLinearVelocity().Length();
		if (length <= STOPPED_VELOCITY_LENGTH)
		{
			return true;
		}
	}
	return false;
}

/**************************************************************************************************
* EOF
**************************************************************************************************/
