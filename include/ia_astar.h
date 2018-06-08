#include "ai.hpp"

/// === ALIASES ===

using pPair = std::pair<uint, std::pair<uint, uint>>;

/// == STRUCTURES ==

/// A Cell with 'f', 'g', 'h' values.
Cell::Cell(Point p): parent(std::make_pair(p.x,p.y)), HasParent(true), f(0u), g(0u), h(0u) 
{   }

Cell::Cell(std::pair<int,int> p): parent(p), HasParent(true), f(0u), g(0u), h(0u) 
{   }

/// Methods
/*
AI::AI(Level level): m_level(level)
{
}*/

bool AI::isValid(Point p, Level & niv)
{

    auto atual = niv.get_current_level();

    return p.x < atual.return_x() and p.y < atual.return_y();
}

bool AI::isUnBlocked(Point p, Level & niv)
{

    auto atual = niv.get_current_level();
    if(atual.get_value(p.x, p.y) != '#' and atual.get_value(p.x, p.y) != '-')
        return true;

    return false;

}

/*uint AI::risk(Point p, Point parent)
{
    uint remaining_checks = m_snake.size() - 1;
    
    auto current_cell = Cell(parent);
    
    // tenho que verificar se a ultima coordenada bate com as 'size' ultimas coordenadas
    while(remaining_checks != 0)
    {
        if(p == current_cell.parent)
            return remaining_checks;
        current_cell = m_cellDetails[current_cell.parent.x][current_cell.parent.y];
        --remaining_checks;
    }
    return 0;
}*/

bool AI::isDestination(Point p, Apple & apple)
{
    auto applePos = apple.get_coordenadas();
    if(p.x == applePos.first and p.y == applePos.second)
        return true;

    return false;
}

double AI::calculateHValue(Point p, Apple & apple)
{
    auto applePos = apple.get_coordenadas();
     return abs(int(p.x - applePos.first)) +
            abs(int(p.y - applePos.second)); 
}

void AI::tracePath( Apple & apple)
{
    auto applePos = apple.get_coordenadas();
    Cell current_cell = Cell(apple.get_coordenadas());
    Cell current_parent = m_cellDetails[applePos.first][applePos.second];

    Direction dir;

    while(!(current_cell.parent == current_parent.parent)){

        if(current_parent.parent.second == current_cell.parent.second){
            if(current_parent.parent.first > current_cell.parent.first)
                dir = Direction::N;
            else
                dir = Direction::S;
        } else{
            if(current_parent.parent.second > current_cell.parent.second)
                dir = Direction::W;
            else
                dir = Direction::E;
        }

        m_path.push(dir);
        current_cell = current_parent;
        current_parent = m_cellDetails[current_cell.parent.first][current_cell.parent.second];
    }
}

// Run A* Search Algorithm
bool AI::aStarSearch( Level & lvl, Apple & app, Snaze & sna )
{
    std::pair<int,int> coorde = sna.get_position();
    std::pair<int,int> coordeApple = app.get_coordenadas();
    Point appll(coordeApple.first, coordeApple.second);
    Point src(coorde.first, coorde.second);
    // If the source is out of range
    if (!isValid(src, lvl))
        throw std::runtime_error("Source is invalid.");
    // If the destination is out of range
    if (!isValid(appll, lvl))
        throw std::runtime_error("Destination is invalid.");
    // Either the source or the destination is blocked
    if (!isUnBlocked(src,lvl) or !isUnBlocked(appll, lvl))
        throw std::runtime_error("Source or the destination is blocked\n");
    
    Maps map = lvl.get_current_level();

    bool closedList[map.return_x()][map.return_y()];
    memset(closedList, false, sizeof (closedList));
    
    // Add snake coords to closed list 
//     std::queue<Point> snake_copy = m_snake;
//     while(!snake_copy.empty())
//     {
//         auto p = snake_copy.front();
//         closedList[p.x][p.y] = true;
//         snake_copy.pop();
//     }
 
    //m_cellDetails.resize(map.return_y());
 
    int i, j;
 
    for (i = 0; i < map.return_x(); ++i)
    {
        //m_cellDetails[i].resize(map.return_x());
        for (j = 0; j < map.return_y(); ++j)
        {
            m_cellDetails[i][j].f = UINT_MAX;
            m_cellDetails[i][j].g = UINT_MAX;
            m_cellDetails[i][j].h = UINT_MAX;
            m_cellDetails[i][j].HasParent = false;

        }
    }
 
    i = src.x, j = src.y;
    m_cellDetails[i][j].f = 0;
    m_cellDetails[i][j].g = 0;
    m_cellDetails[i][j].h = 0;
    m_cellDetails[i][j].HasParent = true;
    m_cellDetails[i][j].parent = std::make_pair(src.x,src.y);

    std::set<pPair> openList;

    openList.insert(std::make_pair(0.0, std::make_pair (i, j)));
    
    while (!openList.empty())
    {
        pPair  p = *openList.begin();
 
        openList.erase(openList.begin());
 
        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;
      
        uint gNew, hNew, fNew;
 
        
        Point points[4] = {Point(i, j+1), Point(i, j-1), Point(i+1, j), Point(i-1, j)};
        uint c;
        for(c = 0; c < 4; c++)
        {
            Point& current_point = points[c];
            
            if (isValid(current_point, lvl))
            {
//                 uint vrisk = risk(current_point, Point(i, j));
//                 if(vrisk > 0)
//                 {
//                     
//                     continue;
//                 }
                if (isDestination(current_point, app))
                {
                    m_cellDetails[current_point.x][current_point.y].parent = std::make_pair(i,j);
                    m_cellDetails[current_point.x][current_point.y].HasParent = true;
                    tracePath(app);
                    return true;
                }
                else if (closedList[current_point.x][current_point.y] == false and
                        isUnBlocked(current_point, lvl) == true)
                {
                    gNew = m_cellDetails[i][j].g + 1;
                    hNew = calculateHValue(current_point, app);
                    fNew = gNew + hNew;
    
                    if (m_cellDetails[current_point.x][current_point.y].f == UINT_MAX or
                        m_cellDetails[current_point.x][current_point.y].f > fNew)
                    {
                        openList.insert( std::make_pair(fNew,
                                                std::make_pair(current_point.x, current_point.y)));
    
                        // Update the details of this cell
                        m_cellDetails[current_point.x][current_point.y].f = fNew;
                        m_cellDetails[current_point.x][current_point.y].g = gNew;
                        m_cellDetails[current_point.x][current_point.y].h = hNew;
                        m_cellDetails[current_point.x][current_point.y].parent = std::make_pair(i,j);
                        m_cellDetails[current_point.x][current_point.y].HasParent = true;
                    }
                }
            }
        }
    }
  
    return false;
}

Direction AI::goto_free_way( Level & lvl, Apple & app, Snaze & sna )
{
    std::pair<int,int> coorder = sna.get_position();
    Point src(coorder.first, coorder.second);
    Maps & map = lvl.get_current_level();
    Point points[] = {Point(src.x-1, src.y), Point(src.x+1, src.y), Point(src.x, src.y-1), Point(src.x, src.y+1)};
    uint min_h = UINT_MAX;
    auto min_h_dir =  ++m_last_move;
    uint c;
    for(c = 0; c < 4; ++c)
    {
        Point c_ = points[c];
        int x_ = c_.x;
        int y_ = c_.y;
        auto object = map.get_value(x_, y_);
        if(object != '#' and object != '-')
        {
            auto dir = src*points[c];
            if(dir == !m_last_move and sna.get_tamanho() == 1)
                continue;
            auto h = calculateHValue(points[c], app);
            if(h < min_h)
            {
                min_h = h;
                min_h_dir = dir;
            }
        }
    }
    m_last_move = min_h_dir;
    return m_last_move;
}

Direction AI::next_move( Level & lvl, Apple & app, Snaze & sna)
{
    m_goal = app.get_coordenadas();
    std::pair<int,int> coord = sna.get_position();
    Point src(coord.first, coord.second);
    if(isDestination(src, app))
    {
        return goto_free_way(lvl, app, sna);
    }
    
    if(!m_path.empty())
    {
        auto dir = m_path.top();
        m_path.pop();
        return dir;
    }
    m_cellDetails.clear();
    if(aStarSearch( lvl, app, sna ))
    {
        auto dir = m_path.top();
        m_path.pop();
        return dir;
    }

    auto dir = goto_free_way(lvl, app, sna);
    return dir;
}