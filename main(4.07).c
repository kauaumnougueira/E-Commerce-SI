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
    03 - INTERFACE DE LOGIN
        3.1- INTERFACE DE CLIENTES\
            > ver produtos no sistema
            > comprar produto
            > devolu��o de produto
            > produtos comprados

        3.2- INTERFACE DE FUNCION�RIOS
            > cadastrar produtos
            > consultar estoque de produtos cadastrados
            > remover produto

    # FUN��ES -> declara��o inicial na linha 36 - 43, defini��es -> linha 55-
*/

/* O que falta/problemas:
- Interface cliente e funcion�rio;
- Resolver problema de exibi��o de caracteres no nome de usu�rio;
*/

//# DADOS:
struct Usuario{    //Struct de armazenamento de dados do usu�rio(cliente/vendedor) do programa:
    char nomeUsuario[70];
    char categoriaUsuario[10];//cliente ou vendedor;
    char senha[10];

};

struct Produto{    //Struct de armazenamento de dados do produto do usu�rio(vendedor):
    char nomeProduto[50];
    char descricao[250];
    int quantidade;
    float preco;
}produto;

//Declara��o inicial de fun��es do programa:
void clientes(); // Interface para usu�rios do tipo clientes;
void vendedor(); // Interface para usu�rios do tipo vendedores;
void login(struct Usuario usuarioAtual, struct Usuario usuarios[20], int indice); // Interface para login de usu�rios;
void erros(char erro[]); // Aviso de erros na utiliza��o do programa;
void inicial(int indice);// Interface inicial;
void cadastro(struct Usuario usuarioAtual, struct Usuario usuarios[20], int indice);// Interface de cadastro de usu�rios;
void salvaEPrintaStruct(struct Usuario usuarioAtual, struct Usuario usuarios[20], int indice, int print);
void voltar(); // Retorno para a interface anterior;

main(){
    //Configura��es do sistema:
    setlocale(LC_ALL,"Portuguese");
    system("color D");

    int indice = 0;

    inicial(indice);//chamada da fun��o de interface inicial;
}

void inicial(int indice){
    system("cls");
//Inst�ncia do usu�rio:
    struct Usuario usuarioAtual;
    struct Usuario usuarios[20];

    int contador = 0, opcao;

    while(contador == 0){
        printf("---------------- SEJA BEM-VINDO � NOSSA LOJA VIRTUAL! ----------------\n");
        printf(" Voc� deseja:\n(1) Fazer cadastro\n(2) Fazer login\n> ");
        scanf("%d", &opcao);
        getchar(); //armazena o enter digitado ap�s a conclus�o do input;

        if(opcao == 1){
            contador++;
            cadastro(usuarioAtual, usuarios, indice);//chamada da fun��o de cadastro de usu�rio;

        }else if(opcao == 2){
            contador++;
            login(usuarioAtual, usuarios, indice);

        }else{
            system("cls");
            erros(" Op��o n�o identificada, por favor insira apenas n�meros correspondentes aos das op��es exibidas.\n");
        }
    }
}

void cadastro(struct Usuario usuarioAtual, struct Usuario usuarios[20], int indice){
    setlocale(LC_ALL,"Portuguese");
    //Teste para conhecimento do da exist�ncia ou n�o de determinado usu�rio:
    system("cls");
    int existe = 0, naoExiste;

    printf("---------------- CADASTRO ----------------\n");
    //Valida��o de usu�rio a partir do nome:
    for(int i = 0; i < 20; i++){
        if(usuarioAtual.nomeUsuario == usuarios[i].nomeUsuario){
            existe = 1;

        }else{
            naoExiste = 0;
        }
    }
    if(existe == 1){
        printf(" Usu�rio j� cadastrado\nRedirecionando para login...");
        system("pause");
        system("cls");
        login(usuarioAtual, usuarios, indice);

    }else{  
        //Cria��o de novo usu�rio:
        int contador = 0, categoria;
        while(contador == 0){
            printf(" Informe a sua categoria:\n(1) Cliente\n(2) Vendedor\n(3) Voltar para o menu inicial\n> ");
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
                erros(" Categoria n�o identificada.");
            }

        }
        contador = 0;
        char senha1[10], senha2[10]; //senha do Usu�rio;
        //Input de dados do novo usu�rio:
        system("cls");
        printf("---------------- CADASTRO ----------------\n");
        printf(" Digite seu nome de usu�rio: ");//adicionar fun��o de verificar se j� existe nome de usu�rio;
        fgets(usuarioAtual.nomeUsuario,50,stdin);
        //Input e confirma��o da senha:
        while(contador == 0){
            printf(" Digite sua senha (at� 10 caracteres): ");
            fgets(senha1,10,stdin);
            printf(" Digite sua senha novamente para confirma��o: ");
            fgets(senha2,10,stdin);

            if(strcmp(senha1,senha2)!=0){
                printf("%s,%s",senha1,senha2);
                erros("Senhas n�o correspondentes");
                contador=0;
            }else{
                printf("\n Cadastrado!");
                strcpy(usuarioAtual.senha, senha1);
                contador++;
                salvaEPrintaStruct(usuarioAtual, usuarios, indice, 0);
                login(usuarioAtual, usuarios, indice); //Usu�rio cadastrado
            }
        }

    }
}
//Interface de login:
void login(struct Usuario usuarioAtual, struct Usuario usuarios[20], int indice){
    system("cls");
    printf("---------------- LOGIN ----------------\n");
    int contador = 0, categoria;
    while(contador == 0){
        printf(" Informe sua categoria:\n(1) Cliente\n(2) Venderdor\n> ");
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
            erros(" Categoria n�o identificada.");
            system("pause");
            system("cls");
        }
    }
    //Login:
    contador = 0;
    while(contador == 0){
        char nome[50], senha[10];
        system("cls");
        printf("---------------- LOGIN ----------------\n");
        printf("Digite seu nome: ");
        fgets(nome, 50, stdin);

        int quantidadeDeErros = 0;
        for(int i = 0; i < 20; i++){
            if(strcmp(nome, usuarios[i].nomeUsuario) < 0 || strcmp(nome, usuarios[i].nomeUsuario)){
                quantidadeDeErros++; //SERVE PARA ACHAR O INDICE E SABER SE ESTA SALVO
                //SE NÃO ACHAR NO BANCO
                if(quantidadeDeErros == 20){
                    erros("Nome n�o cadastrado...\n");
                    int escolha;
                    printf("Deseja se cadastrar?\n(1) Sim\n(2) N�o\n> ");
                    scanf("%d", &escolha);
                    if(escolha == 1){ 
                        cadastro(usuarioAtual, usuarios, indice);
                    }else{
                        contador = 0;
                        break;
                    }
                    contador++;
                }
            //SE ACHAR NO BANCO
            }else{
                printf("Digite sua senha cadastrada: ");
                fgets(senha, 10, stdin);
                if(strcmp(senha,usuarioAtual.senha)<0 || strcmp(senha,usuarioAtual.senha)>0){
                    printf(" Senha digitada incorreta");
                    contador = 0;
                    break;
                }else{
                    contador++;
                    printf("\nUsu�rio %s logado",usuarioAtual.nomeUsuario);
                    salvaEPrintaStruct(usuarioAtual, usuarios, indice, 2);
                    inicial(indice);
                }
            }
        }

        if (strcmp(nome, usuarioAtual.nomeUsuario) < 0 || strcmp(nome, usuarioAtual.nomeUsuario) > 0){
            
        }else{
            
        }
    }
}
//INTERFACE DOS CLIENTES:
void cliente(){
    system("cls");
    printf("---------------- CLIENTES ----------------\n");

}

//INTERFACE DO FUNCION�RIO
void vendedor(){
    system("cls");
    printf("---------------- VENDEDOR ----------------\n");
}

//ERRO ADCIONA
void erros(char erro[]){
    printf("Erro em: %s\n", erro);
}

//SALVA TODOS STRUCTS PARA MOSTRAR
void salvaEPrintaStruct(struct Usuario usuarioAtual, struct Usuario usuarios[20], int index, int print){
    //CADASTRO MANUAL

    if(print == 0){
        //NOME
        strcpy(usuarios[index].nomeUsuario, usuarioAtual.nomeUsuario);
        //CATEGORIA
        strcpy(usuarios[index].categoriaUsuario, usuarioAtual.categoriaUsuario);
        //SENHA
        strcpy(usuarios[index].senha, usuarioAtual.senha);
    }

    //print
    if(print == 1){
        system("cls");
        for(int i = 0; i < 20; i++){
            printf("#Nome: %s\n", usuarios[i].nomeUsuario);
            printf("#Categoria: %s\n", usuarios[i].categoriaUsuario);
            printf("####\n");
        }
    }
}

//volta
void voltar(int indice){
    inicial(indice);
}


