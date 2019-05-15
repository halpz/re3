#pragma once

#pragma once

class CRect
{
public:
	float left;     // x min
	float top;      // y max
	float right;    // x max
	float bottom;   // y min

	CRect(void){
		left = 1000000.0f;
		bottom = 1000000.0f;
		right = -1000000.0f;
		top = -1000000.0f;
	}
	CRect(float l, float b, float r, float t){
		left = l;
		bottom = b;
		right = r;
		top = t;
	}
	void ContainPoint(CVector const &v){
		if(v.x < left) left = v.x;
		if(v.x > right) right = v.x;
		if(v.y < bottom) bottom = v.y;
		if(v.y > top) top = v.y;
	}
};
