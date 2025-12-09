#ifndef PASSWORDVAULT_H
#define PASSWORDVAULT_H

#include <vector>
#include "PasswordEntry.h" // Nécessaire car le vecteur contient des objets PasswordEntry

class PasswordVault {
private:
    // Conteneur dynamique stockant les objets PasswordEntry
    // Correspond à l'attribut "taches" de la classe ListeDeTaches [cite: 351]
    std::vector<PasswordEntry> entries;

public:
    // Constructeur
    PasswordVault();

    // Ajoute une nouvelle entrée dans le coffre
    // Passage par référence comme recommandé dans le PDF [cite: 386]
    void addEntry(const PasswordEntry& entry);

    // Supprime une entrée selon son index
    void deleteEntry(int index);

    // Affiche toutes les entrées stockées
    void listEntries() const;
    
    // (Optionnel) Retourne la taille pour des vérifications
    int size() const;
};

#endif // PASSWORDVAULT_H
