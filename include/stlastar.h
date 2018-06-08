#include <math.h>

#define WORLD_SIZE

struct SearchCell
{
public:
	int m_xcoord, m_zcoord;
	int m_id;
	SearchCell * parent;
	float g;
	float h;

	SearchCell() : parent(0) {}
	SearchCell(int x, int z, SearchCell * _parent = 0) : m_xcoord(x), m_zcoord(z), parent(_parent), m_id(z*WORLD_SIZE + z), g(0), h(0) {};

	float GetF(){ return G+H; }
	float ManHattanDistance(SearchCell * nodeEnd )
	{
		float x = (float) (fabs(this->m_xcoord - nodeEnd->m_xcoord));
		float z = (float) (fabs(this->m_zcoord - nodeEnd->m_zcoord));
		
		return x+z;
	}
	
};