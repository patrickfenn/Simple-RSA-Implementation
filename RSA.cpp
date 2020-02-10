#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;

const string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

char getLetter(int index){

	return letters[index-2];
}

vector<int> getPrimes(int max){

	 vector<int> unique, nonunique;

	 for(int i = 2; i < max; i++){
		 int foo = pow(i,2);
		 while(foo < max){
			 nonunique.push_back(foo);
			 foo = foo + i;
		 }
	 }

	 for(int i = 2; i < max; i++){
		 bool found = false;
		 for(int j = 0; j < nonunique.size(); j++){
			 if(i == nonunique[j]){
				 found = true;
				 break;
			 }
		 }
		 if(!found){
			 unique.push_back(i);
		 }
	 }


	 return unique;
}

vector<int> findPQ(int n){

	vector<int> primes = getPrimes(n), pq;
	for(int i = 0; i < primes.size() && pq.size() < 3; i++){
		if(n % primes[i] == 0){
			pq.push_back(primes[i]);
		}
	}

	return pq;
}

int getPhi(vector<int> pq){

	return ( (pq.front() -1 ) * (pq.back() -1));
}

//find inverse of foo%n, uses extended euclieds
int findInverse(int foo, int n){


	vector<int> one,two;

	for(int i = 0; i < 300; i++){
		one.push_back(foo*i);
		two.push_back(n*i);
	}

	for(int i = 0; i < 300; i++){
		for(int j = 0; j < 300; j++){
			if(one[i] - two[j] == 1){
				return i;
			}
		}
	}


	return -1;
}


int mod1(int base, int exponent, int mod, int rem){

	int ret;
	int tempExp = exponent/2;
	int tempRem = exponent%2;
	int temp;

	if(base == 0){
		return mod;
	}
	if(base == 1 ){
		//cout << "a";
		//cout << base << " " << rem << endl;
		return rem%mod;
	}
	if(exponent == 1){
		//cout << "b";
		//cout << base << " " << rem << endl;
		return (base*rem)%mod;
	}
	if(exponent % 2 == 1){
		//cout << "c";
		//cout << base << " " << rem << endl;
		rem = rem * base;
	}
	if(tempExp > 1){
		//cout << "d";
		//cout << base << " " << rem << endl;
		ret = fmod(pow(base,2),mod);
		return mod1(ret,tempExp,mod,rem);

	}
	//cout << "e" << base	 << " " << exponent << " " << rem << endl;
	return fmod((pow(base,2)*rem),mod);

}

double decrypt(int e, int n, int m){

	vector<int> pq = findPQ(n),ret;
	int phi = getPhi(pq);

	int d = findInverse(e,phi);

	return mod1(m,d,n,1);

}

double encrypt(int e, int n, int m){
	return mod1(m,e,n,1);
}

int main(int argc, char** argv) {

	int arr[58] ={10,7,58,30,23,62,7,64,62,23,62,61,7,41,62,21,7,49,75,7,69,53,58,37,37,41,10,64,50,7,10,64,21,62,61,35,62,61,62,7,52,10,21,58,7,49,75,7,1,62,26,22,53,30,21,10,37,64};
	double foo,bar;
	//cout << mod1(21,33,11,1);
	const char* estring = argv[1];
	const char* nstring = argv[2];
	string mode = argv[3];
	string fileName = argv[4];
	int e = atoi(estring);
	int n = atoi(nstring);
	cout << e << " " << n << " " << mode << " " << fileName << endl;
	return 0;
}

