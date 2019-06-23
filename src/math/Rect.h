#pragma once

class CRect
{
public:
	float left;     // x min
	float bottom;   // y max
	float right;    // x max
	float top;      // y min

	CRect(void){
		left = 1000000.0f;
		top = 1000000.0f;
		right = -1000000.0f;
		bottom = -1000000.0f;
	}
	CRect(float l, float t, float r, float b){
		left = l;
		top = t;
		right = r;
		bottom = b;
	}
	void ContainPoint(CVector const &v){
		if(v.x < left) left = v.x;
		if(v.x > right) right = v.x;
		if(v.y < top) top = v.y;
		if(v.y > bottom) bottom = v.y;
	}

	void Translate(float x, float y){
		left += x;
		right += x;
		bottom += y;
		top += y;
	}
	void Grow(float r){
		left -= r;
		right += r;
		top -= r;
		bottom += r;
	}

	float GetWidth(void) { return right - left; }
	float GetHeight(void) { return bottom - top; }
};
