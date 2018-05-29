class Snaze{
	private:
		int x;
		int y;
		int pontos;
		sc::vector<std::pair<int,int>> tamanho;
		int vidas;

		int x_old;
		int y_old;

	public:

		Snaze( int pos1 = 1, int pos2 = 1, int pont = 0 , int life = 5 ) : x(pos1), y(pos2), pontos(pont), vidas(life){ /*empty*/}

		void set_position(std::pair<int,int> pos){
			x_old = x;
			y_old = y;
			this->x = pos.first;
			this->y = pos.second;
			mover_corpo();
		}

		std::pair<int,int> get_position(){
			return std::make_pair(x,y);
		}

		std::pair<int,int> get_old_position(){
			return std::make_pair(x_old, y_old);
		}

		void add_size(){
			tamanho.push_front(std::make_pair(x_old, y_old));
		}

		sc::vector<std::pair<int,int>> & get_tamanho(){
			return tamanho;
		}

		void print_pos(){
			for( auto & i : tamanho )
				std::cout << "(" << i.first << "," << i.second << ")\n";
		}

		int get_tamanho_size(){
			return tamanho.size();
		}

		void set_score(int x){
			pontos = x;
		}

		int get_score(){
			return pontos;
		}

		void set_life( int x ){
			vidas = x;
		}

		int get_life(){
			return vidas;
		}

		void marcarpontuacao(){
			pontos += 156;
		}

		void perdervida(){
			vidas--;
		}

		void mover_corpo(){
			if( tamanho.size() > 1 ){
			 	tamanho[0] = std::make_pair(x_old, y_old);
			 	/*for( auto i(tamanho.size()-1) ; i != 0 ; i++  ){
			 		tamanho[i] = tamanho[i-1];
			 	}*/
			}
		}

};