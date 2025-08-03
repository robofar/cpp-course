#include <iostream>
#include <tuple>
#include <vector>

typedef std::tuple<double, double, double> Vektor3d;

void UnesiVektor(Vektor3d &v) {
    /* Ovdje cu koristit tie da demonstriram reference i promjenu samog objekta 'vektor' ako se mjenjaju argumenti funkcije tie */
  double x,y,z;
  auto vektor=std::tie(x,y,z);
  std::cout << "X = ";
  std::cin >> x;
  std::cout << "Y = ";
  std::cin >> y;
  std::cout << "Z = ";
  std::cin >> z;
  v=vektor;
}
Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2) {
  Vektor3d vrati=std::make_tuple(std::get<0>(v1)+std::get<0>(v2),std::get<1>(v1)+std::get<1>(v2),std::get<2>(v1)+std::get<2>(v2));
  //ili sam ga mogo odma inicijalizirati sa izracom { ... }
  return vrati;

}
Vektor3d VektorskiProizvod(const Vektor3d &v1, const Vektor3d &v2) {
 // return {v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x};
 Vektor3d vrati=std::make_tuple(std::get<1>(v1)*std::get<2>(v2) - std::get<2>(v1)*std::get<1>(v2),std::get<2>(v1)*std::get<0>(v2) - std::get<0>(v1)*std::get<2>(v2),
          std::get<0>(v1)*std::get<1>(v2) - std::get<1>(v1)*std::get<0>(v2));
  return vrati;
}
void IspisiVektor(const Vektor3d &v) {
  double x=std::get<0>(v);
  double y=std::get<1>(v);
  double z=std::get<2>(v);
  auto v_tie=std::tie(x,y,z); //ekvivalentno sa std::tuple<double &x,double &y, double &z> v_tie;
  /* sada svaki put kad se promjeni x,y ili z, mjenja se i std::get<0 1 2 >(v_tie) -> mada ovdje nista ne znaci */
  std::cout << "{" << std::get<0>(v_tie) << "," << std::get<1>(v_tie) << "," << std::get<2>(v_tie) << "}";
}
int main() {
  Vektor3d a, b;
  std::cout << "Unesi prvi vektor:\n";
  UnesiVektor(a);
  std::cout << "Unesi drugi vektor:\n";
  UnesiVektor(b);
  std::cout << "Suma ova dva vektora je: ";
  IspisiVektor(ZbirVektora(a, b));
  std::cout << std::endl << "Njihov vektorski prozivod je: ";
  IspisiVektor(VektorskiProizvod(a, b));
  return 0;
}