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
            > devolucao de produto
            > produtos comprados

        3.2- INTERFACE DE FUNCIONARIOS
            > cadastrar produtos
            > consultar estoque de produtos cadastrados
            > remover produto

    # FUNCOES -> declaracoes inicial na linha 36 - 43, definicoes -> linha 55-
*/

/* O que falta/problemas:
- Interface cliente e funcionario;
- Resolver problema de exibicao de caracteres no nome de usuario;
*/

//# DADOS:
typedef struct{    //Struct de armazenamento de dados do usuario(cliente/vendedor) do programa:
    char nomeUsuario[70];
    char categoriaUsuario[10];//cliente ou vendedor;
    char senha[10];

}Usuario;

typedef struct{    //Struct de armazenamento de dados do produto do usuario(vendedor):
    int identificacao;
    char nomeProduto[50];
    char nomeVendedor[50];
    int quantidade;
    float preco;
}Produto;

struct Geral{
    //Instancia do usuario:
    Usuario usuarioAtual;
    Usuario usuarios[20];

    //Instancia do usuario:
    Produto produtoAtual;
    Produto produtos[20];
};

//Declaracao inicial de funcoes do programa:
void cliente(struct Geral geral, int indice, int index2); // Interface para usuarios do tipo clientes;
void vendedor(struct Geral geral, int indice, int index2); // Interface para usuarios do tipo vendedores;
void login(struct Geral geral, int indice, int index2); // Interface para login de usuarios;
void inicial(struct Geral geral, int indice, int index2);// Interface inicial;
void cadastro(struct Geral geral, int indice, int index2);// Interface de cadastro de usuarios;
void voltar(struct Geral geral, int indice, int index2); // Retorno para a interface anterior;
void salvaStructUsuario(struct Geral geral, int indice, int index2);
void printaStructUsuario(struct Geral geral, int indice, int index2);
void salvaStructProduto(struct Geral geral, int indice, int index2);
void erros(char erro[]); // Aviso de erros na utilizao do programa;

int main(){
    //Configuracoes do sistema:
    setlocale(LC_ALL,"Portuguese");
    system("color A");
    system("mode 100");

    int indice = 0;
    int index2 = 0;

    struct Geral geral;
    

    inicial(geral, indice, index2);//chamada da funcao de interface inicial;
}

void inicial(struct Geral geral, int indice, int index2){
    system("cls");

    int contador = 0, opcao;

    while(contador == 0){
        printf("___Seja bem-vindo a loja virtual!___");
        printf("\n|                                  |");
        printf("\n|   Voce deseja:                   |\n|   ( 1 ) Fazer Login              |\n|   ( 2 ) Fazer Cadastro           |\n|__________________________________|\n> ");
        scanf("%d", &opcao);
        getchar(); //armazena o enter digitado apos a conclusao do input;

        if(opcao == 1){
            contador++;
            login(geral, indice, index2);//chamada da funcao de cadastro de usuario;

        }else if(opcao == 2){
            contador++;
            cadastro(geral, indice, index2);//chamada da funcao de cadastro de usuario;

        }

        else{
            system("cls");
            erros(" Opcao nao identificada, por favor insira apenas numeros correspondentes aos das opcoes exibidas.\n");
        }
    }
}

void cadastro(struct Geral geral, int indice, int index2){
    setlocale(LC_ALL,"Portuguese");
    //Teste para conhecimento do da existencia ou nao de determinado usuario:
    system("cls");
    int existe = 0, naoExiste;

    printf("_______________________CADASTRO__________________________\n");
    //Validacao de usuario a partir do nome:
    for(int i = 0; i < 20; i++){
        if(geral.usuarioAtual.nomeUsuario == geral.usuarios[i].nomeUsuario){
            existe = 1;

        }else{
            naoExiste = 0;
        }
    }
    if(existe == 1){
        printf(" Usuário já cadastrado\nRedirecionando para login...");
        system("pause");
        system("cls");
        login(geral, indice, index2);

    }else{
        //Criacao de novo usuario:
        int contador = 0, categoria;
        while(contador == 0){
            printf("|                                                       |");
            printf("\n|   Voce deseja se cadastrar como cliente ou vendedor?  |");
            printf("\n|   ( 1 ) Cliente                                       |\n|   ( 2 ) Vendedor                                      |\n|   ( 3 ) Voltar para o menu inicial                    |");
            printf("\n|_______________________________________________________|\n>");
            scanf("%d",&categoria);
            getchar();//armazena o enter inserido no fim do input;
            //Salvando categoria:
            if(categoria == 1){
                indice++;
                strcpy(geral.usuarioAtual.categoriaUsuario,"cliente");
                contador++;

            }else if(categoria == 2){
                indice++;
                strcpy(geral.usuarioAtual.categoriaUsuario,"vendedor");
                contador++;

            }else if(categoria == 3){
                system("cls");
                voltar(geral, indice, index2);
                contador++;

            }else{
                system("cls");
                erros(" Categoria nao identificada.");
            }

        }
        contador = 0;
        char senha1[10], senha2[10]; //senha do Usuario;
        //Input de dados do novo usuario:
        system("cls");
        printf("______________CADASTRO______________\n|");
        printf("\n|   Digite seu nome de usuario:\n> ");//adicionar funcao de verificar se ja existe nome de usuario;
        char nome[50];
        fgets(nome,50,stdin);

        for(int i = 0; i <= 20; i++){
            if(strcmp(nome, geral.usuarios[i].nomeUsuario) != 0){
                if(i==20){
                    strcpy(geral.usuarioAtual.nomeUsuario, nome);
                    //Input e confirmacao da senha:
                    while(contador == 0){
                        printf("|   Digite sua senha (no maximo 10 caracteres):\n> ");
                        fgets(senha1,10,stdin);
                        printf("|   Confirme sua senha:\n> ");
                        fgets(senha2,10,stdin);

                        if(strcmp(senha1,senha2)!=0){
                            printf("%s,%s",senha1,senha2);
                            erros("Senhas nao correspondentes");
                            contador=0;
                        }else{
                            system("cls");
                            printf("\n Cadastrado!");
                            strcpy(geral.usuarioAtual.senha, senha1);
                            contador++;
                            salvaStructUsuario(geral, indice, index2);
                            login(geral, indice, index2); //Usuario cadastrado
                        }
                    }
                }
            }else{
                system("cls");
                erros("Usuário ja cadastrado");
                login(geral, indice, index2);
            }
        }
    }
}

//Interface de login:
void login(struct Geral geral, int indice, int index2){
    system("cls");
    int contador = 0;
    //Login:
    contador = 0;
    while(contador == 0){
        char nome[50], senha[10];
        printf("_________________LOGIN___________________");
        printf("\n|   Digite seu nome:\n> ");
        fgets(nome, 50, stdin);

        for(int i = 0; i <= 20; i++){
            if(strcmp(nome, geral.usuarios[i].nomeUsuario) != 0){
                //SE NAO ACHAR NO BANCO
                if(i == 20){
                    erros("Nome nao cadastrado...\n");
                    int escolha;
                    printf("Deseja se cadastrar?\n(1) Sim\n(2) Nao\n> ");
                    scanf("%d", &escolha);
                    if(escolha == 1){
                        system("cls");
                        cadastro(geral, indice, index2);
                    }else if (escolha == 2){
                        inicial(geral, indice, index2);
                    }else{
                        contador = 0;
                        break;
                    }
                }
            //SE ACHAR NO BANCO
            }else{
                //i E A POSIÇÃO
                printf("|   Digite sua senha:\n> ");
                fgets(senha, 10, stdin);
                if(strcmp(senha, geral.usuarios[i].senha) != 0){
                    printf(" Senha digitada incorreta");
                    contador = 0;
                    break;
                }else{
                    system("cls");
                    contador++;
                    printf("Usuario: %s logado.\n", geral.usuarioAtual.nomeUsuario);
                    salvaS(geral, indice, index2);

                    if(strcmp(geral.usuarios[i].categoriaUsuario, "cliente") == 0){
                        cliente(geral, indice, index2);
                        system("cls");
                    }if(strcmp(geral.usuarios[i].categoriaUsuario, "vendedor") == 0){
                        vendedor(geral, indice, index2);
                        system("cls");
                    }else{

                    }
                }
            }
        }
    }
}

//INTERFACE DOS CLIENTES:
void cliente(struct Geral geral, int indice, int index2){
    int contador = 0;
    while(contador == 0){
        printf("_________________CATALOGO_________________\n");
        printf("|_______________E-Commerce_______________|\n");
        printf("\nPRODUTOS: ");

        int quantidadeprodutos = 0;
        for(int i = 0; i < index2; i++){
            if(geral.produtos[i].quantidade != 0){
                printf("\n|________________________________________");
                printf("\n|Codigo do produto ( %d )\n|", i+1);
                printf("\n|    %s", geral.produtos[i].nomeProduto);
                printf("|    R$ %.2f\n", geral.produtos[i].preco);
                printf("|    Quantidade: %d\n", geral.produtos[i].quantidade);
                printf("|    Vendedor: %s", geral.produtos[i].nomeVendedor);
                quantidadeprodutos++;
            }
        }
        if(quantidadeprodutos==0){
            printf("\nNenhum produto cadastrado!\n");
        }

        printf("\n|_________________________________________\n|                                        |\n");
        printf("|  O que voce deseja?                    |\n|  ( 1 ) Comprar produto                 |\n|  ( 2 ) Sair                            |");
        printf("\n|________________________________________|\n> ");
        int escolha;
        scanf("%d", &escolha);
        getchar();
        if(escolha == 1){
            if(quantidadeprodutos>0){
                int codigoProduto;
                printf("Informe o codigo do produto: ");
                scanf("%d", &codigoProduto);
                    for(int i = 0; i < index2; i++){
                        if(geral.produtos[i].quantidade != 0 && codigoProduto == (i+1)){
                            printf("Quantas unidades de %s voce deseja comprar?\n> ", geral.produtos[i].nomeProduto);
                            int unidades;
                            scanf("%d", &unidades);
                            getchar();
                                if(geral.produtos[i].quantidade - unidades < 0 || unidades<0){
                                    printf("Nao foi possivel efetuar a venda!\n");
                                    system("pause");
                                    system("cls");
                                    }else{
                                        geral.produtos[i].quantidade -= unidades;
                                        printf("\nCompra efetuada!\n");
                                        system("pause");
                                        system("cls");
                                    }
                        }
                    }
            }


        }else if(escolha == 2){
            voltar(geral, indice, index2);
        }
    }
}

//INTERFACE DO FUNCIONARIO
void vendedor(struct Geral geral, int indice, int index2){
    int contador = 0;
    while(contador == 0){
        system("cls");
        printf("_________________VENDEDOR_________________\n|                                        |\n");
        printf("|   ( 1 ) Cadastrar produto              |\n|   ( 2 ) Remover produto                |\n|   ( 3 ) Acesso ao Estoque              |\n|   ( 4 ) Sair                           |");
        printf("\n|________________________________________|\n> ");
        int escolha;
        scanf("%d", &escolha);
        getchar();

        //RECEBENDO PRODUTO
        if(escolha == 1){
            system("cls");
            printf("_________________Menu de cadastro de produtos_________________\n");
            printf("|   Informe o nome do produto:\n> ");
            fgets(geral.produtoAtual.nomeProduto, 50, stdin);
            printf("|   Informe o valor do produto:\n> R$ ");
            scanf("%f", &geral.produtoAtual.preco);
            printf("|   Informe a quantidade:\n> ");
            scanf("%d", &geral.produtoAtual.quantidade);
            strcpy(geral.produtoAtual.nomeVendedor, geral.usuarioAtual.nomeUsuario);
            system("cls");
            salvaStructProduto(geral, indice, index2);

        }else if(escolha == 2){
            system("cls");
            printf("_________________Menu de remoção de produtos_________________\n");
            printf("|   Informe o nome do produto:\n> ");
            char nome[50];
            fgets(nome, 50, stdin);
            for(int i = 0; i <= index2; i++){
                //PRODUTO NAO EXISTE
                if(strcmp(geral.produtos[i].nomeProduto, nome) != 0){
                    if(i == index2){
                        system("cls");
                        erros("Produto não cadastrado");
                        vendedor(geral, indice, index2);
                    }
                }else{
                    strcpy(geral.produtos[i].nomeProduto, "");
                    geral.produtos[i].preco = 0;
                    geral.produtos[i].quantidade = 0;
                    printf("Removido\n");
                    system("pause");
                }
            }

        }else if(escolha == 3){
            printaStructProduto(geral, indice, index2);
            system("pause");
        }
        else if(escolha == 4){
            voltar(geral, indice, index2);
        }
        else{
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

//SALVA O STRUCT DE USUARIO
void salvaStructUsuario(struct Geral geral, int indice, int index2){
    //CADASTRO MANUAL
        //NOME
        strcpy(geral.usuarios[indice].nomeUsuario, geral.usuarioAtual.nomeUsuario);
        //CATEGORIA
        strcpy(geral.usuarios[indice].categoriaUsuario, geral.usuarioAtual.categoriaUsuario);
        //SENHA
        strcpy(geral.usuarios[indice].senha, geral.usuarioAtual.senha);
}

//SALVA O STRUCT DO PRODUTO
void salvaStructProduto(struct Geral geral, int indice, int index2){

            //NOME DO PRODUTO
            strcpy(geral.produtos[index2].nomeProduto, geral.produtoAtual.nomeProduto);
            //PREÇOS
            geral.produtos[index2].preco = geral.produtoAtual.preco;
            //QUANTIDADE
            geral.produtos[index2].quantidade = geral.produtoAtual.quantidade;
            //NOME VENDEDOR
            strcpy(geral.produtos[index2].nomeVendedor, geral.produtoAtual.nomeVendedor);

            index2++;

            printf("Produto cadastrado\n");
            system("pause");
            vendedor(geral, indice, index2);

}
void printaStructProduto(struct Geral geral, int indice, int index2){

    system("cls");
    int quantidadeprodutos = 0;
    for(int i = 0; i < index2; i++){
        if(geral.produtos[i].quantidade != 0){
            printf("______________________\n#Nome do Produto: %s", geral.produtos[i].nomeProduto);
            printf("#Preco: R$ %.2f\n", geral.produtos[i].preco);
            printf("#Quantidade: %d\n", geral.produtos[i].quantidade);
            printf("####\n");
            quantidadeprodutos++;
        }
    }
    if(quantidadeprodutos==0){
            printf("\nNão ha nenhum produto cadastrado.\n");
        }

}

//Volta
void voltar(struct Geral geral, int indice, int index2){
    inicial(geral, indice, index2);
}
