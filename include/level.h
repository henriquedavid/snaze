class Level{
	private:
		Apple apple;
		std::vector<Maps> levels;
		int nivel;

	public:

		Level( int niv = 0 ) : nivel(niv) {/*empty*/}

		void level_up(){
			nivel++;
		}

		void add_maps(std::vector<Maps> map){
			levels = map;
		}

		void configurar_apple(){
			int v_x = apple.gerarCoordenadas(levels[nivel].return_x());
			int v_y = apple.gerarCoordenadas(levels[nivel].return_y());
			
			char elemento = levels[nivel].get_value(v_x, v_y);

			if( elemento != '#')
				apple.set_coordenadas(std::make_pair(v_x, v_y));
			else
				configurar_apple();
		}

		void insert_apple(){
			std::pair<int,int> coord = apple.get_coordenadas();
			levels[nivel].change_value(coord.first, coord.second, apple.get_aparencia());
		}

		// Para fins de compilação.
		void print_all_maps(){
			std::cout << "MAPA = " << levels[nivel].return_x() << " " << levels[nivel].return_y() << std::endl;
			for( auto & i : levels ){
				i.printVector();
			}
			std::pair<int,int> pos = levels[nivel].snaze_position();
			std::cout << "A cobra está na posição: (" << pos.first << "," << pos.second << ")" << std::endl;

		}

};