# 1. Installer les dépendances (via Homebrew)
brew install cmake openssl

# 2. Compiler (en spécifiant le chemin d'OpenSSL si besoin)
mkdir build && cd build
cmake .. -DOPENSSL_ROOT_DIR=$(brew --prefix openssl)
make

# 3. Lancer
./GestionMotsDePasse

Markdown

# 🔐 Gestionnaire de Mots de Passe Sécurisé (C++)

![Language](https://img.shields.io/badge/Language-C%2B%2B17-00599C?style=flat-square&logo=c%2B%2B)
![Security](https://img.shields.io/badge/Security-SHA256%20%2B%20Salt-red?style=flat-square&logo=openssl)
![Compliance](https://img.shields.io/badge/Compliance-ANSSI%202025-success?style=flat-square)
![Persistence](https://img.shields.io/badge/Data-Encrypted%20Storage-blueviolet?style=flat-square)

## 📄 Présentation du Projet

Ce projet a été réalisé dans le cadre du **BTS CIEL** (Cybersécurité, Informatique et réseaux, Électronique), spécifiquement pour le **Bloc 3 : Valorisation de la donnée et cybersécurité**.

L'objectif est de fournir une solution robuste pour le stockage local d'identifiants. Contrairement à un stockage en texte clair, cette application implémente les standards cryptographiques pour garantir la confidentialité des données, même en cas de vol des fichiers de sauvegarde.

### 🚀 Fonctionnalités Clés
* **Création de Compte Sécurisée :** Définition d'un nom d'utilisateur et d'un mot de passe maître chiffré.
* **Authentification Forte :** Vérification stricte des identifiants avant l'accès au coffre-fort.
* **Persistance Chiffrée :** Les données sont sauvegardées sur le disque (`.dat`) mais rendues illisibles (chiffrement) pour empêcher la lecture externe.
* **Gestion Multi-Utilisateurs :** Cloisonnement strict des données (un utilisateur ne voit que ses propres mots de passe).
* **Générateur ANSSI :** Outil intégré pour générer des mots de passe forts (24 caractères) conformes aux normes 2025.
* **Protection contre le "Shoulder Surfing" :** Les mots de passe sont masqués (`****`) par défaut. Une ré-authentification est requise pour les révéler.

---

## 🛡️ Architecture de Sécurité & Cryptographie

La sécurité est le cœur de ce projet. Aucune donnée d'authentification critique n'est stockée en clair.

### 1. Hachage SHA-256
Le mot de passe maître est transformé en une empreinte numérique unique de 256 bits via l'algorithme **SHA-256**. Cette opération est irréversible.

### 2. Salage (Salting)
Pour contrer les attaques par dictionnaire et les *Rainbow Tables*, nous utilisons la technique de la "salaison". Un **sel aléatoire** unique est généré cryptographiquement pour chaque utilisateur via `RAND_bytes` d'OpenSSL.

### 3. Bibliothèque OpenSSL
L'implémentation repose sur la bibliothèque professionnelle **OpenSSL** pour garantir la fiabilité des primitives cryptographiques.

---

## 📘 Documentation Technique des Classes

L'application repose sur une conception Orientée Objet stricte pour garantir la maintenance, la sécurité et la persistance des données.

### 1. Classe `PasswordEntry` (Données)
Représente une entrée atomique dans le coffre-fort.
| Attribut / Méthode | Type | Description |
| :--- | :--- | :--- |
| `owner` | `string` | Propriétaire de l'entrée (permet le cloisonnement des données). |
| `siteName` | `string` | Nom du site web ou service concerné. |
| `username` | `string` | Identifiant de connexion. |
| `password` | `string` | Secret associé (Mot de passe du site). |
| `getOwner()` | `string` | Accesseur de sécurité pour vérifier la propriété de l'entrée. |

### 2. Classe `PasswordVault` (Logique Métier)
Gère la liste des mots de passe en mémoire vive (RAM) et le filtrage.
| Méthode | Rôle Technique |
| :--- | :--- |
| `addEntry(...)` | Ajoute une entrée au vecteur dynamique. |
| `listEntries(..., showClear)` | **Filtrage de sécurité :** N'affiche que les données de l'utilisateur connecté. Le paramètre `showClear` permet de masquer (`****`) ou révéler le mot de passe. |
| `updateEntry(...)` | Met à jour une entrée spécifique. |
| `getAllEntries()` | Fournit l'intégralité des données au `FileManager` pour la sauvegarde. |
| `loadEntries(...)` | Reconstruit le coffre à partir des données chargées du disque. |

### 3. Classe `SecurityManager` (Cryptographie)
Moteur de sécurité reposant sur **OpenSSL**.
| Méthode | Algorithme / Standard utilisé |
| :--- | :--- |
| `generateSalt` | Génération d'aléa cryptographique via `RAND_bytes`. |
| `hashPassword` | Hachage irréversible **SHA-256** (Password + Salt). |
| `verifyMasterPassword` | Recalcule le hash de la saisie et le compare au hash stocké. |
| `generateRandomPassword` | **Générateur ANSSI :** 24 caractères, mélange 4 types (Maj, Min, Digit, Special). |
| `checkPasswordStrength` | **Validateur :** Vérifie si un MDP manuel respecte la politique de complexité. |
| `encryptDecrypt` | **Chiffrement Symétrique :** Applique un algorithme (XOR) pour rendre les fichiers de sauvegarde illisibles à l'œil nu. |

### 4. Classe `FileManager` (Persistance)
Gère la lecture et l'écriture sur le disque dur pour que les données survivent au redémarrage.
| Méthode | Rôle Technique |
| :--- | :--- |
| `saveUsers(...)` | Sauvegarde la liste des comptes dans `users.dat` après chiffrement. |
| `saveVault(...)` | Sauvegarde le contenu du coffre dans `vault.dat` après chiffrement. |
| `loadUsers(...)` | Lit, déchiffre et reconstruit la liste des utilisateurs au démarrage. |
| `loadVault(...)` | Lit, déchiffre et reconstruit le coffre-fort au démarrage. |

---

## 🎓 Compétences Validées

Ce projet démontre la maîtrise des compétences suivantes du référentiel **BTS CIEL-IR** :

* **Développement C++ & POO :** Conception de classes, Encapsulation, Gestion de fichiers (`fstream`).
* **Cybersécurité :** Hachage, Salage, OpenSSL, Chiffrement de fichiers, Normes ANSSI.
* **DevOps & Gestion de Projet :** Git, CMake, Pipeline CI/CD, Documentation technique.

---

## 💻 Guide d'Installation (Utilisateur)

### Prérequis
* Avoir **CMake** installé.
* Avoir un compilateur C++ (GCC, Clang ou MSVC).
* Avoir la bibliothèque **OpenSSL** installée.

### 🪟 Windows
1.  **Installez OpenSSL :** Téléchargez "Win64 OpenSSL v3.x Light" sur [slproweb.com](https://slproweb.com/products/Win32OpenSSL.html). Installez-le dans le dossier par défaut.
2.  Ouvrez un terminal (PowerShell) dans le dossier du projet.
3.  Compilez et lancez :
    ```powershell
    mkdir build
    cd build
    cmake ..
    cmake --build .
    .\Debug\GestionMotsDePasse.exe
    ```
    *(Note : Si le programme ne se lance pas, copiez les fichiers `libssl-3-x64.dll` et `libcrypto-3-x64.dll` depuis `C:\Program Files\OpenSSL-Win64\bin` vers le dossier de l'exécutable).*

### 🐧 Linux (Debian/Ubuntu)
```bash
# 1. Installer les dépendances
sudo apt-get update && sudo apt-get install cmake g++ libssl-dev

# 2. Compiler
mkdir build && cd build
cmake .. && make

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

Run (▶️) : Cliquez sur le petit triangle de lecture pour lancer l'application.

📂 Structure du Projet :
GestionMotsDePasse/
├── CMakeLists.txt       # Configuration de la compilation
├── .gitlab-ci.yml       # Pipeline CI/CD
├── README.md            # Documentation
├── users.dat            # Base de données utilisateurs (Chiffrée)
├── vault.dat            # Base de données coffre-fort (Chiffrée)
├── include/             # Fichiers d'en-tête (.h)
│   ├── PasswordEntry.h
│   ├── PasswordVault.h
│   ├── SecurityManager.h
│   └── FileManager.h
└── src/                 # Codes sources (.cpp)
    ├── main.cpp         # Menu principal
    ├── PasswordEntry.cpp
    ├── PasswordVault.cpp
    ├── SecurityManager.cpp
    └── FileManager.cpp
