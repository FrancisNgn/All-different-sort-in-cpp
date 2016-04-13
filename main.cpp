#include <iostream>
#include <vector>
#include <malloc.h>

using namespace std;
void  echanger(vector<int> &tab, int maxi, int fin);
void triSelection(vector<int> & tableau);
void AfficherTab(vector<int> T);
void triBulle(vector<int> &tableau);
void triRapide(vector<int> & tableau);
void triFusion(vector<int> & tableau);
vector<int> SaisieTab();
int main()
{
    char choix;
    bool stop=false;
    cout << "Bonjour Entrer un tableau:" << endl;
    vector<int> res = SaisieTab();
    cout << "Votre Tableau: " ;
    AfficherTab(res);
    cout << "\n Faite le choix d une methode de tri:" <<endl;
    cout << "\t 1: Tri par selection; \n\t 2: Tri a bulle; \n\t 3: Tri a fusion; \n\t 4: Tri rapide; \n\t 0: Quiter;" ;
    while(!stop){
      cout << "\n Quelle est votre choix? $_";
      cin >> choix;
            switch(choix){
            case '1':
                {
                        triSelection(res);
                        cout << "\n"<<endl;
                        cout << "Tableau trie par selection: ";
                        AfficherTab(res);
                        break;
                }
            case '2':
                {
                        triBulle(res);
                        cout << "\n"<<endl;
                        cout << "Tableau trie a Bulle: ";
                        AfficherTab(res);
                        break;
                }
            case '3':
                {
                        triFusion(res);
                        cout << "\n"<<endl;
                        cout << "Tableau trie par fusion: ";
                        AfficherTab(res);
                        break;
                }
            case '4':
                {
                        triRapide(res);
                        cout << "\n"<<endl;
                        cout << "Tableau trie rapidemment: ";
                        AfficherTab(res);
                        break;
                }
            case '0': {stop = true;break;}
            default : cout << "\n Cette option n existe pas... ne soyer pas idiot svp!!! \n";
            }
    }


    return 0;
}
void AfficherTab(vector<int> T)
{
    for (int i=0 ; i< T.size() ; i++)
    cout << T[i] << " " ;
}

vector<int> SaisieTab()
{
    int taille ;
    cout << " Entrer une taille : " ;
    cin >> taille ;
    vector<int> res(taille,0) ;
    for (int i=0 ; i< taille ; i++) {
        cout << " val " << i+1 << " = " ;
        cin >> res[i] ;
    }
    return res ;
}
void  echanger(vector<int> &tab, int maxi, int fin){
    int tmp = tab[fin];
    tab[fin] = tab[maxi];
    tab[maxi] = tmp;

}
/*
* ICI LE TRI A SELECTION
*/
void triSelection(vector<int> & tableau)
{
    int i, maximum;
    int longueur = tableau.size();
    while(longueur>0)
    {
        // recherche de la plus grande valeur du tableau
        maximum = 0;
        for(i=1; i<longueur; i++)
        if(tableau[i]>tableau[maximum])
        maximum = i;
        // echange du maximum avec le dernier �l�ment
        echanger(tableau, maximum, longueur-1);
        // on traite le reste du tableau
        longueur--;
    }
}
/*
* ICI LE TRI A BULLE
*/
void triBulle(vector<int> &tableau)
{
    int i;
    int longueur= tableau.size();
    bool permutation;
    do
    {
        permutation = false;
        for(i=0; i<longueur-1; i++)
        {
            if(tableau[i]>tableau[i+1])
            {
                echanger(tableau, i, i+1);
                permutation = true;
            }
        }longueur--;
    }
    while(permutation);
}
/*
* ICI LE TRI RAPIDE
*/
int partition(vector<int> & tableau, const int debut, const int fin)
{
    int compteur = debut;
    int pivot = tableau[debut];
    int i;
    for(i=debut+1; i<=fin; i++)
    {
        if(tableau[i]<pivot) // si �l�ment inf�rieur au pivot
        {
            compteur++; // incr�mente compteur cad la place finale du pivot
            echanger(tableau, compteur, i); // �l�ment positionn�
        }
    }
        echanger(tableau, compteur, debut); // le pivot est plac�
    return compteur; // et sa position est retourn�e
}
void triRapideAux(vector<int> & tableau, const int debut, const int fin)
{
    if(debut<fin) // cas d'arr�t pour la r�cursivit�
    {
        int pivot = partition(tableau, debut, fin); // division du tableau
        triRapideAux(tableau, debut, pivot-1); // trie partie1
        triRapideAux(tableau, pivot+1, fin); // trie partie2
    }
}
void triRapide(vector<int> & tableau)
{
    triRapideAux(tableau, 0, tableau.size()-1);
}
/*
* ICI LE TRI A FUSION
*/
void fusion(vector<int> &tableau,const int debut1,const int fin1,const int fin2)
{
    int *tableau2;
    int debut2 = fin1+1;
    int compteur1 = debut1;
    int compteur2 = debut2;
    int i;
    tableau2 = (int*)malloc((fin1-debut1+1)*sizeof(int));
    // copie des �l�ments du d�but de tableau
    for(i=debut1; i<=fin1; i++)
    tableau2[i-debut1] = tableau[i];
    // fusion des deux tableaux
    for(i=debut1; i<=fin2; i++)
    {
        if(compteur1==debut2) // �l�ments du 1er tableau tous utilis�s
        break; // �l�ments tous class�s
        else if(compteur2==(fin2+1)) // �l�ments du 2nd tableau tous utilis�s
        { // copie en fin de tableau des �l�ments du 1er sous tableau
            tableau[i] = tableau2[compteur1-debut1];
            compteur1++;
        }
        else if(tableau2[compteur1-debut1]<tableau[compteur2])
        { // ajout d'1 �l�ment du 1er sous tableau
            tableau[i] = tableau2[compteur1-debut1];
            compteur1++; // on avance ds le 1er sous tableau
        }
        else
        { // copie de l'�l�ment � la suite du tableau
            tableau[i] = tableau[compteur2];
            compteur2++; // on avance ds le 2nd sous tableau
        }
    }
      free(tableau2);
}
void triFusionAux(vector<int> & tableau, const int debut, const int fin)
{
    if(debut!=fin) // condition d'arr�t
    {
    int milieu = (debut+fin)/2;
    triFusionAux(tableau, debut, milieu); // trie partie1
    triFusionAux(tableau, milieu+1, fin); // trie partie2
    fusion(tableau, debut, milieu, fin); // fusion des deux parties
    }
}
void triFusion(vector<int> & tableau)
{
    if(tableau.size()>0)
    triFusionAux(tableau, 0, tableau.size()-1);
}
