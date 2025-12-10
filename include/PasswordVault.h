#ifndef PASSWORDVAULT_H
#define PASSWORDVAULT_H

#include <vector>
#include "PasswordEntry.h"

class PasswordVault {
private:
    std::vector<PasswordEntry> entries;

public:
    PasswordVault();

    void addEntry(const PasswordEntry& entry);
    void deleteEntry(int index);
    
    // Méthode de mise à jour (Update)
    void updateEntry(int index, const PasswordEntry& newEntry);

    void listEntries() const;
    int size() const;
};

#endif // PASSWORDVAULT_H
