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
    float preco;
};

//CHAMANDO FUNÇÕES
void cliente();
void vendedor();
void login(struct User userAtual, struct User users[20], int index);
void error(char erro[]);
void inicial();
void cadastro(struct User userAtual, struct User users[20], int index);
void voltar();

main(){
    //CONFIGURAÇÕES DO SISTEMA
    setlocale(LC_ALL, "Portuguese");
    system("color A");

    int index = 0;

    //INTERFACE INICIAL
    inicial(index);
}

//INTERFACE INICIAL
void inicial(int index){


    //INSTÂNCIA DO USUÁRIO
    struct User userAtual;
    struct User users[20];

    int count = 0, cadLog;

    while(count == 0){
        printf("___Seja bem-vindo à loja virtual!___");
        printf("\n|                                  |");
        printf("\n|   Você deseja:                   |\n|   ( 1 ) Fazer Login              |\n|   ( 2 ) Fazer Cadastro           |\n|__________________________________|\n> ");
        scanf("%d", &cadLog);
        getchar(); //Soluciona erro de tipagem do input
        if(cadLog == 2){
            count++;
            system("cls");
            cadastro(userAtual, users, index);
        }else if(cadLog == 1){
            count++;
            system("cls");
            login(userAtual, users, index);
        }else{
            system("cls");
            error("Não identificado, selecione somente os números ao lado das opções\n");
        }
    }
}

//INTERFACE DE CADATSRO
void cadastro(struct User userAtual, struct User users[20], int index){
    system("cls");
    printf("_______________________CADASTRO__________________________\n");

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
        printf("Usuário já cadastrado\n Sendo redirecionado para LOGIN...");
        login(userAtual, users, index);
    }else{
        int count = 0;
        int categoria;
        while(count == 0){
            printf("|                                                       |");
            printf("\n|   Você deseja se cadastrar como cliente ou vendedor?  |");
            printf("\n|   ( 1 ) Cliente                                       |\n|   ( 2 ) Vendedor                                      |\n|   ( 3 ) Voltar para o menu inicial                    |");
            printf("\n|_______________________________________________________|\n>");
            scanf("%d", &categoria);
            getchar(); //Soluciona erro de tipagem do input
            //SALVANDO CATEGORIA
            if(categoria == 1){
                index++;
                strcpy(userAtual.category, "cliente");
                count++;
            }else if(categoria == 2){
                index++;
                strcpy(userAtual.category, "vendedor");
                count++;
            }else if(categoria == 3){
                system("cls");
                voltar(index);
                count++;
            }else{
                system("cls");
                error("Categoria não identificada");
            }
        }
        count = 0;
        char senha1[10], senha2[10];
        //CADASTRO
        system("cls");
        printf("______________CADASTRO______________\n|");
        printf("\n|   Digite seu nome: ");
        getchar();
        fgets(userAtual.name, 50, stdin);
         while(count == 0){
            printf("|   Digite sua senha (no máximo 10 caracteres): ");
            fgets(senha1, 10, stdin);
            printf("|   Confirme sua senha: ");
            fgets(senha2, 10, stdin);
            if(strcmp(senha1, senha2) < 0 || strcmp(senha1, senha2) > 0){
                system("cls");
                error("Senhas não correspondentes");
                count=0;
            }else{
                system("cls");
                printf("Usuário cadastrado com sucesso!\n");
                count++;
                strcpy(userAtual.senha, senha1);
                login(userAtual, users, index); //USUÁRIO CADASTRADO
                salvaStruct(userAtual, users, index);
            }
        }
    }
}

//INTERFACE DE LOGIN
void login(struct User userAtual, struct User users[20], int index){

    printf       ("_________________LOGIN___________________");
    int count = 0;
    int categoria;
    while(count==0){
        printf("\n|                                       |");
        printf("\n|    Informe a sua categoria:           |\n|    ( 1 ) Cliente                      |\n|    ( 2 ) Vendedor                     |\n|    ( 3 ) Voltar para o menu inicial   |");
        printf("\n|_______________________________________|\n>");
        scanf("%d", &categoria);
        getchar(); //Soluciona erro de tipagem do input
        //SALVANDO CATEGORIA
        if(categoria == 1){
            strcpy(userAtual.category, "cliente");
            count++;
        }else if(categoria == 2){
            strcpy(userAtual.category, "vendedor");
            count++;
        }else if(categoria == 3){
            system("cls");
            voltar();
            count++;
        }else{
            system("cls");
            error("Categoria não identificada");
       }
    }
    //LOGIN
    count = 0;
    int escolha;
    while(count == 0){
        char name[50], senha[10];
        system("cls");
        printf("LOGIN\n");
        printf("Digite seu nome: ");
        getchar();
        fgets(name, 50, stdin);
        if(strcmp(name, userAtual.name) < 0 || strcmp(name, userAtual.name) > 0){
            system("cls");
            error("Nome não cadastrado...");
            printf("Deseja cadastrar? \n( 1 ) Sim \n( 2 ) Não\n> ");
            scanf("%d", &escolha);
            if(escolha == 1){
                cadastro(userAtual, users, index);
            }else{
                count=0;
                voltar();
                break;
            }
            count++;
        }else{
            printf("Digite sua senha: ");
            fgets(senha, 10, stdin);
            if(strcmp(senha, userAtual.senha) < 0 || strcmp(senha, userAtual.senha) > 0){
                system("cls");
                printf("Senha incorreta");
                count = 0;
                voltar();
                break;
            }else{
                count++;
                printf("Usuário logado!");
                salvaStruct(userAtual, users, index);
            }
        }
    }
}

//INTERFACE DO CLIENTE
void cliente(){
    system("cls");
    printf("---Interface para clientes---\n");
}

//INTERFACE DO FUNCIONÁRIO
void funcionario(){
    system("cls");
    printf("---Interface para funcionários---\n");
}

//ERRO ADCIONADO AO PARÂMETRO
void error(char erro[]){
    printf("Erro em: %s\n", erro);
}

//SALVA TODOS STRUCTS PARA MOSTRAR
void salvaStruct(struct User userAtual, struct User users[20], int indice){
    users[indice] = userAtual;
    mostraCadastrados(users);
}

//volta
void voltar(int index){
    inicial(index);
}

