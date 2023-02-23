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

            std::cout << "in: ";
            getline(std::cin, line);
            std::ifstream input(line);

            std::cout << "out: ";
            getline(std::cin, line);
            std::ofstream output(line);

            std::cout << "cipher: ";
            getline(std::cin, line);
            std::string cipher = line;

            if (cipher == "caesar"){
                Message m;
                std::map<char, char> key = m.caesar_encrypt(3, input, output);
            }
        }

        if (line == "decrypt"){
            std::string line;

            std::cout << "key file: " << std::endl;
            getline(std::cin, line);
            std::ifstream key(line);
            //call function that parses key file and returns map 
            //the function reads first line for cipher type, then creates maps for the type

            std::cout << "encrypted file: " << std::endl;
            getline(std::cin, line);
            std::ifstream encrypted(line);

            //Message m;
            //m.decrypt()
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