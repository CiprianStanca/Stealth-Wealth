#pragma once
class CVector3;

class CMapStorage
{
public:
	CMapStorage();
	~CMapStorage();
	void Destroy();

	void AddPoint(float x_, float z_, int level_, float yaw_);
	static CMapStorage * Instance();

	void PrintMap();

	const int MAP_OFFSET = 51;

	int GetMapOffset();
	CVector3 getRandomPoint(int g_x, int g_z, int level);
	CVector3 getNextTileInPath(int g_x, int g_z, int p_x, int p_z, int level);

private:
	static CMapStorage * instance_;
	short int m_aMap[3][110][110];
};

