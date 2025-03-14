#include "MCTS.h"
#include <limits>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <regex>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>

Noeud::Noeud(int state, std::shared_ptr<Noeud> p, int coup)
    : state_val(state), visite_count(0), total_reward(0.0),
      parent(p), coup_from_parent(coup) {}

bool Noeud::est_terminal(const Jeu &game) const
{
    return game.terminal();
}

bool Noeud::est_completement_developpe(const Jeu &game)
{
    return coups_possibles.size() >= game.nb_coups();
}

double Noeud::calcul_ucb(double exploration_param) const
{
    if (visite_count == 0)
        return std::numeric_limits<double>::max();
    return (total_reward / visite_count) +
           exploration_param * sqrt(log(parent.lock()->visite_count) / visite_count);
}

MCTS::MCTS() : racine(std::make_shared<Noeud>(0)) {}

void MCTS::reconstruire_etat(Jeu &game, int state_val)
{
    game.reset();
    std::vector<int> coups;
    while (state_val != 0 && state_val != RACINE)
    {
        int coup = state_val % 10;
        coups.insert(coups.begin(), coup);
        state_val = (state_val - coup) / 10;
    }
    for (int c : coups)
        if (c > 0)
            game.joue(c);
}

std::shared_ptr<Noeud> MCTS::selection(std::shared_ptr<Noeud> noeud)
{
    while (noeud && !noeud->est_terminal(jeu_courant))
    {
        if (!noeud->est_completement_developpe(jeu_courant))
        {
            auto expanded = expansion(noeud);
            if (expanded)
                return expanded;
        }
        noeud = meilleur_enfant_ucb(noeud);
    }
    return noeud;
}

std::shared_ptr<Noeud> MCTS::expansion(std::shared_ptr<Noeud> noeud)
{
    Jeu game_copy;
    reconstruire_etat(game_copy, noeud->state_val);

    // Générer les coups possibles
    int nb = game_copy.nb_coups();
    if (nb <= 0)
        return nullptr;

    for (int coup = 1; coup <= nb; ++coup)
    {
        if (game_copy.coup_licite(coup))
        {
            if (std::find(noeud->coups_possibles.begin(),
                          noeud->coups_possibles.end(),
                          coup) == noeud->coups_possibles.end())
            {
                noeud->coups_possibles.push_back(coup);
            }
        }
    }

    // Créer un nouvel enfant
    if (!noeud->coups_possibles.empty())
    {
        int nouveau_state = noeud->state_val * 10 + noeud->coups_possibles[0];
        auto enfant = std::make_shared<Noeud>(nouveau_state, noeud, noeud->coups_possibles[0]);
        noeud->enfants.push_back(enfant);
        return enfant;
    }
    return nullptr;
}

double MCTS::simulation(std::shared_ptr<Noeud> noeud)
{
    Jeu simulation_game;
    if (noeud)
        reconstruire_etat(simulation_game, noeud->state_val);
    else
        return 0.0;

    while (!simulation_game.terminal())
    {
        int nb = simulation_game.nb_coups();
        if (nb <= 0)
            break;
        int coup = simulation_game.random(nb);
        simulation_game.joue(coup);
    }

    if (simulation_game.victoire())
        return 1.0;
    if (simulation_game.pat())
        return 0.5;
    return 0.0;
}

void MCTS::retropropagation(std::shared_ptr<Noeud> noeud, double resultat)
{
    while (noeud)
    {
        noeud->visite_count++;
        noeud->total_reward += resultat;
        noeud = noeud->parent.lock();
    }
}

std::shared_ptr<Noeud> MCTS::meilleur_enfant_ucb(std::shared_ptr<Noeud> parent)
{
    std::shared_ptr<Noeud> meilleur;
    double max_score = -std::numeric_limits<double>::max();

    for (auto &enfant : parent->enfants)
    {
        double score = enfant->calcul_ucb(exploration_param);
        if (score > max_score)
        {
            max_score = score;
            meilleur = enfant;
        }
    }
    return meilleur;
}

void MCTS::effectuer_recherche(int iterations)
{
    for (int i = 0; i < iterations; ++i)
    {
        auto noeud = selection(racine);
        double resultat = simulation(noeud);
        retropropagation(noeud, resultat);
    }
}

int MCTS::meilleur_coup()
{
    int meilleur = -1;
    int max_visites = -1;

    for (auto &enfant : racine->enfants)
    {
        if (enfant->visite_count > max_visites)
        {
            max_visites = enfant->visite_count;
            meilleur = enfant->coup_from_parent;
        }
    }
    return meilleur;
}


using namespace rapidjson;

void MCTS::save_arbre(const std::string& filename) {
    Document d(kObjectType);
    Document::AllocatorType& allocator = d.GetAllocator();
    
    std::unordered_map<std::shared_ptr<Noeud>, int> node_ids;
    std::queue<std::shared_ptr<Noeud>> queue;
    int current_id = 0;
    
    // Sauvegarde de la racine
    queue.push(racine);
    node_ids[racine] = current_id++;
    
    Value nodes(kObjectType);
    while (!queue.empty()) {
        auto node = queue.front();
        queue.pop();
        
        Value nodeValue(kObjectType);
        nodeValue.AddMember("state", node->state_val, allocator);
        nodeValue.AddMember("visits", node->visite_count, allocator);
        nodeValue.AddMember("reward", node->total_reward, allocator);
        nodeValue.AddMember("coup", node->coup_from_parent, allocator);
        
        // Parent
        if (auto parent = node->parent.lock()) {
            nodeValue.AddMember("parent", node_ids[parent], allocator);
        } else {
            nodeValue.AddMember("parent", -1, allocator);
        }
        
        // Enfants
        Value children(kArrayType);
        for (auto& child : node->enfants) {
            if (!node_ids.count(child)) {
                node_ids[child] = current_id++;
                queue.push(child);
            }
            children.PushBack(node_ids[child], allocator);
        }
        nodeValue.AddMember("children", children, allocator);
        
        // Ajout au document
        nodes.AddMember(Value(std::to_string(node_ids[node]).c_str(), allocator), nodeValue, allocator);
    }
    
    d.AddMember("nodes", nodes, allocator);
    d.AddMember("root_id", node_ids[racine], allocator);
    
    // Écriture fichier
    FILE* fp = fopen(filename.c_str(), "wb");
    char writeBuffer[65536];
    FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
    PrettyWriter<FileWriteStream> writer(os);
    d.Accept(writer);
    fclose(fp);
}

void MCTS::load_arbre(const std::string& filename) {
    FILE* fp = fopen(filename.c_str(), "rb");
    if (!fp) throw std::runtime_error("Cannot open file");
    
    char readBuffer[65536];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    Document d;
    d.ParseStream(is);
    fclose(fp);
    
    if (!d.HasMember("nodes") || !d.HasMember("root_id"))
        throw std::runtime_error("Format de fichier invalide");
    
    std::unordered_map<int, std::shared_ptr<Noeud>> node_map;
    const Value& nodes = d["nodes"];
    
    // Première passe : créer tous les noeuds
    for (Value::ConstMemberIterator itr = nodes.MemberBegin(); itr != nodes.MemberEnd(); ++itr) {
        int id = std::stoi(itr->name.GetString());
        const Value& nodeValue = itr->value;
        
        auto node = std::make_shared<Noeud>(
            nodeValue["state"].GetInt(),
            nullptr,
            nodeValue["coup"].GetInt()
        );
        node->visite_count = nodeValue["visits"].GetInt();
        node->total_reward = nodeValue["reward"].GetDouble();
        
        node_map[id] = node;
    }
    
    // Deuxième passe : lier les relations
    for (Value::ConstMemberIterator itr = nodes.MemberBegin(); itr != nodes.MemberEnd(); ++itr) {
        int id = std::stoi(itr->name.GetString());
        const Value& nodeValue = itr->value;
        auto node = node_map[id];
        
        // Parent
        int parent_id = nodeValue["parent"].GetInt();
        if (parent_id != -1) {
            node->parent = node_map[parent_id];
        }
        
        // Enfants
        const Value& children = nodeValue["children"];
        for (SizeType i = 0; i < children.Size(); i++) {
            node->enfants.push_back(node_map[children[i].GetInt()]);
        }
    }
    
    // Définir la racine
    int root_id = d["root_id"].GetInt();
    if (node_map.count(root_id)) {
        racine = node_map[root_id];
    } else {
        throw std::runtime_error("Noeud racine introuvable");
    }
}