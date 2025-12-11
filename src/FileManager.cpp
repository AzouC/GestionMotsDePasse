#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

FileManager::FileManager() {}

void FileManager::saveUsers(const vector<User>& users) {
    ofstream file(userFile);
    if (file.is_open()) {
        for (const auto& u : users) {
            string line = u.username + "|" + u.passwordHash + "|" + u.salt + "|" + (u.isAdmin ? "1" : "0");
            file << security.encryptDecrypt(line) << endl;
        }
        file.close();
    }
}

void FileManager::saveVault(const vector<PasswordEntry>& entries) {
    ofstream file(vaultFile);
    if (file.is_open()) {
        for (const auto& entry : entries) {
            string line = entry.getOwner() + "|" + entry.getSiteName() + "|" + entry.getUsername() + "|" + entry.getPassword();
            file << security.encryptDecrypt(line) << endl;
        }
        file.close();
    }
}

bool FileManager::loadUsers(vector<User>& users) {
    ifstream file(userFile);
    if (!file.is_open()) return false; 

    users.clear();
    string line;
    while (getline(file, line)) {
        string decrypted = security.encryptDecrypt(line);
        stringstream ss(decrypted);
        string segment;
        vector<string> seglist;
        while(getline(ss, segment, '|')) seglist.push_back(segment);

        if (seglist.size() == 4) {
            User u;
            u.username = seglist[0];
            u.passwordHash = seglist[1];
            u.salt = seglist[2];
            u.isAdmin = (seglist[3] == "1");
            users.push_back(u);
        }
    }
    file.close();
    return (!users.empty());
}

void FileManager::loadVault(vector<PasswordEntry>& entries) {
    ifstream file(vaultFile);
    if (!file.is_open()) return;

    entries.clear();
    string line;
    while (getline(file, line)) {
        string decrypted = security.encryptDecrypt(line);
        stringstream ss(decrypted);
        string segment;
        vector<string> seglist;
        while(getline(ss, segment, '|')) seglist.push_back(segment);

        if (seglist.size() == 4) {
            PasswordEntry entry(seglist[0], seglist[1], seglist[2], seglist[3]);
            entries.push_back(entry);
        }
    }
    file.close();
}
