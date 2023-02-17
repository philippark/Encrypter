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
                if (isupper(line[i])){
                    line[i] = tolower(line[i]);
                }
                outfile << caesar_key[line[i]];
            }
            else{
                outfile << line[i];
            }
            
        }
    }

    in_file.close();
    outfile.close();
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
                if (isupper(line[i])){
                    line[i] = tolower(line[i]);
                }
                outfile << key[line[i]];
            }
            else{
                outfile << line[i];
            }
            
        }
    }
    
    return key;
}

std::map<char, std::vector<std::string>> Message::create_homophonic_encryption(){
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

    return key;
}



std::map<char, std::vector<std::string>> Message::homophonic_encrypt(std::string in, std::string out){
        std::map<char, std::vector<std::string>> key = create_homophonic_encryption();

        
        std::ifstream in_file(in);
        std::ofstream outfile(out);
        std::string line;

        while(getline(in_file, line)){
            for (unsigned int i = 0; i < line.size(); i++){
                if (std::count(alphabet.begin(), alphabet.end(), line[i]) > 0 ){
                    if (isupper(line[i])){
                        line[i] = tolower(line[i]);
                    }
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
    for(unsigned int i = 0; i < alphabet.size(); i++){
        std::vector<char> x;
        for (unsigned j = i; j < alphabet.size(); j++){
            x.push_back(alphabet[j]);
        }
        for (unsigned int z = 0; z < i; z++){
            x.push_back(alphabet[z]);
        }
        vigenere_table[alphabet[i]] = x;
    }
}

void Message::vigenere_encrypt(std::string keyword, std::string in, std::string out){
    create_vigenere_table();

    std::ifstream infile(in);
    std::ofstream outfile(out);
    std::string line;

    int word_count = 0;
    int key_count = 0;

    
    while(getline(infile, line)){
        for (unsigned int i = 0; i < line.size(); i++){
            if (isupper(line[i])){
                line[i] = tolower(line[i]);
            }

            if (std::count(alphabet.begin(), alphabet.end(), line[i]) > 0){
                if (key_count == keyword.size()){
                    key_count = 0;
                }

                auto pos = std::find(alphabet.begin(), alphabet.end(), line[i]);
                int word_index = pos - alphabet.begin();

                outfile << vigenere_table[keyword[key_count]][word_index];

                key_count++;
            }
            else{
                outfile << line[i];
            }
        }
    }

    infile.close();
    outfile.close();
    
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

    infile.close();
    outfile.close();
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

    infile.close();
    outfile.close();

}


void Message::vigenere_decrypt(std::string keyword, std::string in){
    std::ifstream infile(in);
    std::ofstream outfile(in + "_decrypted.txt");

    std::string line;
    
    int key_count = 0;

    while(getline(infile, line)){
        for (unsigned int i = 0; i < line.size(); i++){
            if (std::count(alphabet.begin(), alphabet.end(), line[i]) > 0){
                if(key_count == keyword.size()){
                    key_count = 0;
                }

                auto pos = std::find(vigenere_table[keyword[key_count]].begin(), vigenere_table[keyword[key_count]].end(), line[i]);
                int index = pos - vigenere_table[keyword[key_count]].begin();

                outfile << alphabet[index];


                key_count++;
            }   
            else{
                outfile << line[i];
            }
        }
    }
}