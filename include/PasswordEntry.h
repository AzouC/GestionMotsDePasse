#ifndef PASSWORDENTRY_H
#define PASSWORDENTRY_H

#include <string>

class PasswordEntry {
private:
    std::string siteName;
    std::string username;
    std::string password;

public:
    PasswordEntry();
    PasswordEntry(std::string site, std::string user, std::string pass);

    std::string getSiteName() const;
    std::string getUsername() const;
    std::string getPassword() const;

    void setSiteName(std::string site);
    void setUsername(std::string user);
    void setPassword(std::string pass);
};

#endif // PASSWORDENTRY_H
