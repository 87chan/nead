#include "MyBallManager.h"
#include "AppHeader.h"

USING_NS_CC;

MyBallManager::MyBallManager()
{
}

void MyBallManager::Initialize(b2World* world, cocos2d::CCNode* parentNode)
{
	ManagerBase::Initialize(world, parentNode);
}

void MyBallManager::Update(float delta)
{
	ManagerBase::Update(delta);

	std::vector<MyBall*>::iterator it = BallNodeList.begin();
	for (; it != BallNodeList.end(); ++it)
	{
		(*it)->Update(delta);
	}
}

void MyBallManager::Finalize()
{
	ManagerBase::Finalize();

	std::vector<MyBall*>::iterator it = BallNodeList.begin();
	for (; it != BallNodeList.end(); ++it)
	{
		(*it)->Finalize(WorldRef, ParentRef);
	}

	BallNodeList.clear();
}

void MyBallManager::CreateBall(const cocos2d::Vec2& pos, int shotNum, bool select)
{
	MyBall* ball = MyBall::create();
	CC_ASSERT(ball);

	ball->Initialize(WorldRef, ParentRef, this, pos, shotNum);
	ball->SetSelect(select);

	BallNodeList.push_back(ball);
}

bool MyBallManager::CheckAllFinish()
{
	std::vector<MyBall*>::iterator it = BallNodeList.begin();
	for (; it != BallNodeList.end(); ++it)
	{
		if (!(*it)->IsFinished())
		{
			return false;
		}
	}

	return true;
}

void MyBallManager::ResetAllSelected()
{
	std::vector<MyBall*>::iterator it = BallNodeList.begin();
	for (; it != BallNodeList.end(); ++it)
	{
		(*it)->SetSelect(false);
	}
}

MyBall* MyBallManager::GetSelectedBall()
{
	std::vector<MyBall*>::iterator it = BallNodeList.begin();
	for (; it != BallNodeList.end(); ++it)
	{
		if((*it)->GetIsSelected())
		{
			return (*it);
		}
	}

	return nullptr;
}

MyBall* MyBallManager::GetBall(const cocos2d::Vec2& pos)
{
	std::vector<MyBall*>::iterator it = BallNodeList.begin();
	for (; it != BallNodeList.end(); ++it)
	{
		if (Sprite* sprite = (*it)->GetSprite())
		{
			Rect targetBox = sprite->getBoundingBox();
			if (targetBox.containsPoint(pos))
			{
				return (*it);
			}
		}
	}

	return nullptr;
}

/**************************************************************************************************
* EOF
**************************************************************************************************/
