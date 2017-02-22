#pragma once

#include "SceneBase.h"

class SceneGameMain : public SceneBase
{
public:
	SceneGameMain();
	~SceneGameMain();

	void Initialize() override;
	void update(float delta) override;

private:
	cocos2d::LabelTTF*			TitleLabel;
};

/**************************************************************************************************
*!	EOF
**************************************************************************************************/
