#include "message.h"



std::map<char, char> Message::caesar_encrypt(int displacement, std::string input, std::string output){
    std::map<char, char> caesar_key;

    unsigned int i = 0;
    for (i; i < alphabet.size() - displacement; i++){
        caesar_key[alphabet[i]] = alphabet[i+3];
    }
    //account for letters at the end
    for (int j = 0; j < displacement; j++, i++){
        caesar_key[alphabet[i]] = alphabet[j];
    }



    std::ifstream in_file(input);
    std::ofstream outfile(output);
    std::string line;


    while(getline(in_file, line)){
        for (unsigned int i = 0; i < line.size(); i++){
            if (std::count(alphabet.begin(), alphabet.end(), line[i]) > 0 ){
                outfile << caesar_key[line[i]];
            }
            else{
                outfile << line[i];
            }
            
        }
    }

    return caesar_key;

}

std::map<char, char> Message::monoalphabetic_encrypt(std::string in, std::string out){
    std::vector<int> arrangement;
    for (unsigned int i = 0; i < 26; i++){
        arrangement.push_back(i);
    }
    srand(time(nullptr));
    std::random_shuffle(arrangement.begin(), arrangement.end());
    std::map<char, char> key;

    for (unsigned int i = 0; i < arrangement.size(); i++){
        key[alphabet[i]] = alphabet[arrangement[i]];
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

std::map<char, std::vector<std::string>> Message::homophonic_encrypt(std::string in, std::string out){
        std::vector<std::string> symbols;
        //create symbols
        for (unsigned int i = 0; i < 105; i++){
            if (i / 10 < 1){
                std::string pad = "0" + std::to_string(i);
                symbols.push_back(pad);
                continue;
            }
            symbols.push_back(std::to_string(i));
        } 
        
        std::random_shuffle(symbols.begin(), symbols.end());

        //assign symbols
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

        
        std::ifstream in_file(in);
        std::ofstream outfile(out);
        std::string line;

        while(getline(in_file, line)){
            for (unsigned int i = 0; i < line.size(); i++){
                if (std::count(alphabet.begin(), alphabet.end(), line[i]) > 0 ){
                    int random_index = random() % key[line[i]].size();
                    outfile << key[line[i]][random_index] << "|";
                }
                else{
                    outfile << line[i];
                }
                
            }
        }
    
        return key;

}

void Message::create_vigenere_table(){
    std::map<char, std::vector<char>> vigenere_table;

    for(unsigned int i = 0; i < alphabet.size(); i++){
        std::cout << "a: ";
        std::vector<char> x;
        for (unsigned j = i; j < alphabet.size(); j++){
            std::cout << alphabet[j] << " ";
            x.push_back(alphabet[j]);
        }
        for (unsigned int z = 0; z < i; z++){
            std::cout << alphabet[z] << " ";
            x.push_back(alphabet[z]);
        }
        std::cout << std::endl;
        vigenere_table[alphabet[i]] = x;
    }
}

void Message::vigenere_encrypt(std::string keyword, std::string in){
    //let numbers represent alphabets. for ex: [2][2] is C C on table
    create_vigenere_table();

    

}


void Message::decrypt(std::map<char, char>& key, std::string in){
    std::ifstream infile(in);
    std::ofstream outfile(in+"_decrypted.txt");
    std::string line;
    while (getline(infile, line)){
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


void Message::homophonic_decrypt(std::map<char, std::vector<std::string>>& key, std::string in){
    std::ifstream infile(in);
    std::ofstream outfile(in+"_decrypted.txt");
    std::string line;

    while(getline(infile, line)){
        std::string word = "";
        for (unsigned int i = 0; i < line.size(); i++){
            if(std::isdigit(line[i])){
                std::string digit(1, line[i]);
                word += digit;
            }
            else{
                std::map<char, std::vector<std::string>>::iterator itr = key.begin();
                while (itr != key.end()){
                for (unsigned int i = 0; i < itr->second.size(); i++){
                    if (itr->second[i] == word){
                    outfile << itr->first;
                    }
                }
                itr++;
                }
                word = "";
                if (line[i] != '|'){
                    outfile << line[i];
                }
            }
            
        }

    }

}