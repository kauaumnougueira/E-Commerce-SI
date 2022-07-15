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
            > devolucao de produto
            > produtos comprados

        3.2- INTERFACE DE FUNCIONARIOS
            > cadastrar produtos
            > consultar estoque de produtos cadastrados
            > remover produto

    # FUNCOES -> declaracoes inicial na linha 36 - 43, definicoes -> linha 55-
*/

//# DADOS:
struct Usuario{// Struct de armazenamento de dados do usuario(cliente/vendedor) do programa:
    char nomeUsuario[70];
    char categoriaUsuario[10]; // cliente ou vendedor;
    char senha[12];
};

struct Produto{ // Struct de armazenamento de dados do produto do usuario(vendedor):
    char nomeProduto[50];
    int quantidade;
    float preco;
};

// Declaracao inicial de funcoes do programa:
void cliente();  // Interface para usuarios do tipo clientes;
void vendedor();                              // Interface para usuarios do tipo vendedores;
void login();    // Interface para login de usuarios;
void inicial();  // Interface inicial;
void cadastro(); // Interface de cadastro de usuarios;
void salvaStructUsuario();
void voltar(); // Retorno para a interface anterior;
void salvaStructProduto();
void erros(char erro[]); // Aviso de erros na utilizao do programa;
void printaStructProduto();//printa os produtos se estiverem preenchidos

//indices
int indice = 0;
int indice2 = 0;

// Instancia do usuario:
struct Usuario usuarioAtual;
struct Usuario usuarios[20];

// Instancia do produto
struct Produto produtoAtual;
struct Produto produtos[20];

int main(){
    // Configuracoes do sistema:
    setlocale(LC_ALL, "Portuguese");
    system("color A");
    system("mode 100");


    inicial(); // chamada da funcao de interface inicial;
    return 0;
}

void inicial(){
    system("cls");

    int contador = 0, opcao;

    while (contador == 0){
        printf("___Seja bem-vindo a loja virtual!___");
        printf("\n|                                  |");
        printf("\n|   Voce deseja:                   |");
        printf("\n|   ( 1 ) Fazer Login              |");
        printf("\n|   ( 2 ) Fazer Cadastro           |");
        printf("\n|   ( 3 ) Fechar o programa        |");
        printf("\n|__________________________________|\n> ");
        scanf("%d", &opcao);
        getchar(); // armazena o enter digitado apos a conclusao do input;

        if (opcao == 1){
            contador++;
            login(); // chamada da funcao de cadastro de usuario;
        }else if (opcao == 2){
            contador++;
            cadastro(); // chamada da funcao de cadastro de usuario;
        }else if (opcao == 3){
            exit(0);
        }else{
            system("cls");
            erros(" Opcao nao identificada, por favor insira apenas numeros correspondentes aos das opcoes exibidas.\n");
        }
    }
}

void cadastro(){
    setlocale(LC_ALL, "Portuguese");
    system("cls");

    printf("_______________________CADASTRO__________________________\n");
    // Criacao de novo usuario:
    int contador = 0, categoria;
    while (contador == 0){
        printf("|                                                       |");
        printf("\n|   Voce deseja se cadastrar como cliente ou vendedor?  |");
        printf("\n|   ( 1 ) Cliente                                       |");
        printf("\n|   ( 2 ) Vendedor                                      |");
        printf("\n|   ( 3 ) Voltar para o menu inicial                    |");
        printf("\n|_______________________________________________________|\n>");
        scanf("%d", &categoria);
        getchar(); // armazena o enter inserido no fim do input;
        // Salvando categoria:
        if (categoria == 1){
            indice++;
            strcpy(usuarioAtual.categoriaUsuario, "cliente");
            contador++;
        }else if (categoria == 2){
            indice++;
            strcpy(usuarioAtual.categoriaUsuario, "vendedor");
            contador++;
        }else if (categoria == 3){
            system("cls");
            voltar();
            contador++;
        }else{
            system("cls");
            erros(" Categoria nao identificada.");
        }
    }
    contador = 0;
    char senha1[12], senha2[12]; // senha do Usuario;
    // Input de dados do novo usuario:
    system("cls");
    printf("______________CADASTRO______________\n|");
    printf("\n|   Digite seu nome de usuario:\n> "); // adicionar funcao de verificar se ja existe nome de usuario;
    char nome[50];
    fgets(nome, 50, stdin);

    for (int i = 0; i <= 20; i++){
        if (strcmp(nome, usuarios[i].nomeUsuario) != 0){
            if (i == 20){
                strcpy(usuarioAtual.nomeUsuario, nome);
                // Input e confirmacao da senha:
                while (contador == 0){
                    printf("|   Digite sua senha (no maximo 10 caracteres):\n> ");
                    fgets(senha1,12, stdin);
                    
                    printf("|   Confirme sua senha:\n> ");
                    fgets(senha2,12, stdin);

                    if (strcmp(senha1, senha2) != 0){
                        printf("%s,%s", senha1, senha2);
                        erros("Senhas nao correspondentes");
                        contador = 0;
                    }else{
                        system("cls");
                        printf("\n Cadastrado!");
                        strcpy(usuarioAtual.senha, senha1);
                        contador++;
                        salvaStructUsuario(usuarioAtual, usuarios, indice);
                        login(); // Usuario cadastrado
                    }
                }
            }
        }else{
            system("cls");
            erros("Usuario ja cadastrado");
            printf("/Redirecionando para login...");
            system("pause");
            login();
        }
    }
}

// Interface de login:
void login(){
    system("cls");
    int contador = 0;
    // Login:
    contador = 0;
    while (contador == 0){
        char nome[50], senha[12];
        printf("_________________LOGIN___________________");
        printf("\n|   Digite seu nome:\n> ");
        fgets(nome, 50, stdin);

        for (int i = 0; i <= 20; i++){
            if (strcmp(nome, usuarios[i].nomeUsuario) != 0){
                // SE NAO ACHAR NO BANCO
                if (i == 20){
                    erros("\nNome nao cadastrado...");
                    int escolha;
                    printf("\nDeseja se cadastrar?\n(1) Sim\n(2) Nao\n> ");
                    scanf("%d", &escolha);
                    getchar();
                    if (escolha == 1){
                        system("cls");
                        cadastro();
                    }else if (escolha == 2){
                        inicial();
                    }else{
                        contador = 0;
                        break;
                    }
                }
                // SE ACHAR NO BANCO
            }else{
                // i E A POSICAO
                printf("|   Digite sua senha:\n> ");
                fgets(senha, 12, stdin);
                if (strcmp(senha, usuarios[i].senha) != 0){
                    system("cls");
                    printf(" Senha digitada incorreta\n");
                    contador = 0;
                    break;
                }else{
                    system("cls");
                    contador++;

                    if (strcmp(usuarios[i].categoriaUsuario, "cliente") == 0){
                        cliente();
                    }
                    if (strcmp(usuarios[i].categoriaUsuario, "vendedor") == 0){
                        vendedor();
                        system("cls");
                    }
                }
            }
        }
    }
}

// INTERFACE DOS CLIENTES:
void cliente(){
    int contador = 0;
    while (contador == 0){
        printf("_________________CATALOGO_________________\n");
        printf("|_______________E-Commerce_______________|\n");
        printf("\nPRODUTOS: ");

        int quantidadeprodutos = 0;
        for (int i = 0; i < indice2; i++){
            if (produtos[i].quantidade != 0){
                printf("\n________________________________________");
                printf("\n|Codigo do produto ( %d )\n|", i + 1);
                printf("\n|    %s", produtos[i].nomeProduto);
                printf("|    R$ %.2f\n", produtos[i].preco);
                printf("|    Quantidade: %d\n", produtos[i].quantidade);
                quantidadeprodutos++;
            }
        }
        if (quantidadeprodutos == 0){
            printf("\nNenhum produto cadastrado!\n");
        }else{
            printf("\nHa %d produtos cadastrados.\n", quantidadeprodutos);
        }

        printf("\n_________________________________________");
        printf("\n|                                        |");
        printf("\n|  O que voce deseja?                    |");
        if (quantidadeprodutos > 0){
            printf("\n|  ( 1 ) Comprar produto                 |");
            printf("\n|  ( 2 ) Pesquisar um produto            |");
        }
        printf("\n|  ( 3 ) Sair                            |");
        printf("\n|________________________________________|\n> ");
        int escolha;
        scanf("%d", &escolha);
        getchar();
        if (escolha == 1 && quantidadeprodutos > 0){
            if (quantidadeprodutos > 0){
                int codigoProduto, produtoexiste = 0;
                printf("Informe o codigo do produto: ");
                scanf("%d", &codigoProduto);
                for (int i = 0; i < indice2; i++){
                    if (produtos[i].quantidade != 0 && codigoProduto == (i + 1)){
                        printf("Quantas unidades de %s voce deseja comprar?\n> ", produtos[i].nomeProduto);
                        int unidades;
                        scanf("%d", &unidades);
                        getchar();
                        if (produtos[i].quantidade - unidades < 0 || unidades < 0 || unidades == 0){
                            printf("Nao foi possivel efetuar a venda!\n");
                            produtoexiste++;
                            system("pause");
                            system("cls");
                        }else{
                            produtos[i].quantidade -= unidades;
                            float gastos;
                            gastos = (unidades * produtos[i].preco);
                            printf("\nCompra efetuada no valor de R$ %.2f.\n ", gastos);
                            printf("\n");
                            produtoexiste++;
                            system("pause");
                            system("cls");
                        }
                    }
                }
                if (produtoexiste == 0){
                    printf("Nao ha este produto no estoque.\n");
                    system("pause");
                    system("cls");
                }
            }
        }else if (escolha == 2 && quantidadeprodutos > 0){
            printf("|   Informe o nome do produto:\n> ");
            char nome[50];
            int k = 0;
            fgets(nome, 50, stdin);
            for (int i = 0; i <= indice2; i++){
                if (strcmp(produtos[i].nomeProduto, nome) == 0){
                    system("cls");
                    printf("Aqui esta o produto pesquisado.\n");
                    printf("________________________________________");
                    printf("\n|Codigo do produto ( %d )\n|", i + 1);
                    printf("\n|    %s", produtos[i].nomeProduto);
                    printf("|    R$ %.2f\n", produtos[i].preco);
                    printf("|    Quantidade: %d\n", produtos[i].quantidade);
                    k++;
                    system("pause");
                    system("cls");
                }
            }
            if (k == 0){
                printf("Nao temos este produto na loja.\n\n");
                system("pause");
                system("cls");
            }
        }else if (escolha == 3){
            voltar();
        }else{
            system("cls");
            printf("Opcao invalida.\n");
        }
    }
}

// INTERFACE DO FUNCIONARIO
void vendedor(){
    int contador = 0;
    while (contador == 0){
        system("cls");
        printf("_________________VENDEDOR_________________");
        printf("\n|                                        |");
        printf("\n|   ( 1 ) Cadastrar produto              |");
        printf("\n|   ( 2 ) Remover produto                |");
        printf("\n|   ( 3 ) Acesso ao Estoque              |");
        printf("\n|   ( 4 ) Sair                           |");
        printf("\n|________________________________________|\n> ");
        int escolha;
        scanf("%d", &escolha);
        getchar();
        // RECEBENDO PRODUTO
        if (escolha == 1){
            system("cls");
            printf("_________________Menu de cadastro de produtos_________________\n");
            printf("|   Informe o nome do produto:\n> ");
            fgets(produtoAtual.nomeProduto, 50, stdin);
            for(int i = 0; i <= indice2; i++){
                if(indice2 != 0 && strcmp(produtoAtual.nomeProduto, produtos[i].nomeProduto) == 0){
                    printf("|   Quantas unidades deseja adcionar ao produto?\n> ");
                    int quantidadeadd;
                    scanf("%d", &quantidadeadd);
                    produtos[i].quantidade += quantidadeadd;
                    vendedor();
                }else if(i == indice2){
                    printf("|   Informe o valor do produto:\n> R$ ");
                    scanf("%f", &produtoAtual.preco);
                    printf("|   Informe a quantidade:\n> ");
                    scanf("%d", &produtoAtual.quantidade);
                    system("cls");
                    salvaStructProduto();
                    break;
                }
            }
        }else if (escolha == 2){
            system("cls");
            printf("_________________Menu de remocao de produtos_________________\n");
            printf("|   Informe o nome do produto:\n> ");
            char nome[50];
            fgets(nome, 50, stdin);
            for (int i = 0; i <= indice2; i++){
                // PRODUTO NAO EXISTE
                if (strcmp(produtos[i].nomeProduto, nome) != 0){
                    if (i == indice2){
                        system("cls");
                        erros("Produto nao cadastrado");
                        vendedor();
                    }
                }else{
                    strcpy(produtos[i].nomeProduto, "");
                    produtos[i].preco = 0;
                    produtos[i].quantidade = 0;
                    printf("Removido\n");
                    system("pause");
                }
            }
        }else if (escolha == 3){
            printaStructProduto();
            system("pause");
        }else if (escolha == 4){
            voltar();
        }else{
            contador = 0;
            erros("Escolha nao identificada, favor escolher uma das alternativas...");
            system("pause");
            break;
        }
    }
}

// ERRO ADCIONA
void erros(char erro[]){
    printf("Erro em: %s\n", erro);
}

// SALVA TODOS STRUCTS PARA MOSTRAR
void salvaStructUsuario(){
    // CADASTRO MANUAL
    // NOME
    strcpy(usuarios[indice].nomeUsuario, usuarioAtual.nomeUsuario);
    // CATEGORIA
    strcpy(usuarios[indice].categoriaUsuario, usuarioAtual.categoriaUsuario);
    // SENHA
    strcpy(usuarios[indice].senha, usuarioAtual.senha);
}

void salvaStructProduto(){
    // NOME DO PRODUTO
    strcpy(produtos[indice2].nomeProduto, produtoAtual.nomeProduto);
    // PRECOS
    produtos[indice2].preco = produtoAtual.preco;
    // QUANTIDADE
    produtos[indice2].quantidade = produtoAtual.quantidade;

    // AUMENTAR INDICE
    indice2++;
    printf("Produto: %s cadastrado\n", produtoAtual.nomeProduto);
    system("pause");
}
    
void printaStructProduto(){
    system("cls");
    int quantidadeprodutos = 0;
    for (int i = 0; i < indice2; i++){
        if (produtos[i].quantidade != 0){
            printf("______________________");
            printf("\n#Nome do Produto: %s", produtos[i].nomeProduto);
            printf("#Preco: R$ %.2f\n", produtos[i].preco);
            printf("#Quantidade: %d\n", produtos[i].quantidade);
            printf("####\n");
            quantidadeprodutos++;
        }
    }
    if (quantidadeprodutos == 0){
        printf("\nNao ha nenhum produto cadastrado.\n");
    }
}

// Volta
void voltar(){
    inicial();
}