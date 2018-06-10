/// Classe que controla todas as informações da maçã.
class Apple{

	private:
		/// Recebe a aparencia da maçã.
		char aparencia;
		/// Informa a quantidade de maçãs que restam para passar de nível.
		int quantidade;
		/// Armazena as coordenadas da maçã.
		std::pair<int,int> coordenadas;

	public:
		/// Construtor padrão para a maçã, iniciando com 5 maçãs para passar de nível e aparencia em forma de o.
		Apple( int quant = 5 ){
			quantidade = quant;
			aparencia = 'o';
		}

		/// Gera posições randomicas.
		int gerarCoordenadas(int x_ou_y){
			std::mt19937 gen;
			std::uniform_int_distribution<int> dis;

			std::random_device rd;
			gen.seed( rd() );
			std::uniform_int_distribution<int>::param_type p( 1, x_ou_y-2);
			dis.param( p );

			int value = dis(gen);

			return  value;

		}

		/// Retorna as coordenadas da maçã.
		std::pair<int,int> get_coordenadas(){
			return coordenadas;
		}

		/// Configura as coordenadas da maçã.
		void set_coordenadas(std::pair<int,int> coor){
			int x = coor.first;
			int y = coor.second;

			coordenadas = std::make_pair(x, y);
		}

		/// Diminuir quantidade de maçãs.
		void lost_quantity(){
			quantidade--;
		}

		/// Retorna a quantidade de maçãs.
		int get_quantity(){
			return quantidade;
		}

		/// Modifica a quantidade de maçãs para um valor especifico.
		void set_quantity( int v ){
			quantidade = v;
		}

		/// Torna a aparência da maçã como o.
		void show_apple(){
			aparencia = 'o';
		}

		/// Retorna a aparência da maçã.
		char get_aparencia(){
			return aparencia;
		}

		/// Mostra a posição da maçã (efeitos de testes).
		void show_position(){
			std::cout << "(" << coordenadas.first << "," << coordenadas.second << ")\n";
		}

		/// Modifica a aparencia da maçã caso seja mordida.
		bool mordida(){
			if(aparencia == ' ')
				return true;

			return false;
		}


};