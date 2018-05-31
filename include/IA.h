class IA : public Player{
	
public:

	class Position{
	public:

		int x;
		int y;

		Position( int a, int b ) : x(a), y(b){/* empty */}

		std::pair<int,int> get_position(){
			return std::make_pair(x,y);
		}

		void set_position(std::pair<int,int> & posicao){
			x = posicao.first;
			y = posicao.second;
		}
	};

	class Maze{

		private:
			sc::vector<sc::vector<char>> maze_;
			Position dir;

		public:

		enum direction_t{ NORTH=0, EAST, SOUTH, WEST};


		/*Maze( const sc::vector<sc::vector<char>> & l ){
			maze_ = l;
		}*/

		enum cell_t { START, WALL, BODY, WALK };

		Position get_start_position( Snaze & cobra ){

			auto posicao = cobra.get_position();

			return Position(posicao.first, posicao.second);

		}

		bool is_apple( Position & pos, Apple & apple ){
			std::pair<int,int> pos_player = pos.get_position();
			std::pair<int,int> pos_apple = apple.get_coordenadas();

			if(pos_player.first == pos_apple.first && pos_player.second == pos_apple.second)
				return true;
			return false;
		}

		bool is_blocked( Position & pos,  direction_t dir ){

			if(dir == direction_t::NORTH)
				if(maze_[pos.x+1][pos.y] == '#' || maze_[pos.x+1][pos.y] == '-')
					return true;

			if(dir == direction_t::SOUTH)
				if(maze_[pos.x-1][pos.y] == '#' || maze_[pos.x-1][pos.y] == '-')
					return true;

			if(dir == direction_t::WEST)
				if(maze_[pos.x][pos.y-1] == '#' || maze_[pos.x][pos.y-1] == '-')
					return true;

			if(dir == direction_t::EAST)
				if(maze_[pos.x][pos.y+1] == '#' || maze_[pos.x][pos.y+1] == '-')
					return true;

			return false;
		}

		void mark_cell( const Position & pos ){
			maze_[pos.x][pos.y] = 'x';
		}

		void unmark_cell( const Position & pos ){
			maze_[pos.x][pos.y] = ' ';
		}

		bool is_marked( const Position & pos ){
			if(maze_[pos.x][pos.y] == 'x')
				return true;
			return false;
		}

	};

	Position walk_to_cell( Position & p, const Maze::direction_t & d ){
		switch(d){
			case Maze::direction_t::NORTH: return Position(p.x+1, p.y);
			case Maze::direction_t::SOUTH: return Position( p.x-1, p.y );
			case Maze::direction_t::EAST: return Position( p.x, p.y+1 );
			default: return Position( p.x, p.y-1 );
		}
	}


	bool solve_maze(  Maze & mz,  Position  start, Apple & apple ){
		if(mz.is_apple(start, apple)) return true;
		if(mz.is_marked(start)) return false;
		mz.mark_cell( start );
		for( auto i(Maze::direction_t::NORTH) ; i < 4 ; ){
			if( not mz.is_blocked(start, i))
				if(solve_maze(mz,walk_to_cell(start, i), apple)){
					std::cout << "ACHOU!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
					return true;
				}
		}
		
		return false;
	}
	
};