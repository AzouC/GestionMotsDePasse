/**
 * @file PasswordEntry.h
 * @brief Définition de la classe représentant une entrée de mot de passe.
 * @author Malo
 * @version 2.0
 * @date Decembre 2025
 */

#ifndef PASSWORDENTRY_H
#define PASSWORDENTRY_H

#include <string>

/**
 * @class PasswordEntry
 * @brief Représente une entrée unique dans le coffre-fort.
 * * Cette classe agit comme un conteneur de données (Data Object).
 * Elle stocke les informations relatives à un compte spécifique :
 * le site, l'identifiant, le mot de passe et le propriétaire de l'entrée.
 */
class PasswordEntry {
private:
    std::string siteName;   ///< Nom du site web ou du service (ex: "Google")
    std::string username;   ///< Identifiant de connexion sur le site
    std::string password;   ///< Mot de passe en clair (stocké uniquement en RAM)
    std::string owner;      ///< Nom de l'utilisateur propriétaire de cette entrée

public:
    /**
     * @brief Constructeur par défaut.
     * Initialise une entrée vide.
     */
    PasswordEntry();

    /**
     * @brief Constructeur complet.
     * @param owner Le nom de l'utilisateur créateur de l'entrée.
     * @param site Le nom du site web.
     * @param user L'identifiant de connexion.
     * @param pass Le mot de passe associé.
     */
    PasswordEntry(std::string owner, std::string site, std::string user, std::string pass);

    // --- Accesseurs (Getters) ---
    std::string getSiteName() const;  ///< Retourne le nom du site.
    std::string getUsername() const;  ///< Retourne l'identifiant.
    std::string getPassword() const;  ///< Retourne le mot de passe.
    std::string getOwner() const;     ///< Retourne le propriétaire (pour le filtrage).

    // --- Mutateurs (Setters) ---
    void setSiteName(std::string site);
    void setUsername(std::string user);
    void setPassword(std::string pass);
    void setOwner(std::string owner);
};

#endif // PASSWORDENTRY_H
