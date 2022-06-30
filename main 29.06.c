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
        3.2- INTERFACE DE FUNCION�RIOS
    #FUNCTIONS
*/

//OP��O: ADCIONAR STRUCT PARA CATEGORIA (FUNCION�RIO OU CLIENTE)

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

//CHAMANDO FUN��ES
void cliente();
void vendedor();
void login(struct User userAtual, struct User users[20], int index);
void error(char erro[]);
void inicial();
void cadastro(struct User userAtual, struct User users[20], int index);
void voltar();

main(){
    //CONFIGURA��ES DO SISTEMA
    setlocale(LC_ALL, "Portuguese");
    system("color A");

    int index = 0;

    //INTERFACE INICIAL
    inicial(index);
}

//INTERFACE INICIAL
void inicial(int index){
    system("cls");

    //INST�NCIA DO USU�RIO
    struct User userAtual;
    struct User users[20];

    int count = 0, cadLog;

    while(count == 0){
        printf("___Seja bem-vindo � loja virtual!___");
        printf("\n|                                  |");
        printf("\n|   Voc� deseja:                   |\n|   ( 1 ) Fazer Login              |\n|   ( 2 ) Fazer Cadastro           |\n|__________________________________|\n> ");
        scanf("%d", &cadLog);
        getchar(); //Soluciona erro de tipagem do input
        if(cadLog == 2){
            count++;
            cadastro(userAtual, users, index);
        }else if(cadLog == 1){
            count++;
            login(userAtual, users, index);
        }else{
            system("cls");
            error("N�o identificado, selecione somente os n�meros ao lado das op��es\n");
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
        printf("Usu�rio j� cadastrado\n Sendo redirecionado para LOGIN...");
        login(userAtual, users, index);
    }else{
        int count = 0;
        int categoria;
        while(count == 0){
            printf("|   Voc� deseja se cadastrar como cliente ou vendedor?  |\n( 1 ) Cliente\n( 2 ) Vendedor\n( 3 ) Voltar para o menu inicial\n> ");
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
                error("Categoria n�o identificada");
            }
        }
        count = 0;
        char senha1[10], senha2[10];
        //CADASTRO
        system("cls");
        printf("CADASTRO\n");
        printf("---Interface para cadastro---\n");
        printf("Digite seu nome: ");
        getchar();
        fgets(userAtual.name, 50, stdin);
         while(count == 0){
            printf("Digite sua senha (no m�ximo 10 caracteres): ");
            fgets(senha1, 10, stdin);
            printf("Confirme sua senha: ");
            fgets(senha2, 10, stdin);
            if(strcmp(senha1, senha2) < 0 || strcmp(senha1, senha2) > 0){
                system("cls");
                error("Senhas n�o correspondentes");
                count=0;
            }else{
                printf("Cadastrado!");
                count++;
                strcpy(userAtual.senha, senha1);
                login(userAtual, users, index); //USU�RIO CADASTRADO
                salvaStruct(userAtual, users, index);
            }
        }
    }
}

//INTERFACE DE LOGIN
void login(struct User userAtual, struct User users[20], int index){
    system("cls");
    printf("______________LOGIN________________");
    int count = 0;
    int categoria;
    while(count==0){
        printf("\n|                                 |");
        printf("\n|    Informe a sua categoria:     |\n|    ( 1 ) Cliente                |\n|    ( 2 ) Vendedor               |");
        printf("\n|_________________________________|\n>");
        scanf("%d", &categoria);
        getchar(); //Soluciona erro de tipagem do input
        //SALVANDO CATEGORIA
        if(categoria == 1){
            strcpy(userAtual.category, "cliente");
            count++;
        }else if(categoria == 2){
            strcpy(userAtual.category, "vendedor");
            count++;
        }else{
            system("cls");
            error("Categoria n�o identificada");
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
            error("Nome n�o cadastrado...");
            printf("Deseja cadastrar? \n( 1 ) Sim \n( 2 ) N�o\n> ");
            scanf("%d", &escolha);
            if(escolha == 1){
                cadastro(userAtual, users, index);
            }else{
                count=0;
                voltar(); //SE A PESSOA ESCOLHER N�O SE CADATRAR O PROGRAMA TEM QUE VOLTAR PRA TELA INICIALL, COMO FAZ ISSO?????????????????
                break;
            }
            count++;
        }else{
            printf("Digite sua senha: ");
            fgets(senha, 10, stdin);
            if(strcmp(senha, userAtual.senha) < 0 || strcmp(senha, userAtual.senha) > 0){
                printf("Senha incorreta");
                count = 0;
                break;
            }else{
                count++;
                printf("Usu�rio logado!");
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

//INTERFACE DO FUNCION�RIO
void funcionario(){
    system("cls");
    printf("---Interface para funcion�rios---\n");
}

//ERRO ADCIONADO AO PAR�METRO
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

