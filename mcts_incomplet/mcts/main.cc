#include "MCTS.h"
#include <iostream>

int main() {
    MCTS mcts;
    mcts.effectuer_recherche(7500); 

    int meilleur = mcts.meilleur_coup();
    std::cout << "Meilleur coup trouve : " << meilleur << std::endl;
    return 0;
}
