#ifndef GAME_AI_H
#define GAME_AI_H

#include <iostream>
#include <stack>
#include <climits>
#include <set>
#include <cstring>
#include <vector>
#include <memory>
#include <deque>

#include "game_classes.hpp"

/// Estrutura para armazenar os parâmetros necessários para o algoritmo A*.
struct Cell
{
    std::pair<int,int> parent;
    bool HasParent;
    uint f, g, h, i;
    // i é valor de custo adicional para que essa não colida com a cauda 

    /// Contrutor default para o struct.
    Cell() = default;
    /// Construtor que recebe uma localização,
    Cell(Point p);
    /// Construtor que recebe um std::pair<int,int> com coordenadas.
    Cell(std::pair<int,int> p);
};

/// Classe que controla a IA de forma a seguir o algoritmo A*.
class AI : public Player
{
    public:
        
        /// Retorna qual deve ser a próxima posição da IA.
        Direction next_move( Level & lvl, Apple & app, Snaze & sna);
        /// Anda pelo caminho livre.
        Direction goto_free_way( Level & lvl, Apple & app, Snaze & sna );
        
        
    private:

        /// Verifica se em uma determinada posição é válida.
        bool isValid(Point p, Level & niv);
        /// Verifica se não possui nenhuma parede ou calda em determinada posição.
        bool isUnBlocked(Point p, Level & niv);
        /// Verifica se é onde está a maçã.
        bool isDestination(Point p, Apple & apple);
        /// Calcula o valor de 'h' de forma que seja um bom caminho. H que informa os custos de movimentos para encontrar o menor.
        double calculateHValue(Point p, Apple & apple);
        /// Traça o caminho do ponto de partida ao destino.
        void tracePath(Apple & apple);
        /// Função para encontrar o caminho mais curto entre a origem até o destino, de acordo com o algoritmo A*.
        bool aStarSearch( Level & lvl, Apple & app, Snaze & sna );
        
        /// Level atual.
        std::shared_ptr< Level > m_level;
        /// Quais serão os caminhos percorridos,
        std::stack<Direction> m_path;
        /// Detalhes de cada célula, o que há nelas.
        std::vector< std::vector<Cell> > m_cellDetails;
        /// O caminho final.
        std::stack<std::pair<int,int>> Path;
        /// O ponto de destino.
        std::pair<int,int> m_goal;
        /// Pontos que não é possível percorrer.
        std::pair<int,int> m_critical_point;
        /// Último movimento.
        Direction m_last_move = Direction::S;
        
       
};

#include "ia_astar.h"

#endif