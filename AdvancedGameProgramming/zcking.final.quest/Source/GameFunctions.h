#pragma once
#include "Definitions.h"
#include "Box2D/Box2D.h"

const float fPRV = 10.0f;

inline float PW2RW(float x) { return x*fPRV; }

inline float RW2PW(float x) { return x / fPRV; }

inline float RW2PW(int x) { return (float)x / fPRV; }

inline float RW2PWAngle(float x) { return((float)x*(2.0f*3.14159f) / 360.0f); } //degrees to radians

inline float PW2RWAngle(float x) { return((float)x*360.0f / (2.0f*3.14159f)); } //radians to degrees

inline GAME_FLT degToRads(GAME_FLT degs) { return degs * (PI / 180.0f); }

inline GAME_FLT radsToDegs(GAME_FLT rads) {	return rads * (180.0f / PI); }

inline b2Vec2 GV2PV(GAME_VEC v) {
	return(b2Vec2(RW2PW(v.x), RW2PW(v.y)));
}

inline GAME_VEC PV2GV(b2Vec2 v) {
	GAME_VEC tmp;
	tmp.x = PW2RW(v.x);
	tmp.y = PW2RW(v.y);
	return tmp;
}