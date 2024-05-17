// Feito por: Matheus Herminio Da Silva
// RA: 201027747
// Compilado pelo: GCC++ do DevC++
// Sistema operacional: Windows 10  
#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <Windows.h>
#include <time.h>
#include <locale.h>
#include <ctype.h>
using namespace std;

map<string, string> identy;
string tens = "0";
string unit = "0";
string res;
string next;
FILE *filename;

///////////////////////////////// APRESENTACAO DO ARQUIVO //////////////////////////////////////////////////
void type(const char * p){
	
	
	if (NULL == p)
		return;
		
	while (*p){
		
		printf("%c\xDB", *p++);
		
		::Sleep(25);
		
		printf("\b \b"); 
		
		::Sleep(25);
		
		}
		::Sleep(250);
}  // Faz a animação de digitar no type

void apresentacao(){
	
	struct tm *data_hora_atual;     
  time_t segundos;
  
  time(&segundos);   
  
  data_hora_atual = localtime(&segundos);  
  
	type("Ola usuario! \n\n");
	type("Trabalho II de Compiladores \n \n");
	type("Feito Por: Matheus Herminio Da Silva\n\n");
	
	
  type("Data de hoje: ");
  printf("%d/", data_hora_atual->tm_mday);  
  printf("%d/", data_hora_atual->tm_mon+1);
  printf("%d\n\n", data_hora_atual->tm_year+1900);  
  
  
	Sleep(3000);
	
	system("cls");
	
} 
///////////////////////////////////////////////////////////////////////////////////////////////////////////

char Row[100];
int cnt = 1;
int numNxt;

char Func_Next(string result, int numNxt);

string CODE(string code);

int sub_func();

int term();

int factor();

int variable();

int Number();

int identifier();

int procedure_decl();

int compose_command();

int command();

void error(int cnt, int tipo);

int programs();

int block();

int part_varible_decl();

int varible_decl();

int list_identy();

int command_no_rotu();

int atrib();

int call_procedure();

int command_condi();

int command_repeat();

int list_expr();

int expre();

int relation();

int expre_simple();

bool EspecSymb(string next);

bool ResWord(string next);

bool letter(string next);

bool digit(string next);


bool letter(string next){
char p = next[0];
    if((p >= 65 && p <= 90) || (p >= 97 && p <= 122)){
        return true;
    }

    return false;
}

bool digit(string next){
char p = next[0];
    if(p >= 48 && p <= 57){
        return true;
    }

    return false;
}

bool EspecSymb(string next){
    char p = next[0];
    if((p >= 40 && p <= 46) || (p >= 58 && p <= 62)){
        return true;
    }

    return false;
}

bool ResWord(string next){
if(next == "program" || next == "var" || next == "integer" || next == "begin" ||
    next == "procedure" || next == "do" || next == "div" || next == "if" || next == "then" ||
    next == "else" || next == "end" || next == "read" || next == "while" || next == "write"||
    next == "boolean" || next == "or" || next == "and" || next == "not"){
        return true;
    }

    return false;
}

char Func_Next(string result, int pos){
if(next == "\n" && pos != 0){
    if(!feof(filename)){
            cnt++;
            result = fgets(Row, 100, filename);
            res = result;
            numNxt = 0;
            pos = 0;
        }
    }
    return result[pos];
}

string CODE(string code){
	
    if(code == "program"){
        code = "p";
        
    }else if(code == "var"){
        code = "v";
        
    }else if(code == "integer"){
        code = "i";
        
    }else if(code == "begin"){
        code = "b";
        
    }else if(code == "do"){
        code = "d";
        
    }else if(code == "write"){
        code = "wr";
        
    }else if(code == "or"){
        code = "o";
        
    }else if(code == "and"){
        code = "a";
        
    }else if(code == "boolean"){
        code = "z";
        
    }else if(code == "procedure"){
        code = "pr";
        
    }else if(code == "div"){
        code = "/";
        
    }else if(code == "then"){
        code = "t";
        
    }else if(code == "end"){
        code = "f";
        
    }else if(code == "read"){
        code = "r";
    
     }else if(code == "if"){
        code = "s";
        
    }else if(code == "else"){
        code = "e";
	    
    }else if(code == "while"){
        code = "w";
        
    }else if(code == "not"){
        code = "n";
        
    }else if(EspecSymb(code)){
        return code;
        
    }else if(identy.count(code)){
        code = identy[code];
        
    }else{
        string novoId;
        if(unit == "9"){
            unit = "0";
            tens[0]++;
        }else{
        	
            unit[0]++;
        }

        if(tens == "0"){
            novoId = "id" + unit;
            
        }else{
        	
            novoId = "id" + tens + unit;
        }

        identy[code] = novoId;
        code = novoId;
    }

    return code;
}

void error(int cnt, int tipo){
    if(tipo == 2){
        cout << "\n\nErro de caractere invalido na linha " << cnt << "\n";
    }else if(tipo == 1){
        cout << "\n\nErro de numero mal formado na linha " << cnt << "\n";
    }else{
        cout << "\n\nErro de sintaxe na linha " << cnt << "\n";
    }
}

int block(){
if(!part_varible_decl()){
        return 0;
    }
    sub_func();
    return compose_command();
}

int part_varible_decl(){
if(next == "\n"){
        next = Func_Next(res, ++numNxt);
    }

    while(next != "\n" && next != "\r" && numNxt < res.size()){
    if(next == " "){
            next = Func_Next(res, ++numNxt);
            continue;
            
        }else if(next == "\t"){
            next = Func_Next(res, ++numNxt);
            continue;
            
        }else if(letter(next)){
        if(next == "v"){
                next = Func_Next(res, ++numNxt);
                return varible_decl();
            }
        }
    }

    return 0;
}

int varible_decl(){
    if(next == "\n"){
        next = Func_Next(res, ++numNxt);
    }

    while(next != "\n" && next != "\r" && numNxt < res.size()){
        if(next == " "){
            next = Func_Next(res, ++numNxt);
            continue;
            
        }else if(next == "\t"){
            next = Func_Next(res, ++numNxt);
            continue;
            
        }while(next == "i"){
            if(list_identy()){
                if(next == ":"){
                    next = Func_Next(res, ++numNxt);
                    
                }else{
                    return 0;
                }

                if(next == "i" || next == "z"){
                    next = Func_Next(res, ++numNxt);
                    if(next == ";"){
                        next = Func_Next(res, ++numNxt);
                        
                    }else{
                        return 0;
                    }
                    if(!feof(filename)){
                        next = Func_Next(res, ++numNxt);
                        if(next != "i"){
                            return 1;
                        }
                    }else{
                        return 1;
                    }
                }else{
                    return 0;
                }
            }else{
                return 0;
            }
        }
    }

    return 0;
}

int programs(){
if (!res.empty()){  
    next = res[0];
	numNxt = 0;

        while(next != "\n" && next != "\r" && numNxt < res.size()){
            if(next == " "){
                next = Func_Next(res, ++numNxt);
                cout << " ";
                continue;
                
            }else if(next == "\t"){
                next = Func_Next(res, ++numNxt);
                continue;
                
            }else if(letter(next)){
                if(next == "p"){
                    next = Func_Next(res, ++numNxt);
                    if(identifier()){
                        return block();
                        
                    }else{
                        return 0;
                    }
                }
            }
        }
    }
    return 0;
}

int sub_func(){
    return procedure_decl();
}

int list_identy(){
if(next == "\n"){
        next = Func_Next(res, ++numNxt);
    }

    while(next != "\n" && next != "\r" && numNxt < res.size()){
        if(next == " "){
            next = Func_Next(res, ++numNxt);
            continue;
            
        }else if(next == "\t"){
            next = Func_Next(res, ++numNxt);
            continue;
        }
        while(next != ":" && next != "\n"){
            if(identifier()){
                if(next == ","){
                    next = Func_Next(res, ++numNxt);
                    
                }else{
                    if(next != ":"){
                        return 0;
                    }
                }
            }
        }
        return 1;
    }

    return 0;
}

int procedure_decl(){
if(next == "\n"){
        next = Func_Next(res, ++numNxt);
    }

    while(next != "\n" && next != "\r" && numNxt < res.size()){
    if(next == " "){
            next = Func_Next(res, ++numNxt);
            continue;
            
        }else if(next == "\t"){
            next = Func_Next(res, ++numNxt);
            continue;
            
        }else if(letter(next)){
            if(next == "p"){
                next = Func_Next(res, ++numNxt);
                if(next == "r"){
                    next = Func_Next(res, ++numNxt);
                    if(identifier()){
                        if(next == ";"){
                            next = Func_Next(res, ++numNxt);
                            return block();
                            
                        }else{
                            return 0;
                        }
                        
                    }else{
                        return 0;
                    }
                    
                }else{
                    return 0;
                }
                
            }else{
                return 0;
            }
        }
    }

    return 0;
}

int compose_command(){
if(next == "\n"){
        next = Func_Next(res, ++numNxt);
    }

    while(next != "\n" && next != "\r" && numNxt < res.size()){
    if(next == " "){
            next = Func_Next(res, ++numNxt);
            continue;
            
        }else if(next == "\t"){
            next = Func_Next(res, ++numNxt);
            continue;
            
        }else if(letter(next)){
            if(next == "b"){
                next = Func_Next(res, ++numNxt);
                while(next != "f"){
                    if(!command()){
                        return 0;
                    }
                    if(next != ";" && next != "\n" && next != "f"){
                        return 0;
                    }else{
                        if(next != "f"){
                            next = Func_Next(res, ++numNxt);
                        }
                    }
                    if(next == "\n"){
                        next = Func_Next(res, ++numNxt);
                    }
                }
                next = Func_Next(res, ++numNxt);
                if(next == ";" || next == "."){
                    next = Func_Next(res, ++numNxt);
                }
                return 1;
                
            }else{
                return 0;
            }
            
        }else{
            return 0;
        }
    }

    return 0;
}

int command(){
if(next == "\n"){
        next = Func_Next(res, ++numNxt);
    }

    while(next != "\n" && next != "\r" && numNxt < res.size()){
        if(next == " "){
            next = Func_Next(res, ++numNxt);
            continue;
            
        }else if(next == "\t"){
            next = Func_Next(res, ++numNxt);
            continue;
            
        }else if(!digit(next)){
            return command_no_rotu();
        }
    }

    return 0;
}

int command_no_rotu(){
if(next == "\n"){
        next = Func_Next(res, ++numNxt);
    }

    while(next != "\n" && next != "\r" && numNxt < res.size()){
        if(next == " "){
            next = Func_Next(res, ++numNxt);
            continue;
            
        }else if(next == "\t"){
            next = Func_Next(res, ++numNxt);
            continue;
            
        }else if(!digit(next)){
            return (atrib() || call_procedure() || compose_command()
                    || command_condi() || command_repeat());
        }
    }

    return 0;
}

int atrib(){
if(next == "\n"){
        next = Func_Next(res, ++numNxt);
    }

    while(next != "\n" && next != "\r" && numNxt < res.size()){
    if(next == " "){
            next = Func_Next(res, ++numNxt);
            continue;
            
        }else if(next == "\t"){
            next = Func_Next(res, ++numNxt);
            continue;
            
        }else if(variable()){
            if(next == ":"){
                next = Func_Next(res, ++numNxt);
                if(next == "="){
                    next = Func_Next(res, ++numNxt);
                    return expre();
                    
                }else{
                    return 0;
                }
                
            }else{
                while(next != "i"){
                    next = Func_Next(res, --numNxt);
                }
                return 0;
            }
            
        }else{
            return 0;
        }
    }

    return 0;
}

int call_procedure(){
if(next == "\n"){
        next = Func_Next(res, ++numNxt);
    }

    while(next != "\n" && next != "\r" && numNxt < res.size()){
        if(next == " "){
            next = Func_Next(res, ++numNxt);
            continue;
            
        }else if(next == "\t"){
            next = Func_Next(res, ++numNxt);
            continue;
        }
        if(identifier()){
            while(next != ";"){
                if(!list_expr()){
                    return 0;
                }
                if(next == ","){
                    next = Func_Next(res, ++numNxt);
                    
                }else if(next != ";"){
                    return 0;
                }
            }
            return 1;
            
        }else if(next == "r"){
            next = Func_Next(res, ++numNxt);
            while(next != ";"){
                if(!list_expr()){
                    return 0;
                }
                if(next == ","){
                    next = Func_Next(res, ++numNxt);
                    
                }else if(next != ";"){
                    return 0;
                }
            }
            return 1;
            
        }else if(next == "w"){
            next = Func_Next(res, ++numNxt);
            if(next == "r"){
                next = Func_Next(res, ++numNxt);
                while(next != ";"){
                    if(!list_expr()){
                        return 0;
                    }
                    if(next == ","){
                        next = Func_Next(res, ++numNxt);
                        
                    }else if(next != ";"){
                        return 0;
                    }
                }
                return 1;
                
            }else{
                next = Func_Next(res, --numNxt);
                return 0;
            }
            
        }else{
            return 0;
        }
    }

    return 0;
}

int command_condi(){
if(next == "\n"){
        next = Func_Next(res, ++numNxt);
    }

    while(next != "\n" && next != "\r" && numNxt < res.size()){
        if(next == " "){
            next = Func_Next(res, ++numNxt);
            continue;
            
        }else if(next == "\t"){
            next = Func_Next(res, ++numNxt);
            continue;
        }
        if(next == "s"){
            next = Func_Next(res, ++numNxt);
            if(expre()){
                if(next == "t"){
                    next = Func_Next(res, ++numNxt);
                    if(command_no_rotu()){
                        if(next == ";"){
                            next = Func_Next(res, ++numNxt);
                            if(next == "\n"){
                                next = Func_Next(res, ++numNxt);
                            }
                            
                        }else{
                            return 0;
                        }
                        if(next == "e"){
                            next = Func_Next(res, ++numNxt);
                            if(command_no_rotu()){
                                if(next == ";"){
                                    next = Func_Next(res, ++numNxt);
                                    
                                }else{
                                    return 0;
                                }
                                return 1;
                            }else{
                                return 0;
                            }
                        }
                        return 1;
                    }else{
                        return 0;
                    }
                }else{
                    return 0;
                }
            }else{
                return 0;
            }
        }else{
            return 0;
        }
    }

    return 0;
}

int command_repeat(){
if(next == "\n"){
        next = Func_Next(res, ++numNxt);
    }

    while(next != "\n" && next != "\r" && numNxt < res.size()){
    if(next == " "){
            next = Func_Next(res, ++numNxt);
            continue;
            
        }else if(next == "\t"){
            next = Func_Next(res, ++numNxt);
            continue;
        }
        if(next == "w"){
            next = Func_Next(res, ++numNxt);
            if(expre()){
                if(next == "d"){
                    next = Func_Next(res, ++numNxt);
                    if(command_no_rotu()){
                        next = Func_Next(res, ++numNxt);
                        return 1;
                        
                    }else{
                        return 0;
                    }
                    
                }else{
                    return 0;
                }
                
            }else{
                return 0;
            }
        }else{
            return 0;
        }
    }

    return 0;
}

int list_expr(){
if(next == "\n"){
        next = Func_Next(res, ++numNxt);
    }

    while(next != "\n" && next != "\r" && numNxt < res.size()){
        if(next == " "){
            next = Func_Next(res, ++numNxt);
            continue;
            
        }else if(next == "\t"){
            next = Func_Next(res, ++numNxt);
            continue;
        }
        if(expre()){
            while(expre()){
                next = Func_Next(res, ++numNxt);
            }
            return 1;
            
        }else{
            return 0;
        }
    }

    return 0;
}

int expre(){
if(next == "\n"){
        next = Func_Next(res, ++numNxt);
    }

    while(next != "\n" && next != "\r" && numNxt < res.size()){
        if(next == " "){
            next = Func_Next(res, ++numNxt);
            continue;
            
        }else if(next == "\t"){
            next = Func_Next(res, ++numNxt);
            continue;
        }
        if(expre_simple()){
            while(relation()){
                if(!expre_simple()){
                    return 0;
                }
            }
            return 1;
            
        }else{
            return 0;
        }
    }

    return 0;
}

int relation(){
if(next == "\n"){
        next = Func_Next(res, ++numNxt);
    }

    while(next != "\n" && next != "\r" && numNxt < res.size()){
    if(next == " "){
            next = Func_Next(res, ++numNxt);
            continue;
            
        }else if(next == "\t"){
            next = Func_Next(res, ++numNxt);
            continue;
        }
        if(next == "="){
            next = Func_Next(res, ++numNxt);
            return 1;
            
        }else if(next == "<"){
            next = Func_Next(res, ++numNxt);
            if(next == "=" || next == ">"){
                next = Func_Next(res, ++numNxt);
            }
            return 1;
            
        }else if(next == ">"){
            next = Func_Next(res, ++numNxt);
            if(next == "="){
                next = Func_Next(res, ++numNxt);
            }
            return 1;
        }else{
            return 0;
        }
    }

    return 0;
}

int expre_simple(){
if(next == "\n"){
        next = Func_Next(res, ++numNxt);
    }

    while(next != "\n" && next != "\r" && numNxt < res.size()){
        if(next == " "){
            next = Func_Next(res, ++numNxt);
            continue;
            
        }else if(next == "\t"){
            next = Func_Next(res, ++numNxt);
            continue;
            
        }else if(next == "+" || next == "-"){
            next = Func_Next(res, ++numNxt);
        }
        if(!term()){
            return 0;
            
        }else{
            while(next == "+" || next == "-" || next == "o"){
                next = Func_Next(res, ++numNxt);
                if(!term()){
                    return 0;
                }
            }
            return 1;
        }
    }

    return 0;
}

int term(){
if(next == "\n"){
        next = Func_Next(res, ++numNxt);
    }

    while(next != "\n" && next != "\r" && numNxt < res.size()){
        if(next == " "){
            next = Func_Next(res, ++numNxt);
            continue;
            
        }else if(next == "\t"){
            next = Func_Next(res, ++numNxt);
            continue;
        }
        if(!factor()){
            return 0;
            
        }else{
            while(next == "*" || next == "/" || next == "a"){
                next = Func_Next(res, ++numNxt);
                if(!factor()){
                    return 0;
                }
            }
            return 1;
        }
    }

    return 0;
}

int factor(){
if(next == "\n"){
        next = Func_Next(res, ++numNxt);
    }

    while(next != "\n" && next != "\r" && numNxt < res.size()){
    if(next == " "){
            next = Func_Next(res, ++numNxt);
            continue;
            
        }else if(next == "\t"){
            next = Func_Next(res, ++numNxt);
            continue;
        }
        if(variable() || Number()){
            return 1;
            
        }else if(next == "("){
            next = Func_Next(res, ++numNxt);
            if(!expre()){
                return 0;
            }
            if(next == ")"){
                next = Func_Next(res, ++numNxt);
                return 1;
                
            }else{
                return 0;
            }
            
        }else if(next == "n"){
            if(!factor()){
                return 0;
            }else{
                return 1;
            }
        }else{
            return 0;
        }
    }

    return 0;
}

int variable(){
    return identifier();
}

int Number(){
if(next == "\n"){
        next = Func_Next(res, ++numNxt);
    }

    while(next != "\n" && next != "\r" && numNxt < res.size()){
        if(next == " "){
            next = Func_Next(res, ++numNxt);
            continue;
            
        }else if(next == "\t"){
            next = Func_Next(res, ++numNxt);
            continue;
        }
        if(digit(next)){
            next = Func_Next(res, ++numNxt);
            while(digit(next)){
                next = Func_Next(res, ++numNxt);
            }
            return 1;
            
        }else{
            return 0;
        }
    }

    return 0;
}

int identifier(){
if(next == "\n"){
        next = Func_Next(res, ++numNxt);
    }

    while(next != "\n" && next != "\r" && numNxt < res.size()){
        if(next == " "){
            next = Func_Next(res, ++numNxt);
            continue;
            
        }else if(next == "\t"){
            next = Func_Next(res, ++numNxt);
            continue;
            
        }else if(letter(next)){
            if(next == "i"){
                next = Func_Next(res, ++numNxt);
                if(next == "d"){
                    next = Func_Next(res, ++numNxt);
                    if(digit(next)){
                        next = Func_Next(res, ++numNxt);
                        while(digit(next)){
                            next = Func_Next(res, ++numNxt);
                        }
                        return 1;
                        
                    }else{
                        return 0;
                    }
                    
                }else{
                    return 0;
                }
                
            }else{
                return 0;
            }
            
        }else{
            return 0;
        }
    }

    return 0;
}

int main(){

apresentacao();
	
ofstream f_out;
f_out.open("Arquivo_Intermediario.txt");
string result;

    filename = fopen("Exemplo1_Trab2_Compiladores.txt", "rt");
    if (filename == NULL){
        printf("Houve um erro na abertura do arquivo, por favor verifique o nome do arquivo\n");
        return 0;
    }

    while (!feof(filename)){
        result = fgets(Row, 100, filename);
        if (!result.empty()){  
            cout << cnt << " ";
            next = result[0];
            numNxt = 0;

            while(next != "\n" && next != "\r" && numNxt < result.size()){
                string atom;
                string symbol;

                if(next == " "){
                    next = Func_Next(result, ++numNxt);
                    cout << " ";
                    continue;
                    
                }else if(next == "\t"){
                    next = Func_Next(result, ++numNxt);
                    continue;
                    
                }else if(EspecSymb(next)){ 
                    string s = next;
                    next = Func_Next(result, ++numNxt);

                    if(s == ":" && next == "="){
                        s = ":=";
                        next = Func_Next(result, ++numNxt);
                    }

                    symbol = CODE(s);
                    
                }else if(letter(next)){
                    do{
                        atom += next;
                        next = Func_Next(result, ++numNxt);
                    }while(letter(next) || digit(next));

                    symbol = CODE(atom);
                    
                }else if(digit(next)){
                    do{
                        atom += next;
                        next = Func_Next(result, ++numNxt);
                    }while(digit(next));

                    if(letter(next)){
                        error(cnt, 1);
                        return 0;
                    }

                    symbol = atom;
                    
                }else{
                	
                    error(cnt, 2);
                    return 0;
                }
                cout << symbol;
                f_out << symbol;
            }
            cout << "\n";
            f_out << "\n";
        }
        cnt++;
    }
    fclose(filename);
    f_out.close();

    filename = fopen("Arquivo_Intermediario.txt", "rt");
    if(filename == NULL){
        cout << "\nProblema na abertura do filename auxiliar\n";
        return 0;
    }

    res = fgets(Row, 100, filename);

    cnt = 1;

    int compilacao = programs();

    if(compilacao){
       type("\nCompilado com sucesso"); 
    }
    else{
        error(cnt, 3);
    }

    return 0;
}
