#include<stdio.h>
#include<locale.h>
#include<windows.h>
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

//FIM-DATA

main(){
    //SYSTEM CONFIGS
    setlocale(LC_ALL, "portuguese");
    system("color D");

    //USER INSTANCY
    struct User useratual;

    //SEPARATING INTERFACES
    printf("Informe sua categoria(cliente/funcionario): ");
    fgets(useratual.category, 10, stdin);
    if(useratual.category == "cliente"){
        client();
    }else if(useratual.category == "funcionario"){
        functionary();
    }else{
        error("categoria não reconhecida");
    }
}


//CLIENT INTERFACE 
void client(){

}

//FUNCTIONARY INTERFACE
void functionary(){

}

//THE ERROR MESSAGE IN THE PARAMETER
void error(what){
    printf("Erro em %s", what);
}