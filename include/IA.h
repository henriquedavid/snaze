class IA{

	using pPair = std::pair< uint, pair<uint,uint>>;

private:
	int x_def, y_def;

public:

	IA( Maps & map ){
		x_def = map.return_x();
		y_def = map.return_y();
	}

	void atualiza_x_y(int x, int y){
		x_def = x;
		y_def = y;
	}
	

	struct cell
	{

		int parent_i, parent_j;
		// f = g + h
		double f, g, h;
			 
	};

	bool isValid( int row, int col )
{		return (row >= 1) && (row < x_def) && (col >= 1) && (col < y_def);
	}

	bool isUnBlocked( Maps map, int x, int y ){
		if(map.get_value(x,y) == ' ' || map.get_value(x,y) == 'o' )
			return true;
		else
			return false;
	}

	bool isDestination( int row, int col, Pair dest ){
		if( row == dest.first && col == dest.second )
			return true;
		else
			return false;
	}

	double calculateHValue( int row, int col, Pair dest ){
		return ((double) sqrt ((row-dest.first)*(row-dest.first) + (col-dest.second)*(col-dest.second)));
	}
	
	void tracePath( cell cellDetails[][y_def],, Pair dest ){
		printf("\nThe path is ");
		int row = dest.first;
		int col = dest.second;

		stack<Pair> Path;

		while(!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col )){
			Path.push(make_pair(row,col));
			int temp_row = cellDetails[row][col].parent_i;
			int temp_col = cellDetails[row][col].parent_j;
			row = temp_row;
			col = temp_col;
		}

		Path.push(make_pair(row,col));
		while(!Path.empty()){
			pair<int,int> p = Path.top();
			Path.pop();
			printf("-> (%d,%d) ", p.first, p.second);
		}

		return;
	}

	void aStarSearch( int grid[][y_def], Snaze & src, Apple & dest )
	{
		std::pair<int,int> snazepos = src.get_position();
		std::pair<int,int> applepos = dest.get_coordenadas();

		if(isValid(snazepos.first, snazepos.second) == false)
			return;

		if(isValid(applepos.first, applepos.second) == false)
			return;

		if( isUnBlocked(grid, snazepos.first, snazepos.second) == false ||
			isUnBlocked(grid, applepos.first, applepos.second) == false )
		{
			return;
		}

		if( isDestination( snazepos.first, snazepos.second, applepos))
			return;

		bool closedList[x_def][y_def];
		memset( closedList, false, sizeof(closedList));

		cell cellDetails[x_def][y_def];

		int i,j;

		for( i = 0 ; i < x_def ; i++ ){
			for( j = 0 ; j <y_def ; j++){
				cellDetails[i][j].f = FLT_MAX;
				cellDetails[i][j].g = FLT_MAX;
				cellDetails[i][j].h = FLT_MAX;
				cellDetails[i][j].parent_i = -1;
				cellDetails[i][j].parent_j = -1;
			}
		}

		i = snazepos.first, j = snazepos.second;

		cellDetails[i][j].f = 0.0;
		cellDetails[i][j].g = 0.0;
		cellDetails[i][j].h = 0.0;
		cellDetails[i][j].parent_i = i;
		cellDetails[i][j].parent_j = j;

		set<pPair> openList;

		openList.insert(make_pair(0.0, make_pair(i,j)));

		bool foundDest = false;

		while(!openList.empty()){
			pPair p = *openList.begin();
			openList.erase(openList.begin());

			i = p.second.first;
			j = p.second.second;
			closedList[i][j] = true;

			double gNew, hNew, fNew;

			// --------------------- NORTE

			if(isValid(i-1, j) == true){
				if(isDestination(i-1,j, dest) == true){
					cellDetails[i-1][j].parent_i = i;
					cellDetails[i-1][j].parent_j = j;
					std::cout << "The destination cell is found\n";
					tracePath(cellDetails, dest);
					foundDest = true;
					return;
				} else if(closedList[i-1][j] == false && isUnBlocked(grid, i-1, j) == true){
					gNew = cellDetails[i-1][j].g + 1.0;
					hNew = calculateHValue(i-1, j, dest);
					fNew = gNew + hNew;

					if(cellDetails[i-1][j].f == FLT_MAX || cellDetails[i-1][j].f > fNew){
						openList.insert(make_pair(fNew, make_pair(i-1,j)));
						cellDetails[i-1][j].f = fNew;
						cellDetails[i-1][j].g = gNew;
						cellDetails[i-1][j].h = hNew;
						cellDetails[i-1][j].parent_i = i;
						cellDetails[i-1][j].parent_j = j;
					}
				} 
			}

			// --------------------- SUL

			if(isValid(i+1, j) == true){
				if(isDestination(i+1,j, dest) == true){
					cellDetails[i+1][j].parent_i = i;
					cellDetails[i+1][j].parent_j = j;
					std::cout << "The destination cell is found\n";
					tracePath(cellDetails, dest);
					foundDest = true;
					return;
				} else if(closedList[i+1][j] == false && isUnBlocked(grid, i+1, j) == true){
					gNew = cellDetails[i+1][j].g + 1.0;
					hNew = calculateHValue(i+1, j, dest);
					fNew = gNew + hNew;

					if(cellDetails[i+1][j].f == FLT_MAX || cellDetails[i+1][j].f > fNew){
						openList.insert(make_pair(fNew, make_pair(i+1,j)));
						cellDetails[i+1][j].f = fNew;
						cellDetails[i+1][j].g = gNew;
						cellDetails[i+1][j].h = hNew;
						cellDetails[i+1][j].parent_i = i;
						cellDetails[i+1][j].parent_j = j;
					}
				} 
			}

			// --------------------- OESTE

			if(isValid(i, j+1) == true){
				if(isDestination(i,j+1, dest) == true){
					cellDetails[i][j+1].parent_i = i;
					cellDetails[i][j+1].parent_j = j;
					std::cout << "The destination cell is found\n";
					tracePath(cellDetails, dest);
					foundDest = true;
					return;
				} else if(closedList[i][j+1] == false && isUnBlocked(grid, i, j+1) == true){
					gNew = cellDetails[i][j+1].g + 1.0;
					hNew = calculateHValue(i, j+1, dest);
					fNew = gNew + hNew;

					if(cellDetails[i][j+1].f == FLT_MAX || cellDetails[i][j+1].f > fNew){
						openList.insert(make_pair(fNew, make_pair(i,j+1)));
						cellDetails[i][j+1].f = fNew;
						cellDetails[i][j+1].g = gNew;
						cellDetails[i][j+1].h = hNew;
						cellDetails[i][j+1].parent_i = i;
						cellDetails[i][j+1].parent_j = j;
					}
				} 
			}

			// --------------------- LESTE

			if(isValid(i, j-1) == true){
				if(isDestination(i,j-1, dest) == true){
					cellDetails[i][j-1].parent_i = i;
					cellDetails[i][j-1].parent_j = j;
					std::cout << "The destination cell is found\n";
					tracePath(cellDetails, dest);
					foundDest = true;
					return;
				} else if(closedList[i][j-1] == false && isUnBlocked(grid, i, j-1) == true){
					gNew = cellDetails[i][j-1].g + 1.0;
					hNew = calculateHValue(i, j-1, dest);
					fNew = gNew + hNew;

					if(cellDetails[i][j-1].f == FLT_MAX || cellDetails[i][j-1].f > fNew){
						openList.insert(make_pair(fNew, make_pair(i,j-1)));
						cellDetails[i][j-1].f = fNew;
						cellDetails[i][j-1].g = gNew;
						cellDetails[i][j-1].h = hNew;
						cellDetails[i][j-1].parent_i = i;
						cellDetails[i][j-1].parent_j = j;
					}
				} 
			}
		}

		if(foundDest == false)
			std::cout << "Failed to find the Destination  Cell\n";

		return;

	}

};