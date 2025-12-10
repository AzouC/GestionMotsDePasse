#include "SecurityManager.h"
#include <openssl/sha.h>
#include <openssl/rand.h>
#include <iostream>
#include <cstdio> // Pour sprintf

using namespace std;

SecurityManager::SecurityManager() {}

string SecurityManager::generateSalt(int length) {
    unsigned char *buffer = new unsigned char[length];
    int rc = RAND_bytes(buffer, length);
    if (rc != 1) {
        delete[] buffer;
        return ""; 
    }
    // Note : Conversion brute pour stockage simple
    string salt(reinterpret_cast<char*>(buffer), length);
    delete[] buffer;
    return salt;
}

string SecurityManager::hashPassword(const string& password, const string& salt) {
    string input = password + salt;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(input.c_str()), input.length(), hash);

    char hashedPassword[2 * SHA256_DIGEST_LENGTH + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashedPassword + (i * 2), "%02x", hash[i]);
    }
    hashedPassword[2 * SHA256_DIGEST_LENGTH] = 0;
    return string(hashedPassword);
}

// Nouvelle méthode exigée par le sujet
bool SecurityManager::verifyMasterPassword(const string& inputPassword, const string& storedHash, const string& storedSalt) {
    // On re-calcule le hash avec l'entrée utilisateur et le sel stocké
    string calculatedHash = hashPassword(inputPassword, storedSalt);
    // On compare
    return (calculatedHash == storedHash);
}
