#ifndef PASSWORDENTRY_H
#define PASSWORDENTRY_H

#include <string>

class PasswordEntry {
private:
    // Attributs privés (Encapsulation)
    // "Chaque entrée inclut un nom de site, un nom d'utilisateur et le mot de passe associé."
    std::string siteName;
    std::string username;
    std::string password;

public:
    // Constructeur par défaut
    PasswordEntry();

    // Constructeur surchargé (pour créer une entrée complète directement)
    PasswordEntry(std::string site, std::string user, std::string pass);

    // Accesseurs (Getters) - pour lire les valeurs
    std::string getSiteName() const;
    std::string getUsername() const;
    std::string getPassword() const;

    // Mutateurs (Setters) - pour modifier les valeurs si besoin
    void setSiteName(std::string site);
    void setUsername(std::string user);
    void setPassword(std::string pass);
};

#endif // PASSWORDENTRY_H
