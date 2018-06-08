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

struct Cell
{
    std::pair<int,int> parent;
    bool HasParent;
    uint f, g, h, i;
    // i é valor de custo adicional para que essa não colida com a cauda 

    
    Cell() = default;
    Cell(Point p);
    Cell(std::pair<int,int> p);
};

class AI : public Player
{
    public:
        
        //AI(Level level);
        Direction next_move( Level & lvl, Apple & app, Snaze & sna);
        Direction goto_free_way( Level & lvl, Apple & app, Snaze & sna );
        
        
    private:

        // -- Astar algorithm funcions
        bool isValid(Point p, Level & niv);
        bool isUnBlocked(Point p, Level & niv);
        //uint risk(Point p, Point parent);
        bool isDestination(Point p, Apple & apple);
        double calculateHValue(Point p, Apple & apple);
        void tracePath(Apple & apple);
        bool aStarSearch( Level & lvl, Apple & app, Snaze & sna );
        
        
        std::shared_ptr< Level > m_level;
        
        std::stack<Direction> m_path;
        std::vector< std::vector<Cell> > m_cellDetails;
        std::stack<std::pair<int,int>> Path;
        std::pair<int,int> m_goal;
        
        std::pair<int,int> m_critical_point;
        Direction m_last_move = Direction::S;
        
       
};

#include "ia_astar.h"

#endif