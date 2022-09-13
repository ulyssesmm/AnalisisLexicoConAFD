#ifndef __AFD_HPP__
#define __AFD_HPP__

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
#include "tokens.hpp"

class Afd{
public:
    Afd()=default;
    Afd(string filename);
    ~Afd()=default;
    TOKEN yylex();
    string get_token_value();
    void error(string msg);
    void close_file();
private:
    // TODO: Agregar variables para contar las líneas del archivo
    ifstream file;
    string token_value;
    char c;
    int edo;
    map<int, map<int, int>> afd;
    map<char, int> cols;
    vector<bool> accept;
    char get_char();
    void open_file(string filename);    
    int line=1; 
};


#endif // !__AFD_HPP__
