#include "Afd.hpp"

Afd::Afd(string file)
{
    open_file(file);
    //TODO: Agregar las transiciones de acuerdo a la tabla obtenida en clase
    afd = {
        {0, {{1,1}, {2,2}, {5,7}}},
        {1, {{1,1}, {2,2}}},
        {2, {{1,3}}},
        {3, {{1,3}, {3,4}}},
        {4, {{1,6}, {4,5}}},
        {5, {{1,6}}},
        {6, {{1,6}}}
    };

    // TODO: Agregar las columnas para los caractres
    cols = {
        {'0', 1} ,{'1',1}, {'2', 1}, {'3',1}, {'4',1}, {'5',1}, {'6',1}, {'7',1}, {'8',1}, {'9',1},
        {'.',2}, {'E',3}, {'e',3}, {'+',4}, {'-',4}, {' ',5}, {'\n',5}, {'\t',5}, {'\r',5}, {'\v',5},
    };

    // TODO: Agregar los estados de aceptación
    accept = {
        false, true, false, true, false, false, true, true
    };
    c = get_char();
}


string Afd::get_token_value()
{
    return token_value;
}
void Afd::error(string msg)
{
    cout<<msg<<endl;
    close_file();
    exit(EXIT_FAILURE);
}

void Afd::close_file(){
    if(file.is_open()) file.close();
}

char Afd::get_char()
{
    if(!file.eof()){
        return file.get();
    }
    return EOF;
}

void Afd::open_file(string filename)
{
    file.open(filename, ios::in);
    if(!file.is_open()) error("El archivo no se encuentra");
}
TOKEN Afd::yylex()
{
    edo = 0;        
    string buffer="";
    map<int, int>::iterator row;    
    map<char, int>::iterator col;
    while(true){
        col = cols.find(c);
        row = afd[edo].find(col->second);
        if(c==EOF && buffer=="") return FIN;
        if(row != afd[edo].end()){
            buffer += c;
            edo = row->second;
            c = get_char();            
        }else{
            
            if(accept[edo]){                
                token_value = buffer;
                switch (edo)
                {
                // TODO: Agregar los casos para que se retornen correctamente los tokens
                case 1:                        
                    return ENTERO;
                case 3: case 6:
                    return REAL;
                case 7:
                    if(c=='\n') line++;
                    token_value ="";
                    buffer = "";
                    c = get_char();
                    edo = 0;
                    break;                
                }                
            }else{
                c= get_char();
                return ERROR;            
            }
        }
    }
}