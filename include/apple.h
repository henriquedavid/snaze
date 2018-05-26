class Apple{

	private:
		char aparencia;
		int quantidade;
		std::pair<int,int> coordenadas;

	public:

		Apple( int quant = 5, Maps mapa ) : quantidade(quant) {
			aparencia = '🍎';
			coordenadas = std::make_pair(gerarCoordenadas(mapa.return_x), gerarCoordenadas(mapa.return_y));
		}

		/// Gera posições randomicas.
		int gerarCoordenadas(int x_ou_y){
			std::mt19937 gen;
			std::uniform_int_distribution<int> dis;

			std::random_device rd;
			gen.seed( rd() );
			std::uniform_int_distribution<int>::param_type p( 1, x_ou_y-1);
			dis.param( p );

			int value = dis(gen);

			return  value;

		}

		void lost_quantity(){
			quantidade--;
		}

		int get_quantity(){
			return quantidade;
		}

		void set_quantity( int v ){
			quantidade = v;
		}

		void hide_apple(){
			aparencia = ' ';
		}


};