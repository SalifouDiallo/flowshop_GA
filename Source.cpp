#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#include <numeric>
#include <ctime>
#include <string>
#include <set>
#include <chrono>


using namespace std;

// Classe représentant un individu (une solution)
class Individual {
public:
    vector<int> genes; // Séquence de tâches (permutation)
    double fitness;    // Valeur de fitness (inverse du makespan)

    // Constructeur qui initialise un individu avec une séquence aléatoire de tâches
    Individual(int num_tasks) : genes(num_tasks), fitness(0) {
        iota(genes.begin(), genes.end(), 0); // Remplit genes de 0 à num_tasks-1
        random_device rd;
        mt19937 g(rd());
        shuffle(genes.begin(), genes.end(), g); // Mélange aléatoirement les gènes
    }

    // Calcule la fitness de l'individu basée sur le makespan
    void calculateFitness(const vector<vector<int>>& task_times, int num_machines) {
        int num_tasks = genes.size();

        // Crée un tableau pour stocker le temps de fin pour chaque machine
        vector<int> machine_end_times(num_machines, 0);  // Temps de fin de chaque machine
        vector<int> task_end_times(num_tasks, 0);        // Temps de fin de chaque tâche

        // Calcul du makespan pour chaque tâche
        for (int machine = 0; machine < num_machines; ++machine) {
        for (int task_idx = 0; task_idx < num_tasks; ++task_idx) {
            task_end_times[genes[task_idx]] = max(task_end_times[genes[task_idx]], machine_end_times[machine])+ task_times[genes[task_idx]][machine];
            machine_end_times[machine] = task_end_times[genes[task_idx]];
            }
        }

        // Le makespan est le temps final de la dernière tâche sur la dernière machine
        fitness = 1.0 / machine_end_times.back(); // L'inverse du makespan pour maximiser la fitness
    }


};

// Fonction pour lire une instance à partir d'un fichier
void readInstance(const string& filename, int& num_tasks, int& num_machines, vector<vector<int>>& task_times) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Erreur lors de l'ouverture du fichier!" << endl;
        return;
    }

    string line;
    // Lire le nombre de tâches et de machines
    file >> num_tasks >> num_machines;

    // Lire la matrice des temps
    task_times.resize(num_tasks, vector<int>(num_machines));
    for (int j = 0; j < num_machines; ++j) {
        for (int i = 0; i < num_tasks; ++i) {
            file >> task_times[i][j];
        }
    }
    file.close();
}

// Fonction de croisement entre deux parents pour produire deux enfants
void crossover(const Individual& parent1, const Individual& parent2, Individual& child1, Individual& child2) {
    random_device rd;
    mt19937 g(rd());
    uniform_int_distribution<> dis(0, parent1.genes.size() - 1);
    int crossover_point = dis(g);
    child1.genes = parent1.genes;
    child2.genes = parent2.genes;
    for (size_t i = crossover_point; i < child1.genes.size(); ++i) {
        swap(child1.genes[i], child2.genes[i]);
    }
}

// Fonction de réparation pour gérer les tâches répétées
void repair(Individual& individual) {
    set<int> seen;
    vector<int> duplicates;
    for (int task : individual.genes) {
        if (!seen.insert(task).second) {
            duplicates.push_back(task); // Tâche en double
        }
    }
    set<int> missing;
    for (int i = 0; i < individual.genes.size(); ++i) {
        if (seen.find(i) == seen.end()) {
            missing.insert(i); // Tâches manquantes
        }
    }
    auto miss_it = missing.begin();
    for (int& dup : duplicates) {
        auto it = find(individual.genes.begin(), individual.genes.end(), dup);
        if (it != individual.genes.end() && miss_it != missing.end()) {
            *it = *miss_it; // Remplace la tâche en double par une tâche manquante
            ++miss_it;
        }
    }
}

// Fonction de mutation qui échange deux tâches dans la séquence
void mutate(Individual& individual, double mutation_rate = 0.1) {
    random_device rd;
    mt19937 g(rd());
    uniform_real_distribution<> dis(0, 1);
    if (dis(g) < mutation_rate) {
        uniform_int_distribution<> task_dis(0, individual.genes.size() - 1);
        int index1 = task_dis(g);
        int index2 = task_dis(g);
        swap(individual.genes[index1], individual.genes[index2]);
    }
}

// Intégration de la réparation dans la fonction de croisement
void crossoverAndRepair(const Individual& parent1, const Individual& parent2, Individual& child1, Individual& child2) {
    crossover(parent1, parent2, child1, child2);
    repair(child1); // Applique la réparation après le croisement
    repair(child2); // Applique la réparation après le croisement
}

// Classe pour gérer l'algorithme génétique
class GeneticAlgorithm {
public:
    vector<Individual> population;
    int population_size;
    int num_generations;
    vector<vector<int>> task_times;
    int num_machines;

    // Constructeur
    GeneticAlgorithm(int num_tasks, int n_machines, int pop_size, int n_gen, const vector<vector<int>>& times)
        : population_size(pop_size), num_generations(n_gen), task_times(times), num_machines(n_machines) {
        for (int i = 0; i < population_size; ++i) {
            population.emplace_back(num_tasks);
        }
    }

    // Exécute l'algorithme génétique
    void run() {
        for (int gen = 0; gen < num_generations; ++gen) {
            // Évaluation de la fitness de chaque individu
            for (Individual& ind : population) {
                ind.calculateFitness(task_times, num_machines);
            }
            // Tri par fitness décroissante
            sort(population.begin(), population.end(), [](const Individual& a, const Individual& b) {
                return a.fitness > b.fitness;
                });

            // Affiche la meilleure fitness et la meilleure permutation
            cout << "Generation " << gen << ": Best fitness = " << 1/population.front().fitness << endl;
            cout << "Best permutation: ";
            for (int task : population.front().genes) {
                cout << task << " ";
            }
            cout << endl;

            // Sélection des meilleurs individus
            vector<Individual> new_population;
            int survivors = population_size / 2;
            for (int i = 0; i < survivors; ++i) {
                new_population.push_back(population[i]);
            }

            // Génération des nouveaux individus par croisement et mutation
            while (new_population.size() < population_size) {
                for (int i = 0; i < survivors; i += 2) {
                    Individual child1 = population[i];
                    Individual child2 = population[i + 1];
                    crossoverAndRepair(population[i], population[i + 1], child1, child2);
                    //mutate(child1);
                    //mutate(child2);
                    new_population.push_back(child1);
                    new_population.push_back(child2);
                }
            }

            // Remplacement de l'ancienne population par la nouvelle
            population = new_population;
        }
    }
};

// Fonction principale
int main() {
    int num_tasks;
    int num_machines;
    vector<vector<int>> task_times;

    // Lire l'instance à partir du fichier
    readInstance("tai1.txt", num_tasks, num_machines, task_times);

    int population_size = 10000;
    int num_generations = 100;

    // Démarrer le chronomètre
    auto start = chrono::high_resolution_clock::now();

    GeneticAlgorithm ga(num_tasks, num_machines, population_size, num_generations, task_times);
    ga.run(); // Lance l'algorithme génétique

    // Arrêter le chronomètre
    auto end = chrono::high_resolution_clock::now();

    // Calculer le temps écoulé en millisecondes
    chrono::duration<double, milli> elapsed = end - start;
    cout << "Temps d'exécution : " << elapsed.count() << " ms" << endl;

    return 0;
}
