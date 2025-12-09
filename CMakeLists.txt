cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(GestionMotsDePasse)

# Spécification du standard C++ (C++17 est un bon standard moderne)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- 1. Recherche de la bibliothèque OpenSSL ---
# Indispensable pour <openssl/sha.h> et <openssl/rand.h>
# Référence : Fiche "Hachage des mots de passe", section 1.3 et 2.1
find_package(OpenSSL REQUIRED)

# --- 2. Inclusion des dossiers d'en-tête (.h) ---
# Permet de faire #include "Fichier.h" sans préciser le chemin complet
include_directories(include)

# Si OpenSSL est trouvé, on inclut aussi ses headers système
if(OpenSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
endif()

# --- 3. Liste des fichiers sources (.cpp) ---
set(SOURCES
    src/main.cpp
    src/PasswordEntry.cpp
    src/PasswordVault.cpp
    src/SecurityManager.cpp
)

# --- 4. Création de l'exécutable ---
add_executable(GestionMotsDePasse ${SOURCES})

# --- 5. Édition des liens (Linker) ---
# On lie l'exécutable avec les bibliothèques binaires d'OpenSSL (Crypto et SSL)
target_link_libraries(GestionMotsDePasse OpenSSL::SSL OpenSSL::Crypto)
