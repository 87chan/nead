#pragma once

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "base/CCDirector.h"
#include "AppHeader.h"

namespace SceneUtil
{
	template<class Class, class Trans>
	static void TransitionScene(float fadeTime = 1.0f)
	{
		Director::getInstance()->replaceScene(Trans::create(fadeTime, AppUtil::createNode<Class>()));
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
