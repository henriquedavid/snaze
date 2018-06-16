/// Configura todas as informações ocorridas nos níveis.
class Level{
	private:
		/// Vetor com todos os mapas de cada level.
		std::vector<Maps> levels;
		/// Controle de qual o nível atual.
		unsigned int nivel;

	public:

		void show(){
			std::cout << "X = " << get_current_level().return_x() << " Y = " << get_current_level().return_y() << std::endl;
			print_current_map();
		}
		
		/// Construtor padrão do nível começando em 0.
		Level( int niv = 0 ) : nivel(niv) {/*empty*/}

		int get_quantity_levels(){
			return levels.size();
		}

		/// Controlador para validação sobre o próximo nível.
		void level_up( Apple & apple, Snaze & cobra ){
			// Verifica se a quantidade de maçãs realmente é 0.

			if( nivel+1 < levels.size() && apple.get_quantity() == 1){
				nivel++;
				apple.set_quantity(6);
				apple.show_apple();
				cobra.begin_size();
				show();
			}

			if( apple.get_quantity() == 0 ){
				// Aumenta a variavel nível.
				if(nivel+1 != levels.size())
					nivel++;
				// Torna a quantidade de maçãs para 5.
				apple.set_quantity(5);
				// Ativa a visualização da maçã.
				apple.show_apple();
				// Reseta o tamanho da cobra.
				cobra.begin_size();
				show();
			} else{
				// Faz a cobra comer a maçã.
				eat_apple(apple);
				// Faz a cobra aumentar de tamanho.
				cobra.add_size();
				// Insere a calda na cobra.
				inserir_calda(cobra);
			}
		}

		/// Adiciona os mapas a classe Level.
		void add_maps(std::vector<Maps> map){
			levels = map;
		}

		/// Retorna a quantidade de níveis.
		int all_levels(){
			return levels.size();
		}

		/// Faz com que a cobra coma a maçã.
		void eat_apple(Apple & apple){
			apple.lost_quantity();
		}

		/// Retorna qual o nível atual.
		int get_level(){
			return nivel;
		}

		/// Verifica se não há mais níveis e a quantidade de maças é 0.
		bool win(Apple & apple){
			if(nivel+1 >= levels.size() && apple.get_quantity() == 0)
				return true;
			//if(nivel+1 >= levels.size() && apple.get_quantity() == 0)
			//	return true;
			return false;
		}

		/// Configura a posição da maçã no mapa, de forma que ela não fique em cima de paredes ou em cima da cobra (corpo).
		void configurar_apple(Apple & apple){
			// Gera a posição da maçã.
			int v_x = apple.gerarCoordenadas(levels[nivel].return_x());
			int v_y = apple.gerarCoordenadas(levels[nivel].return_y());
			
			// Reccebe o que está naquela posição.
			char elemento = levels[nivel].get_value(v_x, v_y);

			// Verifica se não há nada naquela posição.
			if( elemento != '#' && elemento != '.' && elemento != '-'){
				apple.show_apple();
				apple.set_coordenadas(std::make_pair(v_x, v_y));
				if(apple.get_quantity() != 0 && nivel+1 <= levels.size())
					insert_apple(apple);
				}
			else
				configurar_apple(apple);
		}

		/// Insere a maçã em um local determinado.
		void insert_apple(Apple & apple){
			std::pair<int,int> coord = apple.get_coordenadas();
			levels[nivel].change_value(coord.first, coord.second, apple.get_aparencia());
		}

		/// Verifica se a cobra está na maçã, ou seja se a cobra comeu a maçã.
		bool snake_in_apple(Apple & apple){
			// Recebe a posição da cobra.
			std::pair<int,int> posSnake = levels[nivel].snaze_position();
			// Recebe a posição da maçã.
			std::pair<int,int> posApple = apple.get_coordenadas();

			int x_snake = posSnake.first;
			int y_snake = posSnake.second;
			int x_apple = posApple.first;
			int y_apple = posApple.second;

			// Vericia se a cobra está na maçã.
			if(x_snake == x_apple && y_snake == y_apple)
				return true;

			return false;
		}

		/// Imprime todos os níveis.
		void print_all_maps(){
			// Para cada nível imprime o mapa.
			for( auto & i : levels ){
				i.printVector();
			}
		}

		/// Imprime apenas o nível atual.
		void print_current_map(){
			levels[nivel].printVector();
		}

		/// Modifica a posição da cobra.
		void change_snaze_pos(std::pair<int,int> coordenadas, Snaze & cobra){
			levels[nivel].change_snaze_position(coordenadas, cobra);
		}

		/// Recebe o mapa do nível atual.
		Maps & get_current_level(){
			return levels[nivel];
		}

		/// Insere a calda, ou seja, faz com que seja inserida a calda na cobra.
		void inserir_calda(Snaze & cobra){

			limpa_mapa();

			for( auto i(0); i < cobra.get_tamanho_size(); i++ ){
				levels[nivel].change_value(cobra.get_calda(i).first, cobra.get_calda(i).second, '-');
			}

		}


		/// Limpa a configuração do mapa anterior, onde tem corpo da cobra não tem mais.
		void limpa_mapa(){
			for(auto i(0); i < levels[nivel].return_x() ; i++){
				for(auto j(0) ; j < levels[nivel].return_y(); j++){
					if( levels[nivel].get_value(i,j) == '-')
						levels[nivel].change_value(i,j, ' ');
				}
			}
		}

};