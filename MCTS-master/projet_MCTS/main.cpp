
#include <iostream>
#include <mutex>

#include "arbitre.h"

#include <memory>
#include "MCTS.h"

#define NB_PARTIES 50
using namespace std;

int main()
{


    // // //initialise la graine du générateur aléatoire
    std::srand(std::time(nullptr));

    // création de l'Arbitre (graine , joueur 1, joueur 2 , nombre de parties)
    Arbitre a(player::RAND, player::MCTS, NB_PARTIES);
    // commence le challenge
    a.challenge();

    // MCTS mcts;
    // mcts.load_arbre("arbre2_mcts");
    // int nb_parties = 100000;
    // mcts.self_play(nb_parties);
    // return 0;
}
