/// Controle sobre as informações da cobra.
class Snaze{
	private:
		/// Posição na horizontal.
		int x;
		/// Posição na vertical.
		int y;
		/// Quantos pontos possui.
		int pontos;
		/// Vetor com as coordenadas do corpo da IA.
		sc::vector<std::pair<int,int>> tamanho;
		/// Quantidade de vidas.
		int vidas;

		/// Posição anterior a atual em x.
		int x_old;
		/// Posição anterior a atual em y.
		int y_old;

	public:

		/// Construtor padrão da cobra.
		Snaze( int pos1 = 1, int pos2 = 1, int pont = 0 , int life = 5 ) : x(pos1), y(pos2), pontos(pont), vidas(life){ /*empty*/}

		/// Modifica a posição da cobra para uma posição definida.
		void set_position(std::pair<int,int> pos){
			x_old = x;
			y_old = y;
			this->x = pos.first;
			this->y = pos.second;
			// Move o corpo juntamnete com a cobra.
			mover_corpo();
		}

		/// Retorna a posição da cobra.
		std::pair<int,int> get_position(){
			return std::make_pair(x,y);
		}

		/// Retorna a posição anterior da cobra (ajudar na inclusão do corpo).
		std::pair<int,int> get_old_position(){
			return std::make_pair(x_old, y_old);
		}

		/// Adição de uma nova parte da calda na posição anterior da cobra.
		void add_size(){
			tamanho.push_front(std::make_pair(x_old, y_old));
		}

		/// Retorna o vetor com as caldas.
		sc::vector<std::pair<int,int>> & get_tamanho(){
			return tamanho;
		}

		/// Imprime a posição da cobra (fins de testes).
		void print_pos(){
			for( auto & i : tamanho )
				std::cout << "(" << i.first << "," << i.second << ")\n";
		}

		/// Retorna o tamanho da calda.
		int get_tamanho_size(){
			return tamanho.size();
		}

		/// Configura a pontuação da cobra.
		void set_score(int x){
			pontos = x;
		}

		/// Retorna pontuação.
		int get_score(){
			return pontos;
		}

		/// Configura a quantidade de vidas da cobra.
		void set_life( int x ){
			vidas = x;
		}

		/// Retorna a quantidade de vidas.
		int get_life(){
			return vidas;
		}

		/// Marca a pontuação cada vez que come a maçã.
		void marcarpontuacao(){
			pontos += 156;
		}

		/// Perder uma vida.
		void perdervida(){
			vidas--;
		}

		/// Move a calda cada vez que a cobra anda.
		void mover_corpo(){
			if( tamanho.size() > 0 ){
			 	for( auto i(tamanho.size()-1) ; i != 0 ; i--  ){
			 		tamanho[i] = tamanho[i-1];
			 	}
			 	tamanho[0] = std::make_pair(x_old, y_old);
			}
		}

		/// Retorna a posição de uma determinada posição da calda.
		std::pair<int,int> get_calda(int i){
			return tamanho[i];
		}

		/// Remove o rabo e deixa só a cabeça.
		void begin_size(){
			tamanho.clear();
		}

};