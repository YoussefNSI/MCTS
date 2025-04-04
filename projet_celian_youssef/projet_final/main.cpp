
#include <iostream>
#include <mutex>

#include "arbitre.h"
#include "MCTS.h"
#include "Trainer.h"

#define NB_PARTIES 50
using namespace std;

int main()
{
    // Entraînement
    // MCTSTrainer trainer(25000, 200);
    // trainer.train();
    // std::cout << "Entraînement terminé" << std::endl;

    //initialise la graine du générateur aléatoire
    std::srand(std::time(nullptr));

    // création de l'Arbitre (graine , joueur 1, joueur 2 , nombre de parties)
    Arbitre a (player::RAND, player::MCTS, NB_PARTIES);
    // commence le challenge
    a.challenge();
    return 0;
}
