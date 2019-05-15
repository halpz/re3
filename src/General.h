class CGeneral
{
public:
	static float GetATanOfXY(float x, float y){
		if(y >= 0.0f) return atan2(x, y);
		return atan2(x, y) + 2*M_PI;
	}

	// not too sure about all these...
	static uint16 GetRandomNumber(void)
		{ return myrand() & 0xFFFF; }
	// Probably don't want to ever reach high
	static float GetRandomNumberInRange(float low, float high)
		{ return low + (high - low)*(GetRandomNumber()/65536.0f); }
};
