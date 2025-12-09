#include "SecurityManager.h"
#include <openssl/sha.h>
#include <openssl/rand.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstring> // Pour strlen si besoin

using namespace std;

// Constructeur par défaut
SecurityManager::SecurityManager() {
    // Initialisation si nécessaire (rien de spécifique requis par les fiches)
}

/**
 * Génère un sel aléatoire pour renforcer la sécurité des mots de passe.
 * Basé sur le code de la fiche notionnelle "Hachage" (Activité 2.4).
 * [cite: 595, 605]
 */
string SecurityManager::generateSalt(int length) {
    // Création du buffer pour les octets aléatoires
    unsigned char *buffer = new unsigned char[length];

    // Génération aléatoire via OpenSSL
    // RAND_bytes renvoie 1 en cas de succès
    int rc = RAND_bytes(buffer, length);
    
    if (rc != 1) {
        // Gestion d'erreur basique : on pourrait lancer une exception ici
        cerr << "Erreur lors de la génération du sel (RAND_bytes failed)." << endl;
        delete[] buffer;
        return ""; 
    }

    // Conversion du buffer binaire en chaîne hexadécimale lisible
    // Note : Le PDF convertit directement en string via reinterpret_cast[cite: 614],
    // mais pour un sel stockable/lisible, une conversion hexadécimale est préférable.
    // Je respecte ici la logique "string" simple du PDF pour ne pas complexifier,
    // mais attention : le reinterpret_cast brut peut poser souci à l'affichage.
    // Voici l'implémentation exacte demandée par la fiche corrigée :
    
    string salt(reinterpret_cast<char*>(buffer), length);
    
    delete[] buffer;
    return salt;
}

/**
 * Hache le mot de passe en utilisant l'algorithme SHA-256 et un sel.
 * Implémentation de la fonction hashPassword2 de la fiche notionnelle.
 * [cite: 632]
 */
string SecurityManager::hashPassword(const string& password, const string& salt) {
    // Concaténation du mot de passe et du sel [cite: 632]
    string input = password + salt;

    // Buffer pour stocker l'empreinte brute (32 octets pour SHA-256)
    unsigned char hash[SHA256_DIGEST_LENGTH];

    // Calcul du hachage SHA-256 [cite: 633]
    SHA256(reinterpret_cast<const unsigned char*>(input.c_str()), input.length(), hash);

    // Conversion de l'empreinte binaire en chaîne hexadécimale
    // La taille est (2 * 32) + 1 pour le caractère de fin de chaîne '\0'
    char hashedPassword[2 * SHA256_DIGEST_LENGTH + 1];

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        // Écriture formatée en hexadécimal (2 caractères par octet) [cite: 640]
        sprintf(hashedPassword + (i * 2), "%02x", hash[i]);
    }

    // Assurer la terminaison de la chaîne (optionnel avec sprintf qui le fait, mais sûr)
    hashedPassword[2 * SHA256_DIGEST_LENGTH] = 0;

    return string(hashedPassword);
}
