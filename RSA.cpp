#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <sstream>

using namespace std;

const string letters = "..ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

char getLetter(int index){

	return letters[index];
}

int getNumber(char letter){
	letter = toupper(letter);
	for(int i = 0; i < letters.length(); i++){
		if(letter == letters[i]){
			return i;
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

	vector<int> primes = getPrimes(n), pq,ret;
	for(int i = 0; i < primes.size(); i++){
		if(remainder(n,primes[i]) == 0){
			pq.push_back(primes[i]);
		}
	}
	for(int i = 0; i < pq.size(); i++){
		for(int j = 0; j < pq.size(); j++){
			if(pq[i] * pq[j] == n){
				ret.push_back(pq[i]);
				ret.push_back(pq[j]);
				return ret;
			}
		}
	}




	return ret;
}

int getPhi(vector<int> pq){
	return ( (pq.front() -1 ) * (pq.back() -1));
}

//find inverse of foo%n, uses extended euclieds
int findInverse(int e, int phi){


	vector<int> one,two;

	for(int i = 0; i < 300; i++){
		one.push_back(e*i);
		two.push_back(phi*i);
	}

	for(int i = 0; i < 300; i++){
		for(int j = 0; j < 300; j++){
			if((one[i] -two[j]) == 1){
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

vector<double> decrypt(vector<int> in, int e, int n){

	vector<int> pq = findPQ(n);
	vector<double>ret;
	int phi = getPhi(pq);

	int d = findInverse(e,phi);

	for(int i= 0; i < in.size(); i++){
		ret.push_back( mod1(in[i],d,n,1) );
	}
	return ret;

}

vector<double> encrypt(vector<int> in, int e, int n){
	vector<double> ret;
	for(int i = 0; i < in.size(); i++){
		ret.push_back(mod1(in[i],e,n,1));
	}
	return ret;
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
	vector<int> read;

	const char* estring = argv[1];
	const char* nstring = argv[2];
	const char* mode = argv[3];
	const char* fileName = argv[4];
	int e = atoi(estring);
	int n = atoi(nstring);
	fstream fio1, fio2;
	string line, token;

	cout << fileName << " " << e << " " << n;
	if((string)mode == "e"){


		fio1.open((string)fileName, fstream::in);
		while(fio1){
			getline(fio1,line);
			for(int i = 0; i < line.length(); i++){
				read.push_back(getNumber(line[i]));
			}
		}
		fio1.close();

		vector<double>en = encrypt(read,e,n);

		fio2.open("incrypted.txt", fstream::out);
		for(int i = 0; i < en.size(); i++){
			fio2<< en[i];
		}
		fio2.close();
		cout << "incrypted.txt";
	}
	//add code for file io here, read file into the read vector
	if((string)mode == "d"){
	fio1.open((string)fileName, fstream::in);
	read.clear();
	while(fio1){
		getline(fio1,line);
		istringstream ss(line);
		while(ss){
			ss >> token;
			read.push_back(atoi(token.c_str()));
		}
	}
	fio1.close();
	vector<double> de = decrypt(read,e,n);

	fio2.open("decrypted.txt", fstream::out);
	for(int i = 0; i < de.size(); i++){
		fio2 << getLetter(de[i]);
	}
	fio2.close();
	vector<int> pq = findPQ(n);
	cout << "p = " << pq.front() << ", q = " << pq.back() << ", decrypted.txt";
	}



	return 0;
}
