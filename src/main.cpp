#include <iostream>
#include <string>
#include <limits> // Nécessaire pour vider le buffer cin sous Windows

// Inclusion des en-têtes de vos classes
#include "PasswordEntry.h"
#include "PasswordVault.h"
#include "SecurityManager.h"

using namespace std;

// Fonction utilitaire pour nettoyer le buffer d'entrée (problème fréquent sous Windows après un cin >> int)
void viderBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    // Instanciation des gestionnaires
    SecurityManager security;
    PasswordVault vault;

    // Variables pour la session utilisateur
    string masterPasswordHash = ""; // Stockera l'empreinte du mot de passe maître
    string masterSalt = "";         // Stockera le sel unique
    bool compteCree = false;        // Pour savoir si l'utilisateur a déjà configuré son compte
    bool estConnecte = false;       // État de connexion [cite: 423]
    int choix = -1;

    // --- Boucle principale du programme ---
    while (choix != 0) {
        cout << "\n==============================================" << endl;
        cout << "   APPLICATION GESTION MOTS DE PASSE" << endl;
        cout << "==============================================" << endl;

        // Affichage dynamique du menu selon l'état [cite: 423, 424]
        if (!compteCree) {
            cout << "1. Creer un compte (Master Password)" << endl;
        } else if (!estConnecte) {
            cout << "1. Se connecter" << endl;
        } else {
            // Options disponibles uniquement si connecté [cite: 424]
            cout << "1. Ajouter un mot de passe" << endl;
            cout << "2. Lister les mots de passe" << endl;
            cout << "3. Supprimer un mot de passe" << endl;
            cout << "4. Se deconnecter" << endl;
        }
        cout << "0. Quitter" << endl;
        cout << "Votre choix : ";
        
        if (!(cin >> choix)) { // Gestion erreur de saisie non numérique
            cout << "Erreur : Veuillez entrer un nombre." << endl;
            viderBuffer();
            continue;
        }
        viderBuffer(); // Consommer le retour à la ligne restant

        // --- Traitement des actions ---
        switch (choix) {
        case 0:
            cout << "Fermeture de l'application..." << endl;
            break;

        case 1:
            if (!compteCree) {
                // --- Création de compte [cite: 417] ---
                cout << "Definition du mot de passe Maitre : ";
                string inputMdp;
                getline(cin, inputMdp);

                // Sécurisation : Génération du sel et hachage [cite: 590, 628]
                masterSalt = security.generateSalt(16); 
                masterPasswordHash = security.hashPassword(inputMdp, masterSalt);
                
                compteCree = true;
                cout << "Compte cree avec succes ! Vous pouvez maintenant vous connecter." << endl;
            } 
            else if (!estConnecte) {
                // --- Connexion [cite: 423] ---
                cout << "Entrez votre mot de passe Maitre : ";
                string inputMdp;
                getline(cin, inputMdp);

                // Vérification : on re-hache la saisie avec le sel stocké 
                string attemptHash = security.hashPassword(inputMdp, masterSalt);

                if (attemptHash == masterPasswordHash) {
                    estConnecte = true;
                    cout << "Connexion reussie !" << endl;
                } else {
                    // Gestion d'erreur [cite: 426]
                    cout << "Erreur : Mot de passe incorrect." << endl;
                }
            } 
            else {
                // --- Ajouter une entrée (Si connecté) [cite: 418] ---
                string site, user, pass;
                cout << "Nom du site : ";
                getline(cin, site);
                cout << "Nom utilisateur : ";
                getline(cin, user);
                cout << "Mot de passe : ";
                getline(cin, pass);

                // Création de l'objet et ajout au vecteur via le Vault
                PasswordEntry nouvelleEntree(site, user, pass);
                vault.addEntry(nouvelleEntree);
                cout << "Entree ajoutee !" << endl;
            }
            break;

        case 2:
            if (estConnecte) {
                // --- Lister les tâches [cite: 424] ---
                cout << "\n--- Liste de vos mots de passe ---" << endl;
                vault.listEntries(); // Cette méthode doit faire les cout des entrées
            } else {
                cout << "Option invalide." << endl;
            }
            break;

        case 3:
            if (estConnecte) {
                // --- Supprimer une entrée [cite: 418] ---
                cout << "\n--- Suppression ---" << endl;
                // On affiche d'abord la liste pour que l'utilisateur choisisse un index
                vault.listEntries(); 
                
                cout << "Entrez le numero (index) a supprimer : ";
                int index;
                if (cin >> index) {
                    // Attention : gérer le décalage d'index (utilisateur tape 1, vecteur attend 0) 
                    // si votre affichage commence à 1. Sinon, passer l'index direct.
                    vault.deleteEntry(index); 
                    cout << "Entree supprimee." << endl;
                } else {
                    cout << "Saisie invalide." << endl;
                    viderBuffer();
                }
            } else {
                cout << "Option invalide." << endl;
            }
            break;

        case 4:
            if (estConnecte) {
                // --- Déconnexion [cite: 424] ---
                estConnecte = false;
                cout << "Vous etes deconnecte." << endl;
            } else {
                cout << "Option invalide." << endl;
            }
            break;

        default:
            cout << "Choix non reconnu." << endl;
            break;
        }
    }

    return 0;
}
