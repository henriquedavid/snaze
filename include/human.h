#ifndef HUMAN_H
#define HUMAN_H

#include "player.h"

class Human : public Player{
    Movimento next_move();
};

Player::Movimento Human::next_move()
{
        int sentido = 0;
        Player::Movimento mov;

		// Ações de testes com jogador HUMANO
		std::cout << "Insira a próxima posição da Cobra:\n";
		std::cin >> sentido;

		if( sentido == 0 )
			mov = Player::Movimento::NORTH;
		else if( sentido == 1)
			mov = Player::Movimento::SOUTH;
		else if( sentido == 2 )
			mov = Player::Movimento::EAST;
		else
			mov = Player::Movimento::WEST;
        return mov;
}

#endif
