class SnazeGame{

	enum Estados
	{
		START = 0,
		RUNNING,
		PROCESSING_EVENTS,
		UPDATING,
		RENDERING,
		APPLE_OVER,
		LEVEL_UP,
		DEAD,
		WON,
		GAME_OVER
	};

private:
	std::vector<Maps> mapas;
	Snaze cobrinha;
	Level nivel;
	Estados state;


public:

	/// Inicializa o jogo.
	void initialize_game(std::string inputdata){
		state = START;
		// Realiza a leitura dos dados.
		this->mapas = readMaps(inputdata);
		
		// Envia os mapas para a classe nível.
		nivel.add_maps(mapas);
		// Verifica e configura as posições da apple.
		nivel.configurar_apple();
		// Insere a apple na posição configurada no mapa.
		nivel.insert_apple();

		//print_all_maps();		

		//cobrinha.set_position(mapas[0].snaze_position());

	}

	void process_events(){
		state = PROCESSING_EVENTS;
		// A IA irá atuar aqui.
	}

	void update(){
		state = UPDATING;
		if( nivel.snake_in_apple() ){
			state = LEVEL_UP;
			render();
			nivel.level_up();
		}

	}

	void render(){
		state = RENDERING;
		//system("clear");
		nivel.print_all_maps();
	}

	bool game_over(){
		state = GAME_OVER;
		if(cobrinha.get_life() == 0){
			state = APPLE_OVER;
			return false;
		}
		if(nivel.win()){
			state = WON;
			return false;
		}

		return true;
	}

};