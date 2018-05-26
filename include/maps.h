class Maps{

private:
	/// Altura do mapa.
	int x_total;
	/// Largura do mapa.
	int y_total;
	/// Mapa
	std::vector<std::vector< char >> mapa;

public:
	/// Construtor principal.
	Maps(int x=0, int y=0 ) : x_total(x), y_total(y) { /*empty*/ }

	/// Adiciona os objetos do mapa.
	void add_objects(std::vector<char> linhas){
		int a = 0;
		std::vector<char> vet;
		for(auto i(0); i < x_total ; i++){
			vet.clear();
			for( auto j(0) ; j < y_total; j++ ){
				vet.push_back(linhas[a]);
				a++;
			}

			mapa.push_back(vet);
		}
	}

	void clear_all(){
		x_total = 0;
		y_total = 0;
		mapa.clear();
	}

	void changexey(int x, int y){
		x_total = x;
		y_total = y;
	}

	/// Modifica um valor em uma determinada posição.
	void change_value( int x, int y, char value ){
		mapa[x][y] = value;
	}
	
	/// Modifica o valor da largura do mapa.
	void change_x( int valor ){
		this->x_total = valor;
	}

	/// Modifica o valor da altura do mapa.
	void change_y( int valor ){
		this->y_total = valor;
	}

	/// Retorna o valor da largura do mapa.
	int return_x(){
		return x_total;
	}

	/// Retorna o valor da altura do mapa.
	int return_y(){
		return y_total;
	}

	/// Imprime o mapa.
	void printVector(){

		for( auto i(0) ; i < x_total; ++i ){
			for( auto j(0); j < y_total ; ++j )
				std::cout << mapa[i][j];
			std::cout << std::endl;
		}

	}

	/// Retorna a posição da cobra.
	std::pair<int,int> snaze_position(){

		for( auto i(0) ; i < x_total; ++i ){
			for( auto j(0); j < y_total ; ++j )
				if(mapa[i][j] == '>' || mapa[i][j] == '<' || mapa[i][j] == 'v' || mapa[i][j] == '^')
					return std::make_pair(i+1,j+1);
		}

		return std::make_pair(0,0);
	}

};