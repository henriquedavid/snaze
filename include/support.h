std::vector<Maps> readMaps( std::string name_input ){
	
	std::vector<Maps> mapas;
	std::vector<char> valores;
	
	std::cout << "Trying to open input file... ";

	std::ifstream file_input;

	file_input.open(name_input);

	if( file_input.fail() ){
		std::cout << "error! Try again!\n";
		exit(-1);
	}

	// Processa os valores a uma variavel char
	std::string v;
	// Junta os valores que são valores;
	std::string xey = "";
	// Verifica se é um novo mapa
	bool space = false;
	bool muda_x_y = true;
	int x = 0;
	int y = 0;
	std::string x_s = "";
	std::string y_s = "";

	Maps mapa(x, y);

	while( getline(file_input, v) ){

		if( v[0] == '0' || v[0] == '1' || v[0] == '2' || v[0] == '3' || v[0] == '4' || v[0] == '5' || v[0] == '6' || v[0] == '7' || v[0] == '8' || v[0] == '9' ){

			valores.clear();
			mapa.clear_all();

			space = false;
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

		} else{

			if(v != "-"){

				if( muda_x_y == true ){
					std::string::size_type sz;
					x = std::stoi(x_s, &sz);
					y = std::stoi(y_s, &sz);

					mapa.changexey(x, y);

					muda_x_y = false;
				}

				for( auto & i : v ){
					valores.push_back(i);
				}

			}
		}

		// A condição de que esse mapa terminou é encontrar uma string com "-" no final do mapa
		if( v == "-"){

			mapa.add_objects(valores);

			mapas.push_back(mapa);
		}

	}

	file_input.close();

	std::cout << "done!\n";

	return mapas;

}