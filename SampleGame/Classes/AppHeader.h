#pragma once
#include "base\CCRef.h"

#define PTM_RATIO 32.0f
#define TAG_BALL 0
#define TAG_GOAL 1
#define UI_LAYER 1
#define MENU_LAYER 2

static const int	VELOCITY_ITERATIONS = 8;
static const int	POSITION_ITERATIONS = 1;

static const float	MAX_LENGTH = 200.0f;	// êLÇŒÇ∑í∑Ç≥ÇÃç≈ëÂ.
static const float	SELECT_LENGTH_THRESHOULD = 10.f;	// ëIëâ¬î\Ç»í∑Ç≥ÇÃËáíl.

static const float	DEFAULT_MASS = 300.0f;
static const float	DEFAULT_DENSITY = 1.0f; // ñßìx.
static const float	DEFAULT_RESTITUTION = 0.5f; // îΩî≠åWêî.
static const float	DEFAULT_FRICTION = 1.0f; // ñÄéC.
static const float	DEFAULT_ANGULAR_DAMPLING = 8.0f; // å∏êä.

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

/**************************************************************************************************
* EOF
**************************************************************************************************/
