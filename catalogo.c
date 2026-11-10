
#include <stdio.h>
#include <string.h>

#define MAX_PRODUTOS 100

// Estrutura dos produtos
struct Produto {
    int codigo;
    char nome[50];
    char categoria[30];
    char marca[30];
    float preco;
};

struct Produto produtos[MAX_PRODUTOS];
int quantidade = 0;

// Busca um produto pelo codigo
int buscarCodigo(int codigo) {
    int i;

    for (i = 0; i < quantidade; i++) {
        if (produtos[i].codigo == codigo) {
            return i;
        }
    }

    return -1;
}

// Salva os produtos no arquivo
void salvarDados() {
    FILE *arquivo;

    arquivo = fopen("produtos.dat", "wb");

    if (arquivo != NULL) {
        fwrite(&quantidade, sizeof(int), 1, arquivo);
        fwrite(produtos, sizeof(struct Produto), quantidade, arquivo);
        fclose(arquivo);
    } else {
        printf("Erro ao salvar os dados!\n");
    }
}

// Carrega os produtos salvos
void carregarDados() {
    FILE *arquivo;
    int qtdSalva;

    arquivo = fopen("produtos.dat", "rb");

    if (arquivo != NULL) {
        if (fread(&qtdSalva, sizeof(int), 1, arquivo) == 1 &&
            qtdSalva >= 0 && qtdSalva <= MAX_PRODUTOS) {

            if (fread(produtos, sizeof(struct Produto), qtdSalva, arquivo) == qtdSalva) {
                quantidade = qtdSalva;
            }
        }

        fclose(arquivo);
    }
}

// Mostra os dados de um produto
void mostrarProduto(struct Produto p) {
    printf("\nCodigo: %d\n", p.codigo);
    printf("Nome: %s\n", p.nome);
    printf("Categoria: %s\n", p.categoria);
    printf("Marca: %s\n", p.marca);
    printf("Preco: R$ %.2f\n", p.preco);
}

// Cadastra um produto
void cadastrarProduto() {
    int codigo;

    if (quantidade >= MAX_PRODUTOS) {
        printf("\nLimite de produtos atingido!\n");
        return;
    }

    printf("\n===== CADASTRAR PRODUTO =====\n");

    printf("Digite o codigo: ");

    if (scanf("%d", &codigo) != 1) {
        printf("Codigo invalido!\n");
        while (getchar() != '\n');
        return;
    }

    getchar();

    if (codigo <= 0) {
        printf("O codigo deve ser maior que zero!\n");
        return;
    }

    if (buscarCodigo(codigo) != -1) {
        printf("Esse codigo ja existe!\n");
        return;
    }

    produtos[quantidade].codigo = codigo;

    printf("Digite o nome: ");
    fgets(produtos[quantidade].nome, 50, stdin);
    produtos[quantidade].nome[strcspn(produtos[quantidade].nome, "\n")] = '\0';

    printf("Digite a categoria: ");
    fgets(produtos[quantidade].categoria, 30, stdin);
    produtos[quantidade].categoria[strcspn(produtos[quantidade].categoria, "\n")] = '\0';

    printf("Digite a marca: ");
    fgets(produtos[quantidade].marca, 30, stdin);
    produtos[quantidade].marca[strcspn(produtos[quantidade].marca, "\n")] = '\0';

    printf("Digite o preco: ");

    if (scanf("%f", &produtos[quantidade].preco) != 1) {
        printf("Preco invalido!\n");
        while (getchar() != '\n');
        return;
    }

    getchar();

    if (produtos[quantidade].preco <= 0) {
        printf("O preco precisa ser maior que zero!\n");
        return;
    }

    quantidade++;

    salvarDados();

    printf("\nProduto cadastrado com sucesso!\n");
}

// Lista todos os produtos
void listarProdutos() {
    int i;

    printf("\n===== PRODUTOS CADASTRADOS =====\n");

    if (quantidade == 0) {
        printf("Nao ha produtos cadastrados.\n");
        return;
    }

    for (i = 0; i < quantidade; i++) {
        printf("\n--------------------------\n");
        mostrarProduto(produtos[i]);
    }
}

// Pesquisa pelo codigo
void pesquisarPorCodigo() {
    int codigo;
    int posicao;

    printf("\nDigite o codigo do produto: ");

    if (scanf("%d", &codigo) != 1) {
        printf("Codigo invalido!\n");
        while (getchar() != '\n');
        return;
    }

    getchar();

    posicao = buscarCodigo(codigo);

    if (posicao == -1) {
        printf("Produto nao encontrado.\n");
    } else {
        printf("\nProduto encontrado:\n");
        mostrarProduto(produtos[posicao]);
    }
}

// Pesquisa pelo nome
void pesquisarPorNome() {
    char nome[50];
    int i;
    int encontrou = 0;

    printf("\nDigite o nome ou parte do nome: ");
    fgets(nome, 50, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (i = 0; i < quantidade; i++) {
        if (strstr(produtos[i].nome, nome) != NULL) {
            mostrarProduto(produtos[i]);
            encontrou = 1;
        }
    }

    if (encontrou == 0) {
        printf("Produto nao encontrado.\n");
    }
}

// Consulta por categoria
void consultarCategoria() {
    char categoria[30];
    int i;
    int encontrou = 0;

    printf("\nDigite a categoria: ");
    fgets(categoria, 30, stdin);
    categoria[strcspn(categoria, "\n")] = '\0';

    for (i = 0; i < quantidade; i++) {
        if (strcmp(produtos[i].categoria, categoria) == 0) {
            mostrarProduto(produtos[i]);
            encontrou = 1;
        }
    }

    if (encontrou == 0) {
        printf("Nenhum produto encontrado nessa categoria.\n");
    }
}

// Altera os dados de um produto
void alterarProduto() {
    int codigo;
    int posicao;
    struct Produto novoProduto;

    printf("\nDigite o codigo do produto que deseja alterar: ");

    if (scanf("%d", &codigo) != 1) {
        printf("Codigo invalido!\n");
        while (getchar() != '\n');
        return;
    }

    getchar();

    posicao = buscarCodigo(codigo);

    if (posicao == -1) {
        printf("Produto nao encontrado.\n");
        return;
    }

    printf("\nProduto atual:\n");
    mostrarProduto(produtos[posicao]);

    novoProduto = produtos[posicao];

    printf("\nDigite o novo nome: ");
    fgets(novoProduto.nome, 50, stdin);
    novoProduto.nome[strcspn(novoProduto.nome, "\n")] = '\0';

    printf("Digite a nova categoria: ");
    fgets(novoProduto.categoria, 30, stdin);
    novoProduto.categoria[strcspn(novoProduto.categoria, "\n")] = '\0';

    printf("Digite a nova marca: ");
    fgets(novoProduto.marca, 30, stdin);
    novoProduto.marca[strcspn(novoProduto.marca, "\n")] = '\0';

    printf("Digite o novo preco: ");

    if (scanf("%f", &novoProduto.preco) != 1) {
        printf("Preco invalido. O produto nao foi alterado.\n");
        while (getchar() != '\n');
        return;
    }

    getchar();

    if (novoProduto.preco <= 0) {
        printf("Preco invalido. O produto nao foi alterado.\n");
        return;
    }

    produtos[posicao] = novoProduto;

    salvarDados();

    printf("\nProduto alterado com sucesso!\n");
}

// Exclui um produto
void excluirProduto() {
    int codigo;
    int posicao;
    int i;

    printf("\nDigite o codigo do produto que deseja excluir: ");

    if (scanf("%d", &codigo) != 1) {
        printf("Codigo invalido!\n");
        while (getchar() != '\n');
        return;
    }

    getchar();

    posicao = buscarCodigo(codigo);

    if (posicao == -1) {
        printf("Produto nao encontrado.\n");
        return;
    }

    for (i = posicao; i < quantidade - 1; i++) {
        produtos[i] = produtos[i + 1];
    }

    quantidade--;

    salvarDados();

    printf("\nProduto excluido com sucesso!\n");
}

// Menu principal
int main() {
    int opcao;

    carregarDados();

    do {
        printf("\n==================================\n");
        printf("      CATALOGO DE ELETRONICOS\n");
        printf("==================================\n");

        printf("1 - Cadastrar produto\n");
        printf("2 - Listar produtos\n");
        printf("3 - Pesquisar por codigo\n");
        printf("4 - Pesquisar por nome\n");
        printf("5 - Consultar por categoria\n");
        printf("6 - Alterar produto\n");
        printf("7 - Excluir produto\n");
        printf("0 - Sair\n");

        printf("\nEscolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("\nOpcao invalida!\n");
            while (getchar() != '\n');
            continue;
        }

        getchar();

        switch (opcao) {
            case 1:
                cadastrarProduto();
                break;

            case 2:
                listarProdutos();
                break;

            case 3:
                pesquisarPorCodigo();
                break;

            case 4:
                pesquisarPorNome();
                break;

            case 5:
                consultarCategoria();
                break;

            case 6:
                alterarProduto();
                break;

            case 7:
                excluirProduto();
                break;

            case 0:
                printf("\nPrograma encerrado!\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}
