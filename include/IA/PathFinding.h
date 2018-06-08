#include "SearchCell.h"

class PathFinding{
public:
	PathFinding( void );
	~PathFinding( void );

	void FindPath( std::pair<int,int> currentPos, std::pair<int,int> targetPos );
	std::pair<int,int> NextPathPos();
	void ClearOpenList(){ m_openList.clear(); }
	void ClearVisitedList(){ m_visitedList.clear(); }
	void ClearPathToGoal() { m_pathToGoal.clear(); }
	bool m_intializedStartGoal;
	bool m_foundGoal;

private:
	void SetStartAndGoal(SearchCell start, SearchCell goal);
	void PathOpened(int x, int z, float newCost, SearchCell * parent);
	SearchCell *GetNextCell();
	void ContinuePath();

	SearchCell * m_startCell;
	SearchCell * m_goalCell;
	sc::vector<SearchCell*> m_openList;
	sc::vector<SearchCell*> m_visitedList;
	sc::vector<std::pair<int,int>> m_pathToGoal;

}