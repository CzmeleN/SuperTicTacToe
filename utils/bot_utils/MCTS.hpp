#pragma once 
#include "Bot.hpp"

#define constant_uct 2
#define easy_heura_sim 20
#define medium_heura_sim 35
#define hard_heura_sim 130

#define easy_MCTS 4
#define medium_MCTS 5
#define hard_MCTS 6

#define easy_max_sim_MCTS 4
#define medium_max_sim_MCTS 8
#define hard_max_sim_MCTS 27

struct states_tree{
    states_tree *parent;
    std::vector<states_tree*> sons;
    int sector;
    int wins;
    int visits;
    std::pair<int, int> coord;
};

class MCTS : public Bot{
public:
    int max_sim, heura_sim;
    states_tree *tree;

    //constructor and destructor
    MCTS(TicTacToeData data, int mode);
    ~MCTS();

    //methods
    std::pair<int, int> main_fun();
    int heura(states_tree *node);
    inline double uct(states_tree *node);

    //metods for traversing tree
    void select_leaf();
    void unselect_leaf(int score, int vis);
    states_tree *generate_son(states_tree *parent, int x, int y, int sector);
    void expand(states_tree *parent, int sector);

    //methods to for tree
    void free_tree(states_tree* node);
};