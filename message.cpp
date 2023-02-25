#include "message.h"



void Message::caesar_encrypt(int displacement, std::ifstream& in_file, std::string file_name){
    std::ofstream out_file(file_name.substr(0, file_name.size()-4) + "_encrypted.txt");
    std::map<char, char> caesar_key;

    unsigned int i = 0;
    for (i; i < alphabet.size() - displacement; i++){
        caesar_key[alphabet[i]] = alphabet[i+3];
    }
    //account for letters at the end
    for (int j = 0; j < displacement; j++, i++){
        caesar_key[alphabet[i]] = alphabet[j];
    }



    std::string line;


    while(getline(in_file, line)){
        for (unsigned int i = 0; i < line.size(); i++){
            if (isupper(line[i])){
                line[i] = tolower(line[i]);
            }
            if (std::count(alphabet.begin(), alphabet.end(), line[i]) > 0 ){
                out_file << caesar_key[line[i]];
            }
            else{
                out_file << line[i];
            }
            
        }
    }



    in_file.close();
    out_file.close();

    std::ofstream key_file(file_name.substr(0, file_name.size()-4) + "_key.txt");
    key_file << "caesar" << std::endl;
    for (std::map<char,char>::iterator i = caesar_key.begin(); i != caesar_key.end(); i++){
        key_file << i->first << ": " << i -> second << std::endl;
    }


}

void Message::monoalphabetic_encrypt(std::ifstream &in_file, std::string file_name){
    std::ofstream out_file(file_name.substr(0, file_name.size()-4) + "_encrypted.txt");

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

    std::string line;

    while(getline(in_file, line)){
        for (unsigned int i = 0; i < line.size(); i++){
            if (isupper(line[i])){
                line[i] = tolower(line[i]);
            }
            if (std::count(alphabet.begin(), alphabet.end(), line[i]) > 0 ){
                out_file << key[line[i]];
            }
            else{
                out_file << line[i];
            }
            
        }
    }
    
    std::ofstream key_file(file_name.substr(0, file_name.size()-4) + "_key.txt");
    key_file << "monoalphabetic" << std::endl;
    for (std::map<char,char>::iterator i = key.begin(); i != key.end(); i++){
        key_file << i->first << ": " << i -> second << std::endl;
    }
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



void Message::homophonic_encrypt(std::ifstream &in_file, std::string file_name){
        std::ofstream out_file(file_name.substr(0, file_name.size()-4) + "_encrypted.txt");

        std::map<char, std::vector<std::string>> key = create_homophonic_encryption();

        std::string line;

        while(getline(in_file, line)){
            for (unsigned int i = 0; i < line.size(); i++){
                if (isupper(line[i])){
                    line[i] = tolower(line[i]);
                }
                if (std::count(alphabet.begin(), alphabet.end(), line[i]) > 0 ){
                    int random_index = random() % key[line[i]].size();
                    out_file << key[line[i]][random_index] << "|";
                }
                else{
                    out_file << line[i];
                }
                
            }
        }
    
        std::ofstream key_file(file_name.substr(0, file_name.size()-4) + "_key.txt");
        key_file << "homophonic" << std::endl;
        for (std::map<char,std::vector<std::string>>::iterator i = key.begin(); i != key.end(); i++){
            key_file << i->first << ": ";
            std::vector<std::string> v = i->second;
            for (unsigned int j = 0; j < v.size(); j++){
                key_file << v[j] << " ";
            }
            key_file << std::endl;
        }

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

void Message::vigenere_encrypt(std::string keyword, std::ifstream &in_file, std::string file_name){
    std::ofstream out_file(file_name.substr(0, file_name.size()-4) + "_encrypted.txt");

    create_vigenere_table();

    std::string line;

    int word_count = 0;
    int key_count = 0;

    
    while(getline(in_file, line)){
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

                out_file << vigenere_table[keyword[key_count]][word_index];

                key_count++;
            }
            else{
                out_file << line[i];
            }
        }
    }

    in_file.close();
    out_file.close();

    std::ofstream key_file(file_name.substr(0, file_name.size()-4) + "_key.txt");

    key_file << "vigenere" << std::endl;
    key_file << keyword << std::endl;
    for (std::map<char,std::vector<char>>::iterator i = vigenere_table.begin(); i != vigenere_table.end(); i++){
        key_file << i->first << ": ";
        std::vector<char> v = i->second;
        for (unsigned int j = 0; j < v.size(); j++){
            key_file << v[j] << " ";
        }
        key_file << std::endl;
    }

    
    
}


void Message::decrypt(std::map<char, char>& key, std::ifstream& in_file){
    std::ofstream out_file("decrypted.txt");
    std::string line;
    while (getline(in_file, line)){
        for (unsigned int i = 0; i < line.size(); i++){
            if (std::count(alphabet.begin(), alphabet.end(), line[i]) > 0 ){
                std::map<char, char>::iterator itr = key.begin();
                while (itr != key.end()){
                    if (itr->second == line[i]){
                        out_file << itr->first;
                    }
                    itr++;
                }
            }
            else{
                out_file << line[i];
            }
            
        }
    }

    in_file.close();
    out_file.close();
}


void Message::homophonic_decrypt(std::map<char, std::vector<std::string>>& key, std::ifstream &in_file){
    std::ofstream out_file("decrypted.txt");
    std::string line;

    while(getline(in_file, line)){
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
                    out_file << itr->first;
                    }
                }
                itr++;
                }
                word = "";
                if (line[i] != '|'){
                    out_file << line[i];
                }
            }
            
        }

    }

    in_file.close();
    out_file.close();

}


void Message::vigenere_decrypt(std::string keyword, std::ifstream &in_file){
    std::ofstream out_file("decrypted.txt");

    create_vigenere_table();

    std::string line;
    
    int key_count = 0;

    while(getline(in_file, line)){
        for (unsigned int i = 0; i < line.size(); i++){
            if (std::count(alphabet.begin(), alphabet.end(), line[i]) > 0){
                if(key_count == keyword.size()){
                    key_count = 0;
                }

                auto pos = std::find(vigenere_table[keyword[key_count]].begin(), vigenere_table[keyword[key_count]].end(), line[i]);
                int index = pos - vigenere_table[keyword[key_count]].begin();

                out_file << alphabet[index];


                key_count++;
            }   
            else{
                out_file << line[i];
            }
        }
    }
}