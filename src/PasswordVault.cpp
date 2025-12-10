#include "PasswordVault.h"
#include <iostream>

using namespace std;

PasswordVault::PasswordVault() {}

void PasswordVault::addEntry(const PasswordEntry& entry) {
    entries.push_back(entry);
}

void PasswordVault::deleteEntry(int index) {
    if (index >= 0 && index < (int)entries.size()) {
        entries.erase(entries.begin() + index);
        cout << ">> Entree supprimee avec succes." << endl;
    } else {
        cout << ">> Erreur : Index invalide." << endl;
    }
}

// Mise à jour d'une entrée existante
void PasswordVault::updateEntry(int index, const PasswordEntry& newEntry) {
    if (index >= 0 && index < (int)entries.size()) {
        entries[index] = newEntry; // Remplacement dans le vecteur
        cout << ">> Entree mise a jour avec succes." << endl;
    } else {
        cout << ">> Erreur : Index invalide." << endl;
    }
}

void PasswordVault::listEntries() const {
    if (entries.empty()) {
        cout << ">> Aucun mot de passe enregistre." << endl;
        return;
    }
    for (size_t i = 0; i < entries.size(); ++i) {
        PasswordEntry current = entries[i];
        cout << "[" << i << "] Site: " << current.getSiteName() 
             << " | User: " << current.getUsername() 
             << " | Pass: ********" << endl;
    }
}

int PasswordVault::size() const {
    return (int)entries.size();
}
