/// Realiza a leitura dos mapas a partir de um arquivo externo. 
std::vector<Maps> readMaps( std::string name_input ){
	
	// Vetor para armazenar cada mapa.
	std::vector<Maps> mapas;
	// Vetor para armazenar os detalhes do mapa.
	std::vector<char> valores;
	
	std::ifstream file_input;

	// Abre o arquivo externo.
	file_input.open(name_input);

	// Verifica se foi possível abrir.
	if( file_input.fail() ){
		std::cout << "Trying to open input file...error! Try again!\n";
		exit(-1);
	}

	// Processa os valores a uma variavel char
	std::string v;
	// Junta os valores que são valores de coordenada.;
	std::string xey = "";
	// Verifica se é espaço.
	bool space = false;
	// Verifica se possui cobra o mapa.
	bool cobra = false;
	// Verifica se deve modificar x e y.
	bool muda_x_y = true;

	bool more_100 = false;
	// Variaveis auxiliares.
	int x = 0;
	int y = 0;
	std::string x_s = "";
	std::string y_s = "";

	// Construtor de um mapa padrão.
	Maps mapa(x, y);

	// Verifica cada linha.
	while( getline(file_input, v) ){

		// Testa se é uma posição.
		if( v[0] == '0' || v[0] == '1' || v[0] == '2' || v[0] == '3' || v[0] == '4' || v[0] == '5' || v[0] == '6' || v[0] == '7' || v[0] == '8' || v[0] == '9' ){

			// Limpa o vetor que armazena apenas 1 mapa.
			valores.clear();
			// Limpa os mapas.
			mapa.clear_all();

			space = false;

			// Percorre cada char da linha para obter as posições x e y.
			for( auto & i : v ){
				if(i == ' '){
					space = true;
				}
				if(space == false)
					x_s += i;
				else
					y_s += i;

			}

			muda_x_y = true;
			cobra = false;

		} else{

			// Quando não for '-' ele converte a posição e adiciona os valores das posições e adiciona cada dado do mapa a valores.
			if(v != "-"){
				
				if( muda_x_y == true ){
					std::string::size_type sz;
					x = std::stoi(x_s, &sz);
					y = std::stoi(y_s, &sz);


					mapa.changexey(x, y);
					

					muda_x_y = false;
				}

				for( auto & i : v ){
					// Trata caso o usuário não colocou a cobra no mapa.
					if( i == '<' || i == '>' || i == '^' || i == 'v')
						cobra = true;
					valores.push_back(i);
				}

			}
		}

		// A condição de que esse mapa terminou é encontrar uma string com "-" no final do mapa
		if( v == "-"){

			if(cobra == true)
				mapa.add_objects(valores);

			if(x > 100 || y > 100){
				more_100 = true;
			}

			x_s = "";
			y_s = "";
			x = 0;
			y = 0;

			if(cobra == true)
				mapas.push_back(mapa);
		}

	}

	// Fecha o arquivo.
	file_input.close();

	// Verifica se a cobra está realmennte no mapa.
	if(cobra != true){
		std::cout << "Sorry, this isn't a valid file!\n";
		exit(-1);
	}

	// Verifica se o mapa possui alguma dimensão maior que 100.
	if(more_100){
		std::cout << "Invalid maps!\n";
		exit(-1);
	}

	// Retorna o vetor com todos os mapas.
	return mapas;

}

/// Mensagem de vencedor.
void won_message(){
	system("clear");

	/*std::cout << "Tan tan... tan tan tan tan... tan tan tan\n";
	std::cout << "We got a WINNER! Congratulations!\nMAY THE FORCE BE WITH YOU!\n";*/

	std::cout << "#######################################################################\n";
	std::cout << "###   ##############  ###  ###    ##  ###   ##  ##      ###      ######\n";
	std::cout << "####   ############  ####  ###     #  ###    #  ##  #######  ### ######\n";
	std::cout << "#####   ####  ####  #####  ###  ##    ###  #    ##    #####      ######\n";
	std::cout << "######   ##    ##  ######  ###  ###   ###  ##   ##  #######  ##  ######\n";
	std::cout << "#######      ##   #######  ###  ####  ###  ###  ##      ###  ##  ######\n";
	std::cout << "#######################################################################\n";
	std::cout << "####                  ###  #############  #############################\n";
	std::cout << "#### We got a WINNER! ####   ####  ####   ##########     MAY    #######\n";
	std::cout << "####                  #####   ###  ###   ########### THE FORCE  #######\n";
	std::cout << "###########################             ############   BE WITH  #######\n";
	std::cout << "#############################     #     ############     YOU!   #######\n";
	std::cout << "###############################       #################################\n";
	std::cout << "#################################   ###################################\n";
	std::cout << "#################################   ###################################\n";
	std::cout << "###############################       #################################\n";
	std::cout << "###########################               #############################\n";
	std::cout << "###########################               #############################\n";
	std::cout << "#######################################################################\n";


}

/// Mensagem de perdedor.
void loser_message(){
	system("clear");
/*
	std::cout << "Well... well...\n";
	std::cout << "Oh dear! What an awkward situation\n";*/

	std::cout << "#######################################################################\n";
	std::cout << "#######################################################################\n";
	std::cout << "##        ##      ##          ##      ##       ##  #####  ##      #   #\n";
	std::cout << "##  ########  ##  ##  ##  ##  ##  ######  ###  ##  ####  ###  ##### # #\n";
	std::cout << "##  ########  ##  ##  ##  ##  ##    ####  ###  ###  ###  ###    ### # #\n";
	std::cout << "##  ####  ##      ##  ######  ##  ######  ###  ####  #  ####  #####   #\n";
	std::cout << "##  ####  ##  ##  ##  ######  ##  ######  ###  ####  #  ####  ##### # #\n";
	std::cout << "##        ##  ##  ##  ######  ##      ##       #####   #####      # # #\n";
	std::cout << "#######################################################################\n";
	std::cout << "#######################      |#       #################################\n";
	std::cout << "#######################      |         ################################\n";
	std::cout << "#######################      |        #################################\n";
	std::cout << "#######################      |         ################################\n";
	std::cout << "##############################     ####################################\n";
	std::cout << "###############################    ####################################\n";
	std::cout << "################################   ####################################\n";
	std::cout << "#######################################################################\n";
	std::cout << "############## Oh dear! What an awkward situation! ####################\n";
	std::cout << "#######################################################################\n";

}

void game_init(){
	std::cout << "#######################################################################\n";
	std::cout << "#######################################################################\n";
	std::cout << "##          ###        ###   ##           ###         ###          ####\n";
	std::cout << "##   ##########   ##   ###   ##   #####   #########   ###   ###########\n";
	std::cout << "##   ##########   ###   ##   ##   #####   #######    ####   ###########\n";
	std::cout << "##         ####   ####   #   ##   #####   #####    ######       #######\n";
	std::cout << "########   ####   #####      ##           ####   ########   ###########\n";
	std::cout << "########   ####   ######     ##   #####   ###   #########   ###########\n";
	std::cout << "##         ####   #######    ##   #####   ###         ###          ####\n";
	std::cout << "#######################################################################\n";
	std::cout << "##### o ######### <----- ###### <----- ####### <----- ###### <----- ###\n";
	std::cout << "#######################################################################\n";

}