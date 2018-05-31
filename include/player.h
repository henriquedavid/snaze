class Player{
	private:


	public:


		enum Movimento{
			SOUTH,
			NORTH,
			EAST,
			WEST
		};

		/// Realiza a movimentação da Snaze
		void next_move(Snaze & cobra, Movimento movimento){


			std::pair<int,int> posSnaze = cobra.get_position();
			int x = posSnaze.first;
			int y = posSnaze.second;

			if(movimento == NORTH)
				cobra.set_position(std::make_pair(x+1,y));
			else if(movimento == SOUTH)
				cobra.set_position(std::make_pair(x-1,y));
			else if( movimento == EAST)
				cobra.set_position(std::make_pair(x,y+1));
			else
				cobra.set_position(std::make_pair(x,y-1));			
		}

		void next_move_IA( Maze & maze, Position start, Apple & apple){
			solve_maze();
		}
};