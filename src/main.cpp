#include <iostream>
//#include "afd.hpp"
#include "Afd.hpp"
using namespace std;

//extern string tvalue;

int main(int argc, char *argv[]){
    if(argc <2){
        cout<<"Faltan argumentos a main"<<endl;
        return EXIT_FAILURE;
    }    
    Afd lexer(argv[1]);; //Lexer *lexer = new Lexer();    
    auto token = lexer.yylex();
    while(token != FIN  ){ 
        cout<<"<Clase:"<<token<<", Valor: "<<lexer.get_token_value()<<">"<<endl;
        token = lexer.yylex();
    }
    lexer.close_file();
    return EXIT_SUCCESS;    
}