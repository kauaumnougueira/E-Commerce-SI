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
    system("cls");
    //INSTÂNCIA DO USUÁRIO
    struct User userAtual;
    struct User users[20];

    int k = 0, cadLog;
    
    while(k == 0){
        printf("---Seja bem-vindo à loja virtual!---\n");
        printf("Você deseja:\n( 1 ) Cadastrar \n( 2 ) Entrar\n> ");
        scanf("%d", &cadLog);
        if(cadLog == 1){
            k++;
            cadastro(userAtual, users);
        }else if(cadLog == 2){
            k++;
            login(userAtual, users);
        }else{
            
        }
    }
}

//INTERFACE DE CADATSRO
void cadastro(struct User userAtual, struct User users[20]){
    //TESTE PRA SABER SE EXISTE
    system("cls");
    printf("---Interface de cadastro---\n");

    int existe = 0, nexiste;
    //VALIDANDO A EXISTENCIA DO USUARIO A PARTIR DO NOME
    for(int i = 0; i < 20; i++){
        if(userAtual.name == users[i].name){
            existe = 1;
        }else{
            nexiste = 0;
        }
    }
    if(existe == 1){
        printf("USuário ja cadastrado\n Sendo redirecionado para LOGIN...");
        login(userAtual, users);
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
        char senha1[10], senha2[10];
        //CADASTRO PARA CLIENTES
        system("cls");
        printf("---Interface para clientes---\n");
        printf("Digite seu nome: ");
        getchar();
        fgets(userAtual.name, 50, stdin);
         while(k == 0){
            printf("Digite sua senha (no máximo 10 caracteres): ");
            fgets(senha1, 10, stdin);
            printf("Confirme sua senha: ");
            fgets(senha2, 10, stdin);
            if(strcmp(senha1, senha2) < 0 || strcmp(senha1, senha2) > 0){
                system("cls");
                error("Senhas não correspondentes");
                k=0;
            }else{
                printf("Cadastrado!");
                k++;
                strcpy(userAtual.senha, senha1);
                login(userAtual, users); //USUÁRIO CADASTRADO
            }
        }
    }
}

//INTERFACE DE LOGIN
void login(struct User userAtual, struct User users[20]){
    system("cls");
    printf("---Interface de login---\n");
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
    //LOGIN PARA CLIENTES
    k = 0;
    while(k == 0){
        char name[50], senha[10];
        system("cls");
        printf("---Interface para clientes---\n");
        printf("Digite seu nome: ");
        getchar();
        fgets(name, 50, stdin);
        if(strcmp(name, userAtual.name) < 0 || strcmp(name, userAtual.name) > 0){
            printf("Nome não cadastrado...\n");
            printf("Deseja cadastrar? \n( 1 ) Sim \n( 2 ) Não");
            int escolha;
            if(escolha == 1){
                cadastro(userAtual, users);
            }else{
                k=0;
                break;
            }
            k++;
        }else{
            printf("Digite sua senha: ");
            fgets(senha, 10, stdin);
            if(strcmp(senha, userAtual.senha) < 0 || strcmp(senha, userAtual.senha) > 0){
                printf("Senha incorreta");
                k = 0;
                break;
            }else{
                k++;
                printf("Usuário logado!");
            }
        }
    }
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

//SALVA TODOS STRUCTS PARA MOSTRAR
void salvaStruct(struct User userAtual, struct User users[20], int indice){
    users[indice] = userAtual;
}