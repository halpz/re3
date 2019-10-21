#pragma once

class CObject;

class CProjectileInfo
{
public:
	static bool RemoveIfThisIsAProjectile(CObject *pObject);
};