#include <iostream>
#include <vector>

using namespace std;

vector <unsigned> SystemeParApprobation(vector <unsigned> & resultatVote, const vector<string> jeuxCandidat)
{
    string vote;
    while (true) { // parcourir les votes
        getline(cin, vote);
        if (vote == "-----" || cin.eof()) break;
        for (size_t i(0) ; i < vote.size() ; ++i) { // si valeur = 1, le votant a voté pour le candidat
            if (vote[i] == '1') {
                resultatVote[i] += 1;
            }
        }
    }
    cout << "\n---| Resultat du vote |---\n\n";
    for (size_t i = 0; i < jeuxCandidat.size() ; ++i)
    {
        cout << jeuxCandidat[i] << " : " << resultatVote[i] << endl; // affiche les jeux et le nombres de voies attribué à la fin du vote
    }
    return resultatVote;
}

void TrouverGagnant(const vector <unsigned> & resultat, const vector <string> & jeuxCandidat)
// Renvoie le nom du gagnant ou des gagnants si égalité
{
    vector<string> gagnants; // c'est cette variable que l'on va renvoyer à la fin. Elle nous sert aussi pour comparé les resultats
    unsigned indiceGagnant (0);
    for (size_t i (0) ; i < resultat.size(); ++i)
    {
        if (resultat[indiceGagnant] < resultat[i]) //permet d'avoir le jeux avec le plus de vote
        {
            indiceGagnant = i;
        }
    }
    for (unsigned i (indiceGagnant) ; i < resultat.size() ; ++i) {
        if (resultat[i] == resultat[indiceGagnant]) {
            gagnants.push_back(jeuxCandidat[i]);
        }
    }
    if (gagnants.size() == 1)
    {
        cout << "\nLe gagnant est " << gagnants[0] << endl;
    }
    else {
        cout << "\nLes gagnants sont ";
        for (unsigned i (0) ; i < gagnants.size() ; ++i) {
            cout << gagnants[i];
            if (i != gagnants.size()-1) {
                cout << ", ";
            }
        }
    }
}

void AnalyseEntree()
{
    string ligneFichier;
    unsigned nombreTest; // ligne 1
    getline(cin,ligneFichier);
    nombreTest = stoi(ligneFichier); //le nombre sur la première ligne = nombre de test
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
    }
    vector <string> jeuCandidat = { "Counter strike", "Street Fighter II","Civilization VI","Mario Kart"}; // initialisation de la liste des jeux candidats
    vector <unsigned> resultatVote;
    for (unsigned i = 0; i < nombreTest; ++i) // parcours le nb de set d'entrées
    {
        resultatVote.resize(jeuCandidat.size());
        fill(resultatVote.begin(), resultatVote.end(),0);
        resultatVote = SystemeParApprobation(resultatVote, jeuCandidat);
        TrouverGagnant(resultatVote, jeuCandidat);
    }
}

int main()
{
    AnalyseEntree();
    return 0;
}
