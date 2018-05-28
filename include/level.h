class Level{
	private:
		std::vector<Maps> levels;
		unsigned int nivel;

	public:
		Apple apple;

		Level( int niv = 0 ) : nivel(niv) {/*empty*/}

		void level_up(){
			nivel++;
		}

		void add_maps(std::vector<Maps> map){
			levels = map;
		}

		int all_levels(){
			return levels.size();
		}


		int get_level(){
			return nivel;
		}

		bool win(){
			if(nivel >= levels.size())
				return true;
			return false;
		}

		void configurar_apple(){
			int v_x = apple.gerarCoordenadas(levels[nivel].return_x());
			int v_y = apple.gerarCoordenadas(levels[nivel].return_y());
			
			char elemento = levels[nivel].get_value(v_x, v_y);

			if( elemento != '#' || elemento != '.')
				apple.set_coordenadas(std::make_pair(v_x, v_y));
			else
				configurar_apple();
		}

		void insert_apple(){
			std::pair<int,int> coord = apple.get_coordenadas();
			levels[nivel].change_value(coord.first, coord.second, apple.get_aparencia());
		}

		bool snake_in_apple(){
			std::pair<int,int> posSnake = levels[nivel].snaze_position();
			std::pair<int,int> posApple = apple.get_coordenadas();
			int x_snake = posSnake.first;
			int y_snake = posSnake.second;
			int x_apple = posApple.first;
			int y_apple = posApple.second;

			if(x_snake == x_apple && y_snake == y_apple)
				return true;

			return false;
		}

		void print_all_maps(){
			//std::cout << "MAPA = " << levels[nivel].return_x() << " " << levels[nivel].return_y() << std::endl;
			for( auto & i : levels ){
				i.printVector();
			}
			//std::pair<int,int> pos = levels[nivel].snaze_position();
			//std::cout << "A cobra está na posição: (" << pos.first << "," << pos.second << ")" << std::endl;

		}

		void print_current_map(){
			levels[nivel].printVector();
		}

		void change_snaze_pos(std::pair<int,int> coordenadas){
			levels[nivel].change_snaze_position(coordenadas);
		}

		Maps get_current_level(){
			return levels[nivel];
		}

};