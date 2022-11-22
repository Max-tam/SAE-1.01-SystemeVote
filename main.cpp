/*
auteur: Maxime TAMARIN
dernière modification: 21/11/2022
*/

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

ofstream ofs;
ifstream ifs;

vector <string> votant() // construit un vector string contenant le nom prenom par case
{
    string nom;
    string prenom;
    vector <string> vNomPrenom;
    int nligne = 0; // ligne 0 = nom, ligne 1 = prenom, ligne 2 = nom,...
    ifs.open("votants.txt"); // ouvre le fichier de la liste des votants
    while (true) // boucle pour lire le fichier du début à la fin
    {
        if (ifs.eof()) break; // sortie si fin du fichier
        if (nligne % 2 == 0) // si le reste donne 0 c'est la ligne du nom
            getline(ifs,nom);
        else // sinon c'est la ligne du prénom
        {
            getline(ifs,prenom);
            vNomPrenom.resize(vNomPrenom.size()+1); // redimensionne à taille
            vNomPrenom[vNomPrenom.size()-1] = nom + " " + prenom; // met nom prenom dans le vector
//            cout << vNomPrenom[vNomPrenom.size()-1] << endl; //verifiation des cases du tableau
        }
        ++nligne; // ligne suivante du fichier "votants.txt"
    }
    ifs.close();
    return vNomPrenom;
}

vector <int> vote(const vector <string> & jeuxCandidat,const vector <string> & votant, const vector <int> & voteDesVotants)
{
    int indiceVotant = 0; // indice qui permet de faire passer tout les votants
    int candidatVote; // correspond au numero de placement dans la liste du jeux choisi
    vector <int> resultat; // tableau contenant les résulats ou le resultat resultat[i] se rapporte au candidat candidat[i]
    resultat.resize(jeuxCandidat.size()); // initialisation de la longueur à la même que cel du tableau candidat
    cout << "\n\n---| choix du jeux |---\n\n";
    for (size_t i = 0; i < jeuxCandidat.size(); ++i)
    {
        cout << jeuxCandidat[i] << " : " << i << endl; // affichage du jeux candidat et de son indice (place) attribué
    }
    cout << "---------------------\n\n";
    while (true) // boucle infini
    {
        if ( indiceVotant >= votant.size()) break; // condition de sortie de la boucle infini
        cout << votant[indiceVotant]<< " -> " << voteDesVotants[indiceVotant] << endl;
        candidatVote = voteDesVotants[indiceVotant]; // choix de l'utilisateur du jeux par son indice
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

int testeOracle() // methode d'analyse du fichier teste oracle
{
    vector <string> candidat = { "Counter strike", "Street Fighter II","Civilization VI","Mario Kart"};
    vector <string> votants = votant();
    string ligneFichierOracle;
    ifs.open("testeOracle.txt"); //ouvre le fichier de comparaison
    while (true) //boucle infinie
    {
        if (ifs.eof()) break; // condition si fin de fichier
        getline(ifs,ligneFichierOracle);
        if (ligneFichierOracle == "systemeMajoritaire")
        {
            vector <int> voteDesVotants;
            getline(ifs,ligneFichierOracle);
            while (ligneFichierOracle != "finVote")
            {
                voteDesVotants.resize(voteDesVotants.size()+1);
                voteDesVotants[voteDesVotants.size()-1] =  stoi(ligneFichierOracle); // conversion string -> int
//                cout << voteDesVotants[voteDesVotants.size()-1] << endl; // teste (a supp)
                getline(ifs,ligneFichierOracle);
            }
            vote(candidat,votants,voteDesVotants); // lance la méthode pour prendre en compte les votes
        }
    }
    ifs.close();
    return 1;
}

int main()
{
//    cout << "\n\n=====| Vote par Scrutin uninominal majoritaire à un tour |=====\n\n";

//    vector <string> candidat = { "Counter strike", "Street Fighter II","Civilization VI","Mario Kart"}; // initialisation de la liste des jeux candidats
//    vector <int> resultatVote (candidat.size());
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
    testeOracle();
    return 0;
}
