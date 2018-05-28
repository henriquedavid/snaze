class SnazeGame{

public:
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
	Player player;


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

		// Configura a posição da cobrinha.
		Maps atual = nivel.get_current_level();
		cobrinha.set_position(atual.snaze_position());

		std::cout << "Level atual = " << nivel.get_level() << "  Total de Levels = " << nivel.all_levels() << std::endl;
		std::cout << "Vidas = " << cobrinha.get_life() << std::endl;

		nivel.print_current_map();

	}

	/// Processa todas as ações executas pela IA.
	void process_events(){
		state = PROCESSING_EVENTS;
		std::pair<int,int> new_pos;
		int sentido = 0;

		// Ações de testes com jogador HUMANO
		std::cout << "Insira a próxima posição da Cobra:\n";
		std::cin >> sentido;

		Player::Movimento mov;

		if( sentido == 0 )
			mov = Player::Movimento::NORTH;
		else if( sentido == 1)
			mov = Player::Movimento::SOUTH;
		else if( sentido == 2 )
			mov = Player::Movimento::EAST;
		else
			mov = Player::Movimento::WEST;

		player.next_move(cobrinha, mov);

		// A IA irá atuar aqui.
	}

	/// Atualiza as informações no mapa
	void update(){
		state = UPDATING;
		if( nivel.snake_in_apple() || nivel.apple.mordida() ){
			state = LEVEL_UP;
			render();
			nivel.level_up();
		} else{
			if(colisao())
				cobrinha.perdervida();
			else
				nivel.change_snaze_pos(cobrinha.get_position());
		}

	}

	void render(){
		system("clear");
		std::cout << "Level atual = " << nivel.get_level() << "  Total de Levels = " << nivel.all_levels() << std::endl;
		std::cout << "Vidas = " << cobrinha.get_life() << std::endl;
		nivel.print_current_map();
	}

	bool game_over(){
		if(cobrinha.get_life() == 0){
			state = APPLE_OVER;
			return true;
		}



		if(nivel.win()){
			state = WON;
			return true;
		}

		return false;
	}

	Estados get_state(){
		return state;
	}

	bool colisao(){
		std::pair<int,int> cPos = cobrinha.get_position();
		int x = cPos.first;
		int y = cPos.second;
		Maps atual = nivel.get_current_level();
		if( atual.get_value(x,y) == '#' ){
			return true;
		}
		return false;
	}

};