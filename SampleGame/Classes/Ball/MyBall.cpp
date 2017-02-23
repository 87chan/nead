#include "MyBall.h"
#include "AppHeader.h"
#include "MyBallManager.h"

USING_NS_CC;

static const Vec2	SHOT_NUM_OFFSET = Vec2(0.0f, 20.0f);
static const float	NEXT_STANDBY_TIME = 3.0f;
static const float	SELECTED_CIRCLE_RADUIS_OFFSET = 3.0f;

MyBall::MyBall()
: BallMgrRef(nullptr)
, SpriteBatchNode(nullptr)
, LabelShotNum(nullptr)
, CircleSelected(nullptr)
, bSelected(false)
, bStandby(true)
, LeftShotNum(1)
{
}

MyBall::~MyBall()
{
}

void MyBall::Initialize(b2World* world, cocos2d::CCNode* parentNode, std::shared_ptr<MyBallManager> ballMgr, const cocos2d::Vec2& pos, int shotNum)
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

	/* �摜�̕\�� */
	SpriteData = CCSprite::create();
	SpriteData->initWithTexture(SpriteBatchNode->getTexture());
	SpriteData->setPosition(pos);
	SpriteData->setTag(TAG_BALL);
	this->addChild(SpriteData);

	/* �����G���W����̕����̒�` */
	b2BodyDef spriteBodyDef;
	/*
	���̗̂͂ɑ΂��鑮��
	b2_dynamicBody: ���x������͂ɔ�������
	b2_staticBody: ���x�������͂ɔ������Ȃ�
	b2_kinematicBody: ���x������͂ɔ������Ȃ�
	*/
	spriteBodyDef.type = b2_dynamicBody;

	/* �����G���W���̋�ԏ�̍��W */
	spriteBodyDef.position.Set(
		SpriteData->getPositionX() / PTM_RATIO,
		SpriteData->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = SpriteData;

	/* �����G���W����̕����쐬 */
	BodyData = world->CreateBody(&spriteBodyDef);
	b2MassData massData = b2MassData();
	massData.center = BodyData->GetWorldCenter();
	massData.mass = DEFAULT_MASS;
	BodyData->SetMassData(&massData);
	BodyData->SetAngularDamping(DEFAULT_ANGULAR_DAMPLING);

	/* �����G���W����̕����̌`�Ƒ傫�� */
	b2CircleShape spriteShape;
	spriteShape.m_radius = SpriteData->getContentSize().width * 0.5f / PTM_RATIO;

	/* �����̐�����`�i�`�A���x�A���C�j */
	b2FixtureDef spriteFixturedef;
	spriteFixturedef.shape = &spriteShape;
	spriteFixturedef.density = DEFAULT_DENSITY;
	spriteFixturedef.restitution = DEFAULT_RESTITUTION;
	spriteFixturedef.friction = DEFAULT_FRICTION;

	/* �����̐�����`�K�p */
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
		if(!BodyData->IsAwake())
		{
			bStandby = true;

			this->ConsumeLeftShotNum();
			if (BallMgrRef->CheckAllFinish())
			{
				BallMgrRef->ExecuteCallback();
			}
		}
	}

	MySpriteNode::UpdateBody(dt);

	this->UpdateShotNum();

	Vec2 pos = this->GetSpritePos();
	CircleSelected->clear();
	if (bSelected)
	{
		CircleSelected->drawCirlce(
			pos,
			this->GetSpriteWidth() * 0.5f + SELECTED_CIRCLE_RADUIS_OFFSET,
			0.0f,
			DEFAULT_SEGMENTS,
			false,
			ccColor4F::GREEN);
	}
}

void MyBall::UpdateShotNum()
{
	char sNum[32];
	sprintf_s(sNum, "%d", LeftShotNum);

	LabelShotNum->setString(sNum);
	LabelShotNum->setPosition(this->GetSpritePos() + SHOT_NUM_OFFSET);
}

void MyBall::OnShot(const b2Vec2& force)
{
	if (b2Body* body = this->GetBodyData())
	{
		body->ApplyForce(force, body->GetWorldCenter(), true);

		bStandby = false;
	}
}

/**************************************************************************************************
* EOF
**************************************************************************************************/
