#include <stack>

class IA : public Player{
	
    public:

        IA(Maps& atual, Snaze& cobrinha, Apple& apple);
        
        class Position{
            public:

                int x;
                int y;

                Position( int a, int b ) : x(a), y(b){/* empty */}

                std::pair<int,int> get_position(){
                    return std::make_pair(x,y);
                }

                void set_position(std::pair<int,int> & posicao){
                    x = posicao.first;
                    y = posicao.second;
                }
                
                Movimento next_move();
        };

        class Maze{

            private:
                
                Position dir;

            public:
                sc::vector<sc::vector<char>> maze_;
                
            enum direction_t{ NORTH=0, EAST, SOUTH, WEST};

            // por cópia
            Maze( sc::vector<sc::vector<char>> l  = {}): dir(0, 0)
            { 
                maze_ = l;
            }

            enum cell_t { START, WALL, BODY, WALK };

            Position get_start_position( Snaze & cobra ){

                auto posicao = cobra.get_position();

                return Position(posicao.first, posicao.second);

            }

            bool is_apple( Position & pos, Apple & apple ){
                std::pair<int,int> pos_player = pos.get_position();
                std::pair<int,int> pos_apple = apple.get_coordenadas();

                if(pos_player.first == pos_apple.first && pos_player.second == pos_apple.second)
                    return true;
                return false;
            }

            bool is_blocked( Position & pos,  direction_t dir ){

                if(dir == direction_t::NORTH)
                    if(maze_[pos.x+1][pos.y] == '#' || maze_[pos.x+1][pos.y] == '-')
                        return true;

                if(dir == direction_t::SOUTH)
                    if(maze_[pos.x-1][pos.y] == '#' || maze_[pos.x-1][pos.y] == '-')
                        return true;

                if(dir == direction_t::WEST)
                    if(maze_[pos.x][pos.y-1] == '#' || maze_[pos.x][pos.y-1] == '-')
                        return true;

                if(dir == direction_t::EAST)
                    if(maze_[pos.x][pos.y+1] == '#' || maze_[pos.x][pos.y+1] == '-')
                        return true;

                return false;
            }

            void mark_cell( const Position & pos ){
                maze_[pos.x][pos.y] = 'x';
            }

            void unmark_cell( const Position & pos ){
                maze_[pos.x][pos.y] = ' ';
            }

            bool is_marked( const Position & pos ){
                if(maze_[pos.x][pos.y] == 'x')
                    return true;
                return false;
            }

        };

        Position walk_to_cell( Position & p, const Maze::direction_t & d ){
            switch(d){
                case Maze::direction_t::NORTH: return Position(p.x+1, p.y);
                case Maze::direction_t::SOUTH: return Position( p.x-1, p.y );
                case Maze::direction_t::EAST: return Position( p.x, p.y+1 );
                default: return Position( p.x, p.y-1 );
            }
        }


        bool solve_maze(  Maze & mz,  Position  start, Apple & apple ){
            
    
            if(mz.is_apple(start, apple)) return true;
            if(mz.is_marked(start)) return false;
            mz.mark_cell( start );
            for( auto i(Maze::direction_t::NORTH) ; i < 4 ; ){
                if( not mz.is_blocked(start, i))
                    if(solve_maze(mz,walk_to_cell(start, i), apple)){
                        std::cout << "ACHOU!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
                        return true;
                    }
            }
            
            return false;
        }
        
        Player::Movimento next_move();
    private:
        // a IA tem que saber onde está localizada
        Snaze* cobrinha; 
        Maze maze;
        Apple* apple;
};


Player::Movimento IA::next_move()
{
    std::pair<int,int> posSnake = cobrinha->get_position();
    
    std::pair<int,int> next_marked;
    bool next_marked_found = false;
    
    // percorre a vizinha procurando a proxima marcacao
    char c;
    std::cin >> c;
    
    
    for(int i = -1; i <= 1 and !next_marked_found and posSnake.first + i >= 0 and posSnake.first + i < (int) maze.maze_.size(); i++)
    {
        for(int j = -1; j <= 1 and posSnake.second + j >= 0 and posSnake.second + j < (int) maze.maze_.size(); j++)
        {
            Position pos(posSnake.first + i, posSnake.second + j);
            if(maze.is_marked(pos))
            {
                maze.unmark_cell(pos);
                next_marked = {posSnake.first + i, posSnake.second + j};
                next_marked_found = true;
                break;
            }
        }
    }
    
    if(next_marked_found)
    {
       
        
        int dx = next_marked.first - posSnake.first;
        int dy = next_marked.second - posSnake.second;
        if(dx == 0){
            // movimento horizontal
            if(dy > 0)
                return Player::Movimento::EAST;
            else
                return Player::Movimento::WEST;
        }else{
            if(dx > 0)
                return Player::Movimento::SOUTH;
            else
                return Player::Movimento::NORTH;
                
        }
    }
    else
    {
     
        Position start(posSnake.first, posSnake.second);
        if(solve_maze(maze, start, *apple))
            return next_move();
        else 
            return Player::Movimento::EAST;
    }
}

IA::IA(Maps& atual, Snaze& cobrinha, Apple& apple)
{
    this->cobrinha = &cobrinha;
    this->apple = &apple;
    
    int h = atual.return_x();
    int w = atual.return_y();
    
    sc::vector<sc::vector<char>> map;
    for(int i = 0; i < h; ++i)
    {
        map[i].reserve(w);
        for(int j = 0; j < w; ++j)
        {
            map[i].push_back(atual.get_value(i, j));
        }
    }
    
    this->maze = IA::Maze(map);
}
