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
    char senha[10];
}userReturn;

struct Product{
    char nameProd[50];
    char description[250];
    int quantity;
};

//CHAMANDO FUNÇÕES
void client();
void funcionario();
void error(char erro[]);
void inicial();

main(){
    //CONFIGURAÇÕES DO SISTEMA
    setlocale(LC_ALL, "Portuguese");
    system("color D");

    

    //INTERFACE INICIAL
    inicial();
}

//INTERFACE INICIAL
void inicial(){
    //INSTÂNCIA DO USUÁRIO
    struct User userAtual;
    struct User users[20];

    int k = 0, cadLog;
    
    while(k == 0){
        printf("---Seja bem-vindo à loja virtual!---\n");
        printf("Você deseja:\n( 1 ) Cadastrar \n( 2 ) Entrar \n");
        scanf("%d", &cadLog);
        getchar();
        if(cadLog == 1){
            k++;
            cadastro(userAtual, users);
        }else if(cadLog == 2){
            k++;
            login(userAtual);
        }else{
            
        }
    }
}

//INTERFACE DE CADATSRO
void cadastro(struct User userAtual, struct User users[20]){
    //TESTE PRA SABER SE EXISTE
    system("cls");
    int existe = 0, nexiste;
    for(int i = 0; i < 20; i++){
        if(userAtual.name == users[i].name){
            existe = 1;
        }else{
            nexiste = 0;
        }
    }
    if(existe == 1){
        printf("USuário ja cadastrado\n Sendo redirecionado para LOGIN...");
        login(userAtual);
    }else{
        int k = 0;
        int categoria;
        while(k==0){
            printf("Informe a sua categoria:\n( 1 ) Cliente\n( 2 ) Funcionário\n> ");
            scanf("%d", &categoria);
            //SALVANDO CATEGORIA
            if(categoria == 1){
                strcpy(userAtual.category, "cliente");
                k++;
            }else if(categoria == 2){
                strcpy(userAtual.category, "funcionario");
                k++;
            }else{
                system("cls");
                error("Categoria não identificada");
            }

        }
        k = 0;
        while(k == 0){
            char senha1[10], senha2[10];
            system("cls");
            printf("---Interface para clientes---\n");
            printf("Digite seu nome: ");
            fgets(userAtual.name, 50, stdin);
            printf("Digite sua senha (no máximo 10 caracteres): ");
            scanf("%d", &senha1);
            printf("Confirme sua senha: ");
            scanf("%d", &senha2);
            if(strcmp(senha1, senha2) < 0 || strcmp(senha1, senha2) > 0){
                error("Senhas não correspondentes");
                k=0;
            }else{
                k++;
                strcpy(userAtual.senha, senha1);
            }
            //USUÁRIO CADASTRADO
        }
    }
}

//INTERFACE DE LOGIN
void login(){

}

//INTERFACE DO CLIENTE
void client(){
    system("cls");
    printf("---Interface para clientes---\n");
}

//INTERFACE DO FUNCIONÁRIO
void funcionario(){
    system("cls");
    printf("---Interface para funcionários---\n");
}

//ERRO ADCIONADO AO PARÂMETRO
void error( char erro[]){
    printf("Erro em: %s\n", erro);
}

