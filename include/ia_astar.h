#include "ai.hpp"

/// === ALIASES ===

using pPair = std::pair<uint, std::pair<uint, uint>>;

/// == STRUCTURES ==

/// A Cell with 'f', 'g', 'h' values.
Cell::Cell(Point p): parent(std::make_pair(p.x,p.y)), HasParent(true), f(0u), g(0u), h(0u) 
{   }


Cell::Cell(std::pair<int,int> p): parent(p), HasParent(true), f(0u), g(0u), h(0u) 
{   }


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

bool AI::isDestination(Point p, Apple & apple)
{
    auto applePos = apple.get_coordenadas();
    if(p.x == applePos.first and p.y == applePos.second)
        return true;

    return false;
}

double AI::calculateHValue(Point p, Apple & apple)
{
    /// Retorna o valor utilizando a formula da distância.
    auto applePos = apple.get_coordenadas();
     return abs(int(p.x - applePos.first)) +
            abs(int(p.y - applePos.second)); 
}

void AI::tracePath( Apple & apple)
{
    auto applePos = apple.get_coordenadas();
    Cell current_cell = Cell(applePos);
    Cell current_parent = m_cellDetails[current_cell.parent.first][current_cell.parent.second];

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

/// Run A* Search Algorithm
bool AI::aStarSearch( Level & lvl, Apple & app, Snaze & sna )
{
    // Obtem as coordenadas da cobra e da maçã.
    std::pair<int,int> coorde = sna.get_position();
    std::pair<int,int> coordeApple = app.get_coordenadas();

    // Atribui as coordenadas a uma classe Point.
    Point appll(coordeApple.first, coordeApple.second);
    Point src(coorde.first, coorde.second);
    
    // Verifica se o ponto da cobra está dentro do mapa.
    if (!isValid(src, lvl))
        throw std::runtime_error("Source is invalid.");
    
    // Verifica se o ponto da maçã está no mapa.
    if (!isValid(appll, lvl))
        throw std::runtime_error("Destination is invalid.");
    
    // Verifica se a origem e o destino não estão disponiveis.
    if (!isUnBlocked(src,lvl) or !isUnBlocked(appll, lvl))
        throw std::runtime_error("Source or the destination is blocked\n");

    // Recebe o mapa do nível atual.
    Maps map = lvl.get_current_level();

    // Cria uma lista fechada e inicializa com falso, de forma que nenhuma célula tenha sido inicializada
    // ainda.
    bool closedList[map.return_y()][map.return_x()];
    memset(closedList, false, sizeof (closedList));
    
 
    m_cellDetails.resize(map.return_x());
 
    int i, j;
    

    for (i = 0; i < map.return_x(); ++i)
    {
        m_cellDetails[i].resize(map.return_y());
        for (j = 0; j < map.return_y(); ++j)
        {
            m_cellDetails[i][j].f = UINT_MAX;
            m_cellDetails[i][j].g = UINT_MAX;
            m_cellDetails[i][j].h = UINT_MAX;
            m_cellDetails[i][j].HasParent = false;

        }
    }

    // Inicializa os parâmetros da A*.
    i = src.x, j = src.y;
    m_cellDetails[i][j].f = 0;
    m_cellDetails[i][j].g = 0;
    m_cellDetails[i][j].h = 0;
    m_cellDetails[i][j].HasParent = true;
    m_cellDetails[i][j].parent = std::make_pair(i, j);

    // Cria uma lista aberta para armazenar os valores de f, g e h, de forma que f = g + h.
    std::set<pPair> openList;

    // Coloca a primeira posição na lista aberta e configura para o f ser 0.
    openList.insert(std::make_pair(0.0, std::make_pair (i, j)));
    
    while (!openList.empty())
    {
        pPair  p = *openList.begin();
 
        // Remove esta posição da lista.
        openList.erase(openList.begin());
 
        // Adiciona a posição a lista fechada.
        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;
      
        uint gNew, hNew, fNew;
 
        // Para cada uma das 4 posições verifica a partir da posição que se encontra.
        Point points[4] = {Point(i, j+1), Point(i, j-1), Point(i+1, j), Point(i-1, j)};
        uint c;
        for(c = 0; c < 4; c++)
        {
            Point& current_point = points[c];
            
            // Só executa este pocesso se for válida a posição.
            if (isValid(current_point, lvl))
            {
                // Se o destino for válido é igual ao sucessor atual.
                if (isDestination(current_point, app))
                {
                    // Configura o 'parent' da posição de destino. 
                    m_cellDetails[current_point.x][current_point.y].parent = std::make_pair(i,j);
                    m_cellDetails[current_point.x][current_point.y].HasParent = true;
                    tracePath(app);
                    return true;
                }
                // Se o sucessor já está na lista fechada ou está bloqueada então ignore. Caso contrário siga.
                else if (closedList[current_point.x][current_point.y] == false and
                        isUnBlocked(current_point, lvl) == true)
                {
                    gNew = m_cellDetails[i][j].g + 1;
                    hNew = calculateHValue(current_point, app);
                    fNew = gNew + hNew;
    
                    // Se não está na lista aberta, adicione-a. Faça a posição atual ser a posição do parent.
                    // Grava os valores de f, g e h da posição.
                    if (m_cellDetails[current_point.x][current_point.y].f == UINT_MAX or
                        m_cellDetails[current_point.x][current_point.y].f > fNew)
                    {
                        openList.insert( std::make_pair(fNew,
                                                std::make_pair(current_point.x, current_point.y)));
    
                        // Atualiza as informações da célula (bloco).
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
    // Retorna as coordenadas da cobra.
    std::pair<int,int> coorder = sna.get_position();

    // Cria um Point com as coordenadas da cobra.
    Point src(coorder.first, coorder.second);
    
    // Recebe o nível atual.
    Maps & map = lvl.get_current_level();
    
    // Armazena todas as possíveis rotas (cima, baixo, esquerda, direita).
    Point points[] = {Point(src.x-1, src.y), Point(src.x+1, src.y), Point(src.x, src.y-1), Point(src.x, src.y+1)};
    
    uint min_h = UINT_MAX;
    
    auto min_h_dir =  ++m_last_move;
    
    uint c;
    
    for(c = 0; c < 4; ++c)
    {
        // Obtem qual a orientação a ser seguida.
        Point c_ = points[c];
        
        // Obtem as posições.
        int x_ = c_.x;
        int y_ = c_.y;
        
        // Obtem o que há naquela posição do mapa.
        auto object = map.get_value(x_, y_);
        
        // Verifica se não está bloqueado.
        if(object != '#' and object != '-')
        {
            auto dir = src*points[c];
            if(dir == !m_last_move and sna.get_tamanho() == 1)
                continue;

            // Calcula o novo valor de H.
            auto h = calculateHValue(points[c], app);
            
            // Verifica se o menor valor de h é h ou min_h, se sim muda.
            if(h < min_h)
            {
                min_h = h;
                min_h_dir = dir;
            }
        }
    }

    // Muda o último movimento realizado.
    m_last_move = min_h_dir;
    
    // Retorna o último movimento.
    return m_last_move;
}

Direction AI::next_move( Level & lvl, Apple & app, Snaze & sna)
{
    // Recebe a posição da maçã.
    m_goal = app.get_coordenadas();
    // Recebe a posição da cobra.
    std::pair<int,int> coord = sna.get_position();

    // Cria um Point com os dados de origem.
    Point src(coord.first, coord.second);
    
    // Verifica se já não é a origem.
    if(isDestination(src, app))
    {
        return goto_free_way(lvl, app, sna);
    }
    
    // Verifica se o caminho não está livre.
    if(!m_path.empty())
    {
        auto dir = m_path.top();
        m_path.pop();
        return dir;
    }

    // Limpa qualquer dado presente nos dados de cada bloco.
    m_cellDetails.clear();

    // Caso não foi encontrado o caminho então busque.
    if(aStarSearch( lvl, app, sna ))
    {
        auto dir = m_path.top();
        if(m_path.empty())
            throw std::runtime_error("[ERROR]: invalid search return\n");
        m_path.pop();
        return dir;
    }

    // Percorre a direção para ver se é possível percorrer.
    auto dir = goto_free_way(lvl, app, sna);
    return dir;
}
