class Snaze{
	private:
		int x;
		int y;
		int pontos;
		int tamanho;
		int vidas;

	public:

		Snaze( int pos1 = 1, int pos2 = 1, int pont = 0, int sz = 0 , int life = 5 ) : x(pos1), y(pos2), pontos(pont), tamanho(sz), vidas(life){ /*empty*/}

		void set_position(std::pair<int,int> pos){
			this->x = pos.first;
			this->y = pos.second;
		}

		std::pair<int,int> get_position(){
			return std::make_pair(x,y);
		}

		void set_score(int x){
			pontos = x;
		}

		int get_score(){
			return pontos;
		}

		void set_tamanho( int x ){
			tamanho = x;
		}

		int get_tamanho(){
			return tamanho;
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

};