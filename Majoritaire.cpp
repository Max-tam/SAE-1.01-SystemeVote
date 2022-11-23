/*
auteur: Maxime TAMARIN
dernière modification: 22/11/2022
*/

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

ofstream ofs;
ifstream ifs;


vector <int> vote(const vector <string> & jeuxCandidat,const vector <string> & votant)
{
    int indiceVotant = 0; // indice qui permet de faire passer tout les votants
    int candidatVote; // correspond au numero de placement dans la liste du jeux choisi
    vector <int> resultat; // tableau contenant les résulats ou le resultat resultat[i] se rapporte au candidat candidat[i]
    resultat.resize(jeuxCandidat.size()); // initialisation de la longueur à la même que cel du tableau candidat
    while (true) // boucle infini
    {
        if ( indiceVotant >= votant.size()) break; // condition de sortie de la boucle infini
        cout << "\n\n---| choix du jeux |---\n\n";
        for (size_t i = 0; i < jeuxCandidat.size(); ++i)
        {
            cout << jeuxCandidat[i] << " : " << i << endl; // affichage du jeux candidat et de son indice (place) attribué
        }
        cout << "\nparmi les jeux suivant quel est le meilleur ?\n\n"<< votant[indiceVotant]<< " -> ";
        cin >> candidatVote; // choix de l'utilisateur du jeux par son indice
        if (candidatVote < jeuxCandidat.size()) // condition si l'indice correspond bien à la liste donné (pour éviter des erreurs de dépassement) (vote non pris en compte sinon)
        {
            resultat[candidatVote] = resultat[candidatVote] + 1; // ajoute une voie au jeux choisi
        }
        ++indiceVotant;
    }
    cout << "\n\n---| Resultat du vote |---\n\n";
    for (size_t i = 0; i < jeuxCandidat.size() ; ++i)
    {
        cout << jeuxCandidat[i] << " : " << resultat[i] << endl; // affiche les jeux et le nombres de voies attribué à la fin du vote
    }
    return resultat;
}

string systemeMajoritaire(const vector <int> & resultat, const vector <string> & jeuxCandidat) //fonction du Vote par Scrutin uninominal majoritaire à un tour (renvoie le nom du gagnant)
{
    string gagnant = jeuxCandidat[0]; // c'est cette variable que l'on va renvoyer à la fin. Elle nous sert aussi pour comparé les resultats
    int indiceGagnant = 0;
    int egalite = 0; // variable pour savoir si il y a égalité. 0 = non et 1 = oui
    for (size_t i = 1; i < resultat.size(); ++i)
    {
        if (resultat[indiceGagnant] < resultat[i]) //permet d'avoir le jeux avec le plus de vote
        {
            gagnant = jeuxCandidat[i];
            indiceGagnant = i;
            egalite = 0; // quand on change de gagnant alors l'égalité si elle à lieu avant est retiré
        }
        else if(resultat[indiceGagnant] == resultat[i]) egalite = 1; // détecte si il y a une égalité
    }
    if (egalite == 1) return "egalite"; // si il y a égalité
    return gagnant; // si il n'y en a pas
}

void AnalyseEntree()
{
    string ligneFichier;
    int nombreTeste; // ligne 1
    getline(cin,ligneFichier);
    nombreTeste = ligneFichier.size(); //le nombre de caractère sur la première ligne = nombre de teste
    string nom;
    string prenom;
    vector <string> vNomPrenom; // ligne 2 - n
    while (true)
    {
        getline(cin,nom);
        if ( nom == "f" || cin.eof()) break; // pourquoi pas de prise en compte du contenue de la ligne avant la fin ?
        getline(cin,prenom);
        vNomPrenom.resize(vNomPrenom.size()+1);
        vNomPrenom[vNomPrenom.size()-1] = nom + " " + prenom;
        cout << vNomPrenom[vNomPrenom.size()-1] << endl;
    }
    vector <string> candidat = { "Counter strike", "Street Fighter II","Civilization VI","Mario Kart"}; // initialisation de la liste des jeux candidats
    for (int i = 0; i < nombreTeste; ++i) // suite à verifier (de ici)
    {
        vector <int> resultatVote (candidat.size());
        resultatVote = vote(candidat,vNomPrenom);
        for (int j = 0; j < 4; ++j)
        {
            getline(cin,ligneFichier);
            if (stoi(ligneFichier) == resultatVote[j])
                cout << "passe" << endl;
            else
                cout << "faux"; // à ici
        }
    }
}

int main()
{
    AnalyseEntree();
    return 0;
//    vector <string> votants = votant();
//    resultatVote = vote(candidat,votants); // fonction pour enregistrer les votes manuellement
//    string gagnant = systemeMajoritaire(resultatVote,candidat); // fonction de calcul automatique des résultats du systeme Majoritaire
//    if (gagnant == "egalite")
//    {
//        cout << "\n\nPersonne n'a gagné. Il y a égalité" << endl; // si il y a égalité
//    }
//    else
//    {
//        cout << "\n\nLe gagnant du vote par systeme Majoritaire est " << gagnant << endl; // si il n'y a pas égalité
//    }
}
