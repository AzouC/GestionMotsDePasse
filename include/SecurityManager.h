#ifndef SECURITYMANAGER_H
#define SECURITYMANAGER_H

#include <string>

class SecurityManager {
public:
    SecurityManager();
    
    // Génère une chaîne aléatoire de taille donnée
    std::string generateSalt(int length);
    
    // Hache le mot de passe avec le sel fourni
    std::string hashPassword(const std::string& password, const std::string& salt);
};

#endif // SECURITYMANAGER_H
