#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include<random>
#include <cctype>
#include <fstream>

class Message{
public:
    void create_vigenere_table();
    std::map<char, std::vector<std::string>> create_homophonic_encryption();

    //encrypt
    void caesar_encrypt(int displacement, std::ifstream& in_file, std::string file_name);
    void monoalphabetic_encrypt(std::ifstream &in_file, std::string file_name);
    void homophonic_encrypt(std::ifstream &in_file, std::string file_name);
    void vigenere_encrypt(std::string keyword, std::ifstream &in_file, std::string filename);
    
    //decrypt
    void decrypt(std::map<char, char>& key, std::ifstream& in_file);
    void homophonic_decrypt(std::map<char, std::vector<std::string>>& key, std::ifstream &in_file);
    void vigenere_decrypt(std::string keyword, std::ifstream &in_file);


private:
    std::vector<char> alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    std::vector<int> letter_frq = {8, 2, 3, 4, 13, 2, 2, 6, 7, 1, 1, 4, 3, 7, 8, 2, 1, 6, 6, 9, 3, 1, 2, 1, 2, 1};

    std::map<char, std::vector<char>> vigenere_table;

    

};