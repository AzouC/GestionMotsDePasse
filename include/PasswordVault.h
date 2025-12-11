/**
 * @file PasswordVault.h
 * @brief Gestion de la collection de mots de passe (CRUD en mémoire).
 * @author Malo
 */

#ifndef PASSWORDVAULT_H
#define PASSWORDVAULT_H

#include <vector>
#include "PasswordEntry.h"

/**
 * @class PasswordVault
 * @brief Gère le stockage volatile et la manipulation des mots de passe.
 * * Cette classe agit comme une base de données en mémoire vive (RAM).
 * Elle permet d'ajouter, modifier, supprimer et lister des entrées.
 * Elle assure le cloisonnement des données entre les utilisateurs lors de l'affichage.
 */
class PasswordVault {
private:
    /**
     * @brief Vecteur dynamique stockant toutes les entrées de tous les utilisateurs.
     */
    std::vector<PasswordEntry> entries;

public:
    PasswordVault();

    /**
     * @brief Ajoute une nouvelle entrée dans le coffre.
     * @param entry L'objet PasswordEntry à stocker.
     */
    void addEntry(const PasswordEntry& entry);

    /**
     * @brief Supprime une entrée par son index.
     * @param index L'index de l'élément dans le vecteur global.
     */
    void deleteEntry(int index);

    /**
     * @brief Met à jour une entrée existante.
     * @param index L'index de l'élément à modifier.
     * @param newEntry Le nouvel objet remplaçant l'ancien.
     */
    void updateEntry(int index, const PasswordEntry& newEntry);

    /**
     * @brief Affiche la liste des mots de passe (Filtrage de sécurité).
     * * Cette méthode parcourt le coffre et n'affiche que les entrées appartenant
     * à l'utilisateur connecté (ou toutes si c'est un Admin).
     * * @param currentUser Le nom de l'utilisateur connecté.
     * @param isAdmin Booléen indiquant si l'utilisateur a les droits d'administration.
     * @param showClear Si true, affiche les mots de passe en clair. Sinon, affiche '********'.
     */
    void listEntries(std::string currentUser, bool isAdmin, bool showClear = false) const;
    
    /**
     * @brief Retourne le nombre total d'entrées.
     * @return Taille du vecteur.
     */
    int size() const;

    /**
     * @brief Récupère toutes les entrées pour la sauvegarde.
     * @return Une copie complète du vecteur entries.
     */
    std::vector<PasswordEntry> getAllEntries() const;

    /**
     * @brief Charge les données depuis une sauvegarde.
     * @param loadedEntries Le vecteur d'entrées lu depuis le fichier.
     */
    void loadEntries(const std::vector<PasswordEntry>& loadedEntries);
};

#endif // PASSWORDVAULT_H
