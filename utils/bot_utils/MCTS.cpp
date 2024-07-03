#include "MCTS.hpp"

MCTS::MCTS(TicTacToeData data, int mode) : Bot(data){
    if(mode == easy_MCTS) max_sim = easy_max_sim_MCTS, heura_sim = easy_heura_sim;
    else if(mode == medium_MCTS) max_sim = medium_max_sim_MCTS, heura_sim = medium_heura_sim;
    else max_sim = hard_max_sim_MCTS, heura_sim = hard_heura_sim;

    tree = MCTS::generate_son(nullptr, -1, -1, data.sector);
}

MCTS::~MCTS(){
    free_tree(tree);
}

void MCTS::free_tree(states_tree* node){
    for(auto son: node -> sons)
        free_tree(son);
    
    delete node;
}

states_tree* MCTS::generate_son(states_tree* parent, int x, int y, int sector){
    states_tree *node = new states_tree;
    node -> parent = parent;
    node -> wins = 0;
    node -> visits = 0;
    node -> coord = {x, y};
    node -> sector = sector;

    return node;
}

// we are in a leaf and we want to expand it 
void MCTS::expand(states_tree* parent, int sector){
    //geenerate all sons 
    std::vector<std::pair<int, int>> possible_moves;
    possible_moves = MCTS::generate_possible_moves();

    int score_sum = 0, vis = 0;
    for(auto [x, y]: possible_moves){
        //create son
        states_tree *son = MCTS::generate_son(parent, x, y, MCTS::idx_of_next_subgame(x, y));
        parent -> sons.push_back(son);

        //test him
        int score = heura(son);
        son -> visits += heura_sim;
        son -> wins += score;

        score_sum += score;
        vis += heura_sim;
    }

    //backpropagate
    unselect_leaf(score_sum, vis);
}

inline double MCTS::uct(states_tree *node){
    if(node -> visits == 0) return (double) inf;
    return (double) node -> wins / node -> visits + std::sqrt(constant_uct) * std::sqrt((double) std::log((node -> parent == nullptr ? 1 : node -> parent -> visits)) / node -> visits);
}

void MCTS::select_leaf(){
    if(tree -> sons.empty()){ //we are in a leaf
        return; 
    }

    states_tree *best_son = nullptr;
    double best_score = -1;

    for(auto son: tree -> sons){
        double score = uct(son);
        if(score > best_score){
            best_score = score;
            best_son = son;
        }
    }

    // go to best son 
    MCTS::put_sign(best_son -> coord.first, best_son -> coord.second);
    MCTS::change_player();
    data.sector = MCTS::idx_of_next_subgame(best_son ->coord.first, best_son -> coord.second);
    tree = best_son;

    // go to node's best son
    MCTS::select_leaf();
}

std::pair<int, int> MCTS::main_fun(){
    int before = data.sector;
    for(int i = 0; i < max_sim; i++){
        //selection
        MCTS::select_leaf();

        //expansion && simulation && backpropagation
        MCTS::expand(tree, data.sector);
    }

    //returning most visitable son
    double most_win = -1;
    states_tree *best_son;

    for(auto son: tree -> sons)
        if((double) son -> wins / son -> visits > most_win){
            most_win = (double) son -> wins / son -> visits;
            best_son = son;
        }

    return std::make_pair(best_son -> coord.first, best_son -> coord.second);
}

void MCTS::unselect_leaf(int score, int vis){
    tree -> visits += vis;
    tree -> wins += score;
    data.sector = tree -> sector; 
 
    if(tree -> parent != nullptr){
        MCTS::unput_sign(tree -> coord.first, tree -> coord.second);
        MCTS::change_player();

        tree = tree -> parent;
        MCTS::unselect_leaf(score, vis);
    }
}

int MCTS::heura(states_tree *node){
    int win_cnt = 0;
    TicTacToeData data_copy = data;
    std::vector<Sign> subgame_score_copy = subgame_score;

    for(int i = 0; i < heura_sim; i++){
        while(!MCTS::game_over()){
            std::vector<std::pair<int, int>> possible_moves;
            possible_moves = generate_possible_moves();

            int idx = rand() % possible_moves.size();
            auto [x, y] = possible_moves[idx];

            MCTS::put_sign(x, y);
            MCTS::change_player();
            data.sector = MCTS::idx_of_next_subgame(x, y);
        }

        if(MCTS::game_score() == max_player) win_cnt += 2;
        else if(MCTS::game_score() == Sign::Empty) win_cnt += 1;

        data = data_copy;
        subgame_score = subgame_score_copy;
    }

    return win_cnt;
}