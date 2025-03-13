#include "joueur_MCTS.h"

Joueur_MCTS::Joueur_MCTS(std::string nom, bool joueur, int nb_iterations)
    : Joueur(nom, joueur), iterations(nb_iterations) {
        mcts_engine = std::make_unique<MCTS>();
    }

void Joueur_MCTS::initialisation() {
    // Initialisation une fois au début du programme
    mcts_engine->reset(RACINE);
}

void Joueur_MCTS::init_partie() {
    // Réinitialisation au début de chaque nouvelle partie
    mcts_engine.reset(RACINE);
}

char Joueur_MCTS::nom_abbrege() const {
    return 'M'; // Abréviation pour MCTS
}

void Joueur_MCTS::recherche_coup(Jeu jeu, int& coup) {
    // Synchronisation avec l'état actuel
    mcts_engine->reset(jeu.get_etat());
    
    // Exécution de la recherche
    mcts_engine->effectuer_recherche(iterations);
    
    // Récupération du meilleur coup
    coup = mcts_engine->meilleur_coup();
    

    if(coup == -1 || !jeu.coup_licite(coup)) {
        coup = 1; 
    }
}