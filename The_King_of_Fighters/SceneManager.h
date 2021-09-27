#pragma once
#include "Config.h"
#include "Singleton.h"

class SceneManager : public Singleton<SceneManager>
{
private:
	eScene nowScene;
	bool readyChangeScene;
public:
	//virtual void Init();
	//virtual void Update();
	//virtual void Render();
	//virtual void Release();

	void Init();

	inline eScene getScene() { return this->nowScene; }
	inline void setScene(eScene nowScene) { this->nowScene = nowScene; }
	inline bool getReadyChangeScene() { return this->readyChangeScene; }
	inline void setReadyChangeScene(bool readyChangeScene) { this->readyChangeScene = readyChangeScene; }
};

