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
        cout << ">> Entree supprimee." << endl;
    } else cout << ">> Erreur Index." << endl;
}

void PasswordVault::updateEntry(int index, const PasswordEntry& newEntry) {
    if (index >= 0 && index < (int)entries.size()) {
        entries[index] = newEntry;
        cout << ">> Mise a jour OK." << endl;
    } else cout << ">> Erreur Index." << endl;
}

// MODIF ICI : Gestion de l'affichage masqué/clair
void PasswordVault::listEntries(string currentUser, bool isAdmin, bool showClear) const {
    bool found = false;
    cout << "\n--- COFFRE FORT (" << currentUser << ") ---" << endl;
    
    for (size_t i = 0; i < entries.size(); ++i) {
        if (isAdmin || entries[i].getOwner() == currentUser) {
            cout << "ID [" << i << "] "; 
            if (isAdmin) cout << "[Proprio: " << entries[i].getOwner() << "] ";
            
            cout << "Site: " << entries[i].getSiteName() 
                 << " | User: " << entries[i].getUsername() 
                 << " | Pass: ";
            
            // C'est ici que la magie opère
            if (showClear) {
                cout << entries[i].getPassword(); // Affiche en clair
            } else {
                cout << "********"; // Masque par défaut
            }
            cout << endl;
            
            found = true;
        }
    }
    if (!found) cout << ">> Aucune entree visible." << endl;
}

int PasswordVault::size() const { return (int)entries.size(); }
vector<PasswordEntry> PasswordVault::getAllEntries() const { return entries; }
void PasswordVault::loadEntries(const vector<PasswordEntry>& loadedEntries) { entries = loadedEntries; }
