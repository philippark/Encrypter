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

void print_title_screen(){
    std::ifstream title_screen("title_art.txt");
    std::string line;
    while (getline(title_screen, line)){
        std::cout << line << std::endl;
    }


}

void options(){

}

int main(int argc, char* argv[]){
    print_title_screen();
    std::string in, out, cipher;

    while(true){
        std::cout << "cyphen> ";
        std::string line;
        getline(std::cin, line);
        if (line == "q"){
            break;
        }

        
    }



    if (cipher == "--caesar"){
        Message m;
        std::map<char, char> key = m.caesar_encrypt(3, in, out);
        m.decrypt(key, out);
    }

    if (cipher == "--monoalphabetic"){
        Message m;
        std::map<char, char> key2 = m.monoalphabetic_encrypt(argv[1], argv[2]);
        m.decrypt(key2, argv[2]);
    }

    if (cipher == "--homophonic"){
        Message m;
        std::map<char, std::vector<std::string>> key = m.homophonic_encrypt(argv[1], argv[2]);
        m.homophonic_decrypt(key, argv[2]);
    }

    if (cipher == "--vigenere"){
        std::cout << "key word: ";
        std::string keyword;
        std::cin >> keyword;
        Message m;
        m.vigenere_encrypt("houghton", argv[1], argv[2]);
        m.vigenere_decrypt("houghton", argv[2]);

    }

    

}