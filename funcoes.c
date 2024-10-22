#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para leitura da sala de triagem
int LerSalaTri() {
  int a = 0;
  printf("\nInforme o tamanho da sala de triagem, min 3 max 5\n");
  while ((a > 5) || (a < 3)) {
    scanf("%d", &a);
    if ((5 < a) || (a < 3)) {
      printf("\n\033[1;31mNúmero inválido!\033[0m\nTamanho min 3 e max 5\n\nInforme um novo "
             "número:\n");
    }
  }
  system("clear");
  return a;
}

// Função para leitura da quantidade de doses
int LerDoses() {
  int a = 0;
  printf("\nInforme a quantia de doses disponiveis: \n");
  while (a <= 0) {
    scanf("%d", &a);
    if (a <= 0) {
      printf("\n\033[1;31mNúmero inválido!\033[0m\nFavor informar número "
             "maior que 0!\n\nInforme um novo número\n");
    }
  }
  system("clear");
  return a;
}

// Função para exbibição e escolha no menu
int EscolhaMenu() {
  int a = 0;
  printf("\n\n\033[1;36m===================== MENU =====================\033[0m\n");
  printf("\n\033[1;35mSelecione uma das opções abaixo:\033[0m\n\n [1] - Cadastrar interessado\n "
         "[2] "
         "- Confirmação de imunização\n [3] - Exibir fila em triagem\n [4] - "
         "Relatórios\n [5] - Encerrar\n\n ");
  do {
    while (!scanf("%d", &a)) {
      flush_in();
      printf("\033[1;31mVocê digitou um caracter!\033[0m\nFavor informe um número de 1 a 5!\n");
    }
    if ((a > 5) || (a < 1)) {
      printf("\n\033[1;31mOpção inválida!\033[0m\nSelecione uma opção de 1 a 5:\n");
    }
  } while ((a > 5) || (a < 1));
  return a;
}

// Função para exibição e escolha do submenu
int EscolhaSubMenu() {
  char sub;
  printf("\n\n\033[1;36m=================== RELATÓRIOS ===================\033[0m\n");
  printf("\n\033[1;35mEscolha o relatório desejado:\033[0m \n\n [a] - Quantidade de doses "
         "aplicadas e doses disponíveis\n [b] - Relação de pessoas "
         "imunizadas "
         "\n [c] - Relação de pessoas cadastradas na fila de espera e "
         "fora da "
         "triagem \n [d] - Gerar arquivo para impressão (com todas as "
         "informações de A, B e C)\n [e] - Voltar ao menu anterior\n ");
  void flush_in();
  scanf(" %c", &sub);
  return sub;
}

// Função para limpeza de buffer ao ler string
void flush_in() {
  int ch;
  do {
    ch = fgetc(stdin);
  } while (ch != EOF && ch != '\n');
}

// Ler string
void lerString(char s[], int tam) {
  fgets(s, tam, stdin);
  s[strcspn(s, "\n")] = 0;
}

// Ler pessoa
struct Tpessoa lerPessoa() {
  struct Tpessoa aux;
  flush_in();
  printf("Digite o nome do interessado: ");
  lerString(aux.nome, 30);
  printf("Digite o sobrenome do interessado: ");
  lerString(aux.sobrenome, 40);
  do {

    printf("Digite o sexo (f/m): ");
    scanf("%c", &aux.sexo);
    flush_in();
    if ((aux.sexo != 'f') && (aux.sexo != 'm'))
      printf("\033[1;33mDigite 'f' para feminino, ou 'm' para masculino!\033[0m\n");

  } while ((aux.sexo != 'f') && (aux.sexo != 'm'));
  printf("Digite a idade da pessoa: ");
  scanf("%d", &aux.idade);
  return aux;
}

// Exibe interessados na fila
void imprimeFilaPessoas(struct Tpessoa fila[], int tamanho) {
  printf("\nPessoas na fila: ");
  for (int cont = 0; cont < tamanho; cont++) {
    printf("\nNome: %s", fila[cont].nome);
    printf("\nIdade: %d", fila[cont].idade);
  }
}

// Validação para finalizar o dia
int fimDia() {
  char op, sub_menu;
  printf("\033[1;32mDoses esgotadas e todos os interessados cadastrados foram "
         "imunizados!\nDeseja encerar o programa?\n\nS = "
         "sim\nN = Não\033[0m\n");
  while ((op != 'S') && (op != 'N')) {
    scanf(" %c", &op);
    if ((op != 'S') && (op != 'N')) {
      printf("\n\033[1;31mOpção inválida!\033[0m\nInforme 'S' para sim ou 'N' para não:\n");
    }
  }
  return op;
 }