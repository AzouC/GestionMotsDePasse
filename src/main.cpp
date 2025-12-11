/**
 * @file main.cpp
 * @brief Point d'entrée de l'application "Gestionnaire de Mots de Passe".
 * @author Malo
 * @version 2.0 (Version Finale)
 * * Ce fichier contient la boucle principale, le menu en mode console (CLI)
 * et l'orchestration entre les composants (Vault, Security, File).
 */

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "PasswordEntry.h"
#include "PasswordVault.h"
#include "SecurityManager.h"
#include "FileManager.h"

using namespace std;

void viderBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    SecurityManager security;
    PasswordVault vault;
    FileManager fileManager;
    
    vector<User> users;
    User* currentUser = nullptr; 
    bool estConnecte = false;
    int choix = -1;

    // --- CHARGEMENT ---
    cout << "=== CHARGEMENT DU SYSTEME ===" << endl;
    if (fileManager.loadUsers(users)) {
        cout << ">> Utilisateurs charges." << endl;
        vector<PasswordEntry> loadedVault;
        fileManager.loadVault(loadedVault);
        vault.loadEntries(loadedVault);
        cout << ">> Coffre charge." << endl;
    } else {
        cout << ">> Premier lancement : Creation ADMIN." << endl;
        string adminName, adminPass;
        cout << "Nom admin : "; getline(cin, adminName);
        cout << "Pass admin : "; getline(cin, adminPass); 
        
        string s = security.generateSalt(16);
        string h = security.hashPassword(adminPass, s);
        users.push_back({adminName, h, s, true});
        
        fileManager.saveUsers(users);
        cout << ">> Admin sauvegarde !" << endl;
    }

    // --- BOUCLE ---
    while (choix != 0) {
        cout << "\n==============================================" << endl;
        cout << "   GESTIONNAIRE PERSISTANT (2025)" << endl;
        cout << "==============================================" << endl;

        if (!estConnecte) {
            cout << "1. Se connecter" << endl;
        } else {
            cout << "Connecte : " << currentUser->username;
            if (currentUser->isAdmin) cout << " [ADMIN]";
            cout << endl;
            cout << "----------------------------------------------" << endl;
            cout << "1. Ajouter un mot de passe" << endl;
            cout << "2. Lister les mots de passe" << endl;
            cout << "3. Modifier un mot de passe" << endl;
            cout << "4. Supprimer un mot de passe" << endl;
            cout << "5. Outil : Generer un mot de passe" << endl;
            
            if (currentUser->isAdmin) {
                cout << "--- ADMINISTRATION ---" << endl;
                cout << "8. Creer un nouvel utilisateur" << endl;
                cout << "9. Voir la liste des utilisateurs" << endl;
            }
            cout << "6. Se deconnecter" << endl;
        }
        cout << "0. Quitter" << endl;
        cout << "Votre choix : ";
        
        if (!(cin >> choix)) {
            cout << "Erreur de saisie." << endl;
            viderBuffer();
            continue;
        }
        viderBuffer();

        switch (choix) {
        case 0: cout << "Au revoir !" << endl; break;

        case 1: 
            if (!estConnecte) {
                string uName, uPass;
                cout << "Utilisateur : "; getline(cin, uName);
                cout << "Mot de passe : "; getline(cin, uPass);

                bool loginSuccess = false;
                for (auto &u : users) {
                    if (u.username == uName) {
                        if (security.verifyMasterPassword(uPass, u.passwordHash, u.salt)) {
                            currentUser = &u;
                            estConnecte = true;
                            loginSuccess = true;
                            cout << ">> Connexion reussie !" << endl;
                        }
                    }
                }
                if (!loginSuccess) cout << ">> Echec connexion." << endl;
            } 
            else {
                // AJOUT
                string site, uLogin, pass;
                cout << "Site : "; getline(cin, site);
                cout << "Login : "; getline(cin, uLogin);
                
                cout << "Utiliser un MDP fort (24 car., Recommandation ANSSI) ? (1:Oui / 0:Non) : ";
                int sugg;
                if (cin >> sugg && sugg == 1) {
                     viderBuffer();
                     pass = security.generateRandomPassword(24);
                     cout << "---------------------------------------" << endl;
                     cout << ">> Genere : " << pass << endl;
                     cout << "---------------------------------------" << endl;
                } else {
                    viderBuffer();
                    bool isStrong = false;
                    do {
                        cout << "Mot de passe (Min 16, Complexe) : "; getline(cin, pass);
                        isStrong = security.checkPasswordStrength(pass);
                        if (!isStrong) cout << ">> REFUSE (Norme ANSSI)." << endl;
                    } while (!isStrong);
                }

                PasswordEntry entry(currentUser->username, site, uLogin, pass);
                vault.addEntry(entry);
                fileManager.saveVault(vault.getAllEntries());
                cout << ">> Sauvegarde OK." << endl;
            }
            break;

        case 2: // LISTER (AVEC REVELATION SECURISEE)
            if (estConnecte) {
                // 1. Affichage masqué par défaut
                vault.listEntries(currentUser->username, currentUser->isAdmin, false);
                
                cout << "\n----------------------------------------------" << endl;
                cout << "Voulez-vous reveler les mots de passe ? (1:Oui / 0:Non) : ";
                int reveal;
                if (cin >> reveal && reveal == 1) {
                    viderBuffer();
                    
                    // 2. Vérification du Master Password
                    cout << ">> SECURITE : Veuillez confirmer votre Mot de Passe Maitre : ";
                    string confirmPass;
                    getline(cin, confirmPass);
                    
                    if (security.verifyMasterPassword(confirmPass, currentUser->passwordHash, currentUser->salt)) {
                        cout << "\n>> Identite confirmee. Affichage en clair..." << endl;
                        vault.listEntries(currentUser->username, currentUser->isAdmin, true);
                    } else {
                        cout << ">> ERREUR : Mot de passe incorrect. Acces refuse." << endl;
                    }
                } else {
                    viderBuffer();
                }
            }
            break;

        case 3: // MODIFIER
            if (estConnecte) {
                vault.listEntries(currentUser->username, currentUser->isAdmin, false);
                cout << "ID a modifier : ";
                int idx;
                if (cin >> idx) {
                    viderBuffer();
                    string site, uLogin, pass;
                    cout << "Site : "; getline(cin, site);
                    cout << "User : "; getline(cin, uLogin);
                    
                    cout << "Generer nouveau MDP (24 car., ANSSI) ? (1:Oui / 0:Non) : ";
                    int sugg;
                    if (cin >> sugg && sugg == 1) {
                         viderBuffer();
                         pass = security.generateRandomPassword(24);
                         cout << ">> Genere : " << pass << endl;
                    } else {
                        viderBuffer();
                        bool isStrong = false;
                        do {
                            cout << "Nouveau Pass (Min 16, Complexe) : "; getline(cin, pass);
                            isStrong = security.checkPasswordStrength(pass);
                            if (!isStrong) cout << ">> REFUSE (Norme ANSSI)." << endl;
                        } while (!isStrong);
                    }
                    
                    PasswordEntry updated(currentUser->username, site, uLogin, pass);
                    vault.updateEntry(idx, updated);
                    fileManager.saveVault(vault.getAllEntries());
                } else viderBuffer();
            }
            break;

        case 4: // SUPPRIMER
            if (estConnecte) {
                vault.listEntries(currentUser->username, currentUser->isAdmin, false);
                cout << "ID a supprimer : ";
                int idx;
                if (cin >> idx) {
                    vault.deleteEntry(idx);
                    fileManager.saveVault(vault.getAllEntries());
                } else viderBuffer();
            }
            break;

        case 5: // OUTIL
            if (estConnecte) cout << "Resultat : " << security.generateRandomPassword(24) << endl;
            break;

        case 6: // DECO
            if (estConnecte) {
                estConnecte = false;
                currentUser = nullptr;
                cout << ">> Deconnexion." << endl;
            }
            break;

        case 8: // CREER USER
            if (estConnecte && currentUser->isAdmin) {
                string newName, newPass;
                cout << "Nom utilisateur : "; getline(cin, newName);
                
                cout << "Generer un mot de passe initial fort (24 car., ANSSI) ? (1:Oui / 0:Non) : ";
                int sugg;
                if (cin >> sugg && sugg == 1) {
                     viderBuffer();
                     newPass = security.generateRandomPassword(24);
                     cout << "---------------------------------------" << endl;
                     cout << ">> MDP Initial Genere : " << newPass << endl;
                     cout << "---------------------------------------" << endl;
                } else {
                    viderBuffer();
                    bool isStrong = false;
                    do {
                        cout << "Saisir MDP Initial (Min 16, Complexe) : "; getline(cin, newPass);
                        isStrong = security.checkPasswordStrength(newPass);
                        if (!isStrong) cout << ">> REFUSE (Norme ANSSI)." << endl;
                    } while (!isStrong);
                }
                
                string s = security.generateSalt(16);
                string h = security.hashPassword(newPass, s);
                
                string adminName = currentUser->username;
                users.push_back({newName, h, s, false});
                
                for(auto &u : users) { if(u.username == adminName) { currentUser = &u; break; } }
                
                fileManager.saveUsers(users);
                cout << ">> Utilisateur cree." << endl;
            }
            break;

        case 9: // LISTE USERS
             if (estConnecte && currentUser->isAdmin) {
                 for(const auto& u : users) cout << "- " << u.username << endl;
             }
             break;

        default: cout << "Inconnu." << endl; break;
        }
    }
    return 0;
}
