#include "stdafx.h"
#include "MapStorage.h"

FILE *fout;

CMapStorage::CMapStorage()
{
	// define map;

	for (register int i = 0; i < 110; i++)
	{
		for (register int j = 0; j < 110; j++)
		{
			m_aMap[1][i][j] = 1;
			m_aMap[2][i][j] = 2;
		}
	}
}


CMapStorage::~CMapStorage()
{
}

void
CMapStorage::Destroy()
{
	if (instance_)
	{
		delete instance_;
		instance_ = 0;
	}
}

void CMapStorage::AddPoint(float x_, float z_, int level_, float yaw_)
{
	int d_X = (int)(floor(x_)) + MAP_OFFSET;
	int d_Z = (int)(floor(z_)) + MAP_OFFSET;

	if (yaw_ == 90.0)
	{
		m_aMap[level_][d_X][d_Z] = 0;
		m_aMap[level_][d_X][d_Z-1] = 0;
		m_aMap[level_][d_X][d_Z+1] = 0;
	}
	if (int(yaw_) % 180 == 0)
	{
		m_aMap[level_][d_X][d_Z] = 0;
		m_aMap[level_][d_X - 1][d_Z] = 0;
		m_aMap[level_][d_X + 1][d_Z] = 0;
	}
}

CMapStorage * CMapStorage::Instance()
{
	if (instance_ == 0)
	{
		instance_ = new CMapStorage();
	}
	return instance_;
}

void CMapStorage::PrintMap()
{
	fopen_s(&fout, "resources/map.txt", "w");
	
	for (register int i = 0; i < 110; i++)
	{
		for (register int j = 0; j < 110; j++)
		{
			fprintf_s(fout, " %d ", m_aMap[1][i][j]);
		}
		fprintf_s(fout,"\n");
	}
	
	fprintf_s(fout, "\n#### LEVEL 2 #### \n");

	for (register int i = 0; i < 110; i++)
	{
		for (register int j = 0; j < 110; j++)
		{
			fprintf_s(fout, " %d ", m_aMap[2][i][j]);
		}
		fprintf_s(fout, "\n");
	}
}

int CMapStorage::GetMapOffset()
{
	return MAP_OFFSET;
}

CVector3 CMapStorage::getRandomPoint(int g_x, int g_z, int level)
{
	CVector3 position;
	int a = g_x;
	int b = g_z;

	//srand(time(NULL));
	//int chosenOne = g_x * g_z / level / 10 * (g_x + g_z) / ( (g_x - g_z)*g_x / g_z  ) ;
	int chosenOne = 17;
	if (chosenOne < 2) chosenOne = 2;
	int i = 1;
	while (1) {
		if (m_aMap[level][a - 1][b - 1] != 0 && i%chosenOne == 0)
		{
			position.m_fX = a - 1;
			position.m_fZ = b - 1;
			break;
		}
		//if (m_aMap[level][a][b - 1] != 0  && i%chosenOne == 0)
		//{
			//position.m_fX = a;
			//position.m_fZ = b - 1;
			//break;
		//}
		if (m_aMap[level][a + 1][b - 1] != 0 && i%chosenOne == 0)
		{
			position.m_fX = a + 1;
			position.m_fZ = b - 1;
			break;
		}
		//if (m_aMap[level][a - 1][b] != 0 && i%chosenOne == 0)
		//{
			//position.m_fX = a - 1;
			//position.m_fZ = b;
			//break;
		//}
		//if (m_aMap[level][a + 1][b] != 0  && i%chosenOne == 0)
		//{
			//position.m_fX = a + 1;
			//position.m_fZ = b ;
			//break;
		//}
		if (m_aMap[level][a - 1][b + 1] !=0  && i%chosenOne == 0)
		{
			position.m_fX = a - 1;
			position.m_fZ = b + 1;
			break;
		}
		//if (m_aMap[level][a][b + 1] !=0  && i%chosenOne == 0)
		//{
			//position.m_fX = a;
			//position.m_fZ = b + 1;
			//break;
		//}
		if (m_aMap[level][a + 1][b + 1] != 0 && i%chosenOne == 0)
		{
			position.m_fX = a + 1;
			position.m_fZ = b + 1;
			break;
		}

		i++;
	}
	
	return position;
}

struct QueueComponents
{
	int x;
	int z;
	int father;
};

CVector3 CMapStorage::getNextTileInPath(int g_x, int g_z, int p_x, int p_z, int level)
{
	int path[80][80];
	for (int i = 0; i < 80; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			path[i][j] = 0;
		}
	}
	int length = 1;
	QueueComponents queue[1600]; // made special struct for this queue 
	CVector3 newPosition;
	queue[1].x = g_x;
	queue[1].z = g_z;
	queue[1].father = 0;
	path[g_x][g_z] = 1;
	int a, b;

	int i = 1;
	while (i <= length)
	{
		a = queue[i].x;
		b = queue[i].z;
		if (m_aMap[level][a - 1][b - 1] == level && path[a - 1][b - 1] == 0)
		{
			length++;
			queue[length].x = a-1;
			queue[length].z = b-1;
			queue[length].father = i;
			path[a - 1][b - 1] = 1;
			if (path[p_x][p_z] == 1)
			{
				break;
			}
		}
		if (m_aMap[level][a][b - 1] == level && path[a][b-1] == 0)
		{
			length++;
			queue[length].x = a;
			queue[length].z = b - 1;
			queue[length].father = i;
			path[a][b-1] = 1;
			if (path[p_x][p_z] == 1)
			{
				break;
			}
		}
		if (m_aMap[level][a+1][b - 1] == level && path[a + 1][b-1] == 0)
		{
			length++;
			queue[length].x = a + 1;
			queue[length].z = b - 1;
			queue[length].father = i;
			path[a + 1][b-1] = 1;
			if (path[p_x][p_z] == 1)
			{
				break;
			}
		}
		if (m_aMap[level][a - 1][b] == level && path[a - 1][b] == 0)
		{
			length++;
			queue[length].x = a - 1;
			queue[length].z = b;
			queue[length].father = i;
			path[a - 1][b] = 1;
			if (path[p_x][p_z] == 1)
			{
				break;
			}
		}
		if (m_aMap[level][a + 1][b] == level && path[a+1][b]==0)
		{
			length++;
			queue[length].x = a + 1;
			queue[length].z = b;
			queue[length].father = i;
			path[a + 1][b] = 1;
			if (path[p_x][p_z] == 1)
			{
				break;
			}
		}
		if (m_aMap[level][a - 1][b + 1] == level && path[a - 1][b+1] == 0)
		{
			length++;
			queue[length].x = a - 1;
			queue[length].z = b + 1;
			queue[length].father = i;
			path[a - 1][b + 1] = 1;
			if (path[p_x][p_z] == 1)
			{
				break;
			}
		}
		if (m_aMap[level][a][b + 1] == level && path[a][b + 1] == 0)
		{
			length++;
			queue[length].x = a;
			queue[length].z = b + 1;
			queue[length].father = i;
			path[a][b + 1] = 1;
			if (path[p_x][p_z] == 1)
			{
				break;
			}
		}
		if (m_aMap[level][a + 1][b + 1] == level && path[a + 1][b + 1] == 0)
		{
			length++;
			queue[length].x = a + 1;
			queue[length].z = b + 1;
			queue[length].father = i;
			path[a + 1][b + 1] = 1;
			if (path[p_x][p_z] == 1)
			{
				break;
			}
		}
		i++;
	}
	// now we know the best path is the one that has the father stored in last member of the queue
	// all we need to do is follow the path back to the origin and return the position of the first step the path is taking

	i = length;

	while (queue[i].father > 0)
	{
		i = queue[i].father;
	}

	newPosition.m_fX = queue[i].x;
	newPosition.m_fZ = queue[i].z;
	newPosition.m_fX = 0;

	return newPosition;
}

CMapStorage * CMapStorage::instance_ = 0;