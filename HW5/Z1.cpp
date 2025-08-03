#include <iostream>
#include <vector>
#include <initializer_list>
#include <functional>
#include <stdexcept>
#include <algorithm>

template <typename TipEl, template<typename...> class Kontejner = std::vector>
class Tok {
    Kontejner<TipEl> kolekcija;
public:
    template<typename TipEl2, template<typename...> class Kontejner2>
        friend class Tok; //stvara prijateljstvo izmedju razlicitih vrsta tokova
    template<typename IterTip>
        Tok(IterTip pocetak, const IterTip iza_kraja) {
            int i=0;
            while(pocetak!=iza_kraja) {
                kolekcija.insert(std::begin(kolekcija)+i,*pocetak);
                pocetak++;
                i++;
            }
        }
    template<typename IterabilniKontejner>
        Tok(const IterabilniKontejner &kontejner) {
            int i=0;
            for(auto it=std::begin(kontejner);it!=std::end(kontejner);it++) {
                kolekcija.insert(std::begin(kolekcija)+i,*it);
                i++;
            }
        }
    Tok(std::initializer_list<TipEl> lista) {
        int i=0;
        for(auto it=lista.begin();it!=lista.end();it++) {
            kolekcija.insert(std::begin(kolekcija)+i,*it);
            i++;
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////
    static Tok<TipEl,Kontejner> Opseg(TipEl poc, TipEl kraj, TipEl korak=1) {
        Tok<TipEl,Kontejner> novi({});
        int j=0;
        for(TipEl i=poc;i<=kraj;i+=korak) {
            novi.kolekcija.insert(std::begin(novi.kolekcija)+j,i);
            j++;
        }
        return novi;
    }
    unsigned int Velicina() const {
        int vel=0;
        for(auto it=std::begin(kolekcija);it!=std::end(kolekcija);it++) {
            vel++;
        }
        return vel;
    }
    bool Prazan() const {
        if(Velicina()==0) return true; //velicina se svakako poziva nad objektom Tok
        return false;
    }
    Tok<TipEl,Kontejner> Limitiraj(unsigned int n) const {
        if(n>=Velicina()) return *this; //i ako je jednak opet vrati
        Tok<TipEl,Kontejner> novi({});
        int i=0;
        for(auto it=std::begin(kolekcija);it!=std::end(kolekcija);it++) {
            novi.kolekcija.insert(std::begin(novi.kolekcija)+i,*it);
            i++;
            if(i==n) break;
        }
        return novi;
    }
    Tok<TipEl,Kontejner> Preskoci(unsigned int n) const {
        Tok<TipEl,Kontejner> novi({});
        int j=0;
        int i=0;
        if(n>=Velicina()) return novi;
        auto it=std::begin(kolekcija);
        while(i<n) {
            it++;
            i++;
        }
        for(auto x=it;x!=std::end(kolekcija);x++) {
            novi.kolekcija.insert(std::begin(novi.kolekcija)+j,*x);
            j++;
        }
        return novi;
    }
    Tok<TipEl,Kontejner> Obrnut() const {
        Tok<TipEl,Kontejner> novi({});
        int j=0;
        auto it=std::end(kolekcija);
        it--;
        for(int i=Velicina()-1;i>=0;i--) {
            novi.kolekcija.insert(std::begin(novi.kolekcija)+j,*it);
            j++;
            it--;
        }
        it++;
        return novi;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    Tok<TipEl,Kontejner> Akcija(std::function<void(void)> akcija) const {
        auto kopija=*this;
        akcija();
        return kopija;
    }
    void ZaSvaki(std::function<void(TipEl)> akcija) const {
        for(auto it=std::begin(kolekcija); it!=std::end(kolekcija); it++) {
            akcija(*it);
        }
    }
    Tok<TipEl,Kontejner> Filtriraj(std::function<bool(TipEl)> predikat) const {
        Tok<TipEl,Kontejner> novi({});
        int i=0;
        for(auto it=std::begin(kolekcija);it!=std::end(kolekcija);it++) {
            if(predikat(*it)) {
                novi.kolekcija.insert(std::begin(novi.kolekcija)+i,*it);
                i++;
            }
        }
        return novi;
    }
    TipEl PronadjiPrvi() const {
        if(Velicina()==0) throw std::logic_error("Tok je prazan");
        auto it=std::begin(kolekcija);
        return *it; //ovako sam uradio da ne pisem .at(0) jer mozda neki kontejner ne podrzava indeksiranje
    }
    TipEl PronadjiPosljednji() const {
        if(Velicina()==0) throw std::logic_error("Tok je prazan");
        auto it=std::end(kolekcija);
        it--;
        return *it;
    }
    bool ZadovoljavaBaremJedan(std::function<bool(TipEl)> kriterij) const {
        if(Velicina()==0) return true;
        for(auto it=std::begin(kolekcija);it!=std::end(kolekcija);it++) {
            if(kriterij(*it)) return true;
        }
        return false;
    }
    bool ZadovoljavaNijedan(std::function<bool(TipEl)> kriterij) const {
        for(auto it=std::begin(kolekcija);it!=std::end(kolekcija);it++) {
            if(kriterij(*it)) return false;
        }
        return true;
    }
    bool ZadovoljavajuSvi(std::function<bool(TipEl)> kriterij) const {
        for(auto it=std::begin(kolekcija);it!=std::end(kolekcija);it++) {
            if(!kriterij(*it)) return false;
        }
        return true;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    TipEl Akumuliraj(TipEl inicijalna,std::function<TipEl(TipEl,TipEl)> akumulator) const {
        if(Velicina()==0) return inicijalna;
        auto prvi=std::begin(kolekcija);
        TipEl x=*prvi;
        if(Velicina()==1) return x;
        prvi++;
        TipEl y=*prvi;
        if(Velicina()==2) return akumulator(x,y);
        prvi++;
        TipEl rezultat=akumulator(x,y); //pocetno stanje
        auto it=prvi;
        for(it=prvi;it!=std::end(kolekcija);it++) {
            rezultat=akumulator(rezultat,*it);
        }
        return rezultat;
    }
    TipEl Akumuliraj(std::function<TipEl(TipEl,TipEl)> akumulator) const {
        if(Velicina()==0) throw std::logic_error("Tok je prazan");
        return Akumuliraj(-1411,akumulator); //svkako nece nikad moc biti zadovoljen uslov return inicijalna u gornjoj verziji
                    // jer ce prije toga u ovoj verziji biti bacen izuzetak
    }
    Tok<TipEl,Kontejner> Sortirano(std::function<bool(TipEl,TipEl)> komparator = [](TipEl x,TipEl y) { return x<y; }) const {
        Tok<TipEl,Kontejner> novi({});
        int i=0;
        for(auto it=std::begin(kolekcija);it!=std::end(kolekcija);it++) {
            novi.kolekcija.insert(std::begin(novi.kolekcija)+i,*it);
            i++;
        }
        std::sort(std::begin(novi.kolekcija),std::end(novi.kolekcija),komparator);
        return novi;
    }
    Tok<TipEl,Kontejner> Unikatno(std::function<bool(TipEl,TipEl)> komparator = [](TipEl x,TipEl y) { return x==y; }) const {
        Tok<TipEl,Kontejner> novi({});
        Tok<TipEl,Kontejner> q({});
        int i=0;
        for(auto it=std::begin(kolekcija);it!=std::end(kolekcija);it++) {
            q.kolekcija.insert(std::begin(q.kolekcija)+i,*it);
            i++;
        }
        int j=0;
        std::sort(std::begin(q.kolekcija),std::end(q.kolekcija),std::less<int>());
        for(auto it=std::begin(q.kolekcija);it!=std::end(q.kolekcija);it++) {
            novi.kolekcija.insert(std::begin(novi.kolekcija)+j,*it);
            TipEl provjera=*it;
            while(provjera==*it) {
                it++;
                if(it==std::end(q.kolekcija)) break;
            }
            if(it==std::end(q.kolekcija)) break;
            it--; //zbog ovog plusa gore u petlji
            j++;
        }
        return novi;
    }
    Tok<TipEl,Kontejner> Proviri(std::function<void(TipEl)> akcija) const {
        Tok<TipEl,Kontejner> novi({});
        int i=0;
        for(auto it=std::begin(kolekcija);it!=std::end(kolekcija);it++) {
            novi.kolekcija.insert(std::begin(novi.kolekcija)+i,*it);
            i++;
        }
        for(auto it=std::begin(kolekcija);it!=std::end(kolekcija);it++) {
            akcija(*it);
        }
        return novi;
    }
    TipEl Minimalan(std::function<bool(TipEl,TipEl)> komparator = [](TipEl x,TipEl y) { return x<y; }) const {
        if(Velicina()==0) throw std::logic_error("Tok je prazan");
        TipEl min=*std::begin(kolekcija);
        for(auto it=std::begin(kolekcija);it!=std::end(kolekcija);it++) {
            if(komparator(*it,min)) min=*it;
        }
        return min;
    }
    TipEl Maksimalan(std::function<bool(TipEl,TipEl)> komparator = [](TipEl x,TipEl y) { return x>y; }) const {
        if(Velicina()==0) throw std::logic_error("Tok je prazan");
       // auto rez=std::max_element(std::begin(kolekcija),std::end(kolekcija),komparator);
        TipEl max=*std::begin(kolekcija);
        for(auto it=std::begin(kolekcija);it!=std::end(kolekcija);it++) {
           if(komparator(*it,max)) max=*it;
        }
        return max;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////
    template<typename Kont2>
        Kont2 Sakupi(std::function<void(Kont2&,TipEl)> kombinator) const {
            Kont2 x; //ovo Kont2 je kao parametar sablona citav kontejner a ne tip
            for(auto it=std::begin(kolekcija);it!=std::end(kolekcija);it++) {
                kombinator(x,*it);
            }
            return x;
        }
    template<typename TipEl2>
        Tok<TipEl2,Kontejner> Mapiraj(std::function<TipEl2(TipEl)> maper) const {
            Tok<TipEl2,Kontejner> novi({});
            int i=0;
            for(auto it=std::begin(kolekcija);it!=std::end(kolekcija);it++) {
                novi.kolekcija.insert(std::begin(novi.kolekcija)+i,maper(*it));
                i++;
            }
            return novi;
        }
    template<typename TipEl2>
        Tok<TipEl2,Kontejner> MapirajPoravnato(std::function<Tok<TipEl2,Kontejner>(TipEl)> maper) const {
            Tok<TipEl2,Kontejner> novi({});
            for(auto it=std::begin(kolekcija);it!=std::end(kolekcija);it++) {
                auto x=maper(*it); //vraca tok novi
                for(auto it2=std::begin(x.kolekcija);it2!=std::end(x.kolekcija);it2++) {
                    novi.kolekcija.insert(std::end(novi.kolekcija),*it2); //moze i end umjesto begin+i
                }
            }
            return novi;
        }
};


int main ()
{
try {
    int niz[]{1,2,3,4,5};
    Tok<int> tok=Tok<int>(niz+1,niz+3);
    std::cout<<tok.Velicina()<<" "<<tok.Prazan();
    std::cout<<std::endl;
    Tok<int>{5,4,8,3,2,5,0,8}.Limitiraj(5).ZaSvaki([](int i) { std::cout<<i<<" "; });
    std::cout<<std::endl;
    Tok<int>{1,2,3}.Mapiraj<int>([](int i){ return i*4;});
    std::cout<<std::endl;
    Tok<std::vector<int>> q {
        {4,5,6},
        {1,2,3,4,5},
        {12,13}
    };
    q.MapirajPoravnato<int>([](const std::vector<int> &v) { return Tok<int>(v); }).ZaSvaki([](int i) { std::cout<<i<<" ";});
    std::cout<<std::endl;
    std::cout<<Tok<int>{1,5,6,-10,-12,4}.Minimalan();
    std::cout<<std::endl;
    std::cout<<Tok<int>{1,5,6,-10,-12,20,4}.Maksimalan();
    std::cout<<std::endl;
    Tok<double>{1,8,-1,6,4,-3}.Filtriraj([](double d) { return d<0; }).ZaSvaki([](double d) { std::cout<<d<<" ";});
    std::cout<<std::endl;
    Tok<int>{1,1,1,2,2,2,3,4,4,4,5,5,6}.Unikatno().ZaSvaki([](int i) { std::cout<<i<<" "; });
    std::cout<<std::endl;
    Tok<int>{1,1,1,2,2,3,3,3,4,4,5,5,6,6,6}.Unikatno().ZaSvaki([](int i) { std::cout<<i<<" "; });
    std::cout<<std::endl;
}
catch(std::logic_error iz) {
    std::cout<<iz.what();
}
	return 0;
}