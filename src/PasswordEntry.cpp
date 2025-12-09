#include "PasswordEntry.h"

using namespace std;

/**
 * Constructeur par défaut.
 * Initialise les attributs à vide ou avec des valeurs par défaut.
 * Similaire au constructeur par défaut de la classe Tache.
 */
PasswordEntry::PasswordEntry() {
    this->siteName = "";
    this->username = "";
    this->password = "";
}

/**
 * Constructeur surchargé.
 * Permet d'initialiser l'objet avec des valeurs spécifiques dès sa création.
 * * @param site Le nom du site web ou de l'application
 * @param user Le nom d'utilisateur associé
 * @param pass Le mot de passe associé
 */
PasswordEntry::PasswordEntry(string site, string user, string pass) {
    this->siteName = site;
    this->username = user;
    this->password = pass;
}

// --- Implémentation des Getters (Accesseurs) ---

string PasswordEntry::getSiteName() const {
    return this->siteName;
}

string PasswordEntry::getUsername() const {
    return this->username;
}

string PasswordEntry::getPassword() const {
    return this->password;
}

// --- Implémentation des Setters (Mutateurs) ---

void PasswordEntry::setSiteName(string site) {
    this->siteName = site;
}

void PasswordEntry::setUsername(string user) {
    this->username = user;
}

void PasswordEntry::setPassword(string pass) {
    this->password = pass;
}
