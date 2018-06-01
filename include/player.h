#ifndef PLAYER_H
#define PLAYER_H

/*
 * O player é uma entidade abststrata que tem a responsabilidade de dizer pro jogo qual seu proximo movimento
 */

class Player{
	public:
		enum Movimento{
			SOUTH,
			NORTH,
			EAST,
			WEST
		};
		/// Realiza a movimentação da Snaze
		virtual Movimento next_move() = 0;
        // se o jogo suportar dois players, o player terá que processar eventos globais, pois a IA
        // terá que saber, por exemplo, se a maça já foi comida por outro player para achar a solução
        // novamente
        
};

#endif
