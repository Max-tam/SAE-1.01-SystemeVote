#include <iostream>
#include <vector>

using namespace std;

vector <int> vote(const vector <string> & jeuxCandidat, const vector <string> & votant)
{
    unsigned indiceVotant = 0; // indice qui permet de faire passer tout les votants
    string candidatVote; // correspond au numero de placement dans la liste du jeux choisi (au départ il est sous forme de string)
    vector <vector <int>> resultat; // matrice contenant les résulats du nombre de vote par préférence où le resultat resultat[i][j] se rapporte au candidat candidat[i]
    typedef vector <int> CVLine;
    typedef vector <CVLine> CMatrix;
    CMatrix classement; // mat
    resultat.resize (jeuxCandidat.size(), vector <int> (jeuxCandidat.size())); // Fixe le nombre de lignes et le nombre des colonnes
    vector <int> resF; // tableau contenant le nombre de points finals de chaque candidat
    resF.resize(jeuxCandidat.size()); // Fixe le nombre de case du tableau
    int quotient = jeuxCandidat.size(); // sert à multiplier le nombre de vote par préférence (*4 lorsque c'est le nombre de vote n°1)
    int point = 0; // variable permettant de calculer le nombre de points
    int point2 = 0;
    while (true) // boucle infini
    {
        if ( indiceVotant >= votant.size()) break; // condition de sortie de la boucle infini
        for (size_t i = 0; i < jeuxCandidat.size(); ++i)
        {
            getline(cin,candidatVote); // choix de l'utilisateur du jeux par son indice
            if (stoi(candidatVote) < jeuxCandidat.size()) // condition si l'indice correspond bien à la liste donné (pour éviter des erreurs de dépassement)
            {
                resultat[stoi(candidatVote)][i] = resultat[stoi(candidatVote)][i] +1 ; // ajoute une voie au jeux choisi
            }
        }
        ++indiceVotant;
    }
    /*cout << "\n\n---| Resultat du vote |---\n\n";
    for (size_t i = 0; i < jeuxCandidat.size() ; ++i)
    {
        cout << jeuxCandidat[i] << " :  ";
        for (size_t j = 0; j < jeuxCandidat.size() ; ++j){
            cout << resultat[i][j] << " "; // affiche les jeux et le nombres de voies attribué à la fin du vote
            if (j == jeuxCandidat.size()-1){
                cout << endl;
            }
        }

    }*/
    cout <<"\n---| comptage des points |---\n\n" ;
    for (size_t i = 0; i < jeuxCandidat.size() ; ++i)
    {
        for (size_t j = 0; j < jeuxCandidat.size() ; ++j){
            point = point + quotient * resultat[i][j];
            --quotient;
        }
        resF[i] = point;
        point2 = point;
        point = 0;
        quotient = jeuxCandidat.size();
        cout << jeuxCandidat[i] << " = " << resF[i] << endl;
    }
    return resF; // renvoie un vector contenant le résultat final du vote
}

string systemeParClassement(const vector <int> & resF, const vector <string> & jeuxCandidat)
{
    string gagnant = jeuxCandidat[0]; // c'est cette variable que l'on va renvoyer à la fin. Elle nous sert aussi pour comparer les resultats
    int indiceGagnant = 0;
    int max = 0;
    for (size_t i = 0; i < jeuxCandidat.size(); ++i)
    {
        if(resF[i] > max) //permet d'avoir le jeux avec le plus de points
        {
            max = resF[i];
            indiceGagnant = i;
            gagnant = jeuxCandidat[indiceGagnant];
        }
        else if(max == resF[i]){ // détermine s'il y a une égalité
            gagnant = "egalite";
        }
    }
    cout <<"\n---| annonce vainqueur |---\n\n" << "le vainqueur est : " << gagnant << endl;
    return gagnant;
}

int AnalyseEntree() // analyse le fichier en entrée et compare les résultats
{
    string ligneFichier;
    int nombreTeste; // ligne 1
    getline(cin,ligneFichier);
    nombreTeste = stoi(ligneFichier); //le nombre sur la première ligne = nombre de teste
    string nom;
    string prenom;
    vector <string> vNomPrenom; // ligne 2 - n
    while (true) // enregistre tous les votants
    {
        getline(cin,nom);
        if ( nom == "f" || cin.eof()) break; // pourquoi pas de prise en compte du contenue de la ligne avant la fin ?
        getline(cin,prenom);
        vNomPrenom.resize(vNomPrenom.size()+1);
        vNomPrenom[vNomPrenom.size()-1] = nom + " " + prenom; // chaque case = Nom Prenom
    }
    vector <string> candidat = { "Counter strike", "Street Fighter II","Civilization VI","Mario Kart"}; // initialisation de la liste des jeux candidats
    for (int i = 0; i < nombreTeste; ++i) // suite à verifier (de ici)
    {
        vector <int> resultatVote (candidat.size());
        resultatVote = vote(candidat,vNomPrenom); // utilisation fonction vote
        for (int j = 0; j < 4; ++j) // parcours les résultats
        {
            getline(cin,ligneFichier);
            if (stoi(ligneFichier) != resultatVote[j]) // stoi() convertion string --> int
            {
                return -1; // si le resultat correspond pas au attente retourne -1
            }
        }
        string nomGagnant;
        nomGagnant = systemeParClassement(resultatVote,candidat); // utilisation fonction systemeParClassement
        getline(cin,ligneFichier);
        if (ligneFichier != nomGagnant)
            return -1; // si gagnant correspond pas au attente retourne -1
    }
    return 1;
}

int main()
{
    AnalyseEntree();
    return 0;
}
