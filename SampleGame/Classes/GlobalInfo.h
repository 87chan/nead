#pragma once

#include "cocos2d.h"

class GlobalInfo
{
private:
	GlobalInfo() {}
	~GlobalInfo() {}

private:
	struct GlobalInfoDeleter
	{
		void operator()(GlobalInfo *p) { delete p; }
	};

	typedef std::unique_ptr<GlobalInfo, GlobalInfoDeleter> GlobalInfoPtr;
	static GlobalInfoPtr Instance;

public:
	static GlobalInfoPtr& GetInstance()
	{
		if (!Instance.get())
		{
			Instance.reset(new GlobalInfo());
		}

		return Instance;
	}

	std::string str;
};

/**************************************************************************************************
* EOF
**************************************************************************************************/
