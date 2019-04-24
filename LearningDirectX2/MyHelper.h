#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include "BoxCollider.h"


class MyHelper {
public:
	static RECT BoxColliderToRect(BoxCollider col);
	static float Clamp(float x, float a, float z);
};