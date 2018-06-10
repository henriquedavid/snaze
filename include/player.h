#ifndef PLAYER_H
#define PLAYER_H 

class Player{
	private:


	public:

		/// Movimento o qual a cobra pode fazer.
		enum Movimento{
			NORTH,
			SOUTH,
			EAST ,
			WEST
		};
		
		/// Atribui o movimento que o humano escolheu para a cobra.
		void next_move(Snaze & cobra, Apple & apple, Movimento & movimento){

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

};

#endif