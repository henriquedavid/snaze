#include "PathFinding.h"

PathFinding::PathFinding( void )
{
	m_intializedStartGoal = false;
	m_foundGoal = false;
}

PathFinding::~PathFinding( void ){

}

void PathFinding::FindPath( std::pair<int,int> currentPos, std::pair<int,int> targetPos ){
	if(!m_intializedStartGoal)
	{
		for(int i = 0 ; i < m_openList.size(); i++){
			delete m_openList[i];
		}

		m_openList.clear();

		for( int i = 0 ; i < m_visitedList.size() ; i++ )
			delete m_visitedList[i];
		m_visitedList.clear();

		for( int i = 0 ; i < m_pathToGoal.size() ; i++ )
			delete m_visitedList[i];
		m_visitedList.clear();

		//initialize Start
		SearchCell start;
		start.m_xcoord = currentPos.x;
		start.m_zcoord = currentPos.z;

		SearchCell goal;
		goal.m_xcoord = targetPos.x;
		goal.m_zcoord = targetPos.z;

		SetStartGoal(start, goal);
		m_intializedStartGoal = true;
	}

	if(m_intializedStartGoal)
	{
		ContinuePath();
	}
}

void PathFinding::SetStartAndGoal(SearchCell start, SearchCell goal)
{
	m_startCell = new SearchCell(start.m_xcoord, start.m_zcoord, NULL);
	m_goalCell = new SearchCell(goal.m_xcoord, goal.m_zcoord, &goal);

	m_startCell->g = 0;
	m_startCell->h = m_startCell->ManHattanDistance(m_goalCell);
	m_startCell->parent = 0;

	m_openList.push_back(m_startCell);
}

SearchCell * PathFinding::GetNextCell(){
	float bestF = 999999.0f;
	int cellIndex = -1;
	SearchCell * nextCell = NULL;

	for( int i = 0 ; i < m_openList.size(); i++)
	{
		if(m_openList[i]->GetF() < bestF)
		{
			bestF = m_openList[i]->GetF();
			cellIndex = i;
		}
	}

	if(cellIndex >= 0){
		nextCell = m_openList[cellIndex];
		m_visitedList.push_back(nextCell);
		m_openList.erase(m_openList.begin() + cellIndex);
	}

	return nextCell;
}

void PathFinding::PathOpened( int x, int z, float newCost, SearchCell * parent)
{
	if(CELL_BLOCK)
		return;

	int id = z * WORLD_SIZE + x;
	for( int i = 0 ; i < m_visitedList.size() ; i++){
		if(id == m_visitedList[i]->m_id)
			return;
	}

	SearchCell * newChild = new SearchCell(x, z, parent);
	newChild->g = newCost;
	newChild->h = parent->ManHattanDistance(m_goalCell);

	for( int i = 0 ; i < m_openList.size() ; i++)
	{
		if(id == m_openList[i]->m_id)
		{
			float newF = newChild->g + newCost + m_openList[i]->h;

			if(m_openList[i]->GetF() > newF)
			{
				m_openList[i]->g = newChild->g + newCost;
				m_openList[i]->parent = newChild;
			}
			else
			{
				delete newChild;
				return;
			}
		}
	}

	m_openList.push_back(newChild);
}

void PathFinding::ContinuePath(){
	if(m_openList.empty())
	{
		return;
	}

	SearchCell *  currentCell = GetNextCell();

	if(currentCell->m_id == m_goalCell->m_id)
	{
		m_goalCell->parent = currentCell->parent;

		SearchCell * getPath;

		for( getPath = m_goalCell ; getPath != NULL ; getPath->parent)
		{
			m_pathToGoal.push_back(new Vector3(getPath->m_xcoord, 0, getPath->m_zcoord));
		}

		m_foundGoal = true;
		return;
	}
	else
	{
		//rightSide
		PathOpened(currentCell->m_xcoord +1 , currentCell->m_zcoord, currentCell->g+1, currentCell);
		//leftSide
		PathOpened(currentCell->m_xcoord -1 , currentCell->m_zcoord, currentCell->g+1, currentCell);

		//Top
		PathOpened(currentCell->m_xcoord , currentCell->m_zcoord+1, currentCell->g+1, currentCell);
		//Down
		PathOpened(currentCell->m_xcoord , currentCell->m_zcoord-1, currentCell->g+1, currentCell);

		for(int i = 0 ; i < m_openList.size() ; i++){
			ìf(currentCell->m_id == m_openList[i]->m_id)
			{
				m_openList.erase(m_openList,begin()	+ i);
			}
		}
	}
}

Vector3 PathFinding::NextPathPos(Snaze & snaze){
	int index = 1;

	Vector3 nextPos;
	nextPos.x = m_pathToGoal[m_pathToGoal.size() - index]->x;
	nextPos.z = m_pathToGoal[m_pathToGoal.size() - index]->z;

	Vector3 distance = nextPos - snaze.get_position();

	if(index < m_pathToGoal.size()){
		if(distance.Length() < snaze.radius)
		{
			m_pathToGoal.erase(m_pathToGoal.end() - index);
		}
	}

	return nextPos;
}