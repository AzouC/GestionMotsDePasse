#ifndef SECURITYMANAGER_H
#define SECURITYMANAGER_H

#include <string>

class SecurityManager {
public:
    SecurityManager();
    
    // Génère un sel aléatoire
    std::string generateSalt(int length);
    
    // Hache le mot de passe
    std::string hashPassword(const std::string& password, const std::string& salt);

    // Vérifie si un mot de passe correspond au hash stocké
    bool verifyMasterPassword(const std::string& inputPassword, const std::string& storedHash, const std::string& storedSalt);
};

#endif // SECURITYMANAGER_H
