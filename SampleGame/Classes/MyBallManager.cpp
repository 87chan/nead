#include "MyBallManager.h"
#include "AppHeader.h"

USING_NS_CC;

MyBallManager::MyBallManager()
: callbackGameOver(nullptr)
{
}

MyBallManager::~MyBallManager()
{
}

void MyBallManager::EntryBallNode(MyBall* ball)
{
	BallNodeList.push_back(ball);
}

void MyBallManager::Finalize(b2World* world, cocos2d::CCNode* parentNode)
{
	std::vector<MyBall*>::iterator it = BallNodeList.begin();
	for (; it != BallNodeList.end(); ++it)
	{
		(*it)->Finalize(world, parentNode);
	}

	BallNodeList.clear();
}

void MyBallManager::Update(float dt)
{
	std::vector<MyBall*>::iterator it = BallNodeList.begin();
	for (; it != BallNodeList.end(); ++it)
	{
		(*it)->Update(dt);
	}
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
