class SnazeGame{

private:
	std::vector<Maps> mapas;

public:


	void print_all_maps(){
		std::cout << "MAPA = " << mapas[0].return_x() << " " << mapas[0].return_y() << std::endl;
		for( auto & i : mapas ){
			i.printVector();
		}

	}

	void initialize_game(std::string inputdata){

		this->mapas = readMaps(inputdata);
		print_all_maps();

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