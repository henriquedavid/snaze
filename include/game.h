#include "memory"
#include <unistd.h>

using PlayerRef = std::unique_ptr<Player>;

class SnazeGame{

public:
	/// Estados possíveis do jogo.
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
	/// Armazena todos os mapas recebidos do arquivo externo.
	std::vector<Maps> mapas;
	/// Cobra.
	Snaze cobrinha;
	/// Níveis.
	Level nivel;
	/// Estado do jogo.
	Estados state;
	/// Jogador.
	Player player;
	/// Maça.
	Apple apple;
	/// Funcionamento da IA.
	AI ia;

    /// Controle de qual tipo de jogador deve ser executado.
    /// true = jogador humano ; false = IA.
    bool player_Human = false;

public:

	/// Inicializa o jogo, configurando todas as classes, como a maça, a cobra e o mapa (leitura).
	void initialize_game(std::string inputdata){
		/// Coloca o estado do jogo para iniciado.
		system("clear");
		state = START;
		game_init();

		// Realiza a leitura dos dados.
		this->mapas = readMaps(inputdata);
		
		// Envia os mapas para a classe nível.
		nivel.add_maps(mapas);
		// Verifica e configura as posições da apple.
		nivel.configurar_apple(apple);
		// Insere a apple na posição configurada no mapa.
		nivel.insert_apple(apple);

		// Recebe o mapa atual.
		Maps atual = nivel.get_current_level();
		// Configura a posição da cobrinha.
		cobrinha.set_position(atual.snaze_position());

		// Informa a quantidade de vidas e o total de níveis.
		std::cout << "###########                                                  ##########\n";
		std::cout << "###########      Level atual = " << (nivel.get_level()+1) << "   |  Total de Levels = " << nivel.all_levels() << "    ##########"<< std::endl;
		std::cout << "###########                                                  ##########\n";
		// Informa a quantidade de vidas e maças.
		std::cout << "###########            ";
		std::cout << "Vidas = " << cobrinha.get_life() << "  Maças: " << apple.get_quantity() << " de 5.";
		std::cout << "             ##########\n";
		std::cout << "###########                                                  ##########\n";
		std::cout << "#######################################################################\n";

		// Imprime o nível atual.
		nivel.print_current_map();

		char modo;

		std::cout << "########      O jogador está configurado para ser a IA,        ########\n########    deseja modificar para você controlar a cobra?        ######\n                          (y/n) :";
		std::cin >> modo;

		while( modo != 'y' && modo != 'n' ){
			std::cout << "Digite uma opção válida: \n(y/n) :";
			std::cin >> modo;
		}

		if(modo == 'y')
			player_Human = true;
		else 
			player_Human = false;



	}

	/// Processa todas as ações executas pelo jogador, ou pela IA.
	void process_events(){

        // Modifica o estado para processar os eventos.
		state = PROCESSING_EVENTS;

		std::pair<int,int> new_pos;

		// Verifica se está configurado para jogar a IA ou um humano.
		if(player_Human == true){
			int sentido = 0;
			//unsigned char tecla;

			// Recebe qual a posição desejada.
	        std::cout << "################   Insira o próximo movimento da Cobra:   ###############\n";
			std::cin >> sentido;

			// Gera novo movimento.
			Player::Movimento mov;

			// Atribui o movimento escolhido para mov.
			// 0 = NORTH, 1 = SOUTH, 2 = EAST e 3 = WEST.
			if( sentido == 0 )
				mov = Player::Movimento::NORTH;
			else if( sentido == 1)
				mov = Player::Movimento::SOUTH;
			else if( sentido == 2 )
				mov = Player::Movimento::EAST;
			else
				mov = Player::Movimento::WEST;

			// Envia as informações para processar no mapa os dados.
        	player.next_move(cobrinha, apple, mov, nivel.get_current_level());
		
		} else{

			// Recebe as coordenadas da cobra no mapa.
			auto coordCobra = cobrinha.get_position();

			try{

		        // Chama a IA para gerar o próximo movimento.
		        switch(ia.next_move(nivel, apple, cobrinha)){
	        		// Configura a posição da cobra a partir da IA..
					case Direction::N:
						cobrinha.set_position(std::make_pair(--coordCobra.first,coordCobra.second));
						break;
					case Direction::S:
						cobrinha.set_position(std::make_pair(++coordCobra.first,coordCobra.second));
						break;
					case Direction::E:
						cobrinha.set_position(std::make_pair(coordCobra.first,++coordCobra.second));
						break;
					case Direction::W:
						cobrinha.set_position(std::make_pair(coordCobra.first,--coordCobra.second));
						break;
					default:
						throw std::runtime_error("[ERROR]: Invalid player movement detected.");
				}

			} catch( std::runtime_error ex ){
				cobrinha.set_life(1);
			}

        }

	}

	/// Atualiza as informações no mapa, como se o usuário passou de nível, mordeu a maça ou houve colisão.
	void update(){
		// Modifica o estado para atualizando.
		state = UPDATING;

		// Verifica se a maça foi mordida.
		if( nivel.snake_in_apple(apple) || apple.mordida() ){
			cobrinha.marcarpontuacao();
			// Renderiza as informações.
			render();
			// Verifica se é possível passar de nível.
			nivel.level_up(apple, cobrinha);
			// Torna a maça visível.
			apple.show_apple();
			// Modifica a posição da maça no mapa.
			nivel.configurar_apple(apple);
		} else{
			// Verifica se houve colisão.
			if(colisao())
				cobrinha.perdervida();
			else
				nivel.change_snaze_pos(cobrinha.get_position(), cobrinha);
		}

	}

	/// Gera a situação do jogo para o usuário.
	void render(){
        system("clear");
		//std::cout << "Tamanho da cobra = " << cobrinha.get_tamanho_size() << std::endl ;
		//cobrinha.print_pos();

        if(player_Human == true){
        	std::cout << "#######################################################################\n";
        	std::cout << "######     0 - Baixo | 1 - Cima | 2 - Direita | 3 - Esquerda     ######\n";
        }
        game_init();
		// Mostra os dados de level atual e o total de levels.
		std::cout << "###########                                                  ##########\n";
		std::cout << "###########      Level atual = " << (nivel.get_level()+1) << "   |  Total de Levels = " << nivel.all_levels() << "    ##########"<< std::endl;
		std::cout << "###########                                                  ##########\n";
		// Informa a quantidade de vidas e maças.
		std::cout << "###########            ";
		std::cout << "Vidas = " << cobrinha.get_life() << "  Maças: " << apple.get_quantity() << " de 5.";
		std::cout << "             ##########\n";
		std::cout << "###########                                                  ##########\n";
		std::cout << "#######################################################################\n";
		// Faz com que a calda ande com a cobra.
		nivel.inserir_calda(cobrinha);

		// Imprime o mapa atual.
		nivel.print_current_map();
	}

	/// Verifica se é possível que o jogo continue.
	bool game_over(){

		// Intervalo de tempo.
        usleep(100000);

		// Verifica a quantidade vidas.
		if(cobrinha.get_life() == 0){
			state = APPLE_OVER;
			return true;
		}
		// Verifica se o jogador já passou por todos os níveis.
		if(nivel.win(apple) && apple.get_quantity() == 1 && nivel.get_level() != nivel.get_quantity_levels()){
			state = WON;
			return true;
		}

		if(nivel.win(apple) && apple.get_quantity() == 0){
			state = WON;
			return true;
		}

		return false;
	}

	/// Retorna o estado do jogo.
	Estados get_state(){
		return state;
	}

	/// Verifica se ocorreu alguma colisão.
	bool colisao(){
		// Recebe a posição da cobra.
		std::pair<int,int> cPos = cobrinha.get_position();
		int x = cPos.first;
		int y = cPos.second;
		// Recebe mapa atual.
		Maps atual = nivel.get_current_level();
		// Verifica se é alguma colisão.
		if( atual.get_value(x,y) == '#' || atual.get_value(x,y) == '-'){
			return true;
		}
		
		return false;
	}



};
