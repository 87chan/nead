#pragma once

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "base/CCDirector.h"

namespace SceneUtil
{
	template<class T>
	static T* create()
	{
		T *pRet = new(std::nothrow) T();
		if (pRet && pRet->init())
		{
			pRet->autorelease();
			return pRet;
		}
		else
		{
			delete pRet;
			pRet = nullptr;
			return nullptr;
		}
	}

	// 派生クラスに都度「createScene」関数を作成するのが手間な為.
	// テンプレートを用いる.
	// SceneBase::createScene<派生クラス>();
	template<class T>
	static T* createScene()
	{
		auto scene = create<T>();
		return scene;
	}

	template<class Class, class Trans>
	static void TransitionScene(float fadeTime = 1.0f)
	{
		Director::getInstance()->replaceScene(Trans::create(fadeTime, createScene<Class>()));
	}
}

class SceneBase : public cocos2d::Scene
{
public:
	SceneBase();
	virtual ~SceneBase();
	
	bool init() override;

	// シーン開始時に必要な処理はここに書く.
	virtual void Initialize() {}
	
	virtual void update(float delta);
};

/**************************************************************************************************
*!	EOF
**************************************************************************************************/
