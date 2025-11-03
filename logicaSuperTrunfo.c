#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Definição da estrutura para representar uma Carta de Cidade
typedef struct {
    char estado[30];
    char codigo[5];
    char nome_cidade[50];
    long long populacao;     // População (valor grande)
    double area_km2;         // Área em km²
    double pib_bilhoes;      // PIB em Bilhões de Reais
    int pontos_turisticos;   // Número de Pontos Turísticos
    double densidade_populacional; // Calculada: População / Área
} CartaCidade;

// --- Funções de Utilitário ---

// Limpa o buffer de entrada (essencial após scanf para evitar problemas com fgets)
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Exibe os dados de uma carta
void exibir_carta(const CartaCidade *carta, int numero) {
    printf("\n--- Detalhes da Carta %d: %s (%s) ---\n", numero, carta->nome_cidade, carta->estado);
    printf("  [1] População: %lld habitantes\n", carta->populacao);
    printf("  [2] Área: %.2f km²\n", carta->area_km2);
    printf("  [3] PIB: R$ %.2f Bilhões\n", carta->pib_bilhoes);
    printf("  [4] Pontos Turísticos: %d\n", carta->pontos_turisticos);
    printf("  [5] Densidade Populacional: %.2f hab/km² (MENOR VENCE)\n", carta->densidade_populacional);
    printf("-----------------------------------------\n");
}

// Cadastra interativamente os dados de uma carta
void cadastrar_carta(CartaCidade *carta, int numero) {
    printf("\n--- Cadastro da Carta %d ---\n", numero);

    printf("Estado (ex: SP): ");
    scanf("%s", carta->estado);
    limpar_buffer();

    printf("Código da Carta (ex: A01): ");
    scanf("%s", carta->codigo);
    limpar_buffer();

    printf("Nome da Cidade: ");
    fgets(carta->nome_cidade, 50, stdin);
    carta->nome_cidade[strcspn(carta->nome_cidade, "\n")] = 0; // Remove o '\n'

    printf("População (habitantes): ");
    scanf("%lld", &carta->populacao);
    limpar_buffer();

    printf("Área (km²): ");
    scanf("%lf", &carta->area_km2);
    limpar_buffer();

    printf("PIB (Bilhões de R$): ");
    scanf("%lf", &carta->pib_bilhoes);
    limpar_buffer();

    printf("Número de Pontos Turísticos: ");
    scanf("%d", &carta->pontos_turisticos);
    limpar_buffer();

    // Cálculo da Densidade Populacional
    carta->densidade_populacional = (carta->area_km2 > 0) ? 
        (double)carta->populacao / carta->area_km2 : 0.0;

    printf("Carta %d cadastrada com sucesso!\n", numero);
}

// Retorna o valor do atributo com base na escolha
double obter_valor_atributo(const CartaCidade *carta, int atributo_index) {
    switch (atributo_index) {
        case 1: return (double)carta->populacao;
        case 2: return carta->area_km2;
        case 3: return carta->pib_bilhoes;
        case 4: return (double)carta->pontos_turisticos;
        case 5: return carta->densidade_populacional;
        default: return 0.0;
    }
}

// Retorna o nome do atributo com base na escolha
const char* obter_nome_atributo(int atributo_index) {
    switch (atributo_index) {
        case 1: return "População";
        case 2: return "Área";
        case 3: return "PIB";
        case 4: return "Pontos Turísticos";
        case 5: return "Densidade Populacional";
        default: return "Atributo Desconhecido";
    }
}

// Retorna se o atributo tem a regra de "MENOR VENCE"
bool eh_regra_inversa(int atributo_index) {
    // Apenas Densidade Populacional tem regra inversa
    return atributo_index == 5; 
}

// --- Implementação do Nível Novato ---

void nivel_novato(CartaCidade c1, CartaCidade c2) {
    printf("\n\n*** 🏅 INICIANDO NÍVEL NOVATO ***\n");
    
    // 🚩 Objetivo: Comparação baseada em uma propriedade fixa no código (Ex: População)
    const int ATRIBUTO_FIXO = 1; // 1 = População

    printf("Regra do Jogo: Maior valor vence, exceto Densidade Populacional (Menor vence).\n");
    printf("Atributo de comparação fixo: **%s**.\n\n", obter_nome_atributo(ATRIBUTO_FIXO));

    double valor1 = obter_valor_atributo(&c1, ATRIBUTO_FIXO);
    double valor2 = obter_valor_atributo(&c2, ATRIBUTO_FIXO);

    printf("Carta 1 (%s): %.2f\n", c1.nome_cidade, valor1);
    printf("Carta 2 (%s): %.2f\n", c2.nome_cidade, valor2);

    // Lógica de Comparação Simples (if / if-else)
    if (valor1 > valor2) {
        printf("\n🏆 A Carta 1 (%s) Venceu!", c1.nome_cidade);
    } else if (valor2 > valor1) {
        printf("\n🏆 A Carta 2 (%s) Venceu!", c2.nome_cidade);
    } else {
        printf("\n🤝 Empate! Os valores são iguais.");
    }
    printf("\n\n*** NÍVEL NOVATO CONCLUÍDO ***\n");
}

// --- Implementação do Nível Aventureiro ---

void nivel_aventureiro(CartaCidade c1, CartaCidade c2) {
    printf("\n\n*** 🏅 INICIANDO NÍVEL AVENTUREIRO ***\n");
    int escolha;
    int vencedora = 0; // 0: Empate, 1: Carta 1, 2: Carta 2

    // Menu Interativo
    printf("\n--- Menu Interativo de Atributos ---\n");
    printf("1. População (Maior vence)\n");
    printf("2. Área (Maior vence)\n");
    printf("3. PIB (Maior vence)\n");
    printf("4. Pontos Turísticos (Maior vence)\n");
    printf("5. Densidade Populacional (Menor vence)\n");
    printf("Escolha uma opção (1-5): ");
    
    if (scanf("%d", &escolha) != 1 || escolha < 1 || escolha > 5) {
        printf("\nOpção inválida. Retornando ao menu principal.\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();

    printf("\n--- Resultado da Comparação por %s ---\n", obter_nome_atributo(escolha));

    double valor1 = obter_valor_atributo(&c1, escolha);
    double valor2 = obter_valor_atributo(&c2, escolha);
    bool inversa = eh_regra_inversa(escolha);

    // Comparação Aninhada (dentro do switch e if/else)
    if (!inversa) { // Regra padrão: MAIOR VENCE
        if (valor1 > valor2) {
            vencedora = 1;
        } else if (valor2 > valor1) {
            vencedora = 2;
        }
    } else { // Regra inversa (Densidade): MENOR VENCE
        if (valor1 < valor2) {
            vencedora = 1;
        } else if (valor2 < valor1) {
            vencedora = 2;
        }
    }

    // Exibição de Resultados
    if (vencedora == 1) {
        printf("🏆 A Carta 1: **%s** Venceu!\n", c1.nome_cidade);
    } else if (vencedora == 2) {
        printf("🏆 A Carta 2: **%s** Venceu!\n", c2.nome_cidade);
    } else {
        printf("🤝 Empate! Os valores de %s são iguais.\n", obter_nome_atributo(escolha));
    }
    printf("\n*** NÍVEL AVENTUREIRO CONCLUÍDO ***\n");
}

// --- Implementação do Nível Mestre ---

void nivel_mestre(CartaCidade c1, CartaCidade c2) {
    printf("\n\n*** 👑 INICIANDO NÍVEL MESTRE ***\n");
    int atr1, atr2;

    // Menus Dinâmicos - Escolha de Dois Atributos
    printf("\n--- Escolha o PRIMEIRO Atributo de Comparação ---\n");
    printf("1. População | 2. Área | 3. PIB | 4. Pontos Turísticos | 5. Densidade Populacional\n");
    printf("Opção 1 (1-5): ");
    if (scanf("%d", &atr1) != 1 || atr1 < 1 || atr1 > 5) {
        printf("\nOpção inválida. Cancelando Nível Mestre.\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();

    printf("\n--- Escolha o SEGUNDO Atributo de Desempate ---\n");
    printf("Opção 2 (1-5, deve ser diferente de %d): ", atr1);
    if (scanf("%d", &atr2) != 1 || atr2 < 1 || atr2 > 5 || atr2 == atr1) {
        printf("\nOpção inválida ou igual à primeira. Cancelando Nível Mestre.\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();

    printf("\nRegra: 1º Atributo: **%s**. 2º Atributo de Desempate: **%s**.\n", 
           obter_nome_atributo(atr1), obter_nome_atributo(atr2));

    double val1_c1 = obter_valor_atributo(&c1, atr1);
    double val1_c2 = obter_valor_atributo(&c2, atr1);
    bool inv1 = eh_regra_inversa(atr1);

    int vencedor = 0; // 0: Empate, 1: Carta 1, 2: Carta 2
    const char *motivo = "";

    // Lógica de Decisão Complexa (Aninhada e Encadeada)
    
    // Passo 1: Comparação pelo 1º Atributo
    if (!inv1) { // 1º Atributo: MAIOR VENCE
        if (val1_c1 > val1_c2) { vencedor = 1; motivo = obter_nome_atributo(atr1); } 
        else if (val1_c2 > val1_c1) { vencedor = 2; motivo = obter_nome_atributo(atr1); }
    } else { // 1º Atributo: MENOR VENCE
        if (val1_c1 < val1_c2) { vencedor = 1; motivo = obter_nome_atributo(atr1); } 
        else if (val1_c2 < val1_c1) { vencedor = 2; motivo = obter_nome_atributo(atr1); }
    }

    // Passo 2: Desempate pelo 2º Atributo (se houver empate no 1º)
    if (vencedor == 0) {
        double val2_c1 = obter_valor_atributo(&c1, atr2);
        double val2_c2 = obter_valor_atributo(&c2, atr2);
        bool inv2 = eh_regra_inversa(atr2);
        
        motivo = obter_nome_atributo(atr2);
        
        // Uso de Operador Ternário para determinar o vencedor no desempate
        // Estrutura: Condição ? Valor_se_Verdadeiro : Valor_se_Falso
        vencedor = (inv2) // É regra inversa (MENOR VENCE)?
            ? (val2_c1 < val2_c2 ? 1 : (val2_c2 < val2_c1 ? 2 : 0)) // Ternário para regra inversa
            : (val2_c1 > val2_c2 ? 1 : (val2_c2 > val2_c1 ? 2 : 0)); // Ternário para regra padrão (MAIOR VENCE)
    }

    // Exibição de Resultados Avançados
    printf("\n--- Resultado Final ---\n");
    if (vencedor == 1) {
        printf("🏆 A Carta 1: **%s** Venceu!\n", c1.nome_cidade);
        printf("Motivo: %s foi decisivo.\n", motivo);
    } else if (vencedor == 2) {
        printf("🏆 A Carta 2: **%s** Venceu!\n", c2.nome_cidade);
        printf("Motivo: %s foi decisivo.\n", motivo);
    } else {
        printf("🤝 Empate Total! Ambas as cartas são iguais nos atributos **%s** e **%s**.\n",
            obter_nome_atributo(atr1), obter_nome_atributo(atr2));
    }
    printf("\n*** NÍVEL MESTRE CONCLUÍDO ***\n");
}

// --- Função Principal ---

int main() {
    CartaCidade carta1, carta2;
    int escolha_nivel;
    int cartas_cadastradas = 0;

    printf("==========================================\n");
    printf("   Super Trunfo - Países: Todos os Níveis \n");
    printf("==========================================\n");

    // Cadastro Único para todos os níveis
    cadastrar_carta(&carta1, 1);
    cadastrar_carta(&carta2, 2);
    cartas_cadastradas = 1;

    if (cartas_cadastradas) {
        printf("\n==========================================\n");
        printf("        Cartas Cadastradas\n");
        printf("==========================================\n");
        exibir_carta(&carta1, 1);
        exibir_carta(&carta2, 2);
        
        do {
            printf("\n--- Escolha o Nível de Desafio ---\n");
            printf("1. 🏅 Nível Novato (População fixa)\n");
            printf("2. 🏅 Nível Aventureiro (Menu Interativo)\n");
            printf("3. 👑 Nível Mestre (Dois Atributos, Operador Ternário)\n");
            printf("0. Sair\n");
            printf("Escolha uma opção: ");
            
            if (scanf("%d", &escolha_nivel) != 1) {
                escolha_nivel = -1; // Força loop para erro
                limpar_buffer();
                continue;
            }
            limpar_buffer();

            switch (escolha_nivel) {
                case 1:
                    nivel_novato(carta1, carta2);
                    break;
                case 2:
                    nivel_aventureiro(carta1, carta2);
                    break;
                case 3:
                    nivel_mestre(carta1, carta2);
                    break;
                case 0:
                    printf("\nSaindo do programa. Obrigado!\n");
                    break;
                default:
                    printf("\nOpção inválida. Tente novamente.\n");
                    break;
            }
        } while (escolha_nivel != 0);
    }

    return 0;
}