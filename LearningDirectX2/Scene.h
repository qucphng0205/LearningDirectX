#pragma once
#include <d3d9.h>

class Scene {
public:
	Scene();
	virtual ~Scene() {}
	D3DCOLOR GetBackColor();
	//virtual void LoadContent();
	virtual void ProcessInput();
	virtual void Render() = 0;
	virtual void Update(double dt) = 0;
private:
	D3DCOLOR backColor;
};