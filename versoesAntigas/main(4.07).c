#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

/*

CADASTRO RESOLVIDO -> REGRA: TEM QUE LEVAR O STRUCT NO PARAMETRO

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
    int identificacao;
    char nomeProduto[50];
    int quantidade;
    float preco;
};

//Declara��o inicial de fun��es do programa:
void clientes(); // Interface para usu�rios do tipo clientes;
void vendedor(); // Interface para usu�rios do tipo vendedores;
void login(struct Usuario usuarioAtual, struct Usuario usuarios[20], int indice, struct Produto produtos[20], int index2); // Interface para login de usu�rios;
void erros(char erro[]); // Aviso de erros na utiliza��o do programa;
void inicial(struct Usuario usuarioAtual, struct Usuario usuarios[20], int indice, struct Produto produtos[20], int index2);// Interface inicial;
void cadastro(struct Usuario usuarioAtual, struct Usuario usuarios[20], int indice, struct Produto produtos[20], int index2);// Interface de cadastro de usu�rios;
void salvaEPrintaStruct(struct Usuario usuarioAtual, struct Usuario usuarios[20], int indice, int print);
void voltar(); // Retorno para a interface anterior;

main(){
    //Configura��es do sistema:
    setlocale(LC_ALL,"Portuguese");
    system("color D");

    int indice = 0;
    int index2 = 0;

    //Inst�ncia do usu�rio:
    struct Usuario usuarioAtual;
    struct Usuario usuarios[20];

    struct Produto produtos[20];

    inicial(usuarioAtual, usuarios, indice, produtos, index2);//chamada da fun��o de interface inicial;
}

void inicial(struct Usuario usuarioAtual, struct Usuario usuarios[20], int indice, struct Produto produtos[20], int index2){
    system("cls");

    int contador = 0, opcao;

    while(contador == 0){
        printf("---------------- SEJA BEM-VINDO � NOSSA LOJA VIRTUAL! ----------------\n");
        printf(" Voc� deseja:\n(1) Fazer cadastro\n(2) Fazer login\n> ");
        scanf("%d", &opcao);
        getchar(); //armazena o enter digitado ap�s a conclus�o do input;

        if(opcao == 1){
            contador++;
            cadastro(usuarioAtual, usuarios, indice, produtos, index2);//chamada da fun��o de cadastro de usu�rio;

        }else if(opcao == 2){
            contador++;
            login(usuarioAtual, usuarios, indice, produtos, index2);

        }else{
            system("cls");
            erros(" Op��o n�o identificada, por favor insira apenas n�meros correspondentes aos das op��es exibidas.\n");
        }
    }
}

void cadastro(struct Usuario usuarioAtual, struct Usuario usuarios[20], int indice, struct Produto produtos[20], int index2){
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
        login(usuarioAtual, usuarios, indice, produtos, index2);

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
                voltar(usuarioAtual, usuarios, indice, produtos, index2);
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
        char nome[50];
        fgets(nome,50,stdin);

        for(int i = 0; i <= 20; i++){
            if(strcmp(nome, usuarios[i].nomeUsuario) != 0){
                if(i==20){
                    strcpy(usuarioAtual.nomeUsuario, nome);
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
                            login(usuarioAtual, usuarios, indice, produtos, index2); //Usu�rio cadastrado
                        }
                    }
                }
            }else{
                erros("Usuário ja cadastrado");
                login(usuarioAtual, usuarios, indice, produtos, index2);
            }
        }
    }
}
//Interface de login:
void login(struct Usuario usuarioAtual, struct Usuario usuarios[20], int indice, struct Produto produtos[20], int index2){
    system("cls");
    int contador = 0;
    //Login:
    contador = 0;
    while(contador == 0){
        char nome[50], senha[10];
        system("cls");
        printf("---------------- LOGIN ----------------\n");
        printf("Digite seu nome: ");
        fgets(nome, 50, stdin);

        for(int i = 0; i <= 20; i++){
            if(strcmp(nome, usuarios[i].nomeUsuario) != 0){
                //SE NÃO ACHAR NO BANCO
                if(i == 20){
                    erros("Nome n�o cadastrado...\n");
                    int escolha;
                    printf("Deseja se cadastrar?\n(1) Sim\n(2) N�o\n> ");
                    scanf("%d", &escolha);
                    if(escolha == 1){ 
                        cadastro(usuarioAtual, usuarios, indice, produtos, index2);
                    }else if (escolha == 2){
                        inicial(usuarioAtual, usuarios, indice, produtos, index2);
                    }else{
                        contador = 0;
                        break;
                    }
                }
            //SE ACHAR NO BANCO
            }else{
                //i É A POSIÇÃO 
                printf("Digite sua senha cadastrada: ");
                fgets(senha, 10, stdin);
                if(strcmp(senha, usuarios[i].senha) != 0){
                    printf(" Senha digitada incorreta");
                    contador = 0;
                    break;
                }else{
                    contador++;
                    printf("\nUsu�rio %s logado",usuarioAtual.nomeUsuario);
                    salvaEPrintaStruct(usuarioAtual, usuarios, indice, 2);

                    if(strcmp(usuarios[i].categoriaUsuario, "cliente") == 0){
                        cliente();
                    }if(strcmp(usuarios[i].categoriaUsuario, "vendedor") == 0){
                        vendedor(produtos, index2);
                    }else{

                    }
                }
            }
        }
    }
}
//INTERFACE DOS CLIENTES:
void cliente(){
    int contador = 0;
    while(contador == 0){
        system("cls");
        printf("---------------- CLIENTES ----------------\n");
        printf("O que você deseja? \n( 1 ) Comprar produto\n ( 2 ) Deslogar\n ( 3 ) Ver Histórico\n> ");
        
    }
}

//INTERFACE DO FUNCION�RIO
void vendedor(struct Produto produtos[20], int index2){
    int contador = 0;
    while(contador == 0){
        system("cls");
        printf("---------------- VENDEDOR ----------------\n");
        printf(" ( 1 ) Cadastrar produto\n ( 2 ) Remover produto\n ( 3 ) Acesso ao Estoque\n> ");
        int escolha;
        scanf("%d", &escolha);
        getchar();
        //RECEBENDO PRODUTO
        struct Produto produtoAtual;
        if(escolha == 1){
            system("cls");
            
            printf("---------------- Menu de cadastro de produtos ----------------\n");
            printf("Informe o nome do produto:\n");
            fgets(produtoAtual.nomeProduto, 50, stdin);
            printf("Informe o valor do produto:\nR$ ");
            scanf("%f", &produtoAtual.preco);
            printf("quantidade:\n");
            scanf("%d", &produtoAtual.quantidade);
            system("cls");
            salvaStructProduto(produtoAtual, produtos, index2, 0);

            contador++;
        }else if(escolha == 2){
            system("cls");
            printf("---------------- Menu de remoção de produtos ----------------\n");
            printf("Informe o nome do produto:\n");
            char nome[50];
            fgets(nome, 50, stdin);
            for(int i = 0; i <= index2; i++){
                //PRODUTO NAO EXISTE
                if(strcmp(produtos[i].nomeProduto, nome) != 0){
                    if(i == index2){
                        system("cls");
                        erros("produto não cadastrado");
                        vendedor(produtos, index2);
                    }
                }else{
                    strcpy(produtos[i].nomeProduto, "");
                    produtos[i].preco = 0;
                    produtos[i].quantidade = 0;
                    printf("Removido\n");
                    system("pause");
                }
            }
            contador++;
        }else if(escolha == 3){
            salvaStructProduto(produtoAtual, produtos, index2, 1);
            system("\npause");
        }else{
            contador = 0;
            erros("Escolha não identificada, favor escolher uma das alternativas...");
            system("pause");
            break;
        }
    }
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
        for(int i = 0; i < index; i++){
            printf("#Nome: %s\n", usuarios[i].nomeUsuario);
            printf("#Categoria: %s\n", usuarios[i].categoriaUsuario);
            printf("####\n");
        }
    }
}

void salvaStructProduto(struct Produto produtoAtual, struct Produto produtos[20], int index2, int print){

        if(print == 0){
            //NOME DO PRODUTO
            strcpy(produtos[index2].nomeProduto, produtoAtual.nomeProduto);
            //PREÇOS
            produtos[index2].preco = produtoAtual.preco;
            //QUANTIDADE
            produtos[index2].quantidade = produtoAtual.quantidade;

            index2++;
            printf("Produto cadastrado\n");
            system("pause");
            vendedor(produtos, index2);
        }

        if(print == 1){
            for(int i = 0; i < index2; i++){
            printf("#Nome do Produto: %s", produtos[i].nomeProduto);
            printf("#Preco: %2.f\n", produtos[i].preco);
            printf("#Quantidade: %d\n", produtos[i].quantidade);
            printf("####\n");
            }

        }
}

//volta
void voltar(struct Usuario usuarioAtual, struct Usuario usuarios[20], int indice, struct Produto produtos[20], int index2){
    inicial(usuarioAtual, usuarios, indice, produtos, index2);
}

