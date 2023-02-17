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

#include "message.h"

int main(int argc, char* argv[]){
    if (std::string(argv[3]) == "--caesar"){
        Message m;
        std::map<char, char> key = m.caesar_encrypt(3, argv[1], argv[2]);
        m.decrypt(key, argv[2]);
    }

    if (std::string(argv[3]) == "--monoalphabetic"){
        Message m;
        std::map<char, char> key2 = m.monoalphabetic_encrypt(argv[1], argv[2]);
        m.decrypt(key2, argv[2]);
    }

    if (std::string(argv[3]) == "--homophonic"){
        Message m;
        std::map<char, std::vector<std::string>> key = m.homophonic_encrypt(argv[1], argv[2]);
        m.homophonic_decrypt(key, argv[2]);
    }

    if (std::string(argv[3]) == "--vigenere"){
        std::cout << "key word: ";
        std::string keyword;
        std::cin >> keyword;
        Message m;
        m.vigenere_encrypt("houghton", argv[1], argv[2]);
        m.vigenere_decrypt("houghton", argv[2]);

    }


}