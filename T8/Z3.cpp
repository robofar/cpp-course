#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
const int BrojPredmeta(8);
struct Datum {
  int dan, mjesec, godina;
};
struct Ucenik {
  std::string ime, prezime;
  Datum datum_rodjenja;
  int ocjene[BrojPredmeta];
  double prosjek;
  bool prolaz;
};

int main() {
  void UnesiUcenike(Ucenik** p_ucenici,int broj); //dodatni parametar jer saljes pokazivac na niz
  void ObradiUcenike(Ucenik** p_ucenici,int broj);
  void IspisiIzvjestaj(Ucenik** p_ucenici,int broj);
  void OslobodiMemoriju(Ucenik** p_ucenici,int broj);
  int broj_ucenika;
  Ucenik** p_ucenici=nullptr;
  std::cout << "Koliko ima ucenika: ";
  std::cin >> broj_ucenika;
  try {
    p_ucenici=new Ucenik*[broj_ucenika];
    try {
      UnesiUcenike(p_ucenici,broj_ucenika);  // Ovo može izazvati izuzetak!!!
    } catch (...) {
      OslobodiMemoriju(p_ucenici,broj_ucenika);
      throw;
    }
    ObradiUcenike(p_ucenici,broj_ucenika);
    IspisiIzvjestaj(p_ucenici,broj_ucenika);
    OslobodiMemoriju(p_ucenici,broj_ucenika);
  } catch (...) {
    std::cout << "Problemi sa memorijom...\n";
  }
  return 0;
}

void UnesiUcenike(Ucenik** p_ucenici,int broj_ucenika) {
  void UnesiJednogUcenika(Ucenik* p_ucenik);
  for (int i = 0; i < broj_ucenika; i++) {
    std::cout << "Unesite podatke za " << i + 1 << ". ucenika:\n";
    p_ucenici[i] = new Ucenik;
    UnesiJednogUcenika(p_ucenici[i]);
  }
}
void UnesiJednogUcenika(Ucenik* p_ucenik) {
  void UnesiDatum(Datum &datum);
  void UnesiOcjene(int ocjene[], int broj_predmeta);
  std::cout << "  Ime: ";
  std::cin >> p_ucenik->ime;
  std::cout << "  Prezime: ";
  std::cin >> p_ucenik->prezime;
  std::cout << "  Datum rodjenja (D/M/G): ";
  UnesiDatum(p_ucenik->datum_rodjenja);
  UnesiOcjene(p_ucenik->ocjene, BrojPredmeta);
}
void UnesiDatum(Datum &datum) {
  char znak;
  std::cin >> datum.dan >> znak >> datum.mjesec >> znak >> datum.godina;
}

void UnesiOcjene(int ocjene[], int broj_predmeta) {
  for (int i = 0; i < broj_predmeta; i++) {
    std::cout << "  Ocjena iz " << i + 1 << ". predmeta: ";
    std::cin >> ocjene[i];
  }
}
void ObradiUcenike(Ucenik** p_ucenici,int broj_ucenika) {
  void ObradiJednogUcenika(Ucenik *p_ucenik);
  for(int i=0;i<broj_ucenika;i++) ObradiJednogUcenika(p_ucenici[i]);
  std::sort(p_ucenici, p_ucenici+broj_ucenika,
            [](const Ucenik *p_u1, const Ucenik *p_u2) { 
              return p_u1->prosjek > p_u2->prosjek;
            });
}
void ObradiJednogUcenika(Ucenik* p_ucenik) {
  double suma_ocjena = 0;
  p_ucenik->prosjek = 1;
  p_ucenik->prolaz = false;
  for (int ocjena : p_ucenik->ocjene) {
    if (ocjena == 1) return;
    suma_ocjena += ocjena;
  }
  p_ucenik->prolaz = true;
  p_ucenik->prosjek = suma_ocjena / BrojPredmeta;
}

void IspisiIzvjestaj(Ucenik** p_ucenici,int broj_ucenika) {
  void IspisiJednogUcenika(const Ucenik *p_ucenik);
  std::cout << std::endl;
  /* rasponska for petlja ne moze se koristiti sa dinamickom alokacijom, jer p_ucenici treba biti kontejner a ne dvostruki pokazivac */
  //for(const Ucenik *p_ucenik : p_ucenici) IspisiJednogUcenika(p_ucenik);
  for(int i=0;i<broj_ucenika;i++) {
      IspisiJednogUcenika(p_ucenici[i]);
  }
}

void IspisiJednogUcenika(const Ucenik *p_ucenik) {
  void IspisiDatum(const Datum &datum);
  std::cout << "Ucenik " << p_ucenik->ime << " " << p_ucenik->prezime
            << " rodjen ";
  IspisiDatum(p_ucenik->datum_rodjenja);
  if (p_ucenik->prolaz)
    std::cout << " ima prosjek " << std::setprecision(3) << p_ucenik->prosjek;
  else
    std::cout << " mora ponavljati razred";
  std::cout << std::endl;
}

void IspisiDatum(const Datum &datum) {
  std::cout << datum.dan << "/" << datum.mjesec << "/" << datum.godina;
}
void OslobodiMemoriju(Ucenik** p_ucenici,int broj_ucenika) {
  //for(Ucenik *p_ucenik : p_ucenici) delete p_ucenik; -> isto ne moze
  for(int i=0;i<broj_ucenika;i++) delete p_ucenici[i]; //takodjer mora kod dvostrukog pokazivaca ici [i], ne smije .at(i)
  delete[] p_ucenici;
}