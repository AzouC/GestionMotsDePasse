#include "SecurityManager.h"
#include <openssl/sha.h>
#include <openssl/rand.h>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm> 
#include <cctype>

using namespace std;

SecurityManager::SecurityManager() {}

string SecurityManager::generateSalt(int length) {
    unsigned char *buffer = new unsigned char[length];
    if (RAND_bytes(buffer, length) != 1) { delete[] buffer; return ""; }
    string salt(reinterpret_cast<char*>(buffer), length);
    delete[] buffer;
    return salt;
}

string SecurityManager::hashPassword(const string& password, const string& salt) {
    string input = password + salt;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(input.c_str()), input.length(), hash);
    char hashedPassword[2 * SHA256_DIGEST_LENGTH + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) sprintf(hashedPassword + (i * 2), "%02x", hash[i]);
    return string(hashedPassword);
}

bool SecurityManager::verifyMasterPassword(const string& input, const string& hash, const string& salt) {
    return (hashPassword(input, salt) == hash);
}

string SecurityManager::generateRandomPassword(int length) {
    if (length < 24) length = 24;
    const string lower = "abcdefghijklmnopqrstuvwxyz";
    const string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string digits = "0123456789";
    const string special = "!@#$%^&*()-_=+[]{}<>?";
    const string all = lower + upper + digits + special;
    string password = "";
    unsigned char byte; 
    
    // Force la complexité
    if (RAND_bytes(&byte, 1)) password += lower[byte % lower.length()];
    if (RAND_bytes(&byte, 1)) password += upper[byte % upper.length()];
    if (RAND_bytes(&byte, 1)) password += digits[byte % digits.length()];
    if (RAND_bytes(&byte, 1)) password += special[byte % special.length()];

    // Remplissage
    int remaining = length - 4;
    unsigned char *buffer = new unsigned char[remaining];
    if (RAND_bytes(buffer, remaining)) {
        for (int i = 0; i < remaining; i++) password += all[buffer[i] % all.length()];
    }
    delete[] buffer;

    // Mélange
    unsigned char *shuf = new unsigned char[length];
    if (RAND_bytes(shuf, length)) {
        for (int i = length - 1; i > 0; i--) std::swap(password[i], password[shuf[i] % (i + 1)]);
    }
    delete[] shuf;
    return password;
}

bool SecurityManager::checkPasswordStrength(const string& password) {
    if (password.length() < 16) {
        cout << "   [!] Erreur: Mot de passe trop court (" << password.length() << "/16)." << endl;
        return false;
    }
    bool u=false, l=false, d=false, s=false;
    for (char c : password) {
        if (isupper(c)) u=true; else if (islower(c)) l=true;
        else if (isdigit(c)) d=true; else if (ispunct(c)) s=true;
    }
    if(!u || !l || !d || !s) {
        cout << "   [!] Erreur: Manque Majuscule, Minuscule, Chiffre ou Special." << endl;
        return false;
    }
    return true;
}

string SecurityManager::encryptDecrypt(const string& data) {
    char key = 'K'; 
    string output = data;
    for (size_t i = 0; i < data.size(); i++) output[i] = data[i] ^ key;
    return output;
}
