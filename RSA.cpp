//Patrick Fenn SID 862152988 
// Alma Rodriguez (861262171)




#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <sstream>

using namespace std;

const string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

char getLetter(int index){

	return letters[index-2];
}

int getNumber(char letter){
	letter = toupper(letter);
	for(int i = 0; i < letters.length(); i++){
		if(letter == letters[i]){
			return i+2;
		}
	}
	return -1;
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
	for(int i = 0; i < primes.size(); i++){
		for(int j = 0; j < primes.size(); j++){
			if(primes[i] * primes[j] == n ){
				pq.push_back(primes[i]);
				pq.push_back(primes[j]);
			}
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

vector<int> getPrimeFactors(int foo){
	vector<int> primes = getPrimes(foo),ret;
	for(int i = 0; i < primes.size(); i++){
		if(foo % primes[i] == 0){
			ret.push_back(primes[i]);
		}
	}
	return ret;
}
bool check(int e, int n){
	vector<int> pq = findPQ(n);
	if(pq.size() < 2){
		return false;
	}
	int phi = getPhi(pq);

	vector<int> one = getPrimeFactors(e);
	vector<int> two = getPrimeFactors(phi);
	for(int i = 0; i < one.size(); i++){

		for(int j = 0; j < two.size(); j++){
			if(one[i] == two[j]){
				return false;
			}
		}
	}
	return true;
}
int main(int argc, char** argv) {


	vector<int> read,de,en;

	const char* estring = argv[1];
	const char* nstring = argv[2];
	const char* mode = argv[3];
	const char* fileName = argv[4];
	int e = atoi(estring);
	int n = atoi(nstring);
	fstream fio1, fio2;
	string line, token;


	//add code for file io here, read file into the read vector
	if(check(e,n) == 0){
		cout << "Check failed!";
		return 1;
	}
	try{fio1.open((string)fileName,fstream::in);}
	catch(...){
		cout << "file not opened!";
		return 1;
	}
	while(fio1){
		getline(fio1,line);
		for(int i = 0; i < line.length() ; i++){
			read.push_back( (int)line[i]);
		}
	}
	fio1.close();

	if((string)mode == "e"){
		for(int i = 0; i < read.size(); i++){
			en.push_back( encrypt(e,n,read[i]));
		}
		fio2.open("incrypted.txt", fstream::out);
		for(int i = 0; i < en.size(); i++){
			fio2 << en[i] << " ";
		}
		cout << "incrypted.txt";
		//write to encrypt file name will be "incrypted.txt"
	}
	else if((string)mode == "d"){
		for(int i = 0; i < read.size(); i++){
			de.push_back( decrypt(e,n,read[i]));
		}
		fio2.open("decrypted.txt", fstream::out);
		for(int i = 0; i < en.size(); i++){
			fio2 << en[i] << " ";
		}
		vector<int> pq = findPQ(n);
		cout << "p = " << pq.front() << ", q = " << pq.back() << ", decrypted.txt";
		//write to decrypt file name will be "decrypted.txt"
	}
	fio2.close();

	return 0;
}

