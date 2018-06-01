#include "player.h"
#include "human.h"
// #include "IA.h"
#include <memory>

// ALIAS
using PlayerRef = std::unique_ptr<Player>;


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
    /* Devido ser uma tipo abstrato, não poderemos simplesmente fazer 
     * uma cópia comum, temos que guardar uma referencia da qual sabemos
     * que contém o método next_move() implementado. */
	PlayerRef player; 
	Apple apple;


public:

	/// Inicializa o jogo.
	void initialize_game(std::string inputdata){
		state = START;
		// Realiza a leitura dos dados.
		this->mapas = readMaps(inputdata);
		
		// Envia os mapas para a classe nível.
		nivel.add_maps(mapas);
		// Verifica e configura as posições da apple.
		nivel.configurar_apple(apple);
		// Insere a apple na posição configurada no mapa.
		nivel.insert_apple(apple);

		// Configura a posição da cobrinha.
		Maps atual = nivel.get_current_level();
		cobrinha.set_position(atual.snaze_position());

		std::cout << "Level atual = " << (nivel.get_level()+1) << "  Total de Levels = " << nivel.all_levels() << std::endl;
		std::cout << "Vidas = " << cobrinha.get_life() << "  Maças: " << apple.get_quantity() << " de 5." << std::endl;

		nivel.print_current_map();
        
        player = PlayerRef(new IA(mapas[mapas.size()-1], cobrinha, apple));

	}

	/// Processa todas as ações executas pela IA.
	void process_events(){
		state = PROCESSING_EVENTS;
        std::pair<int,int> posSnaze = cobrinha.get_position();
        Player::Movimento mov = player->next_move();
        
        int x = posSnaze.first;
        int y = posSnaze.second;

        if(mov == Player::Movimento::NORTH)
            cobrinha.set_position(std::make_pair(x+1,y));
        else if(mov == Player::Movimento::SOUTH)
            cobrinha.set_position(std::make_pair(x-1,y));
        else if(mov == Player::Movimento::EAST)
            cobrinha.set_position(std::make_pair(x,y+1));
        else
            cobrinha.set_position(std::make_pair(x,y-1));
	}

	/// Atualiza as informações no mapa
	void update(){
		state = UPDATING;
		if( nivel.snake_in_apple(apple) || apple.mordida() ){
			state = LEVEL_UP;
			render();
			nivel.level_up(apple, cobrinha);
			apple.show_apple();
			nivel.configurar_apple(apple);
		} else{
			if(colisao())
				cobrinha.perdervida();
			else
				nivel.change_snaze_pos(cobrinha.get_position(), cobrinha);
		}

	}

	void render(){
		//system("clear");
		std::cout << "Tamanho da cobra = " << cobrinha.get_tamanho_size() << std::endl ;
		cobrinha.print_pos();
		std::cout << "Level atual = " << (nivel.get_level()+1) << "  Total de Levels = " << nivel.all_levels() << std::endl;
		std::cout << "Vidas = " << cobrinha.get_life() << "  Maças: " << apple.get_quantity() << " de 5." << std::endl;
		nivel.inserir_calda(cobrinha);

		nivel.print_current_map();
	}

	bool game_over(){
		if(cobrinha.get_life() == 0){
			state = APPLE_OVER;
			return true;
		}



		if(nivel.win(apple)){
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
		if( atual.get_value(x,y) == '#' || atual.get_value(x,y) == '-'){
			return true;
		}
		return false;
	}



};
