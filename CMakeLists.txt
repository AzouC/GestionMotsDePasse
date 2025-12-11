cmake_minimum_required(VERSION 3.10)
project(GestionMotsDePasse)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Détection d'OpenSSL
find_package(OpenSSL REQUIRED)

# Inclusion des dossiers
include_directories(include)
include_directories(${OPENSSL_INCLUDE_DIR})

# Création de l'exécutable avec TOUS les fichiers
add_executable(GestionMotsDePasse 
    src/main.cpp
    src/PasswordEntry.cpp
    src/PasswordVault.cpp
    src/SecurityManager.cpp
    src/FileManager.cpp
)

# Liaison avec OpenSSL
target_link_libraries(GestionMotsDePasse OpenSSL::SSL OpenSSL::Crypto)
