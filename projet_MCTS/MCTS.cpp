#include "MCTS.h"


void Noeud::ajouterNoeud(std::shared_ptr<Noeud> n)
{
    
    noeuds_fils.push_back(n);
    if (n->parent) // important, la racine n'a pas de noeud parent (nullptr), tous les noeuds sauf la racine 
        n->parent = shared_from_this(); //  retourne un autre shared_ptr vers *this, sans augmenter le compteur
}



int Noeud::score(Jeu j)
{
    if ( j.victoire() ) return 1;
    else if ( j.pat() ) return 0;
    else return -1; // defaite

}

std::shared_ptr<Noeud> Noeud::UBC(std::shared_ptr<Noeud> filsA, std::shared_ptr<Noeud> filsB)
{
    float UBC_a = filsA->gain_accumule + sqrt(2 * log(compteur_scenario) / filsA->compteur_scenario);
    float UBC_b = filsB->gain_accumule + sqrt(2 * log(compteur_scenario) / filsB->compteur_scenario);

    if ( UBC_a > UBC_b )
        return filsA;
    else
        return filsB;

    //return max(UBC_a,UBC_b); 

    // return gain_du_fils + sqrt(2 * log(nb_scénarios_père) / nb_scénario_fils)

}

 

//UBC (etat,numero_coup) : gain_du_fils + sqrt(2 * log(nb_scénarios_père) / nb_scénario_fils)


void Noeud::descente(Jeu j,int & coup) // coup = 1 au 1er appel
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
            std::shared_ptr<Noeud> fils = std::make_shared<Noeud>(j,shared_from_this());
            ajouterNoeud(fils);
            
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

                std::shared_ptr<Noeud> filsA = std::make_shared<Noeud>(j,shared_from_this());
                ajouterNoeud(filsA);
                //std::cout << "coup joué : " << coup_A << std::endl;
                j.joue(coup_A);
                ++coup_A;

                
                std::shared_ptr<Noeud> filsB = std::make_shared<Noeud>(j,shared_from_this());
                ajouterNoeud(filsB);
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
   
    // while (!j.terminal()) // pas une feuille
    // {
        
    //     while ( coup < j.nb_coups() )
    //     {
           
            
    //         std::cout << "coup joué : " << coup << std::endl;
    //         j.joue(coup);
    //         std::shared_ptr<Noeud> fils = std::make_shared<Noeud>(j,shared_from_this());
    //         ajouterNoeud(fils);
            
    //         ++coup;
    //     }


    // }
    // return coup;
}



int Noeud::roll_out(Jeu j)
{
    int coup;
    while (!j.terminal()) // pas une feuille
    {
        coup =  j.random(j.nb_coups());
        std::cout << "coup joué : " << coup << std::endl;
        j.joue(coup);

        std::shared_ptr<Noeud> fils = std::make_shared<Noeud>(j,nullptr);
        ajouterNoeud(fils);

    }
    return score(j); 
}

void Noeud::update(int score)
{
    ++compteur_scenario;
    gain_accumule += score;

    if (parent != nullptr)
    {
        parent->update(score);
    }

}
