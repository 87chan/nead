#pragma once

#define PTM_RATIO 32.0f
#define TAG_BALL 0
#define TAG_GOAL 1
#define UI_LAYER 1
#define MENU_LAYER 2

static const int	VELOCITY_ITERATIONS = 8;
static const int	POSITION_ITERATIONS = 1;

static const float	MAX_LENGTH = 200.0f;	// 伸ばす長さの最大.
static const float	SELECT_LENGTH_THRESHOULD = 10.f;	// 選択可能な長さの閾値.

static const float	DEFAULT_MASS = 300.0f;
static const float	DEFAULT_DENSITY = 1.0f; // 密度.
static const float	DEFAULT_RESTITUTION = 0.5f; // 反発係数.
static const float	DEFAULT_FRICTION = 1.0f; // 摩擦.
static const float	DEFAULT_LINEAR_DAMPLING = 1.0f; // 移動減衰.
static const float	DEFAULT_ANGULAR_DAMPLING = 0.05f; // 回転減衰.

static const int	DEFAULT_SEGMENTS = 64;

class MyCallbackBase
{
public:
	MyCallbackBase() {}

	virtual void Execute() {}
};

template
<class C,class T>
class MyCallback : public MyCallbackBase
{
public:
	MyCallback() {}
	MyCallback(C obj,T func) : Obj(obj), Func(func) {}

	void Execute() override
	{
		(Obj->*Func)();
	}

private:
	C Obj;
	T Func;
};

namespace AppUtil
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

	// 派生クラスに都度「create***」関数を作成するのが手間な為.
	// テンプレートを用いる.
	// SceneBase::createNode<派生クラス>();
	template<class T>
	static T* createNode()
	{
		auto node = create<T>();
		return node;
	}
}

/**************************************************************************************************
* EOF
**************************************************************************************************/
