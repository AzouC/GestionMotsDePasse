🔐 Application de Gestion de Mots de Passe Sécurisée
📄 Contexte du Projet
Ce projet a été réalisé dans le cadre du BTS CIEL, Bloc 3 : "Valorisation de la donnée et cybersécurité". L'objectif est de concevoir une application robuste permettant de stocker des identifiants sensibles en respectant les principes modernes de développement sécurisé et de programmation orientée objet (POO).


🚀 Fonctionnalités Clés
L'application offre une interface en ligne de commande (CLI) sécurisée proposant les services suivants :


Authentification Forte : Création d'un compte protégé par un mot de passe maître chiffré.


Coffre-fort Numérique : Ajout, modification et suppression d'entrées (Site, Utilisateur, Mot de passe).


Consultation Sécurisée : Affichage de la liste des comptes enregistrés.


Architecture Modulaire : Conception extensible permettant l'ajout futur de fonctionnalités (multi-utilisateurs, chiffrement AES des données).

🛡️ Architecture de Sécurité & Cryptographie
La sécurité est au cœur de ce projet. Conformément au cahier des charges, aucune donnée critique d'authentification n'est stockée en clair.

1. Hachage SHA-256
Le mot de passe maître est transformé en empreinte numérique via l'algorithme SHA-256 (Secure Hash Algorithm 256-bits). Cette fonction unidirectionnelle garantit que le mot de passe original ne peut être reconstruit à partir de l'empreinte stockée.

2. Mécanisme de "Salage" (Salting)
Pour contrer les attaques par dictionnaire et les Rainbow Tables (tables arc-en-ciel), un sel aléatoire (random salt) unique est généré cryptographiquement pour chaque utilisateur via OpenSSL (RAND_bytes).


L'empreinte stockée correspond à : SHA256(MotDePasse + Sel).

3. Bibliothèque OpenSSL
L'implémentation repose sur la bibliothèque éprouvée OpenSSL pour garantir la fiabilité des primitives cryptographiques utilisées.

🛠️ Conception Technique (UML & POO)
Le projet respecte une architecture Orientée Objet stricte avec une séparation claire des responsabilités:


PasswordEntry : Encapsule les données d'une entrée unique (Site, Login, Pass).


PasswordVault : Gère la collection dynamique des mots de passe (utilisation de std::vector).


SecurityManager : Classe utilitaire dédiée aux opérations cryptographiques (Génération de sel, calcul de Hash).

⚙️ Installation et Compilation
Prérequis
Compilateur C++ compatible C++17 (GCC, MSVC, Clang).


CMake (Version 3.10 minimum).

Bibliothèque OpenSSL installée sur le système.

Procédure de Build (Windows/Linux)
Le projet utilise un système de build automatisé via CMake.

Bash

# 1. Cloner le dépôt
git clone <url_du_repo>
cd GestionMotsDePasse

# 2. Créer le dossier de build (Bonne pratique CMake)
mkdir build
cd build

# 3. Configurer le projet
cmake ..

# 4. Compiler
make  # ou 'cmake --build .' sous Windows
🔄 Intégration Continue (DevOps)
Le projet intègre une chaîne CI/CD (GitLab CI) pour automatiser la validation du code. À chaque push sur le dépôt, un pipeline s'exécute pour :

Installer les dépendances (CMake, OpenSSL).

Compiler le projet à neuf pour vérifier l'intégrité du code.

📚 Documentation
La documentation technique des classes et méthodes est générée automatiquement via Doxygen. Pour la générer localement :

Bash

doxygen Doxyfile
Le résultat sera disponible dans le dossier docs/html/index.html.

🎓 Compétences Validées
Ce projet permet de valider les compétences suivantes du référentiel BTS CIEL-IR :


C03 : Évaluer la complexité technique et la criticité (gestion des données sensibles).


Gestion de projet : Analyse, conception, réalisation et validation.



Développement : Maîtrise du C++ et de la POO (Encapsulation, Vecteurs, Pointeurs).


Outils DevOps : Git, Versionning, Pipeline CI/CD.

Projet réalisé par [Malo & Romain].
