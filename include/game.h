class SnazeGame{

private:
	std::vector<Maps> mapas;
	Snaze cobrinha;
	Level nivel;



public:

	/// Inicializa o jogo.
	void initialize_game(std::string inputdata){
		// Realiza a leitura dos dados.
		this->mapas = readMaps(inputdata);
		
		// Envia os mapas para a classe nível.
		nivel.add_maps(mapas);
		// Verifica e configura as posições da apple.
		nivel.configurar_apple();
		// Insere a apple na posição configurada no mapa.
		nivel.insert_apple();

		//print_all_maps();

		nivel.print_all_maps();

		//cobrinha.set_position(mapas[0].snaze_position());
		std::pair<int,int> pos = cobrinha.get_position();
		std::cout << "A cobra está na posição: (" << pos.first << "," << pos.second << ")" << std::endl;

	}

	void process_events(){

	}

	void update(){

	}

	void render(){

	}

	bool game_over(){



		return true;

	}

};