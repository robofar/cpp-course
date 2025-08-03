#include <iostream>
#include <vector>

/* Fragmentirana alokacija */
long long int** StirlingoviBrojeviV1(long long int n) {
    if(n<=0) throw std::domain_error("Parametar ne smije biti negativan");
    long long int **mat=nullptr;
    try {
        mat=new long long int*[n+1]{};
        try {
            for(int i=0;i<n+1;i++) {
                mat[i]=new long long int[i+1];
            }
            mat[0][0]=1;
            for(int i=1;i<n+1;i++) mat[i][0]=0;
            for(int i=1;i<n+1;i++) mat[i][i]=1; //moramo ove na dijagonali posebno zbog MEMORIJSKE GRESKE - prisupili bi elementu sa nevalidnim indeksom
            for(int i=1;i<n+1;i++) {
                for(int j=1;j<i;j++) {
                    mat[i][j] = mat[i-1][j-1] + j*mat[i-1][j];
                }
            }
        }
        catch(std::bad_alloc) {
            for(int i=0;i<n+1;i++) delete[] mat[i];
            delete[] mat;
            throw;
        }
    }
    catch(std::bad_alloc) {
        throw std::range_error("Parametar prevelik za raspolozivu memoriju");
    }
    return mat;
}

/* Kontinualna alokacija */
long long int** StirlingoviBrojeviV2(long long int n) {
    if(n<=0) throw std::domain_error("Parametar ne smije biti negativan");
    long long int **mat=nullptr;
    int broj_elemenata=0;
    try {
        mat=new long long int*[n+1]{};
        try {
            for(int i=0;i<n+1;i++) {
                broj_elemenata=broj_elemenata+i+1;
            }
            mat[0]=new long long int[broj_elemenata]; 
            for(int i=1;i<n+1;i++) {
                mat[i]=mat[i-1]+i; //kad budes radio opet ovaj ovo provjeri, moze biti loshe...
            }
            mat[0][0]=1;
            for(int i=1;i<n+1;i++) mat[i][0]=0;
            for(int i=1;i<n+1;i++) mat[i][i]=1; //moramo ove na dijagonali posebno zbog MEMORIJSKE GRESKE - prisupili bi elementu sa nevalidnim indeksom
            for(int i=1;i<n+1;i++) {
                for(int j=1;j<i;j++) {
                    mat[i][j] = mat[i-1][j-1] + j*mat[i-1][j];
                }
            }
        }
        catch(std::bad_alloc) {
            delete[] mat[0];
            delete[] mat;
            throw;
        }
    }
    catch(std::bad_alloc) {
        throw std::range_error("Parametar prevelik za raspolozivu memoriju");
    }
    return mat;
}

int main ()
{
    int n;
    std::cin>>n;
    /* ------------------------------------------------------- */
    long long int **p=nullptr;
    try {
    	p=StirlingoviBrojeviV1(n);
    	for(int i=0;i<n+1;i++) {
    	    for(int j=0;j<i+1;j++) {
    	        std::cout<<p[i][j]<<" ";
    	    }
    	    std::cout<<std::endl;
    	}
    }
    catch(std::domain_error izuzetak) {
        std::cout<<izuzetak.what();
    }
    catch(std::range_error izuzetak) {
        std::cout<<izuzetak.what();
    }
    for(int i=0;i<n+1;i++) delete[] p[i];
    delete[] p; 
    /* --------------------------------------------- */
    std::cout<<std::endl;
    /* ---------------------------------------------------- */
    long long int **q=nullptr;
    try {
    	q=StirlingoviBrojeviV2(n);
    	for(int i=0;i<n+1;i++) {
    	    for(int j=0;j<i+1;j++) {
    	        std::cout<<q[i][j]<<" ";
    	    }
    	    std::cout<<std::endl;
    	}
    }
    catch(std::domain_error izuzetak) {
        std::cout<<izuzetak.what();
    }
    catch(std::range_error izuzetak) {
        std::cout<<izuzetak.what();
    }
    delete[] q[0];
    delete[] q;
    /* -------------------------------------------- */
    return 0;
}