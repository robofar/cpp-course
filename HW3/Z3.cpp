#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <new>
#include <vector>

template <typename TipElemenata>
struct Matrica {
    int br_redova, br_kolona;
    TipElemenata **elementi = nullptr; // VEOMA BITNA INICIJALIZACIJA!
};

template <typename TipElemenata>
void UnistiMatricu(Matrica<TipElemenata> &mat)
{
    if(!mat.elementi) return;
    for(int i = 0; i < mat.br_redova; i++) delete[] mat.elementi[i];
    delete[] mat.elementi;
    mat.elementi = nullptr;
}

template <typename TipElemenata>
Matrica<TipElemenata> StvoriMatricu(int br_redova, int br_kolona)
{
    Matrica<TipElemenata> mat;
    mat.br_redova = br_redova;
    mat.br_kolona = br_kolona;
    mat.elementi = new TipElemenata*[br_redova] {};
    try {
        for(int i = 0; i < br_redova; i++)
            mat.elementi[i] = new TipElemenata[br_kolona];
    } catch(...) {
        UnistiMatricu(mat);
        throw;
    }
    return mat;
}
template <typename TipElemenata>
void UnesiMatricu(char ime_matrice, Matrica<TipElemenata> &mat)
{
    for(int i = 0; i < mat.br_redova; i++)
        for(int j = 0; j < mat.br_kolona; j++) {
            std::cout << ime_matrice
                      << "(" << i + 1 << "," << j + 1 << ") = ";
            std::cin >> mat.elementi[i][j];
        }
}
template <typename TipElemenata>
void IspisiMatricu(Matrica<TipElemenata> &mat,int sirina_ispisa,int preciznost=6,bool treba_brisati=false)
{
    for(int i = 0; i < mat.br_redova; i++) {
        for(int j = 0; j < mat.br_kolona; j++)
            std::cout << std::setw(sirina_ispisa) << std::setprecision(preciznost) << mat.elementi[i][j];
        std::cout << std::endl;
    }
    if(treba_brisati) {
        UnistiMatricu(mat); //morali smo skloniti const da je mozemo unistiti
    }
}
template <typename TipElemenata>
Matrica<TipElemenata> ZbirMatrica(const Matrica<TipElemenata> &m1,const Matrica<TipElemenata> &m2)
{
    if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
        throw std::domain_error("Matrice nemaju jednake dimenzije!");
    auto m3 = StvoriMatricu<TipElemenata>(m1.br_redova, m1.br_kolona);
    for(int i = 0; i < m1.br_redova; i++)
        for(int j = 0; j < m1.br_kolona; j++)
            m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
    return m3;
}

template<typename TipElemenata>
Matrica<TipElemenata> ProduktMatrica(const Matrica<TipElemenata> &m1,const Matrica<TipElemenata> &m2) {
    if(m1.br_kolona!=m2.br_redova) throw std::domain_error("Matrice nisu saglasne za mnozenje");
    Matrica<TipElemenata> nova;
    nova=StvoriMatricu<TipElemenata>(m1.br_redova,m2.br_kolona);
    for(int i=0;i<nova.br_redova;i++) {
        for(int j=0;j<nova.br_kolona;j++) {
            nova.elementi[i][j]=0;
        }
    }
    for(int i=0;i<m1.br_redova;i++) {
        for(int j=0;j<m2.br_kolona;j++) {
            for(int k=0;k<m1.br_kolona;k++) nova.elementi[i][j]+=m1.elementi[i][k]*m2.elementi[k][j];
        }
    }
    return nova;
}

template<typename TipElemenata>
Matrica<TipElemenata> JedinicnaMatrica(int redovi,int kolone) {
    Matrica<TipElemenata> jedinicna;
    jedinicna=StvoriMatricu<TipElemenata>(redovi,kolone);
    for(int i=0;i<redovi;i++) {
        for(int j=0;j<kolone;j++) {
            if(i==j) jedinicna.elementi[i][j]=1;
            else jedinicna.elementi[i][j]=0;
        }
    }
    return jedinicna;
}

template<typename TipElemenata>
Matrica<TipElemenata> DodijeliMatrice(const Matrica<TipElemenata> &b) {
    Matrica<TipElemenata> nova=StvoriMatricu<TipElemenata>(b.br_redova,b.br_kolona);
    for(int i=0;i<b.br_redova;i++) {
        for(int j=0;j<b.br_kolona;j++) {
            nova.elementi[i][j]=b.elementi[i][j];
        }
    }
    return nova;
}

template<typename TipElemenata>
Matrica<TipElemenata> MatricniPolinom(Matrica<TipElemenata> A,std::vector<double> v) {
    if(A.br_redova!=A.br_kolona) throw std::domain_error("Matrica mora biti kvadratna");
    std::vector<Matrica<TipElemenata>> matrice(v.size());
    std::vector<Matrica<TipElemenata>> rezultati(v.size()+1);
    rezultati[0]=StvoriMatricu<TipElemenata>(A.br_redova,A.br_kolona);
    for(int i=0;i<A.br_redova;i++) {
        for(int j=0;j<A.br_kolona;j++) {
            rezultati[0].elementi[i][j]=0;
        }
    }
    if(v.size()==0) {
        return rezultati[0];
    }
    matrice.at(0)=JedinicnaMatrica<TipElemenata>(A.br_redova,A.br_kolona);
    for(int i=0;i<A.br_redova;i++) {
        for(int j=0;j<A.br_kolona;j++) {
            matrice.at(0).elementi[i][j]*=v.at(0);
        }
    }
    /* plitko kopiranje - kopira se i pokazivac i to je isto ko da radis sa A tj ko da si je poslo po referenci
    Zato sam pravio novu funkciju da bi samo dodijelio elemente a ne pokazivac*/
    std::vector<Matrica<TipElemenata>> pomocne(matrice.size()); //napravio vektor zbog dealokacije. sa jednom bi se alociralo 10 puta a samo jedna bila
    pomocne[0]=DodijeliMatrice(A);
    for(int i=1;i<matrice.size();i++) {
        matrice.at(i)=DodijeliMatrice(pomocne[i-1]);
        for(int k=0;k<A.br_redova;k++) {
            for(int l=0;l<A.br_kolona;l++) {
                matrice.at(i).elementi[k][l]*=v.at(i);
            }
        }
        pomocne[i]=ProduktMatrica<TipElemenata>(pomocne[i-1],A);
    }
    for(int i=0;i<pomocne.size();i++) UnistiMatricu(pomocne[i]);
    /* Sabiraj sve matrice i smjesti u matricu rezultat koju vracas iz funkcije */
    // napravicu vektor i za rezultat iz istog razloga gore ko za pomocnu jer:
    //sa funkcijom ZbirMatrica napravim npr 5 puta D.A. matricu al nikad je ne brisem, a nema drugog nacina
    //kako da obrisem svaki put osim da brisem citav vektor
    //btw vektor je kreiran na pocetku jer sam tamo prvi put iskoristio rezultat pa zato
    for(int i=1;i<rezultati.size();i++) {
        rezultati[i]=ZbirMatrica(rezultati[i-1],matrice.at(i-1));// mozda curenje memorije
    }
    Matrica<TipElemenata> rezultat=rezultati[rezultati.size()-1];
    for(int i=0;i<matrice.size();i++) UnistiMatricu(matrice.at(i));
    for(int i=0;i<matrice.size();i++) UnistiMatricu(rezultati.at(i));
    return rezultat;
    /* ZAKLJUCAK
    MORAO SAM SVUGDJE KORISTITI VEKTORE MATRICA, JER NPR NE MOZE rezultat+=Zbir(a,b); jer ovako svaki put kreiram
    novu dinamicki alociranu matricu pomocu fje Zbir a ne mogu je unistiti jer sve nadodajem na jednu matricu rezultat
    Zato sve sto sam radio na ovaj fazon sam zamijenio vektorom matrica da bi poslije mogao fino dealocirati sve to */
}
int main()
{
    Matrica<double> A;
    Matrica<double> rezultat;
    try {
       int n;
       std::cout<<"Unesite dimenziju kvadratne matrice: ";
       std::cin>>n;
       A=StvoriMatricu<double>(n,n);
       std::cout<<"Unesite elemente matrice A: "<<std::endl;
       UnesiMatricu<double>('A',A);
       int x,velicina;
       std::cout<<"Unesite red polinoma: ";
       std::cin>>x;
       std::vector<double> polinomi(x+1);
       std::cout<<"Unesite koeficijente polinoma: ";
       for(int i=0;i<x+1;i++) {
           std::cin>>polinomi.at(i);
       }
       rezultat=MatricniPolinom<double>(A,polinomi);
       IspisiMatricu<double>(rezultat,10,6,true);
    }
    catch(std::bad_alloc) {
        std::cout<<"Nedovoljno memorije!";
    }
    catch(std::domain_error izuzetak) {
        std::cout<<izuzetak.what();
    }
    /* Ova dva brisanja idu slobodno na kraj (nebitno jel se zaista dogodila jedna od ove dvije alokacije)
    nece biti problema pri brisanju cak ako bar neka nije ispravno alocirana JER JE POKAZIVAC NA NJIH INICIJALIZIRAN
    NA NULL PTR PA NEMA PROBLEMA, INACE BI BILO I NE BI SMJELO SAMO IH OVAKO NA KRAJU BRISAT */
   UnistiMatricu(A);
   UnistiMatricu(rezultat);
   return 0;
}
