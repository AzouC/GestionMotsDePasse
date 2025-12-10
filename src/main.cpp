#include <iostream>
#include <string>
#include <limits>
#include "PasswordEntry.h"
#include "PasswordVault.h"
#include "SecurityManager.h"

using namespace std;

// Fonction pour nettoyer le buffer clavier
void viderBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    SecurityManager security;
    PasswordVault vault;

    // Variables de session
    string masterUsername = "";     // Nom d'utilisateur principal
    string masterPasswordHash = ""; // Hash du mot de passe maître
    string masterSalt = "";         // Sel unique
    
    bool compteCree = false;
    bool estConnecte = false;
    int choix = -1;

    while (choix != 0) {
        cout << "\n==============================================" << endl;
        cout << "   GESTIONNAIRE DE MOTS DE PASSE (BTS CIEL)" << endl;
        cout << "==============================================" << endl;

        // Affichage dynamique du menu
        if (!compteCree) {
            cout << "1. Creer un compte (Utilisateur & Mdp)" << endl;
        } else if (!estConnecte) {
            cout << "1. Se connecter" << endl;
        } else {
            cout << "Connecte en tant que : " << masterUsername << endl;
            cout << "----------------------------------------------" << endl;
            cout << "1. Ajouter un mot de passe" << endl;
            cout << "2. Lister les mots de passe" << endl;
            cout << "3. Modifier un mot de passe" << endl;
            cout << "4. Supprimer un mot de passe" << endl;
            cout << "5. Se deconnecter" << endl;
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
        case 0:
            cout << "Au revoir !" << endl;
            break;

        case 1:
            if (!compteCree) {
                // --- CRÉATION DE COMPTE ---
                cout << "Choisissez votre Nom d'utilisateur : ";
                getline(cin, masterUsername);

                cout << "Choisissez votre Mot de passe Maitre : ";
                string inputMdp;
                getline(cin, inputMdp);

                // Sécurisation
                masterSalt = security.generateSalt(16);
                masterPasswordHash = security.hashPassword(inputMdp, masterSalt);
                
                compteCree = true;
                cout << ">> Compte cree avec succes ! Connectez-vous maintenant." << endl;
            } 
            else if (!estConnecte) {
                // --- CONNEXION ---
                string inputUser, inputMdp;
                cout << "Nom d'utilisateur : ";
                getline(cin, inputUser);

                cout << "Mot de passe Maitre : ";
                getline(cin, inputMdp);

                // Vérification stricte : Nom d'utilisateur + Hash du MDP
                if (inputUser == masterUsername && 
                    security.verifyMasterPassword(inputMdp, masterPasswordHash, masterSalt)) {
                    estConnecte = true;
                    cout << ">> Connexion reussie !" << endl;
                } else {
                    cout << ">> Erreur : Identifiants incorrects." << endl;
                }
            } 
            else {
                // --- AJOUTER ---
                string site, user, pass;
                cout << "Nom du site : "; getline(cin, site);
                cout << "Identifiant sur le site : "; getline(cin, user);
                cout << "Mot de passe du site : "; getline(cin, pass);

                PasswordEntry entry(site, user, pass);
                vault.addEntry(entry);
                cout << ">> Entree ajoutee." << endl;
            }
            break;

        case 2: // --- LISTER ---
            if (estConnecte) vault.listEntries();
            break;

        case 3: // --- MODIFIER ---
            if (estConnecte) {
                vault.listEntries();
                cout << "Numero (ID) a modifier : ";
                int index;
                if (cin >> index) {
                    viderBuffer();
                    string site, user, pass;
                    cout << "Nouveau nom du site : "; getline(cin, site);
                    cout << "Nouvel identifiant : "; getline(cin, user);
                    cout << "Nouveau mot de passe : "; getline(cin, pass);
                    
                    PasswordEntry updatedEntry(site, user, pass);
                    vault.updateEntry(index, updatedEntry);
                } else {
                    viderBuffer();
                    cout << "Saisie invalide." << endl;
                }
            }
            break;

        case 4: // --- SUPPRIMER ---
            if (estConnecte) {
                vault.listEntries();
                cout << "Numero (ID) a supprimer : ";
                int index;
                if (cin >> index) {
                    vault.deleteEntry(index);
                } else {
                    viderBuffer();
                    cout << "Saisie invalide." << endl;
                }
            }
            break;

        case 5: // --- DÉCONNEXION ---
            if (estConnecte) {
                estConnecte = false;
                cout << ">> Deconnexion..." << endl;
            }
            break;

        default:
            cout << "Choix inconnu." << endl;
            break;
        }
    }

    return 0;
}
