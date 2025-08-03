#include <iostream>
#include <set>
#include <vector>
//#include <pair>
#include <utility>

template<typename Tip>
std::set<Tip> operator +(const std::set<Tip> &s1,const std::set<Tip> &s2) {
	std::set<Tip> rez;
	for(auto x:s1) rez.insert(x);
	for(auto x:s2) rez.insert(x);
	return rez;
}

template<typename Tip>
std::set<Tip> operator *(const std::set<Tip> &s1,const std::set<Tip> &s2) {
	std::set<Tip> rez;
	for(auto x:s1) {
		for(auto y:s2) {
			if(x==y) {
				rez.insert(x);
				break;
			}
		}
	}
	return rez;
}

template<typename Tip>
std::ostream& operator <<(std::ostream &tok,const std::set<Tip> &s1) {
	tok<<"{";
	int x=s1.size();
	int brojac=0;
	for(auto it=s1.begin();it!=s1.end();it++) {
		if(brojac==x-1) tok<<*it;
		else tok<<*it<<",";
		brojac++;
	}
	tok<<"}";
	return tok;
}

template<typename Tip>
std::set<Tip>& operator +=(std::set<Tip> &s1,const std::set<Tip> &s2) {
	for(auto x:s2) s1.insert(x);
	return s1;
}

template<typename Tip>
std::set<Tip>& operator *=(std::set<Tip> &s1,const std::set<Tip> &s2) {
	std::set<Tip> rez; 
	rez=s1*s2; //setovi se mogu jedan drugom dodjeljivat !!!!!! (btw ovdje sam iskoristio gornji operator (Y))
	s1=rez;
}

template<typename Tip1,typename Tip2>
std::vector<std::pair<Tip1,Tip2>> operator %(const std::set<Tip1> &s1,const std::set<Tip2> &s2) {
	std::vector<std::pair<Tip1,Tip2>> x;
	for(auto it1=s1.begin();it1!=s1.end();it1++) {
		for(auto it2=s2.begin();it2!=s2.end();it2++) {
			std::pair<Tip1,Tip2> q=std::make_pair(*it1,*it2);
			x.push_back(q);
		}
	}
	/* STO NECE OVAKO - JAVLJA NEKU GRESKU za char */
	/*for(auto x:s1) { //moze i for petljom sa iteratorima
		for(auto y:s2) {
			std::pair<Tip1,Tip2> q=std::make_pair(x,y);
			x.push_back(q);
		}
	} */
	return x;
}

template<typename Tip1,typename Tip2>
std::ostream &operator <<(std::ostream &tok,const std::vector<std::pair<Tip1,Tip2>> &v) {
	tok<<"{";
	for(int i=0;i<v.size();i++) {
		if(i==v.size()-1) tok<<"("<<v.at(i).first<<","<<v.at(i).second<<")";
		else tok<<"("<<v.at(i).first<<","<<v.at(i).second<<"),";
	}
	tok<<"}";
	return tok;
}

int main ()
{ 
	std::set<int> s1{2,5,4,1,8};
	std::set<int> s2{6,2,9,4};
	std::cout<<s1+s2<<std::endl;
	std::cout<<s1*s2<<std::endl;
	//////////////////
	std::set<int> s3{4,8,7};
	std::set<char> s4{'F','A','R','I','S'};
	std::cout<<s3%s4<<std::endl;
	///////////////////
	s1*=s2;
	std::cout<<s1<<std::endl;
	s1+=s2;
	std::cout<<s1<<std::endl;

	
	return 0;
}


