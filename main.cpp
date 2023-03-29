#include <bits/stdc++.h>
#include "picosha2.h"

using namespace std;
using namespace picosha2;

class block {
public:
    string data;
    string prev_hash;
    string hash;
    block* next;
};

void makefile(block*);
void count(block*);

string calc_hash(string prev_hash, string data) {

    string p_hash = prev_hash;
    string m_data = data;
    string new_hash;
    stringstream concat;
    concat << p_hash << m_data;
    new_hash = hash256_hex_string(concat.str());
    return new_hash;
}

void genesis_block(block** headref) {
    if (*headref == NULL) {
        block* last = *headref;
        block* new_block = new block();
        new_block->next = NULL;
        new_block->data = "0";
        new_block->prev_hash = "0";
        new_block->hash = calc_hash(new_block->prev_hash, new_block->data);
        *headref = new_block;
        makefile(new_block);
        return;
    }
}

void makefile(block* headref) {
    block* last = headref;
    while (last->next != NULL) {
        last = last->next;
    }
    fstream hashfile;
    hashfile.open("lasthash.txt", ios::out);
    if (hashfile.is_open()) {
        hashfile << last->hash;
    }
}

void new_block(block** headref, string new_data) {
    if (*headref != NULL) {
        block* last = *headref;
        block* new_block = new block();
        new_block->data = new_data;
        new_block->next = NULL;
        while (last->next != NULL) {
            last = last->next;
        }
        new_block->prev_hash = last->hash;
        new_block->hash = calc_hash(new_block->prev_hash, new_block->data);
        last->next = new_block;
        makefile(new_block);
    }
    return;
}

string getlasthash(block* headref) {
    string nm_hash;
    if (headref->next == NULL) {
        string temp1 = "f1534392279bddbf9d43dde8701cb5be14b82f76ec6607bf8d6ad557f60f304e";
        return temp1;
    }
    while (headref->next != NULL) {
        headref = headref->next;
        nm_hash = calc_hash(headref->prev_hash, headref->data);
    }
    return nm_hash;
}

bool verify(block* headref) {
    string lasthash = getlasthash(headref);
    string filehash;
    string filf;
    ifstream hashfil;
    hashfil.open("lasthash.txt", ios::in);
    if (hashfil.is_open()) {
        while (1) {
            hashfil >> filf;
            if (hashfil.eof()) {
                break;
            }
        }
        hashfil.close();
        return filf == lasthash;
    }
}

void print(block* headref) {
    headref = headref->next;
    while (headref != NULL) {
        cout << headref->data << "->";
        headref = headref->next;
    }
    cout << "END\n";
}

void tocheckwinner(block* headref){
	int count1=0,count2=0,count3=0;
	
				
	while(headref!=NULL){
	
	if(headref->data=="1")
	{count1++;}
	if(headref->data=="2")
	{count2++;}
	if(headref->data=="3")
	{count3++;}
	
	headref=headref->next;
	
}
	
	if(count1>count2 && count1>count3)
	{cout<<"winner is :RAHUL SINGH";return ;}	
	if(count2>count1 && count2>count3)
	{cout<<"winner is :KOMAL GUPTA";return ;}
	if(count3>count1 && count3>count2)
	{cout<<"winner is :ABHISHEK TOMAR";return ;}
	
	else {cout<<"\nNo one is the winner\n";
	}
}



int main(){

block* head=NULL;
string n;
  
	genesis_block(&head);
	
	
	
	int exit=5 ,temp;
	
	while(exit!=0){
	if(!verify(head)){
		cout<<"blockchain is compromised\n";	return 0; 
		
		 	}
	cout<<"\nChoose the candidate to vote:\n\n	1.RAHUL SINGH\n	2.KOMAL GUPTA\n	3.ABHISHEK TOMAR\n	4.Any other number to choose NOTA\n";
	cout<<"->"<<" ";
		getline(cin,n);
	
	new_block(&head,n);
	cout<<"\nTO CONTINUE PRESS ANY NUMBER\n\nTO EXIT PRESS '0'\n";
	cin>>exit;
	
	cin.ignore();
		}
		cout<<"THE ORDER OF THE VOTES IS : ";
		print(head);
		cout<<"\nPRESS 1 TO CHECK THE WINNER OR ANY NUMBER TO EXIT :	";
		
		cin>>temp;
	if(temp==1)	
	{
		tocheckwinner(head);	
	}
	else {
		return 0;
	}		
}
