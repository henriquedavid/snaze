class SnazeGame{

private:
	std::vector<Maps> mapas;
	Snaze cobrinha;
	


public:

	// Para fins de compilação.
	void print_all_maps(){
		std::cout << "MAPA = " << mapas[0].return_x() << " " << mapas[0].return_y() << std::endl;
		for( auto & i : mapas ){
			i.printVector();
		}
		std::pair<int,int> pos = mapas[0].snaze_position();
		std::cout << "A cobra está na posição: (" << pos.first << "," << pos.second << ")" << std::endl;

	}
	/// Inicializa o jogo.
	void initialize_game(std::string inputdata){

		this->mapas = readMaps(inputdata);
		print_all_maps();

		cobrinha.set_position(mapas[0].snaze_position());
		std::pair<int,int> pos = cobrinha.get_position();
		std::cout << "A cobra está na posição: (" << pos.first << "," << pos.second << ")" << std::endl;

	}

	void update(){

	}

	void process_events(){

	}

	void render(){

	}

	bool game_over(){



		return true;

	}

};