# 🏭 FlowShop GA — Optimisation par algorithme génétique (C++)

![C++](https://img.shields.io/badge/C++-17-00599C?style=flat-square&logo=cplusplus&logoColor=white)
![Algorithme](https://img.shields.io/badge/Algorithme-Génétique-green?style=flat-square)
![Problème](https://img.shields.io/badge/Problème-Flow_Shop_Scheduling-orange?style=flat-square)
![Population](https://img.shields.io/badge/Population-10_000_individus-blue?style=flat-square)
![Générations](https://img.shields.io/badge/Générations-100-purple?style=flat-square)

> Implémentation d'un **algorithme génétique (GA)** en **C++** pour résoudre le problème d'ordonnancement **Flow Shop Scheduling** — minimisation du makespan (Cmax) sur instances Taillard.  
> Réalisé dans le cadre du cours **8INF309 — Stage-projet I** — UQAC, Automne 2025.

---

## 📋 Table des matières

- [Problème](#-problème--flow-shop-scheduling)
- [Approche](#-approche--algorithme-génétique)
- [Architecture du code](#-architecture-du-code)
- [Résultats](#-résultats)
- [Exécution](#-exécution)
- [Format des instances](#-format-des-instances)
- [Rapport](#-rapport-complet)

---

## 🏗️ Problème : Flow Shop Scheduling

Le problème **Flow Shop** consiste à ordonnancer **n tâches** sur **m machines** avec les contraintes suivantes :

- Chaque tâche doit passer par **toutes les machines** dans le même ordre
- Une machine ne peut traiter **qu'une seule tâche à la fois**
- L'objectif est de minimiser le **makespan (Cmax)** — temps total de complétion

```
Tâches :   T0   T1   T2   T3   T4
           ↓    ↓    ↓    ↓    ↓
M1 : [████][  ][███][  ][████]
M2 :      [███][   ][██][   ][███]
M3 :           [████][  ][███][  ]
                                 ↑ Cmax (makespan)
```

---

## 🧬 Approche : Algorithme génétique

### Représentation

Chaque individu est une **permutation des tâches** :

```
Exemple : [ 3, 1, 4, 0, 2 ]
          → Exécuter d'abord T3, puis T1, puis T4, etc.
```

### Cycle d'évolution

```
Population initiale (aléatoire)
        ↓
  Évaluation fitness (1 / makespan)
        ↓
  Tri par fitness décroissante
        ↓
  Sélection des 50% meilleurs
        ↓
  Croisement (crossover)
        ↓
  Réparation des permutations invalides
        ↓
  Nouvelle population
        ↓
  Répéter sur N générations
```

### Opérateurs génétiques

**Croisement** — échange de gènes à partir d'un point de coupure aléatoire entre deux parents, suivi d'une réparation pour garantir une permutation valide.

**Réparation** — détection et remplacement des tâches dupliquées par les tâches manquantes, assurant la validité de chaque individu.

**Mutation** — échange de deux tâches aléatoires dans la séquence (taux configurable, désactivée par défaut).

---

## 🏛️ Architecture du code

| Classe / Fonction | Rôle |
|---|---|
| `Individual` | Représente une solution — permutation + calcul de fitness |
| `GeneticAlgorithm` | Gère la population, la sélection, le croisement et l'évolution |
| `readInstance()` | Lecture du fichier d'instance Taillard |
| `crossover()` | Croisement à point unique entre deux parents |
| `repair()` | Correction des permutations invalides après croisement |
| `mutate()` | Mutation par échange de deux gènes |

### Structure du projet

```
flowshop_GA/
├── Source.cpp         # Code source complet
├── tai1.txt           # Instance Taillard (500 tâches × 20 machines)
├── README.md
└── documents/
    └── rapport.pdf    # Rapport complet du projet
```

---

## 📊 Résultats

**Instance** : `tai1.txt` — 500 tâches × 20 machines (benchmark Taillard)

**Paramètres** :

| Paramètre | Valeur |
|---|---|
| Taille de population | 10 000 individus |
| Nombre de générations | 100 |
| Taux de mutation | 0.1 (désactivée) |
| Sélection | Top 50% |

Le programme affiche à chaque génération :
- Le **meilleur makespan** trouvé
- La **meilleure permutation** de tâches
- Le **temps d'exécution** total en millisecondes

---

## 🚀 Exécution

### Compilation

```bash
# Linux / macOS
g++ -O2 -std=c++17 -o flowshop Source.cpp

# Windows (MinGW)
g++ -O2 -std=c++17 -o flowshop.exe Source.cpp
```

### Lancement

```bash
# Placez tai1.txt dans le même dossier que l'exécutable
./flowshop
```

### Exemple de sortie

```
Generation 0: Best fitness = 32450
Best permutation: 3 1 4 0 2 ...
Generation 1: Best fitness = 31980
Best permutation: 1 3 0 4 2 ...
...
Generation 99: Best fitness = 28710
Best permutation: 0 2 4 1 3 ...
Temps d'exécution : 4521.32 ms
```

---

## 📄 Format des instances

Les instances suivent le format **Taillard** :

```
n m
t[0][0]  t[1][0]  ...  t[n-1][0]    ← Machine 0
t[0][1]  t[1][1]  ...  t[n-1][1]    ← Machine 1
...
```

Où `n` = nombre de tâches et `m` = nombre de machines.

---

## 📚 Rapport complet

Le rapport détaillé du projet (analyse, résultats, comparaisons) est disponible ici :

[📄 Voir le rapport PDF](docs/rapport.pdf)

---

## 👤 Auteur

**Salifou Diallo**  
Étudiant en informatique — UQAC  
Superviseur : **Jimmy Girard-Nault**  
[![LinkedIn](https://img.shields.io/badge/LinkedIn-0077B5?style=flat-square&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/salifou-diallo-3117702b2/)
[![GitHub](https://img.shields.io/badge/GitHub-181717?style=flat-square&logo=github&logoColor=white)](https://github.com/SalifouDiallo)
