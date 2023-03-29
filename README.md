# Blockchain voting system using C++

A simple voting system using c++ and the Basic knowledge of blockchain. How to work with it. Download the header file named PICOSHA2.H from https://github.com/okdshin/PicoSHA2 Download the main file and run on your IDE.

# Logic

In beginning the genesis block is already been created by the system. Upon new vote, the previous hash and the data will be concatinated and the new hash will be generated. The data will be stored in memory and the last hash will be stored in a .txt file. 

# Logical structures used

1. Linked list
2. File Stream
3. Hash function
4. String Stream

# Working

As hash is unique the last hash that is stored is always unique. The last hash will be stored in a .txt file which helps to check if the data is been tempered or not.
when the voting ends and upon checking who is the winner. the program will again run and from the start and calculate the last hash by checking all the data and previous hashes. It then will  compare the last generated hash with the last hash stored.
If the match - the data is valid.
If not - the data has been tempered and provides an error.
