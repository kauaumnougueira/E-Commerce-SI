#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>

/*
BUILD:
    #DATA
    #MAIN
    1- INTERFACE INICIAL
    2- INTERFACE PARA CADASTRO
    3- INTERFACE DE LOGIN
        3.1- INTERFACE DE CLIENTES
        3.2- INTERFACE DE FUNCIONÁRIOS
    #FUNCTIONS
*/

//OPÇÃO: ADCIONAR STRUCT PARA CATEGORIA (FUNCIONÁRIO OU CLIENTE)

//DATA

struct User{
    char name[50];
    char category[10];
};

struct Product{
    char nameProd[50];
    char description[250];
    int quantity;
};

//CHAMANDO FUNÇÕES
void client();
void funcionario();
void error(char erro[]);
void inicial(int senhaPadrao);

main(){
    //CONFIGURAÇÕES DO SISTEMA
    setlocale(LC_ALL, "Portuguese");
    system("color D");
    int senhaPadrao = 1234;

    //INSTÂNCIA DO USUÁRIO
    struct User userAtual;

    //INTERFACE INICIAL
    inicial(senhaPadrao);
}

//INTERFACE INICIAL
void inicial(int senhaPadrao){
    int k=0;
    int categoria, senha;
    printf("---Seja bem-vindo à loja virtual!---\n");
    while(k==0){
        printf("Informe a sua categoria:\n( 1 ) Cliente\n( 2 ) Funcionário\n> ");
        scanf("%d", &categoria);
            //SEPARAÇÃO DA INTERFACE PARA CLIENTES E FUNCIONÁRIOS
            if(categoria == 1){
                client();
                k++;
            }else if(categoria == 2){
                system("cls");
                printf("Digite a senha para funcionários: ");
                scanf("%d", &senha);
                //É NECESSÁRIO UMA SENHA PARA ACESSO DOS FUNCIONÁRIOS
                printf("%d", senha);
                    if(senha == senhaPadrao){
                        funcionario();
                        k++;
                    }
                    else{
                        system("cls");
                        error("Senhã incorreta");
                    }

            }else{
                system("cls");
                error("Categoria não identificada");
            }

    }
}

//INTERFACE DO CLIENTE
void client(){
    system("cls");
    printf("---Interface para clientes---");
}

//INTERFACE DO FUNCIONÁRIO
void funcionario(){
    system("cls");
    printf("---Interface para funcionários---");
}

//ERRO ADCIONADO AO PARÂMETRO
void error( char erro[]){
    printf("Erro em: %s\n", erro);
}

