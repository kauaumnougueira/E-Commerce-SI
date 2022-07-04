#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

/*
CORPO DO PROGRAMA:
    # DADOS -> linha 21 a 34;
    # MAIN:
    01 - INTERFACE INICIAL
    02 - INTERFACE PARA CADASTRO
    03 - INTERFACE DE LOGIN{
        3.1- INTERFACE DE CLIENTES
        3.2- INTERFACE DE FUNCIONÁRIOS

    # FUNÇÕES -> declaração inicial na linha 36 - 43, definições -> linha 55-
*/

//OPÇÃO: ADCIONAR STRUCT PARA CATEGORIA (FUNCIONÁRIO OU CLIENTE);

//# DADOS:
struct dadosUsuario{    //Struct de armazenamento de dados do usuário(cliente/vendedor) do programa:
    char nomeUsuario[70];
    char categoriaUsuario[10];//cliente ou vendedor;
    char senha[10];

};

struct dadosProduto{    //Struct de armazenamento de dados do produto do usuário(vendedor):
    char nomeProduto[50];
    char descricao[250];
    int quantidade;
    float preco;
}produto;

//Declaração inicial de funções do programa:
void clientes(); // Interface para usuários do tipo clientes;
void vendedor(); // Interface para usuários do tipo vendedores;
void login(struct dadosUsuario usuarioAtual, struct dadosUsuario usuarios[20], int indice); // Interface para login de usuários;
void erros(char erro[]); // Aviso de erros na utilização do programa;
void inicial();// Interface inicial;
void cadastro(struct dadosUsuario usuarioAtual, struct dadosUsuario usuarios[20], int indice);// Interface de cadastro de usuários;
void salvaStruct(struct dadosUsuario usuarioAtual, struct dadosUsuario usuarios[20], int indice);
void voltar(); // Retorno para a interface anterior;

main(){
//Configurações do sistema:
    setlocale(LC_ALL,"Portuguese");
    system("color D");

    int indice = 0;

    inicial(indice);//chamada da função de interface inicial;
}

void inicial(int indice){
    system("cls");
//Instância do usuário:
    struct dadosUsuario usuarioAtual;
    struct dadosUsuario usuarios[20];

    int contador = 0, opcao;

    while(contador == 0){
        printf("---------------- SEJA BEM-VINDO À NOSSA LOJA VIRTUAL! ----------------\n");
        printf("\t Você deseja:\n(1) Fazer cadastro\n(2) Fazer login\n> ");
        scanf("%d",&opcao);
        getchar(); //armazena o enter digitado após a conclusão do input;

        if(opcao == 1){
            contador++;
            cadastro(usuarioAtual, usuarios, indice);//chamada da função de cadastro de usuário;

        }else if(opcao == 2){
            contador++;
            login(usuarioAtual, usuarios, indice);

        }else{
            system("cls");
            erros("\t Opção não identificada, por favor insira apenas números correspondentes aos das opções exibidas.\n");
        }
    }
}

void cadastro(struct dadosUsuario usuarioAtual, struct dadosUsuario usuarios[20], int indice){
//Teste para conhecimento do da existência ou não de determinado usuário:
    system("cls");
    int existe = 0, naoExiste;

    printf("---------------- CADASTRO ----------------\n");
//Validação de usuário a partir do nome:
    for(int i = 0; i < 20; i++){
        if(usuarioAtual.nomeUsuario == usuarios[i].nomeUsuario){
            existe = 1;

        }else{
            naoExiste = 0;
        }
    }
    if(existe == 1){
        printf("\t Usuário já cadastrado\nRedirecionando para login...");
        system("pause");
        system("cls");
        login(usuarioAtual, usuarios, indice);

    }else{  //Criação de novo usuário:
        int contador = 0, categoria;
        while(contador == 0){
            printf("\t Informe a sua categoria:\n(1) Cliente\n(2) Vendedor\n(3) Voltar para o menu inicial\n> ");
            scanf("%d",&categoria);
            getchar();//armazena o enter inserido no fim do input;
        //Salvando categoria:
            if(categoria == 1){
                indice++;
                strcpy(usuarioAtual.categoriaUsuario,"cliente");
                contador++;

            }else if(categoria == 2){
                indice++;
                strcpy(usuarioAtual.categoriaUsuario,"vendedor");
                contador++;

            }else if(categoria == 3){
                system("cls");
                voltar(indice);
                contador++;

            }else{
                system("cls");
                erros("\t Categoria não identificada.");
            }

        }
        contador = 0;
        char senha1[10], senha2[10]; //senha do Usuário;
        //Input de dados do novo usuário:
        system("cls");
        printf("---------------- CADASTRO ----------------\n");
        printf("\t Digite seu nome: ");
        getchar();
        fgets(usuarioAtual.nomeUsuario,50,stdin);
        //Input e confirmação da senha:
        while(contador == 0){
            printf("\t Digite sua senha (até 10 caracteres): ");
            fgets(senha1,10,stdin);
            printf("\t Digite sua senha novamente para confirmação: ");
            fgets(senha2,10,stdin);
            if(strcmp(senha1, senha2) < 0 || strcmp(senha1, senha2) > 0){
                system("cls");
                erros("Senhas não correspondentes");
                contador=0;
            }else{
                printf("\n\t Cadastrado!");
                contador++;
                strcpy(usuarioAtual.senha, senha1);
                login(usuarioAtual, usuarios, indice); //Usuário cadastrado
                salvaStruct(usuarioAtual, usuarios, indice);
            }
        }

    }
}
//Interface de login:
void login(struct dadosUsuario usuarioAtual, struct dadosUsuario usuarios[20], int indice){
    system("cls");
    printf("---------------- LOGIN ----------------\n");
    int contador = 0, categoria;
    while(contador==0){
        printf("\t Informe sua categoria:\n(1) Cliente\n(2) Funcionário\n> ");
        scanf("%d",&categoria);
        getchar();
    //Salvando a categoria:
        if (categoria == 1){
            strcpy(usuarioAtual.categoriaUsuario,"cliente");
            contador++;

        }else if (categoria == 2){
            strcpy(usuarioAtual.categoriaUsuario,"vendedor");
            contador++;

        }else{
            system("cls");
            erros("\t Categoria não identificada.");
            system("pause");
            system("cls");
        }
    }
//Login:
    contador = 0;
    while(contador==0){
        char nome[50], senha[10];
        system("cls");
        printf("---------------- LOGIN ----------------\n");
        printf("\t Digite seu nome: ");
        getchar();
        fgets(nome,50,stdin);
        if (strcmp(nome,usuarioAtual.nomeUsuario) < 0 || strcmp(nome,usuarioAtual.nomeUsuario)>0){
            system("cls");
            erros("\t Nome não cadastrado...\n");
            int escolha;
            printf("\t Deseja se cadastrar?\n(1) Sim\n(2) Não");
            scanf("%d",&escolha);
            if(escolha == 1){
                cadastro(usuarioAtual, usuarios, indice);

            }else{
                contador = 0;
                break;

            }
            contador++;
        }else{
            printf("Digite sua senha cadastrada: ");
            fgets(senha,10,stdin);
            if(strcmp(senha,usuarioAtual.senha)<0 || strcmp(senha,usuarioAtual.senha)>0){
                printf("\t Senha digitada incorreta");
                contador = 0;
                break;

            }else{
                contador++;
                printf("\t Usuário %s logado",usuarioAtual.nomeUsuario);
                salvaStruct(usuarioAtual, usuarios, indice);
            }
        }

    }

}
//INTERFACE DOS CLIENTES:
void cliente(){
    system("cls");
    printf("---------------- CLIENTES ----------------\n");

}

//INTERFACE DO FUNCIONÁRIO
void funcionario(){
    system("cls");
    printf("---------------- VENDEDOR ----------------\n");
}

//ERRO ADCIONA
void erros(char erro[]){
    printf("Erro em: %s\n", erro);
}

//SALVA TODOS STRUCTS PARA MOSTRAR
void salvaStruct(struct dadosUsuario usuarioAtual, struct dadosUsuario usuarios[20], int indice){
    usuarios[indice] = usuarioAtual;
}

//volta
void voltar(int indice){
    inicial(indice);
}




