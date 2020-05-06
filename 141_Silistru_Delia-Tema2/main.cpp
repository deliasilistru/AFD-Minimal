#include "fstream"
#include "string.h"
#include "iostream"
using namespace std;

int stari[30][2], finale[30];
int nr_stari = 0, nr_fin = 0;

//citesti fisierele de input "date.in" - cel cu numarul de stari - si "finale.in" - cel cu starile finale ale automatului.
int citire_fisiere()
{
	char numefis[100] = "date.in";
	ifstream fis(numefis);
	int i = 0;
	while (!fis.eof())
	{
		fis >> nr_stari;
		for(int i = 0; i < nr_stari; i++)
			for(int j = 0; j < 2; j++)
				fis >> stari[i][j];
	}

	char numefis1[100] = "finale.in";
	ifstream fis1(numefis1);
	i = 0;
	while (!fis1.eof())
	{
		fis1 >> finale[i];
		i++;
	}
	nr_fin = i;
	return 0;
}

//functia asta eeste folosita o singrua data pentru a verifica daca o stare apartine multimii de stari finale sau nu ...
bool apartine(int m[30], int x)
{
	bool gasit = false;
	for(int i = 0; i < nr_fin; i++)
		if(m[i] == x)
			gasit = true;

	return gasit;
}


int main()
{
	citire_fisiere();
	bool gasit = false;
    int schimb[30];
	int n = nr_stari;
	char a[30][30];
	int h[30];

	for (int i = 0; i < n; i++)
		h[i] = 0; // vector ce retine daca starea trebuie eliminata sau nu
	h[0] = 1; // starea de intrare

	for (int i=0; i < n; i++)
        schimb[i]=-1;

	for (int i = 0; i < n; i++)// verific daca starile sunt accesibile sau nu si notez in h
	{
		if(stari[i][0] != -1) // -1 inseamna ca nu ma duce nicaieri
			h[stari[i][0]] = 1;

		if(stari[i][1] != -1)
			h[stari[i][1]] = 1;
	}


	/*for (int i = 0; i < n; i++)
		cout<<h[i]<<" ";
		cout<<endl;*/

cout<<"Acesta este automatul initial "<<endl;
	// afisez automatul initial
	for (int i = 0; i < n; i++)
		if (h[i] == 1)
	{
		cout << "(" << i << ", 0) -> ";
		if(h[stari [i][0]] == 0)
			cout << stari[i][0] - 1<< endl;
		else
			cout << stari[i][0]<< endl;

		cout << "(" << i << ", 1) -> ";
		if(h[stari [i][1]] == 0)
			cout << stari[i][1] - 1<< endl;
		else
			cout << stari[i][1]<< endl;
	}

	for(int i = 0; i < nr_stari; i++)
			{for(int j = 0; j < 2; j++)
				cout << stari[i][j]<< " ";
				cout<<endl;
			}

	for(int i = 0; i < n; i++) // elimin starile inaccesibile
		if(h[i] == 0)
	{
		stari[i][0] = -1;
		stari[i][1] = -1;
	}


	for (int i = 0; i < n; i++) // initializez matrice minimizare
		for(int j = 0; j < n; j++)
			a[i][j] = '-';


   for (int i = 0; i < n; i++) // afisare matrice minimizare
    {for(int j = 0; j < n; j++)
			cout<<a[i][j] << " ";
			cout<<endl;	}

    for (int i = 1; i < n; i++)
	{
		for(int j = 0; j < i; j++)
        if((apartine(finale,i) == false and apartine(finale, j) == true) or (apartine(finale,j) == false and apartine(finale, i) == true))
            a[i][j] = '*';
	}

	for(int x = 0; x < nr_fin; x++) //marchez in matricea minimizare linia starilor finale
	{
		for(int i = 0; i < finale[x]; i++)
		{
			if(apartine(finale, i) == false)
				a[finale[x]][i] = '*';
		}
	}

//********************************
	cout << "Matrice marcata doar cu starile finale:" << endl;
	for (int i = 1; i < n; i++) // afisare matrice minimizare
	{
		for(int j = 0; j < i; j++)
			cout << a[i][j] << " ";
		cout << endl;
	}

	//********************************
	int a1, a2, b1, b2;
	gasit = true;


	//  face minimizarea verifica si marcheaza in toate perechile nemarcate pentru a le gasi pe cele echivalente, adica cele care la sfarsit sunt repr prin "-" in matricea a.
	while(gasit == true) //marchez in matricea minimizare pana cand nu imi mai modifica nimic
	{
		gasit = false;
		for(int i = 1; i < n; i++)
		{
			for(int j = 0; j< n-1; j++)
			{
				if(a[j][i] != '*')
				{
					a1 = stari[i][0];
					a2 = stari[j][0];
					b1 = stari[i][1];
					b2 = stari[j][1];

					if(a[a2][a1] == '*')
					{
						a[j][i] = '*';
						a[i][j] = '*';
						gasit = true;
					}

					if(a[b2][b1] == '*')
					{
						a[j][i] = '*';
						a[i][j] = '*';
						gasit = true;
					}
				}
			}
		}
	}

	cout << "\nMatrice:" << endl;
	for (int i = 0; i < n; i++) // afisare matrice minimizare
	{
		for(int j = 0; j < i; j++)
			cout << a[i][j] << " ";
		cout << endl;
	}
	// parcurg matricea din nou pentru a marca in vectorul h - care retine daca o stare trebuie eliminata sau nu - starile echivalente
	for (int i = 0; i < n; i++) // unde exista - in matricea minimizare atunci notez in h ca sunt eliminate
	{
		for(int j = 0; j < i; j++)
			if(a[i][j] == '-')
				{h[i] = 0;
				schimb[i]=j;
                }

	}


int drumuri[30][30];
for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
    drumuri[i][j]=0;

for(int i = 0; i < nr_stari; i++)
    {for(int j = 0; j < 2; j++)
         {drumuri[i][stari[i][j]]=1;
    }
    }

for (int i = 0; i < n; i++) // afisare matrice drumuri
	{
		for(int j = 0; j < n; j++)
			cout << drumuri[i][j] << " ";
		cout << endl;
	}

for(int k=0;k<n;k++)
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
        if(i!=k and j!=k and drumuri[i][j]==0)
            drumuri[i][j]=drumuri[i][k]*drumuri[k][j];

for (int i = 0; i < n; i++) // afisare matrice drumuri
	{
		for(int j = 0; j < n; j++)
			cout << drumuri[i][j] << " ";
		cout << endl;
	}


cout<<endl;

for(int k=0; k<n; k++)
    cout<<schimb[k]<<" ";


for(int k=0; k<n; k++)
    if(schimb[k]!=-1)
{for(int i=0;i<n;i++)
 for(int j=0;j<2;j++)
   if (stari[i][j]==k) stari[i][j]=schimb[k];}


    // afisez nodurile eliminate
	cout << endl << "Nodurile eliminate sunt: " << endl << endl;
	for(int i = 0; i < n; i++)
		if(h[i] == 0)
			cout << "q" << i << endl;
	cout << endl;

	// afisez noul automat minimizat cu starile echivalente eliminate
	cout<<"Acesta este automatul minimal: "<<endl;
	for (int i = 0; i < n; i++)
		if (h[i] == 1)

	{   if(h[stari [i][0]] != 0)
		{cout << "(" << i << ", 0) -> ";
			cout << stari[i][0]<< endl;}

       if(h[stari [i][1]] != 0)
		{cout << "(" << i << ", 1) -> ";
			cout << stari[i][1]<< endl;}
	}



	/*cout<<endl;
	for(int i=0;i< nr_fin - 1;i++)
        cout<<finale[i]<<" ";*/


    cout<<endl<<"Starile finale sunt:"<<endl;
    for(int i=0;i<nr_fin -1 ;i++)
        if(h[finale[i]] == 1)
        cout<<"q"<<finale[i]<<" ";
	return 0;
}
