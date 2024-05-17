// Feito Por: Matheus Herminio Da Silva
// RA: 201027747
// Compilado no GCC 64 bits em um Windows 10 64 bits

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
          
#define max_simbolo 12 
#define max_palavra 20  
#define max_atomo 1000                 

int varSimbolo; 

typedef long long int lld;

//Par de identificador e atomo
typedef struct par parSimbolo;
struct par{
    int ident;           //Salva o identificador (número) do átomo associado
    char atomo[max_atomo];    //Salva o átomo associado
};

//Tabela de Símbolos por LISTA ENCADEADA (não se sabe o limite de átomos...)
typedef struct simbolo *table;
struct simbolo{
    parSimbolo par;    //Par com o identificador e o átomo (palavra) associada
    struct simbolo *prox;
};
table simboloTabela;

///////////////////////////////////////////////////////////
//* FUNÇÕES DO ANALISADOR LÉXICO *//
///////////////////////////////////////////////////////////
//Função PROXIMO: responsável por pular linhas vazias e espaços em branco
char PROXIMO(FILE *arquivo){
    return toupper(fgetc(arquivo));
}
///////////////////////////////////////////////////////////
//Função CÓDIGO: responsável por verificar na tabela (matriz) de símbolos os identificadores e seus respectivos átomos associados!
//Insere caso não esteja contido na tabela...
int CODIGO(char *atomo, lld *contaTabelaSimbolo){
    //Percorre a tabela de símbolos em busca do átomo associado
    table p = simboloTabela;
    while(p){
        if(strcmp(p->par.atomo, atomo) == 0){
            return p->par.ident;
        }
        p = p->prox;
    }

    //Caso não tenha encontrado nada, insere o átomo na tabela e retorna o valor do identificador associado
    parSimbolo par;
    par.ident = (*contaTabelaSimbolo)++;
    strcpy(par.atomo, atomo);

    InsereNoFinal(par); //Inserção no fim da Tabela de Símbolos

    return par.ident; //Retorna o identificador do elemento inserido atualmente
}

///////////////////////////////////////////////////////////
//Função ERRO: retorna um erro ao usuário e a linha em que foi encontrado o erro
void ERRO(lld linha){
    printf("\nOcorreu um erro na compilacao, erro na linha %ldd do codigo\n\n", linha);
    Sleep(3000);
    exit(0);
}

///////////////////////////////////////////////////////////
//Verificador de LETRAS
int verificadorLetra(char caracter){
    return ((caracter >= 'A') && (caracter <= 'Z'));
}

//Verificador de NÚMEROS
int verificadorNumero(char caracter){
    return ((caracter >= '0') && (caracter <= '9'));
}

//Verificador de LETRAS e DÍGITOS
int verificadorNumeroOuLetra(char caracter){
    return (verificadorLetra(caracter) || verificadorNumero(caracter));
}

//Verificador de SÍMBOLOS ESPECIAIS
int verificadorSimboloReservado(char caracter){
    //Símbolos Especiais do PASCAL
    char simbolos[max_simbolo] = {".;,():=<>+-*"};

    int i;
    for(i = 0; i < max_simbolo; i++){
        if(caracter == simbolos[i]){
            //Caso o caractere seja um símbolo eespecial
            return 1;
        }
    }
    return 0;
}


void verificadorPalavraChave(char *word){
    char PalavrasChave[][max_palavra] = {"TK_PROGRAM", "TK_LABEL", "TK_VAR", "TK_PROCEDURE",
                                    "TK_FUNCTION", "TK_BEGIN", "TK_END", "TK_IF", "TK_THEN",
                                    "TK_ELSE", "TK_WHILE", "TK_DO", "TK_OR", "TK_AND", "TK_DIV",
                                    "TK_NOT", "DOT", "SEMICOLOR", "COMMA", "OPEN_PAIR",
                                    "CLOSE_PAIR", "OPEN_BRACKET", "CLOSE_BRACKET",
                                    "COLON", "EQUALS", "DIFFERENT", "MORE_THAN", "LESS_THAN",
                                    "MORE_EQUALS_THAN", "LESS_EQUALS_THAN", "PLUS",
                                    "MINUS", "MULTIPLY", "TK_ASSIGNMENT", "TWO_COLON", "TK_OPEN_COMMENT",
                                    "TK_CLOSE_COMMENT", "TK_READ", "TK_WRITE", "TK_INTEGER", "TK_BOOLEAN"};

    int tamanho = *(&PalavrasChave + 1) - PalavrasChave; //Tamanho da tabela de palavras-chave
    if (varSimbolo <= tamanho && varSimbolo > 0){
        strcpy(word, PalavrasChave[varSimbolo - 1]);
    }
}

///////////////////////////////////////////////////////////
//* FUNÇÕES DA LISTA ENCADEADA *//
///////////////////////////////////////////////////////////
//Inserir ao fim da lista
void InsereNoFinal(parSimbolo par){
    //Alocando espaço para inserção
    table p = (table) malloc(sizeof(struct simbolo));

    p->par = par;
    p->prox = NULL;
    
    if(simboloTabela == NULL){
        simboloTabela = p;
    }
    else{
        table q = simboloTabela;
        while(q->prox){
            q = q->prox;
        }
        q->prox = p;
    }
}

//Percorre a lista e retorna o par (identificador, atomo) associado
void retParSimbolo(int ident, parSimbolo *auxPar){
    table p = simboloTabela;

    (*auxPar).ident = -1;

    while(p){
        if(p->par.ident == ident){
            (*auxPar) = p->par;
            break;
        }
        p = p->prox;
    }
}

///////////////////////////////////////////////////////////
//* FUNÇÕES DE ARQUIVO *//
///////////////////////////////////////////////////////////
//Abrir arquivouivo TEXTO
int LeitorDeArquivo(FILE *(*arquivo), char *nome_arquivo, char *protecao_arquivo){
    //Tenta abrir o arquivouivo texto por algum modo (escrita/leitura)
    return((*arquivo) = fopen(nome_arquivo, protecao_arquivo));
}
//Mostrar conteúdo do Arquivo TEXTO por CARACTERE
void EscritorDeArquivo(FILE *arquivo){
    char caracter;
    while (!feof(arquivo)){
        caracter = getc(arquivo);
        if (!feof(arquivo)) //Não printar o fim de arquivouivo
            printf("%c", caracter);
    }
}
///////////////////////////////////////////////////////////
//* OUTRAS FUNÇÕES *//
///////////////////////////////////////////////////////////
//Inserir os Símbolos Especiais, Símbolos Especiais Compostos e Palavras-Chave na Tabela de Símbolos
void insereSimboloNaTabla(lld *contaTabelaSimbolo){
    (*contaTabelaSimbolo) = 1; //Inicia os identificadores em 1
    int i = 0, tamanho;
    parSimbolo par;

    ///////////////////////////////////////////////////////////
    //Palavras e Símbolos Reservados do PASCAL
    ///////////////////////////////////////////////////////////
    char PalavrasChave[][max_palavra] = {
                                    ":", "=", "<>", ">", "<", ">=", "<=", "+",
                                    ".", ";", ",", "(", ")", "[", "]",
                                    "-", "*", ":=", "..", "(*", "*)",
                                    "READ", "WRITE", "INTEGER", "BOOLEAN", "PROGRAM", "LABEL", "VAR", "PROCEDURE",
                                    "FUNCTION", "BEGIN", "END", "IF", "THEN",
                                    "ELSE", "WHILE", "DO", "OR", "AND", "DIV",
                                    "NOT",};

    tamanho = *(&PalavrasChave + 1) - PalavrasChave; //Tamanho da tabela de palavras-chave
    for (i = 0; i < tamanho; i++){
        par.ident = (*contaTabelaSimbolo)++;
        strcpy(par.atomo, PalavrasChave[i]);

        //Inserção na Tabela de Símbolos
        InsereNoFinal(par);
    }
}

///////////////////////////////////////////////////////////

int main(){

    //Abertura de Arquivo Texto
    FILE *arquivo;
    char *nome_arquivo = "Trab1_Compiladores.txt"; //Diretório/Nome do arquivouivo (neste caso, local...)
    char *protecao_arquivo = "rt"; //Leitura de Arquivo Texto com opção de Escrita

    if(LeitorDeArquivo(&arquivo, nome_arquivo, protecao_arquivo)){
        //Sucesso na abertura do arquivouivo texto!
        
        ///////////////////////////////////////////////////////////////
        //Estruturas do Analisador Léxico
        ///////////////////////////////////////////////////////////////
        //Átomo/Token (palavra encontrada)
        char atomo[max_atomo] = "\0";
        varSimbolo = -1;         //Inicia a identificação GLOBAL com nulo (-1)
        lld contaTabelaSimbolo;   //Contador para os identificadores na inserção da Tabela de Símbolos

        //Caractere do Código (variável "proximo") e a do anterior ("s")
        char caracterCod = '\0', anteriorCaracterCod;

        //Auxiliares para os simbolos especiais compostos
        char simboloEspecial[5] = "\0"; //String auxiliar para salvar simbolos especiais compostos (ex: <=)

        //Linha em análise do código
        lld linha = 1;

        //Inserção das palavras e símbolos pré-definidos na Tabela de Símbolos
        simboloTabela = NULL;
        insereSimboloNaTabla(&contaTabelaSimbolo);

        ///////////////////////////////////////////////////////////////
        //Início de verificação do Analisador Léxico
        ///////////////////////////////////////////////////////////////
        
        printf("%d.\t", linha);
        
        //Percorrer o arquivouivo texto
        caracterCod = PROXIMO(arquivo); //Realiza a leitura do primeiro caractere
        while (!feof(arquivo)){

            //Reseta a string que contém os atomos para próximo atomo
            strcpy(atomo, "\0");

            //Reseta a string associada ao símbolo eespecial composto
            strcpy(simboloEspecial, "\0");

            //Não é caractere eespecial = SPACE pra anterior na tabela ASCII
            if(caracterCod > 32){
                ///////////////////////////////////////////////////////////////
                //Análise de Símbolos Especiais e Símbolos Especiais Compostos
                ///////////////////////////////////////////////////////////////
                if (verificadorSimboloReservado(caracterCod)){
                    //String associada ao símbolo eespecial composto
                    strncat(simboloEspecial, &caracterCod, 1);

                    //Recuperando o próximo caractere
                    anteriorCaracterCod = caracterCod;
                    caracterCod = PROXIMO(arquivo);

                    //Símbolo-> >=
                    if (anteriorCaracterCod == '>'){
                        if (caracterCod == '='){
                            strncat(simboloEspecial, &caracterCod, 1);
                        }
                    }
                    //Símbolo-> <=
                    else if (anteriorCaracterCod == '<'){
                        if (caracterCod == '='){
                            strncat(simboloEspecial, &caracterCod, 1);
                        }
                    }
                    //Símbolo-> :=
                    else if (anteriorCaracterCod == ':'){
                        if (caracterCod == '='){
                            strncat(simboloEspecial, &caracterCod, 1);
                        }
                    }
                    //Símbolo-> ..
                    else if (anteriorCaracterCod == '.'){
                        if (caracterCod == '.'){
                            strncat(simboloEspecial, &caracterCod, 1);
                        }
                    }
                    //Símbolo-> (*
                    else if (anteriorCaracterCod == '('){
                        if (caracterCod == '*'){
                            strncat(simboloEspecial, &caracterCod, 1);
                        }
                    }
                    //Símbolo-> *)
                    else if (anteriorCaracterCod == '*'){
                        if (caracterCod == ')'){
                            strncat(simboloEspecial, &caracterCod, 1);
                        }
                    }

                    //Retorna o valor do Símbolo Eespecial associado
                    varSimbolo = CODIGO(simboloEspecial, &contaTabelaSimbolo);
                    
                    printf(" %s", simboloEspecial);
                }

                ///////////////////////////////////////////////////////////////
                //Análise de Letras e Palavras-Chave
                ///////////////////////////////////////////////////////////////
                else if (verificadorLetra(caracterCod)){
                    do{
                        strncat(atomo, &caracterCod, 1);
                        caracterCod = PROXIMO(arquivo);
                    } while (verificadorNumeroOuLetra(caracterCod));

                    //Retornando o código identificador de uma PALAVRA-CHAVE ou de um novo Átomo
                    varSimbolo = CODIGO(atomo, &contaTabelaSimbolo);
                    
                    printf(" %s", atomo);
                }

                ///////////////////////////////////////////////////////////////
                //Análise de Números
                ///////////////////////////////////////////////////////////////
                else if (verificadorNumero(caracterCod)){
                    do{
                        strncat(atomo, &caracterCod, 1);
                        caracterCod = PROXIMO(arquivo);
                    } while (verificadorNumero(caracterCod));

                    //Caso haja letras após uma sequencia de números...
                    if (verificadorLetra(caracterCod)){
                        ERRO(linha);
                    }

                    varSimbolo = CODIGO(atomo, &contaTabelaSimbolo);

                    strcpy(atomo, "NUMBER");
                    printf(" %s", atomo);
                }

                ///////////////////////////////////////////////////////////////
                //Retorna erro em não ocorrência aos casos anteriores
                ///////////////////////////////////////////////////////////////
                else{
                    ERRO(linha);
                }

                //Realizando manipulações no ponteiro de arquivouivo após espaços vazios
                if (caracterCod >= 32){
                    fseek(arquivo, -1, SEEK_CUR);
                }

                //Caso tenha tido um símbolo eespecial, avança o último caractere
                if (strlen(simboloEspecial) > 1){
                    caracterCod = PROXIMO(arquivo);
                }
            }

            //Pulando as quebras de linha e armazenando na variável
            if (caracterCod == '\n'){
                linha++;

                printf("\n%d.\t", linha);
            }

            //Realiza a leitura eliminando os espaços
            caracterCod = PROXIMO(arquivo);
        }

        //Caso tenha passado em TODOS os testes...
        printf("\n\nO arquivo esta correto lexicamente\n\n");

        //Fechar arquivouivo após o uso
        fclose(arquivo);
    }else{
        //Erro na abertura de arquivouivo
        printf("Houve um erro na abertura de arquivo, verifique o local do arquivo\n\n");
    }

    system("PAUSE");
    return 0;
}