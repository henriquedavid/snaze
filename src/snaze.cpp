#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <random>

#include "../include/maps.h"
#include "../include/apple.h"
#include "../include/level.h"
#include "../include/snake.h"
#include "../include/support.h"
#include "../include/game.h"	// Configurações e controle do jogo.

int main(int argc, char * args[]){

	if( argc < 2 ){
		std::cout << "Wrong syntax! I think you forgot the input argument with the levels.\n";
		exit(0);
	}

	// Entrada principal que instancia todos os objetos e gerencia a execução do jogo.
	SnazeGame sg;

	std::string inputData = args[1];

	// Inicializa o jogo.
	sg.initialize_game(inputData);

	
	/*while( sg.game_over() ){

		// Recebe as ações dos usuários.
		sg.process_events();

		// Modifica a partir das ações realizadas pelo usuário.
		sg.update();

		// Mostra para o usuário visualmente o jogo.
		sg.render();

	}*/

	// Saída do jogo.
	return 0;
}