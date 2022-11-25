/*
auteur: Maxime TAMARIN
dernière modification: 24/11/2022
*/

#include <iostream>
#include <vector>

using namespace std;

vector <int> vote(const vector <string> & jeuxCandidat,const vector <string> & votant)
{
    unsigned indiceVotant = 0; // indice qui permet de faire passer tout les votants
    string candidatVote; // correspond au numero de placement dans la liste du jeux choisi (au départ il est sous forme de string
    vector <int> resultat; // tableau contenant les résulats ou le resultat resultat[i] se rapporte au candidat candidat[i]
    resultat.resize(jeuxCandidat.size()); // initialisation de la longueur à la même que cel du tableau candidat
    while (true) // boucle infini
    {
        if ( indiceVotant >= votant.size()) break; // condition de sortie de la boucle infini
        getline(cin,candidatVote);// choix de l'utilisateur du jeux par son indice
        if (stoi(candidatVote) < jeuxCandidat.size()) // condition si l'indice correspond bien à la liste donné (pour éviter des erreurs de dépassement) (vote non pris en compte sinon)
        {
            resultat[stoi(candidatVote)] = resultat[stoi(candidatVote)] + 1; // ajoute une voie au jeux choisi
        }
        ++indiceVotant;
    }
    cout << "\n---| Resultat du vote |---\n\n";
    for (size_t i = 0; i < jeuxCandidat.size() ; ++i)
    {
        cout << jeuxCandidat[i] << " : " << resultat[i] << endl; // affiche les jeux et le nombres de voies attribué à la fin du vote
    }
    return resultat; // renvoie un vector contenant les resultats du vote
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
    if (egalite == 1)
    {
        cout << "\nil n'y a pas de vainqueur" << endl;
        return "egalite"; // si il y a égalité
    }
    else
        cout << "\nLe gagnant est "<<gagnant << endl;
    return gagnant; // si il n'y en a pas
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
    while (true) // enregistre tout les votants
    {
        getline(cin,nom);
        if ( nom == "f" || cin.eof()) break; // condition de sorti (cin.eof() en cas de bug de la première
        getline(cin,prenom);
        vNomPrenom.resize(vNomPrenom.size()+1); // redimensionne à taille +1 le tableau
        vNomPrenom[vNomPrenom.size()-1] = nom + " " + prenom; // chaque case = Nom Prenom
    }
    vector <string> candidat = { "Counter strike", "Street Fighter II","Civilization VI","Mario Kart"}; // initialisation de la liste des jeux candidats
    for (int i = 0; i < nombreTeste; ++i) // suite à verifier (de ici)
    {
        vector <int> resultatVote (candidat.size());
        resultatVote = vote(candidat,vNomPrenom); // utilisation fonction vote
        for (int j = 0; j < 4; ++j) // parcour les résultats
        {
            getline(cin,ligneFichier);
            if (stoi(ligneFichier) != resultatVote[j]) // stoi() convertion string --> int
                return -1; // si resultat correspond pas au attente retourne -1
        }
        string nomGagnant;
        nomGagnant = systemeMajoritaire(resultatVote,candidat); // utilise fonction systemeMajoritaire
        getline(cin,ligneFichier);
        if (ligneFichier != nomGagnant)
            return -1; //si gagnant correspond pas au attente retourne -1
    }
    return 1;
}

int main()
{
    AnalyseEntree();
    return 0;
}
