#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>

/*
BUILD:
    #DATA
    #MAIN
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


//Interface do cliente
void client(){

}

//Interface do funcionário
void funcionario(){

}


main(){
    //Configurações do programa
    setlocale(LC_ALL, "Portuguese");
    system("color D");
    int k=0;
    int categoria;

    //USER INSTANCY
    struct User useratual;

    //Interface inicial
    printf("---Seja bem-vindo à loja virtual!---\n");
    while(k==0){
        printf("Informe a sua categoria:\n( 1 ) Cliente\n( 2 ) Funcionário\n: ");
        scanf("%d", &categoria);
        //Separação de interfaces para clientes e funcionarios
            if(categoria == 1){
                client();
                k++;
            }else if(categoria == 2){
                funcionario();
                k++;

                }else{
                    system("cls");
                    printf("Categoria inválida.\n");
                }
    }
}
