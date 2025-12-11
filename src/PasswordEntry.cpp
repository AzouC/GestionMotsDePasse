#include "PasswordEntry.h"

using namespace std;

PasswordEntry::PasswordEntry() {
    this->owner = "";
    this->siteName = "";
    this->username = "";
    this->password = "";
}

PasswordEntry::PasswordEntry(string owner, string site, string user, string pass) {
    this->owner = owner;
    this->siteName = site;
    this->username = user;
    this->password = pass;
}

string PasswordEntry::getSiteName() const { return this->siteName; }
string PasswordEntry::getUsername() const { return this->username; }
string PasswordEntry::getPassword() const { return this->password; }
string PasswordEntry::getOwner() const { return this->owner; }

void PasswordEntry::setSiteName(string site) { this->siteName = site; }
void PasswordEntry::setUsername(string user) { this->username = user; }
void PasswordEntry::setPassword(string pass) { this->password = pass; }
void PasswordEntry::setOwner(string owner) { this->owner = owner; }
