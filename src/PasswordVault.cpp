#include "PasswordVault.h"
#include <iostream>

using namespace std;

// Constructeur : Le vecteur s'initialise automatiquement à vide (taille 0)
// [cite: 383]
PasswordVault::PasswordVault() {
}

/**
 * Ajoute une entrée à la fin de la liste.
 * Utilise la méthode push_back du vector.
 * 
 */
void PasswordVault::addEntry(const PasswordEntry& entry) {
    entries.push_back(entry);
}

/**
 * Supprime une entrée à l'index spécifié.
 * Utilise la méthode erase() et l'itérateur begin() comme montré dans l'exemple du PDF.
 * [cite: 392, 393]
 */
void PasswordVault::deleteEntry(int index) {
    // Vérification de sécurité pour éviter de crasher si l'index est invalide
    if (index >= 0 && index < entries.size()) {
        entries.erase(entries.begin() + index);
        cout << "Entree supprimee avec succes." << endl;
    } else {
        cout << "Erreur : Index invalide." << endl;
    }
}

/**
 * Parcourt et affiche toutes les entrées.
 * Correspond à la méthode afficherTaches() de la mission précédente.
 * [cite: 394]
 */
void PasswordVault::listEntries() const {
    if (entries.empty()) {
        cout << "Aucun mot de passe enregistre." << endl;
        return;
    }

    // Boucle for classique pour parcourir le vecteur via l'index
    // [cite: 347]
    for (size_t i = 0; i < entries.size(); ++i) {
        // On récupère l'objet courant
        PasswordEntry current = entries[i];

        // Affichage formaté
        // Note : On suppose ici que PasswordEntry a des accesseurs (Getters)
        cout << "ID [" << i << "] " 
             << "Site: " << current.getSiteName() 
             << " | User: " << current.getUsername() 
             // On n'affiche PAS le mot de passe en clair par sécurité, ou alors masqué
             << " | Pass: ********" << endl;
             
        // Alternative : Si PasswordEntry a une méthode afficher(), on l'appelle ici :
        // current.afficher();
    }
}

int PasswordVault::size() const {
    return entries.size();
}
