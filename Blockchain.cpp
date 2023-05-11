#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "picosha2.h"

using namespace std;
using namespace picosha2;

class Block {
public:
    string data;
    string prevHash;
    string hash;
    Block* next;

    Block(const string& data, const string& prevHash) : data(data), prevHash(prevHash), next(nullptr) {
        calculateHash();
    }

    void calculateHash() {
        stringstream concat;
        concat << prevHash << data;
        hash = hash256_hex_string(concat.str());
    }
};

class Blockchain {
private:
    Block* head;

public:
    Blockchain() : head(nullptr) {}

    void addGenesisBlock() {
        if (head == nullptr) {
            head = new Block("0", "0");
            saveToFile(head->hash);
        }
    }

    void addBlock(const string& data) {
        if (head != nullptr) {
            Block* last = head;
            while (last->next != nullptr) {
                last = last->next;
            }
            Block* newBlock = new Block(data, last->hash);
            last->next = newBlock;
            saveToFile(newBlock->hash);
        }
    }

    string getLastHash() const {
        string newHash;
        if (head == nullptr) {
            newHash = "f1534392279bddbf9d43dde8701cb5be14b82f76ec6607bf8d6ad557f60f304e";
        } else {
            Block* last = head;
            while (last->next != nullptr) {
                last = last->next;
            }
            newHash = last->hash;
        }
        return newHash;
    }

    bool verify() const {
        string lastHash = getLastHash();
        string fileHash;
        ifstream hashFile("lasthash.txt");
        if (hashFile.is_open()) {
            while (hashFile >> fileHash) {
            }
            hashFile.close();
            return (fileHash == lastHash);
        }
        return false;
    }

    void print() const {
        Block* current = head;
        while (current != nullptr) {
            cout << current->data << "->";
            current = current->next;
        }
        cout << "END" << endl;
    }

    void checkWinner() const {
        int count1 = 0, count2 = 0, count3 = 0;
        Block* current = head;
        while (current != nullptr) {
            if (current->data == "1") {
                count1++;
            } else if (current->data == "2") {
                count2++;
            } else if (current->data == "3") {
                count3++;
            }
            current = current->next;
        }

        vector<pair<int, string>> candidates = {
            {count1, "RAHUL SINGH"},
            {count2, "KOMAL GUPTA"},
            {count3, "ABHISHEK TOMAR"}
        };

        sort(candidates.rbegin(), candidates.rend()); // Sort in descending order

        if (candidates.empty() || candidates[0].first == 0) {
            cout << "No one is the winner" << endl;
        } else {
            cout << "Winner is: " << candidates[0].second << endl;
        }
    }

    void saveToFile(const string& hash) const {
        ofstream hashFile("lasthash.txt");
        if (hashFile.is_open()) {
            hashFile << hash;
            hashFile.close();
        } else {
            cout << "Unable to save hash to file." << endl;
        }
    }

    ~Blockchain() {
        Block* current = head;
        while (current != nullptr) {
            Block* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

int main() {
    Blockchain blockchain;
    blockchain.addGenesisBlock();

    int exit = 5, temp;
    while (exit != 0) {
        if (!blockchain.verify()) {
            cout << "Blockchain is compromised" << endl;
            return 0;
        }

        cout << "\nChoose the candidate to vote:\n\n";
        cout << "  1. RAHUL SINGH\n";
        cout << "  2. KOMAL GUPTA\n";
        cout << "  3. ABHISHEK TOMAR\n";
        cout << "  4. Any other number to choose NOTA\n";
        cout << "-> ";
        
        string input;
        getline(cin, input);
        blockchain.addBlock(input);

        cout << "\nTO CONTINUE PRESS ANY NUMBER\n\nTO EXIT PRESS '0'\n";
        cin >> exit;
        cin.ignore();
    }

    cout << "THE ORDER OF THE VOTES IS: ";
    blockchain.print();

    cout << "\nPRESS 1 TO CHECK THE WINNER OR ANY NUMBER TO EXIT: ";
    cin >> temp;
    if (temp == 1) {
        blockchain.checkWinner();
    }

    return 0;
}

