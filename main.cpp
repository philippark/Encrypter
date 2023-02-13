#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "Cypher.h"
#include <algorithm>
#include <cstdlib>
#include<random>
#include <cctype>

std::map<char, char> caesar_encrypt(std::vector<char>& alphabet, unsigned int displacement, std::string in, std::string out){
    std::map<char, char> m;
    unsigned int i = 0;
    for (i; i < alphabet.size() - displacement; i++){
        m[alphabet[i]] = alphabet[i+3];
    }
    //account for letters at the end
    for (int j = 0; j < displacement; j++, i++){
        m[alphabet[i]] = alphabet[j];
    }



    std::ifstream in_file(in);
    std::ofstream outfile(out);
    std::string line;


    while(getline(in_file, line)){
        for (unsigned int i = 0; i < line.size(); i++){
            if (std::count(alphabet.begin(), alphabet.end(), line[i]) > 0 ){
                outfile << m[line[i]];
            }
            else{
                outfile << line[i];
            }
            
        }
    }

    return m;

}

std::map<char, char> monoalphabetic_encrypt(std::vector<char>& alphabet, std::vector<int>& arrangement, std::string in, std::string out){
    std::map<char, char> key;

    for (unsigned int i = 0; i < arrangement.size(); i++){
        key[alphabet[i]] = alphabet[arrangement[i]];
        //std::cout << alphabet[i] << " " << alphabet[arrangement[i]] << std::endl;
    }

    std::ifstream in_file(in);
    std::ofstream outfile(out);
    std::string line;

    while(getline(in_file, line)){
        for (unsigned int i = 0; i < line.size(); i++){
            if (std::count(alphabet.begin(), alphabet.end(), line[i]) > 0 ){
                outfile << key[line[i]];
            }
            else{
                outfile << line[i];
            }
            
        }
    }
    
    return key;
}

void decrypt(std::map<char, char>& key, std::vector<char>& alphabet, std::string in){
    //key should be in format of alphabet : encrypted
    std::ifstream infile(in);
    std::ofstream outfile(in+"_decrypted");
    std::string line;
    while (getline(infile, line)){
        std::cout << line << std::endl;
        for (unsigned int i = 0; i < line.size(); i++){
            if (std::count(alphabet.begin(), alphabet.end(), line[i]) > 0 ){
                std::map<char, char>::iterator itr = key.begin();
                while (itr != key.end()){
                    if (itr->second == line[i]){
                        outfile << itr->first;
                    }
                    itr++;
                }
            }
            else{
                outfile << line[i];
            }
            
        }
    }
}

void homophonic_decrypt(std::map<char, std::vector<std::string>>& key, std::string in){
    std::ifstream infile(in);
    std::ofstream outfile(in+"_decrypted");
    std::string line;
    while (getline(infile, line)){
        std::cout << line << std::endl;
        for (unsigned int i = 0; i < line.size(); i+=2){
            if (std::isdigit(line[i])){
                std::map<char, std::vector<std::string>>::iterator itr = key.begin();
                while (itr != key.end()){
                    for (unsigned int i = 0; i < itr->second.size(); i++){
                        if (itr->second[i] == line.substr(i, i+1)){
                            outfile << itr->first;
                        }
                    }
                    itr++;
                }
            }
            else{
                outfile << line[i];
            }
            
        }
    }

}


int main(int argc, char* argv[]){
    std::vector<char> alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    if (std::string(argv[3]) == "-1"){
        std::map<char, char> key = caesar_encrypt(alphabet, 3, argv[1], argv[2]);
        decrypt(key, alphabet, argv[2]);
    }

    if (std::string(argv[3]) == "-2"){
        std::vector<int> arrangement;
        for (unsigned int i = 0; i < 26; i++){
            arrangement.push_back(i);
        }
        srand(time(nullptr));
        std::random_shuffle(arrangement.begin(), arrangement.end());
        std::map<char, char> key2 = monoalphabetic_encrypt(alphabet, arrangement, argv[1], argv[2]);
        decrypt(key2, alphabet, argv[2]);
    }

    if (std::string(argv[3]) == "-3"){

        std::vector<int> letter_frq = {8, 2, 3, 4, 13, 2, 2, 6, 7, 1, 1, 4, 3, 7, 8, 2, 1, 6, 6, 9, 3, 1, 2, 1, 2, 1};
        std::vector<std::string> symbols;
        for (unsigned int i = 0; i < 105; i++){
            if (i / 10 < 1){
                std::string pad = "0" + std::to_string(i);
                symbols.push_back(pad);
                continue;
            }
            symbols.push_back(std::to_string(i));
        } 
        
        std::random_shuffle(symbols.begin(), symbols.end());

        int sum = 0;
        for (unsigned int i = 0; i < letter_frq.size(); i++){
            sum+=letter_frq[i];
        }

        
        std::map<char, std::vector<std::string>> key;
        int count = 0;
        for (unsigned int i = 0; i < alphabet.size(); i++){
            std::vector<std::string> symbol_assignments;
            key[alphabet[i]] = symbol_assignments;
            for (int j = 0; j < letter_frq[i]; j++){
                key[alphabet[i]].push_back(symbols[count]);
                count++;
            }
        }

        
        std::ifstream in_file(argv[1]);
        std::ofstream outfile(argv[2]);
        std::string line;

        while(getline(in_file, line)){
            for (unsigned int i = 0; i < line.size(); i++){
                if (std::count(alphabet.begin(), alphabet.end(), line[i]) > 0 ){
                    int random_index = random() % key[line[i]].size();
                    outfile << key[line[i]][random_index];
                }
                else{
                    outfile << line[i];
                }
                
            }
        }

        homophonic_decrypt(key, argv[2]);

        
    }



    
}


/*

functions: ascii art, cypher
output commands
take choice input
then take sentence to be cyphered
call cypher function.


*/