🔐 Gestionnaire de Mots de Passe Sécurisé (C++)
📄 Présentation du Projet
Ce projet a été réalisé dans le cadre du BTS CIEL (Cybersécurité, Informatique et réseaux, Électronique), spécifiquement pour le Bloc 3 : Valorisation de la donnée et cybersécurité.

L'objectif est de fournir une solution robuste et sécurisée pour le stockage local d'identifiants. Contrairement à un stockage en texte clair, cette application implémente les standards cryptographiques actuels pour garantir la confidentialité du mot de passe maître.

🚀 Fonctionnalités

Création de Compte Sécurisée : Définition d'un nom d'utilisateur et d'un mot de passe maître chiffré.


Authentification Forte : Vérification stricte des identifiants avant l'accès au coffre-fort.

Gestion CRUD complète :

Ajouter un nouveau mot de passe.

Consulter la liste des comptes enregistrés.

Modifier une entrée existante.

Supprimer une entrée.


Persistance (Session) : Maintien des données en mémoire vive durant l'exécution (vecteurs dynamiques).

🛡️ Architecture de Sécurité & Cryptographie
La sécurité est le cœur de ce projet. Aucune donnée d'authentification critique n'est stockée en clair.

1. Hachage SHA-256
Le mot de passe maître est transformé en une empreinte numérique unique de 256 bits via l'algorithme SHA-256 (Secure Hash Algorithm). Cette opération est irréversible.

2. Salage (Salting)
Pour contrer les attaques par dictionnaire et les Rainbow Tables, nous utilisons la technique de la "salaison".

Un sel aléatoire (random salt) unique est généré cryptographiquement pour chaque utilisateur via RAND_bytes d'OpenSSL.

Formule utilisée : Hash = SHA256(MotDePasse + Sel).

3. Bibliothèque OpenSSL
L'implémentation repose sur la bibliothèque professionnelle OpenSSL pour garantir la fiabilité des primitives cryptographiques.

🎓 Compétences Validées
Ce projet démontre la maîtrise des compétences suivantes du référentiel BTS CIEL-IR :

Développement C++ & POO :

Conception de classes et objets (PasswordEntry, PasswordVault).

Encapsulation des données sensibles.

Utilisation de conteneurs standards (std::vector).

Cybersécurité :

Compréhension des mécanismes de hachage et de sel.

Intégration de bibliothèques tierces de sécurité (OpenSSL).

DevOps & Gestion de Projet :

Utilisation de Git pour le versionning.

Automatisation de la compilation avec CMake.

Pipeline d'intégration continue (GitLab CI).

Documentation technique automatique via Doxygen.

💻 Guide d'Installation (Pour l'utilisateur)
Ce guide est destiné à une personne souhaitant simplement lancer l'application sur sa machine.

Prérequis
Avoir CMake installé.

Avoir un compilateur C++ (GCC, Clang ou MSVC).

Avoir la bibliothèque OpenSSL installée.

🪟 Windows
Installez OpenSSL : Téléchargez "Win64 OpenSSL v3.x Light" sur slproweb.com. Installez-le dans le dossier par défaut.

Ouvrez un terminal (PowerShell) dans le dossier du projet.

Compilez et lancez :

PowerShell

mkdir build
cd build
cmake ..
cmake --build .
.\Debug\GestionMotsDePasse.exe
(Note : Si le programme ne se lance pas, copiez les fichiers libssl-3-x64.dll et libcrypto-3-x64.dll depuis C:\Program Files\OpenSSL-Win64\bin vers le dossier de l'exécutable).

🐧 Linux (Debian/Ubuntu)
Bash

# 1. Installer les dépendances
sudo apt-get update
sudo apt-get install cmake g++ libssl-dev

# 2. Compiler
mkdir build && cd build
cmake ..
make

# 3. Lancer
./GestionMotsDePasse
🍎 macOS
Bash

# 1. Installer les dépendances (via Homebrew)
brew install cmake openssl

# 2. Compiler (en spécifiant le chemin d'OpenSSL si besoin)
mkdir build && cd build
cmake .. -DOPENSSL_ROOT_DIR=$(brew --prefix openssl)
make

# 3. Lancer
./GestionMotsDePasse
🛠️ Guide du Développeur (VS Code)
Ce guide est destiné aux développeurs souhaitant modifier ou analyser le code source via Visual Studio Code, particulièrement sous Windows.

1. Configuration de l'environnement (Windows)
Avant d'ouvrir VS Code, assurez-vous d'avoir installé :

VS Code + Extension "C/C++" + Extension "CMake Tools".

CMake (Ajouté au PATH système).

OpenSSL (Installé dans C:\Program Files\OpenSSL-Win64).

2. Ouverture du Projet
⚠️ Très important : Ne pas ouvrir un fichier seul.

Lancez VS Code.

Faites Fichier > Ouvrir le dossier....

Sélectionnez le dossier racine GestionMotsDePasse-main (celui qui contient directement CMakeLists.txt).

3. Configuration de CMake
Si VS Code ne détecte pas OpenSSL automatiquement, créez un dossier .vscode à la racine et ajoutez un fichier settings.json :

JSON

{
    "cmake.configureSettings": {
        "OPENSSL_ROOT_DIR": "C:/Program Files/OpenSSL-Win64"
    },
    "C_Cpp.default.includePath": [
        "C:/Program Files/OpenSSL-Win64/include",
        "${workspaceFolder}/include"
    ]
}
4. Compilation et Exécution
Utilisez la barre d'état CMake située tout en bas de la fenêtre VS Code (Barre bleue/violette) :

Sélecteur de Kit : Cliquez et choisissez votre compilateur (ex: GCC 13.x.x ou Visual Studio Community).

Build (⚙️) : Cliquez sur la roue dentée pour compiler le projet.

Run (▶️) : Cliquez sur le petit triangle de lecture (à côté de la roue dentée) pour lancer l'application dans le terminal intégré.

📂 Structure du Projet
Plaintext

GestionMotsDePasse/
├── CMakeLists.txt       # Configuration de la compilation (OpenSSL linkage)
├── .gitlab-ci.yml       # Pipeline CI/CD pour GitLab
├── Doxyfile             # Configuration de la documentation
├── README.md            # Ce fichier
├── include/             # Fichiers d'en-tête (.h)
│   ├── PasswordEntry.h
│   ├── PasswordVault.h
│   └── SecurityManager.h
└── src/                 # Codes sources (.cpp)
    ├── main.cpp         # Menu principal et logique utilisateur
    ├── PasswordEntry.cpp
    ├── PasswordVault.cpp
    └── SecurityManager.cpp
