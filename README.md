# Flow Shop Optimization with Genetic Algorithm (C++)

Ce projet implémente un **algorithme génétique (Genetic Algorithm – GA)** en **C++** pour résoudre le problème d'ordonnancement **Flow Shop Scheduling**.

L'objectif est de déterminer un **ordre optimal des tâches** sur plusieurs machines afin de **minimiser le makespan (temps total de complétion)**.

---

# Contexte académique

Ce projet a été réalisé dans le cadre du cours  

**Stage-projet I – 8INF309**

à l'**Université du Québec à Chicoutimi (UQAC)** durant la session **Automne 2025**.

Le projet a été développé sous la supervision du professeur  

**Jimmy Girard-Nault**

---

# Problème : Flow Shop Scheduling

Le problème Flow Shop consiste à planifier l'exécution de **n tâches** sur **m machines**.

Contraintes :

- chaque tâche doit être exécutée sur toutes les machines
- l'ordre des machines est **identique pour toutes les tâches**
- une machine ne peut traiter **qu'une seule tâche à la fois**

L'objectif est de trouver une **permutation des tâches** minimisant le **makespan (Cmax)**.

---

# Approche : Algorithme génétique

L'algorithme génétique utilise des mécanismes inspirés de l'évolution naturelle pour explorer l'espace des solutions.

## Représentation

Un individu correspond à :

- une **permutation des tâches**

Exemple :
[3, 1, 4, 0, 2]


## Étapes de l'algorithme

1. Génération d'une **population initiale aléatoire**
2. Évaluation de la **fitness** de chaque individu
3. **Sélection** des meilleurs individus
4. **Croisement** pour générer de nouveaux individus
5. **Réparation** des permutations invalides
6. Répétition du processus sur plusieurs générations

---

# Fonction de fitness

La fitness est basée sur le **makespan**.
fitness = 1 / makespan


Plus le makespan est faible, meilleure est la solution.

---

# Structure du projet

flowshop_GA/
│
├── main.cpp
├── tai1.txt
│
└── docs/
└── rapport.pdf


---

# Format des instances

Les instances contiennent :
n m


où :

- **n** = nombre de tâches
- **m** = nombre de machines

Suivi des temps de traitement.

Exemple :
500 20


---

# Exécution

Le programme lit le fichier :
tai1.txt

Place ce fichier dans le même dossier que l'exécutable.


---

# Paramètres de l'algorithme

Dans la version actuelle du programme :

- Population : **10000**
- Générations : **100**

Le programme affiche :

- le **meilleur makespan par génération**
- la **meilleure permutation trouvée**
- le **temps total d'exécution**

---

