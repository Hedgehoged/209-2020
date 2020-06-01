#include "HashTable.h"
#include <fstream>
#include <iostream>

int HashTable::hashFunc(const line& d) const //hash function (utilizes horner's method to prevent overflow on large strings)
{
	int hashVal=0,asc;
  std::string s = d.name;
	for(int i=0;i<s.size();i++)
	{
		asc=s[i]>96?s[i]-96:s[i]-64;
		hashVal=(hashVal*32+asc)%arrSize;
	}
	return hashVal;
}

int HashTable::getPrime(int n) const //return the smallest prime number >= 2*n
{
	int i=2*n;
	while(!isPrime(i))
		i++;
	return i;
}

bool HashTable::isPrime(int n) const //check whether n is prime, helper function for getPrime()
{
	bool isPrime=true;
		for(int count=2;count<n && isPrime; count++)
			if(n%count==0)
				isPrime=false;
	return isPrime;
}

void HashTable::deepCopy(const HashTable& h)
{
	if(h.arr!=NULL)
	{
		numOfItems=h.size();
		arrSize=h.maxSize();
		arr=new LinkedList[arrSize];
		for(int i=0;i<arrSize;i++)
			arr[i]=h.arr[i];
	}
}

std::vector<line> HashTable::get() const //returns a vector of all the lines in the hash table
{
	std::vector<line> v,tmp_v;
	for(int i=0;i<maxSize();i++)
	{
		tmp_v=arr[i].get();
		for(int j=0;j<tmp_v.size();j++)
			v.push_back(tmp_v[j]);
	}
	return v;
}

HashTable::HashTable() //default constructor
{
	arrSize=50023;
	arr=new LinkedList[arrSize];
	numOfItems=0;
}

HashTable::HashTable(int n) //creates a hash table to store n items where the size of the array is the smallest prime number >= 2*n
{
	arrSize=getPrime(n);
	arr=new LinkedList[arrSize];
	numOfItems=0;
}


HashTable::HashTable(const HashTable& h) //copy constructor
{
	deepCopy(h);
}


HashTable::~HashTable() //destructor
{
	delete[] arr;
}

HashTable& HashTable::operator=(const HashTable& h) //assignment operator
{
	if(this!=&h)
	{
		if(h.arr!=NULL)
			delete[] arr;
		deepCopy(h);
	}
	return *this;
}

bool HashTable::insert(const line& s) //inserts line s if it doesn't exist in the hash table and returns 1 if insertion successful, 0 otherwise
{
	int hash=hashFunc(s);
	bool successOrFail=arr[hash].insert(s);
	numOfItems++;
	return successOrFail;
}

bool HashTable::remove(const line& s) //removes line s if s exist in the hash table and returns 1 if removal successful, 0 otherwise
{
	int hash=hashFunc(s);
	bool successOrFail=arr[hash].remove(s);
	numOfItems--;
	return successOrFail;
}
int HashTable::removepart(const line& s)
{
	int hash=hashFunc(s);
	int successOrFail;
	try{
			successOrFail=arr[hash].removepart(s);
	}
	catch(int a)
  {
    std::cout << "Caught exception number:  " << a << std::endl;
    return 0;
  }
	if(successOrFail == 2)  numOfItems--;
	return successOrFail;
}

int HashTable::search(const line& s) const //returns 1 if s exist in the hash table, 0 otherwise
{
	int hash=hashFunc(s);
	int found=arr[hash].search(s);
	return found;
}

int HashTable::searchP(const line &s) const
{
	int hash=hashFunc(s);
	int found=arr[hash].searchP(s);
	return found;
}


int HashTable::size() const //returns numOfItems
{
	return numOfItems;
}

int HashTable::maxSize() const //returns arrSize
{
	return arrSize;
}

double HashTable::loadFactor() const //returns the load factor of the hash table
{
	return (numOfItems*1.0)/arrSize;
}

void HashTable::print() const
{
		for(int i=0;i<arrSize;i++)
		{
				if(arr[i].front != NULL)
				{
						arr[i].printList();
				}
		}
}

void HashTable::printclient(int fd) const
{
		for(int i=0;i<arrSize;i++)
		{
				if(arr[i].front != NULL)
				{
						arr[i].printListclient(fd);
				}
		}
}
void HashTable::HashTableToFile(const std::string &filename_items) const
{
		std::ofstream ofs(filename_items);
		for(int i=0;i<arrSize;i++)
		{
				if(arr[i].front != NULL)
				{
						ofs << arr[i];
				}
		}
}
/*
std::vector<line> HashTable::intersection(const HashTable& h) const //returns a vector of line containing intersection of calling object's data and h's data
{
	std::vector<line> ret_v;
	std::vector<line> v=this->get();
	for(int i=0;i<v.size();i++)
		if(h.search(v[i]))
			ret_v.push_back(v[i]);
	return ret_v;
}

std::vector<line> HashTable::unions(const HashTable& h) const //returns a vector of line containing union of calling object's data and h's data
{
	std::vector<line> ret_v;
	std::vector<line> v1=this->get();
	std::vector<line> v2=h.get();
	for(int i=0;i<v2.size();i++) //push_back all h elements
		ret_v.push_back(v2[i]);
	for(int i=0;i<v1.size();i++) //push_back caller elements that are not found in h
		if(!h.search(v1[i]))
			ret_v.push_back(v1[i]);
	return ret_v;
}

std::vector<line> HashTable::difference(const HashTable& h) const //returns a vector of line containing set difference of calling object's data and h's data
{
		std::vector<line> ret_v;
  	std::vector<line> v1=this->get();
    std::vector<line> v2=h.get();
    for(int i=0;i<v1.size();i++) //push_back caller's elements that are not found in h
        if(!h.search(v1[i]))
            ret_v.push_back(v1[i]);
    for(int i=0;i<v2.size();i++) //push_back h's elements that are not found in caller
        if(!this->search(v2[i]))
            ret_v.push_back(v2[i]);
    return ret_v;
}
*/
