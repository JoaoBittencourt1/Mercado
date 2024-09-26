#include <stdio.h>
#include <stdlib.h>

//teste de alteração para o github

#define MAXIMO 100 // Define o número máximo de produtos e itens no carrinho

// Estrutura para armazenar informações dos produtos
typedef struct {
    char NomeProduto[30]; // Nome do produto
    int Idprodutos;       // ID do produto
    float PrecoProdutos;  // Preço do produto
    int quantidadeDisponivel; // Quantidade disponível do produto no estoque
} Produto;

// Estrutura para armazenar informações dos produtos no carrinho
typedef struct {
    Produto Produto;   // Informações do produto
    int quantidade;    // Quantidade do produto no carrinho
} Carrinho;

// Declara arrays e variáveis globais
Produto produtos[MAXIMO]; // Array para armazenar os produtos cadastrados
Carrinho carrinho[MAXIMO]; // Array para armazenar os produtos no carrinho
int ControladorDeProdutos = 0; // Contador de produtos cadastrados
int NumeroProdutos = 0; // Total de produtos cadastrados
int NumeroCarrinho = 0; // Total de itens no carrinho

// Função para exibir o menu principal
void menu() {
    printf("---------------------------------------------------------------------\n");
    printf("                        MERCADO DO JOAO\n");
    printf("---------------------------------------------------------------------\n");
    printf("1. Cadastrar produtos\n");
    printf("2. Listar produtos\n");
    printf("3. Comprar produtos\n");
    printf("4. Visualizar carrinho\n");
    printf("5. Fechar pedido\n");
    printf("6. Sair do sistema\n");
}

// Função para cadastrar novos produtos
void CadastrarProdutos() {
    int numProdutos;

    printf("Quantos produtos voce quer cadastrar? \n");
    if (scanf("%d", &numProdutos) != 1) {
        // Verifica se a entrada é válida
        printf("Entrada invalida!\n");
        while (getchar() != '\n'); // Limpa o buffer de entrada
        return;
    }

    // Verifica se o número de produtos excede o limite
    if (numProdutos + ControladorDeProdutos > MAXIMO) {
        printf("Numero de produtos excede o limite maximo de %d.\n", MAXIMO);
        return;
    }

    // Loop para cadastrar cada produto
    for (int i = 0; i < numProdutos; i++) {
        printf("Produto %d:\n", ControladorDeProdutos + 1);
        printf("Nome: ");
        scanf("%s", produtos[ControladorDeProdutos].NomeProduto); // Lê o nome do produto
        printf("ID (ex: 1987): ");
        scanf("%d", &produtos[ControladorDeProdutos].Idprodutos); // Lê o ID do produto
        printf("Preco: ");
        scanf("%f", &produtos[ControladorDeProdutos].PrecoProdutos); // Lê o preço do produto
        printf("Quantidade disponivel: \n");
        scanf("%d", &produtos[ControladorDeProdutos].quantidadeDisponivel); // Lê a quantidade disponível

        ControladorDeProdutos++;
        NumeroProdutos++;
    }
}

// Função para listar todos os produtos cadastrados
void ListarProdutos() {
    printf("Produtos cadastrados: %d \n", NumeroProdutos);
    for (int i = 0; i < ControladorDeProdutos; i++) {
        printf("Produto %d:\n", i + 1);
        printf("Nome: %s\n", produtos[i].NomeProduto); // Exibe o nome do produto
        printf("ID: %d\n", produtos[i].Idprodutos); // Exibe o ID do produto
        printf("Preco: %.2f\n", produtos[i].PrecoProdutos); // Exibe o preço do produto
        printf("Quantidade Disponivel: %d\n", produtos[i].quantidadeDisponivel); // Exibe a quantidade disponível
        printf("\n");
    }
}

// Função para adicionar produtos ao carrinho
void Adicionarcarrinho(int codigo, int quantidade) {
    for (int i = 0; i < NumeroCarrinho; i++) {
        if (carrinho[i].Produto.Idprodutos == codigo) {
            // Se o produto já está no carrinho, apenas incrementa a quantidade
            carrinho[i].quantidade += quantidade;
            return;
        }
    }

    // Se o produto não está no carrinho, adicione um novo item
    if (NumeroCarrinho < MAXIMO) {
        for (int i = 0; i < ControladorDeProdutos; i++) {
            if (produtos[i].Idprodutos == codigo) {
                if (produtos[i].quantidadeDisponivel >= quantidade) {
                    // Se há quantidade suficiente, adicione o produto ao carrinho
                    carrinho[NumeroCarrinho].Produto = produtos[i];
                    carrinho[NumeroCarrinho].quantidade = quantidade;
                    NumeroCarrinho++;
                    produtos[i].quantidadeDisponivel -= quantidade; // Reduz a quantidade disponível no estoque
                    return;
                } else {
                    printf("Quantidade solicitada excede o estoque disponível.\n");
                    return;
                }
            }
        }
    }
    printf("Produto nao encontrado\n");
}

// Função para pegar e adicionar um produto ao carrinho com base no código fornecido
void pegarProdutoPorCodigo(int codigo) {
    for (int i = 0; i < ControladorDeProdutos; i++) {
        if (produtos[i].Idprodutos == codigo) {
            printf("Produto %d:\n", i + 1);
            printf("Nome: %s\n", produtos[i].NomeProduto); // Exibe o nome do produto
            printf("ID: %d\n", produtos[i].Idprodutos); // Exibe o ID do produto
            printf("Preco: %.2f\n", produtos[i].PrecoProdutos); // Exibe o preço do produto
            printf("Quantidade Disponivel: %d\n", produtos[i].quantidadeDisponivel); // Exibe a quantidade disponível
            printf("\n");

            int quantidade;
            printf("Digite a quantidade que voce deseja comprar: \n");
            scanf("%d", &quantidade); // Lê a quantidade desejada

            if (quantidade > 0) {
                Adicionarcarrinho(codigo, quantidade); // Adiciona o produto ao carrinho
                printf("Produto adicionado ao carrinho com sucesso!\n");
            } else {
                printf("Quantidade invalida.\n");
            }
            return;
        }
    }
    printf("Produto nao encontrado\n");
}

// Função para iniciar o processo de compra de produtos
void ComprarProduto() {
    int codigo;

    printf("Produtos disponiveis: %d\n", NumeroProdutos);
    for (int i = 0; i < ControladorDeProdutos; i++) {
        printf("Produto %d:\n", i + 1);
        printf("Nome: %s\n", produtos[i].NomeProduto); // Exibe o nome do produto
        printf("ID: %d\n", produtos[i].Idprodutos); // Exibe o ID do produto
        printf("Preco: %.2f\n", produtos[i].PrecoProdutos); // Exibe o preço do produto
        printf("Quantidade Disponivel: %d\n", produtos[i].quantidadeDisponivel); // Exibe a quantidade disponível
        printf("\n");
    }
    printf("Digite o codigo do produto que voce deseja comprar: \n");
    scanf("%d", &codigo); // Lê o código do produto desejado
    pegarProdutoPorCodigo(codigo); // Adiciona o produto ao carrinho
}

// Função para visualizar o conteúdo do carrinho
void VisualizarCarrinho() {
    printf("Numero de itens no carrinho: %d\n", NumeroCarrinho);
    for (int i = 0; i < NumeroCarrinho; i++) {
        printf("Produto %d:\n", i + 1);
        printf("Nome: %s\n", carrinho[i].Produto.NomeProduto); // Exibe o nome do produto
        printf("ID: %d\n", carrinho[i].Produto.Idprodutos); // Exibe o ID do produto
        printf("Preco: %.2f\n", carrinho[i].Produto.PrecoProdutos); // Exibe o preço do produto
        printf("Quantidade: %d\n", carrinho[i].quantidade); // Exibe a quantidade do produto no carrinho
    }
}

// Função para fechar o pedido e calcular o total
void FecharPedido() {
    int escolhaa;
    char parcelar;
    float xVezes;
    float ValorFinal;
    float totalPreco = 0.0;

    if (NumeroCarrinho == 0) {
        printf("Nao existem produtos no carrinho\n");
        return;
    }

    // Calcula o valor total do pedido
    for (int i = 0; i < NumeroCarrinho; i++) {
        totalPreco += carrinho[i].Produto.PrecoProdutos * carrinho[i].quantidade;
    }

    // Loop para selecionar o método de pagamento
    while (1) {
        printf("Escolha o metodo de pagamento:\n");
        printf("1. Cartao de credito\n");
        printf("2. Cartao de debito\n");
        printf("3. Dinheiro\n");
        printf("4. Pix\n");
        printf("Escolha: ");

        int c;
        while ((c = getchar()) != '\n' && c != EOF); // Limpa o buffer de entrada

        scanf("%d", &escolhaa);

        switch (escolhaa) {
        case 1:
            while ((c = getchar()) != '\n' && c != EOF); // Limpa o buffer de entrada

            printf("Voce quer parcelar? (y/n): ");
            scanf("%c", &parcelar);
            if (parcelar != 'y' && parcelar != 'n') {//se a resposta for diferente de y ou n, o programa faz vc tentar novamente
                printf("Resposta invalida. Tente novamente!\n");
                continue; 
            }
            if (parcelar == 'y') {
                printf("Em quantas vezes voce quer parcelar? (ate 12x): ");
                scanf("%f", &xVezes);
                if (xVezes > 12 || xVezes < 1) {// se passar o limite,tente novamente
                    printf("Numero de parcelas excedeu o limite ou e invalido. Tente novamente.\n");
                    continue; 
                }
                ValorFinal = totalPreco / xVezes;//calculo do preco final e preco parcelado
                printf("O valor parcelado ficou %.2f de %.0f vezes.\n", ValorFinal, xVezes);
            } else {
                ValorFinal = totalPreco;
                printf("O valor total a ser pago e %.2f\n", ValorFinal);
            }
            break;
        case 2:
            printf("O valor total no debito ficou: %.2f\n", totalPreco);
            break;
        case 3:
            printf("O valor total no dinheiro ficou: %.2f\n", totalPreco);
            break;
        case 4:
            printf("O valor total no Pix ficou: %.2f\n", totalPreco);
            break;
        default:
            printf("Opcao invalida. Tente novamente!\n");
            continue; 
        }
        break; 
    }
}

// Função principal
int main() {
    int escolha;

    while (1) {
        menu(); // Exibe o menu
        printf("\nEscolha uma opcao: ");
        if (scanf("%d", &escolha) != 1) {
            // Verifica se a entrada é válida
            printf("Entrada invalida!\n");
            while (getchar() != '\n'); // Limpa o buffer de entrada
            continue;
        }

        // Executa a função correspondente à opção escolhida
        switch (escolha) {
        case 1:
            CadastrarProdutos();
            break;
        case 2:
            ListarProdutos();
            break;
        case 3:
            ComprarProduto();
            break;
        case 4:
            VisualizarCarrinho();
            break;
        case 5:
            FecharPedido();
            break;
        case 6:
            printf("Saindo do sistema...\n");
            exit(0);
        default:
            printf("Opcao invalida! Tente novamente.\n");
            break;
        }
    }

    return 0;
}