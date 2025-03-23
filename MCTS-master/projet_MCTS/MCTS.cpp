#include "MCTS.h"
#include <fstream>


void Noeud::ajouterNoeud(std::shared_ptr<Noeud> n)
{
    
    noeuds_fils.push_back(n);
    if (n->parent) // important, la racine n'a pas de noeud parent (nullptr), tous les noeuds sauf la racine 
        n->parent = shared_from_this(); //  retourne un autre shared_ptr vers *this, sans augmenter le compteur
}



int MCTS::score(Jeu j)
{
    if ( j.victoire() ) return 1;
    else if ( j.pat() ) return 0;
    else return -1; // defaite

}

std::shared_ptr<Noeud> MCTS::UBC(std::shared_ptr<Noeud> filsA, std::shared_ptr<Noeud> filsB)
{
     float UBC_a, UBC_b;

    if (filsA->getNbScenario() != 0)
        UBC_a = filsA->getGain() + sqrt(2 * log(racine->getNbScenario() ) / filsA->getNbScenario() );
    else if (filsB->getNbScenario() != 0)
        UBC_b = filsB->getGain() + sqrt(2 * log(racine->getNbScenario() ) / filsB->getNbScenario() );
    
    else
    {
        UBC_a = 1;
        UBC_b = 0;
    } 

    if ( UBC_a > UBC_b )
        return filsA;
    else
        return filsB;

}


void MCTS::descente(Jeu j,int & coup) // coup = 1 au 1er appel
{
   
   
    if (!j.terminal())
    {
        if (coup <= j.nb_coups())
        {
            
            if (coup !=0) // coup = 0 racine -> pas de coup
            {
                std::cout << "coup joué : " << coup << std::endl;
            }
            
            j.joue(coup);
            std::shared_ptr<Noeud> fils = std::make_shared<Noeud>(j,racine,coup);
            racine->ajouterNoeud(fils);
            
            ++coup;
        }
        else
        {
            coup = 1;
            int coup_A = coup;
            int coup_B = coup_A + 1;

            if (coup <= j.nb_coups())
            {

                std::cout << "il faut faire UBC" << std::endl;

                std::shared_ptr<Noeud> filsA = std::make_shared<Noeud>(j,racine,coup);
                racine->ajouterNoeud(filsA);
                //std::cout << "coup joué : " << coup_A << std::endl;
                j.joue(coup_A);
                ++coup_A;

                
                std::shared_ptr<Noeud> filsB = std::make_shared<Noeud>(j,racine,coup);
                racine->ajouterNoeud(filsB);
                //std::cout << "coup joué : " << coup_A << std::endl;
                j.joue(coup_B);
                ++coup_B;

                if ( UBC(filsA,filsB) == filsA)
                    coup = coup_A;
                else
                    coup = coup_B;
                std::cout << "UBC -> coup joué : " << coup << std::endl;

            }
        }
    }
   

}



int MCTS::roll_out(Jeu j)
{
    int coup;
    while (!j.terminal()) // pas une feuille
    {
        coup =  j.random(j.nb_coups());
        std::cout << "coup joué : " << coup << std::endl;
        j.joue(coup);

        std::shared_ptr<Noeud> fils = std::make_shared<Noeud>(j,racine,coup);
        racine->ajouterNoeud(fils);

    }
    return score(j); 
}

void MCTS::update(std::shared_ptr<Noeud> n, int score)
{
     while (n) { 
        n->augmenterNbScenario();
        n->setGain(score);
        n = n->getParent();
    }

}

int MCTS::meilleur_coup()
{
    int meilleur = -1;
    int max_visites = -1;

    for (auto &enfant : racine->getFils())
    {
        if (enfant->getNbScenario() > max_visites)
        {
            max_visites = enfant->getNbScenario();
            meilleur = enfant->getCoupParent();
        }
    }
    return meilleur;
}
    
void MCTS::rechercher(int iterations)
{
    for (int i = 0; i< iterations; ++i)
    {
        int coup = 1;
        descente(jeu_courant, coup);
        int score = roll_out(jeu_courant);
        update(racine,score);
    }

}


void MCTS::load_arbre(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Aucun fichier trouvé, démarrage avec un nouvel arbre.\n";
        return;
    }

    std::map<int, std::shared_ptr<Noeud>> noeuds;
    int id, coup_parent, gain, nb_scenario, nb_fils;

    while (file >> id >> coup_parent >> gain >> nb_scenario >> nb_fils) {
        auto noeud = std::make_shared<Noeud>(jeu_courant, nullptr, coup_parent);
        noeud->setGain(gain);
        noeud->setNbScenario(nb_scenario);
        noeuds[id] = noeud;

        for (int i = 0; i < nb_fils; ++i) {
            int id_fils;
            file >> id_fils;
            if (noeuds.find(id_fils) != noeuds.end()) {
                noeud->ajouterNoeud(noeuds[id_fils]);
            }
        }
    }

    if (!noeuds.empty()) {
        racine = noeuds[0];  // Réassigner la racine
        std::cout << "Arbre chargé avec succès !\n";
    }

    file.close();
}



void MCTS::save_arbre(const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Erreur : Impossible d'ouvrir " << filename << " pour sauvegarde.\n";
        return;
    }

    std::queue<std::shared_ptr<Noeud>> queue;
    queue.push(racine);

    int id = 0;
    std::map<std::shared_ptr<Noeud>, int> id_map; // Associer chaque nœud à un ID
    id_map[racine] = id;

    while (!queue.empty()) {
        std::shared_ptr<Noeud> noeud = queue.front();
        queue.pop();

        file << id_map[noeud] << " "
             << noeud->getCoupParent() << " "
             << noeud->getGain() << " "
             << noeud->getNbScenario() << " "
             << noeud->getFils().size();

        for (const auto& fils : noeud->getFils()) {
            id++;
            id_map[fils] = id;  // Associe un nouvel ID au fils
            file << " " << id;
            queue.push(fils);
        }

        file << "\n";
    }

    file.close();
    std::cout << "Arbre sauvegardé dans " << filename << std::endl;
}


void MCTS::self_play(int nb_parties) {
    for (int i = 0; i < nb_parties; ++i) {
        Jeu jeu_copie;
        jeu_copie = jeu_courant;  // Copie pour ne pas modifier l'original
        int coup = 1;

        descente(jeu_copie, coup);  // Sélection d’un coup
        int score = roll_out(jeu_copie);  // Simulation jusqu’à la fin
        update(racine, score);  // Mise à jour des valeurs

        std::cout << "Partie " << i+1 << " terminée, score : " << score << std::endl;
    }

    save_arbre("arbre2_mcts");  // Sauvegarde après entraînement
}

