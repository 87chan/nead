#pragma once

#include "cocos2d.h"
#include "Box2D/Box2D.h"

class SceneBase : public cocos2d::Scene
{
public:
	SceneBase();
	virtual ~SceneBase();

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

	// �h���N���X�ɓs�x�ucreateScene�v�֐����쐬����̂���ԂȈ�.
	// �e���v���[�g��p����.
	// SceneBase::createScene<�h���N���X>();
	template<class T>
	static T* createScene()
	{
		auto scene = SceneBase::create<T>();
		return scene;
	}
	
	bool init() override;

	// �V�[���J�n���ɕK�v�ȏ����͂����ɏ���.
	virtual void Initialize() {}
	
	virtual void update(float delta);
};

/**************************************************************************************************
*!	EOF
**************************************************************************************************/
