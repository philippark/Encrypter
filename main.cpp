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
#include <sstream>
#include "message.h"

void print_title_screen(){
    std::ifstream title_screen("title_art.txt");
    std::string line;
    while (getline(title_screen, line)){
        std::cout << line << std::endl;
    }
    std::cout << std::endl;


}


void encrypt(){
    std::string in, out, cipher;
    std::cout << "Input file: ";
    std::cin >> in;
    std::cout << "Output file: ";
    std::cin >> out;
    std::cout << "Cipher: ";
    std::cin >> cipher;

    std::ifstream input(in);
    std::ofstream output(out);

    if (!input.good()){
        std::cout << "Invalid input file" << std::endl;
        return;
    }

    if (!output.good()){
        std::cout << "Invalid output file" << std::endl;
        return;
    }
}
    


void catalog(){
    std::cout << "x" << std::endl;
    return;
}

std::map<char, char> parse_caesar_key(std::ifstream &key_file){
    std::map<char, char> key;
    std::string line;
    while(getline(key_file, line)){
        key[line[0]] = line[3];
    }

    return key;
}

std::map<char, char> parse_monoalphabetic_key(std::ifstream &key_file){
    std::map<char, char> key;
    std::string line;
    while(getline(key_file, line)){
        key[line[0]] = line[3];
    }

    return key;
}

std::map<char, std::vector<std::string>> parse_homophonic_key(std::ifstream &key_file){
    std::cout << "working" << std::endl;
    std::map<char, std::vector<std::string>> key;
    std::string line;

    while(getline(key_file, line)){
        std::stringstream ss(line.substr(3));
        std::string symbol;
        while(getline(ss, symbol, ' ')){
            key[line[0]].push_back(symbol); 
        }
    }

    return key;
}


void user_input(){
    while(true){
        std::cout << "cyphen> ";
        std::string line;

        getline(std::cin, line);

        if (line == "q"){
            return;
        }

        if (line == "1"){
            catalog();
            continue;
        }

        if (line == "encrypt"){
            std::string file_name;

            std::cout << "in: ";
            getline(std::cin, line);
            std::ifstream input(line);
            file_name = line;

            if (!input.good()){
                std::cout << "Invalid input file " << std::endl;
            }

            std::cout << "cipher: ";
            getline(std::cin, line);
            std::string cipher = line;

            bool encrypted = false;
            if (cipher == "caesar"){
                Message m;
                m.caesar_encrypt(3, input, file_name);
                encrypted = true;
                
            }

            if (cipher == "monoalphabetic"){
                Message m;
                m.monoalphabetic_encrypt(input, file_name);
                encrypted = true;
            }

            if (cipher == "homophonic"){
                Message m;
                m.homophonic_encrypt(input, file_name);
                encrypted = true;
            }

            if (cipher == "vigenere"){
                std::string key_word;
                std::cout << "key word: ";
                getline(std::cin, key_word);

                Message m;
                m.vigenere_encrypt(key_word, input, file_name);
                encrypted = true;
            }

            if (encrypted){
                std::cout << std::endl;
                std::cout << "  Encrypted -> " << file_name.substr(0, file_name.size()-4) << "_encrypted.txt" << std::endl;
                std::cout << std::endl;

                encrypted = false;
            }

            
        }

        if (line == "decrypt"){
            std::string line;

            std::cout << "key file: ";
            getline(std::cin, line);
            std::ifstream key_file(line);

            std::string cipher;
            getline(key_file, cipher);

            std::cout << "encrypted file: ";
            getline(std::cin, line);
            std::ifstream encrypted(line);

            bool decrypted = false;

            if (cipher == "caesar"){
                std::map<char, char> key = parse_caesar_key(key_file);
                Message m;
                m.decrypt(key, encrypted);

                decrypted = true;

            }

            if (cipher == "monoalphabetic"){
                std::map<char, char> key = parse_monoalphabetic_key(key_file);
                Message m;
                m.decrypt(key, encrypted);

                decrypted = true;
            }

            if (cipher == "homophonic"){
                std::map<char, std::vector<std::string>> key = parse_homophonic_key(key_file);
                Message m;
                m.homophonic_decrypt(key, encrypted);

                decrypted = true;
            }

            if (cipher == "vigenere"){
                std::string keyword;
                getline(key_file, keyword);

                Message m;
                m.vigenere_decrypt(keyword, encrypted);

                decrypted = true;
            }

            if(decrypted){
                std::cout << std::endl;
                std::cout << "  Decrypted -> decrypted.txt" << std::endl;
                std::cout << std::endl;
            }

        }

        //store user input
        std::string word;
        std::istringstream command(line);

        std::vector<std::string> user_in;

        while(command >> word){
            user_in.push_back(word);
        }


    }
}

int main(int argc, char* argv[]){
    print_title_screen();
    user_input();


        

        
    
}