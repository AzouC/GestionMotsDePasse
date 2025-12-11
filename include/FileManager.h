/**
 * @file FileManager.h
 * @brief Gestion de la persistance des données sur le disque.
 * @author Malo
 */

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include <string>
#include "PasswordEntry.h"
#include "SecurityManager.h" 

/**
 * @class FileManager
 * @brief Gère la sauvegarde et le chargement des fichiers (.dat).
 * * Cette classe s'occupe de la sérialisation des objets (User et PasswordEntry)
 * vers des fichiers textes, en appliquant un chiffrement via SecurityManager
 * avant l'écriture sur le disque.
 */
class FileManager {
private:
    std::string userFile = "users.dat";   ///< Fichier stockant les comptes utilisateurs
    std::string vaultFile = "vault.dat";  ///< Fichier stockant les mots de passe
    SecurityManager security;             ///< Instance pour chiffrer/déchiffrer les données

public:
    FileManager();

    /**
     * @brief Sauvegarde la liste des utilisateurs.
     * @details Format : encrypt(username|hash|salt|isAdmin)
     * @param users Le vecteur d'utilisateurs à écrire.
     */
    void saveUsers(const std::vector<User>& users);

    /**
     * @brief Sauvegarde le contenu du coffre-fort.
     * @details Format : encrypt(owner|site|user|pass)
     * @param entries Le vecteur d'entrées à écrire.
     */
    void saveVault(const std::vector<PasswordEntry>& entries);

    /**
     * @brief Charge la liste des utilisateurs au démarrage.
     * @param users Vecteur à remplir par référence.
     * @return true si le fichier existe et a été chargé, false sinon (premier lancement).
     */
    bool loadUsers(std::vector<User>& users); 

    /**
     * @brief Charge le contenu du coffre-fort.
     * @param entries Vecteur à remplir par référence.
     */
    void loadVault(std::vector<PasswordEntry>& entries);
};

#endif // FILEMANAGER_H
