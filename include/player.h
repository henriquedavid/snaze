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
		void next_move(Snaze & cobra, Apple & apple, Movimento & movimento, Maps & map){

			std::pair<int,int> posSnaze = cobra.get_position();
			int x = posSnaze.first;
			int y = posSnaze.second;




			if(movimento == NORTH){
				if(map.get_value(x+1,y) != '#' && map.get_value(x+1,y) != '-')
					cobra.set_position(std::make_pair(x+1,y));
				else{
					cobra.perdervida();
					int sentido;
					Movimento mov;
					std::cout << "################   Insira a próxima posição da Cobra:   ###############\n";
					std::cin >> sentido;
					
					if( sentido == 0 )
						mov = Player::Movimento::NORTH;
					else if( sentido == 1)
						mov = Player::Movimento::SOUTH;
					else if( sentido == 2 )
						mov = Player::Movimento::EAST;
					else
						mov = Player::Movimento::WEST;

					next_move(cobra, apple, mov , map);
				}
			}
			else if(movimento == SOUTH){
				if(map.get_value(x-1,y) != '#' && map.get_value(x-1,y) != '-')
					cobra.set_position(std::make_pair(x-1,y));
				else{
					cobra.perdervida();
					int sentido;
					Movimento mov;
					std::cout << "################   Insira a próxima posição da Cobra:   ###############\n";
					std::cin >> sentido;
					
					if( sentido == 0 )
						mov = Player::Movimento::NORTH;
					else if( sentido == 1)
						mov = Player::Movimento::SOUTH;
					else if( sentido == 2 )
						mov = Player::Movimento::EAST;
					else
						mov = Player::Movimento::WEST;

					next_move(cobra, apple, mov , map);
				}
			}
			else if( movimento == EAST){
				if(map.get_value(x, y-1) && map.get_value(x,y+1) != '-')
					cobra.set_position(std::make_pair(x,y+1));
				else{
					cobra.perdervida();
					int sentido;
					Movimento mov;
					std::cout << "################   Insira a próxima posição da Cobra:   ###############\n";
					std::cin >> sentido;
					
					if( sentido == 0 )
						mov = Player::Movimento::NORTH;
					else if( sentido == 1)
						mov = Player::Movimento::SOUTH;
					else if( sentido == 2 )
						mov = Player::Movimento::EAST;
					else
						mov = Player::Movimento::WEST;

					next_move(cobra, apple, mov , map);
				}
			}
			else{
				if(map.get_value(x, y-1) && map.get_value(x,y-1) != '-')
					cobra.set_position(std::make_pair(x,y-1));
				else{
					int sentido;
					Movimento mov;
					std::cout << "################   Insira a próxima posição da Cobra:   ###############\n";
					std::cin >> sentido;
					
					if( sentido == 0 )
						mov = Player::Movimento::NORTH;
					else if( sentido == 1)
						mov = Player::Movimento::SOUTH;
					else if( sentido == 2 )
						mov = Player::Movimento::EAST;
					else
						mov = Player::Movimento::WEST;

					next_move(cobra, apple, mov , map);
				}
			}

		}

};

#endif