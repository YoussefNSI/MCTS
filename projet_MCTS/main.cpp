
#include <iostream>
#include <mutex>

#include "arbitre.h"

#include <memory>
#include "MCTS.h"

#define NB_PARTIES 50
using namespace std;

int main()
{

    Jeu J;

    std::shared_ptr<Noeud> n = std::make_shared<Noeud>(J,nullptr);

    int coup = 0;
    n->descente(J,coup);
    
    int score = n->roll_out(J);
    n->update(score);
    
    std::cout << "score final : " << score << std::endl;
    std::cout << "score final : " << n->getGain() << std::endl;


   


    // int score = n->roll_out(J);
    // std::cout << "score final : " << score << std::endl;

    // n->update(score);

    // std::cout << n->getGain();


    // score = n->roll_out(J);
    // std::cout << "score final : " << score << std::endl;

    // n->update(score);

    // std::cout << n->getGain();


    // //initialise la graine du générateur aléatoire
    // std::srand(std::time(nullptr));

    // // création de l'Arbitre (graine , joueur 1, joueur 2 , nombre de parties)
    // Arbitre a (player::RAND, player::MCTS, NB_PARTIES);
    // // commence le challenge
    // a.challenge();
    return 0;
}
