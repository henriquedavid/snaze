class Level{
	private:
		std::vector<Maps> levels;
		unsigned int nivel;

	public:
		

		Level( int niv = 0 ) : nivel(niv) {/*empty*/}

		void level_up( Apple & apple, Snaze & cobra ){
			if(apple.get_quantity() == 0){
				nivel++;
				apple.set_quantity(5);
				apple.show_apple();
			} else{
				eat_apple(apple);
				cobra.add_size();
				inserir_calda(cobra);
			}
		}

		void add_maps(std::vector<Maps> map){
			levels = map;
		}

		int all_levels(){
			return levels.size();
		}

		void eat_apple(Apple & apple){
			apple.lost_quantity();
		}


		int get_level(){
			return nivel;
		}

		bool win(Apple & apple){
			if(nivel+1 >= levels.size() && apple.get_quantity() == 0)
				return true;
			return false;
		}

		void configurar_apple(Apple & apple){
			int v_x = apple.gerarCoordenadas(levels[nivel].return_x());
			int v_y = apple.gerarCoordenadas(levels[nivel].return_y());
			
			char elemento = levels[nivel].get_value(v_x, v_y);

			if( elemento != '#' && elemento != '.' && elemento != '-'){
				apple.show_apple();
				apple.set_coordenadas(std::make_pair(v_x, v_y));
				insert_apple(apple);
				}
			else
				configurar_apple(apple);
		}

		void insert_apple(Apple & apple){
			std::pair<int,int> coord = apple.get_coordenadas();
			levels[nivel].change_value(coord.first, coord.second, apple.get_aparencia());
		}

		bool snake_in_apple(Apple & apple){
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

		void change_snaze_pos(std::pair<int,int> coordenadas, Snaze & cobra){
			levels[nivel].change_snaze_position(coordenadas, cobra);
		}

		Maps & get_current_level(){
			return levels[nivel];
		}

		void inserir_calda(Snaze & cobra){

			auto calda = cobra.get_tamanho();
			auto current_level = levels[nivel];

			for( auto & i : calda ){
				levels[nivel].change_value(i.first, i.second, '-');
				//std::cout << "Posição =" << "(" << i.first << "," << i.second << ")\n" ;
			}

		}

};