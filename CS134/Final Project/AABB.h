#pragma once
#ifndef AABB_H
#define AABB_H

struct AABB{
	int x, y, w, h;
	inline void setX(int x){this->x = x;}
	inline void setY(int y){this->y = y;}
	inline void setW(int w){this->w = w;}
	inline void setH(int h){this->h = h;}
};
#endif