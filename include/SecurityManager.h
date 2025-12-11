/**
 * @file SecurityManager.h
 * @brief Moteur cryptographique et gestion de la conformité ANSSI.
 * @author Malo
 * @details Utilise la bibliothèque OpenSSL pour les primitives cryptographiques.
 */

#ifndef SECURITYMANAGER_H
#define SECURITYMANAGER_H

#include <string>

/**
 * @struct User
 * @brief Structure de données représentant un utilisateur enregistré.
 */
struct User {
    std::string username;     ///< Nom d'utilisateur unique
    std::string passwordHash; ///< Empreinte SHA-256 du mot de passe
    std::string salt;         ///< Sel aléatoire unique (protection Rainbow Tables)
    bool isAdmin;             ///< Droits d'administration
};

/**
 * @class SecurityManager
 * @brief Gère toutes les opérations de sécurité (Hachage, Aléa, Chiffrement).
 */
class SecurityManager {
public:
    SecurityManager();
    
    /**
     * @brief Génère un sel cryptographique aléatoire.
     * @details Utilise RAND_bytes d'OpenSSL pour garantir une entropie élevée.
     * @param length Longueur du sel souhaitée (recommandé : 16 octets).
     * @return Le sel sous forme de chaîne brute.
     */
    std::string generateSalt(int length);

    /**
     * @brief Calcule le hash SHA-256 d'un mot de passe salé.
     * @param password Le mot de passe en clair.
     * @param salt Le sel unique de l'utilisateur.
     * @return Une chaîne hexadécimale représentant le hash (64 caractères).
     */
    std::string hashPassword(const std::string& password, const std::string& salt);

    /**
     * @brief Vérifie la validité d'un mot de passe maître.
     * @return true si le hash calculé correspond au hash stocké.
     */
    bool verifyMasterPassword(const std::string& inputPassword, const std::string& storedHash, const std::string& storedSalt);

    /**
     * @brief Générateur de mot de passe fort (Conformité ANSSI 2025).
     * @details Génère une chaîne d'au moins 24 caractères contenant obligatoirement :
     * - Majuscules
     * - Minuscules
     * - Chiffres
     * - Caractères spéciaux
     * Le tout est mélangé cryptographiquement.
     * @param length Longueur souhaitée (min 24).
     * @return Le mot de passe généré.
     */
    std::string generateRandomPassword(int length);

    /**
     * @brief Vérifie la robustesse (Hygiène numérique).
     * @param password Le mot de passe à analyser.
     * @return true si le mot de passe respecte la politique de sécurité (Min 16 chars + Complexité).
     */
    bool checkPasswordStrength(const std::string& password);

    /**
     * @brief Chiffrement/Déchiffrement symétrique simple (XOR).
     * @details Utilisé pour obfusquer les fichiers de sauvegarde (.dat) et empêcher
     * la lecture directe via un éditeur de texte.
     * @param data La chaîne à traiter.
     * @return La chaîne transformée.
     */
    std::string encryptDecrypt(const std::string& data); 
};

#endif // SECURITYMANAGER_H
