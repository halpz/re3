#pragma once

// some miami bike leftovers

enum eBikeNodes {
	BIKE_NODE_NONE,
	BIKE_CHASSIS,
	BIKE_FORKS_FRONT,
	BIKE_FORKS_REAR,
	BIKE_WHEEL_FRONT,
	BIKE_WHEEL_REAR,
	BIKE_MUDGUARD,
	BIKE_HANDLEBARS,
	BIKE_NUM_NODES
};

class CBike : public CVehicle
{
public:
	RwFrame *m_aBikeNodes[BIKE_NUM_NODES]; // assuming
	uint8 unk1[96];
	AnimationId m_bikeSitAnimation;
	uint8 unk2[180];
	float m_aSuspensionSpringRatio[4];
};