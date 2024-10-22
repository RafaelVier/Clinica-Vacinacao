#include "header.h"
#include <stdio.h>
#include <stdlib.h>

// Apresentação
int main(void) {
  system("clear");
  printf("\033[1;36m==================== APRESENTAÇÃO ====================\033[0m\n");
  printf("Developed by Rafael\n\nEste programa tem a finalidade de ser usado "
         "em uma clinica de vacinação para o controle de fluxo de pacientes e "
         "de coletar "
         "dados dos interessados\n\n");

  // Variaveis
  char nome_clinica[100], sub_menu, op;
  int sala_tri = 0, doses_disp = 0, menu, cadastrados = 0, doses_apli = 0,
      sala_espera, esperando = 0, count_tri = 0;
  // struct Tpessoa paciente;
  struct Tpessoa aux;
  struct Tpessoa *fila_triagem, *fila_espera, *vacinados;
  // Variaveis impressão
  FILE *pont_arq;

  // Inserção de parametros
  printf("\033[1;36m================== DADOS DA CLINICA ==================\033[0m\n");
  printf("\nInforme o nome da clinica: \n");
  scanf("%s", nome_clinica);
  system("clear");
  // Função para leitura da sala de triagem
  sala_tri = LerSalaTri();
  fila_triagem = (struct Tpessoa *)malloc(sizeof(struct Tpessoa) * sala_tri);
  // Função para leitura da quantidade de doses
  doses_disp = LerDoses();
  vacinados = (struct Tpessoa *)malloc(sizeof(struct Tpessoa) * doses_disp);
  // Tamanho da sala de espera
  sala_espera = doses_disp - sala_tri;
  fila_espera = (struct Tpessoa *)malloc(sizeof(struct Tpessoa) * sala_espera);

  // Menu
  // Função para exbibição e escolha no menu
  menu = EscolhaMenu();

  while (menu != 5) {
    switch (menu) {

    case 1:
      system("clear");
      if (doses_disp > cadastrados) {
        if (cadastrados < sala_tri) {
          fila_triagem[count_tri] = lerPessoa();
          count_tri++;
        } else {
          fila_espera[esperando] = lerPessoa();
          esperando++;
        }
        cadastrados++;
        system("clear");
        printf("\n\033[1;32mInteressado cadastrado\033[0m\nTotal = %d\nSala de espera = %d",
               cadastrados, esperando);

      } else
        printf("\033[1;31mDoses esgotadas, interessado não cadastrado!\033[0m");
      break;

    case 2:
      system("clear");
      if (cadastrados <= 0) {
        printf("\n\n\033[1;33mNenhum interessado cadastro no momento!\033[0m\n\033[1;31mImunização não "
               "realizada!\033[0m\n");
      }
      if (doses_disp > 0) {
        if (cadastrados > 0) {
          // Movendo a pessoa da fila de triagem para a struct vacinados
          vacinados[doses_apli] = fila_triagem[0];
          count_tri--;
          // Fazendo a fila andar na triagem
          for (int i = 0; i < count_tri; i++) {
            fila_triagem[i] = fila_triagem[i + 1];
          }
          doses_disp--;
          doses_apli++;
          cadastrados--;
          printf(
              "\033[1;32mImunização do primeiro da fila realizada\033[0m\n\nDoses disponiveis: "
              "%d\nImunizados: %d\nSala de espera: %d",
              doses_disp, doses_apli, esperando);
        }

        // Primeiro da sala de espera indo para a última posição da triagem
        if (esperando > 0) {
          fila_triagem[sala_tri - 1] = fila_espera[0];
          count_tri++;
          // Fazendo a fila de espera andar
          for (int i = 0; i < esperando; i++) {
            fila_espera[i] = fila_espera[i + 1];
          }
          esperando--;
        }

      } else if ((doses_disp <= 0) && (cadastrados <= 0)) {
        op = fimDia();
        if (op == 'S') {
          printf("\033[1;31mprograma encerrado\033[0m");
          return 0;
        }
      }
      break;

    case 3:
      system("clear");
      if (cadastrados == 0) {
        printf("\033[1;33mNenhum interessado aguardando a ser vacinado!\033[0m\n");
      }
      if (cadastrados > 0) {
        printf("\033[1;34mFila de triagem:\033[0m\n ");
        for (int i = 0; i < count_tri; i++) {
          printf("\n\n\033[1;34mDados do %dº da fila:\033[0m\n", i + 1);
          printf("Nome completo: %s %s\nIdade: %d\nSexo: %c",
                 fila_triagem[i].nome, fila_triagem[i].sobrenome,
                 fila_triagem[i].idade, fila_triagem[i].sexo);
        }
      }
      break;
    // Submenu
    case 4:
      system("clear");
      sub_menu = EscolhaSubMenu();
      while ((sub_menu != 'e') && (sub_menu != 'E')) {

        switch (sub_menu) {
        case 'a':
        case 'A':
          system("clear");
          printf("\n\n\033[1;35mDoses aplicadas:\033[0m %d\n\033[1;35mDoses disponiveis:\033[0m %d\n", doses_apli,
                 doses_disp);
          break;
        case 'b':
        case 'B':
          system("clear");
          if (doses_apli == 0) {
            printf("\n\033[1;33mNenhum paciente vacinado no dia de hoje!\033[0m\n\n");
          }
          if (doses_apli > 0) {
            printf("\033[1;34mPessoas imunizadas:\033[0m\n");
            for (int i = 0; i < doses_apli; i++) {
              printf("\n\n\033[1;34mDados do %dº vacinado:\033[0m\n", i + 1);
              printf("Nome completo: %s %s\nIdade: %d\nSexo: %c",
                     vacinados[i].nome, vacinados[i].sobrenome,
                     vacinados[i].idade, vacinados[i].sexo);
            }
          }

          break;
        case 'c':
        case 'C':
          system("clear");
          if (esperando == 0) {
            printf("\n\033[1;33mNenhum paciente na fila de espera!\033[0m\n");
          }
          if (esperando > 0) {
            printf("\033[1;34mFila de espera:\033[0m\n");
            for (int i = 0; i < esperando; i++) {
              printf("\n\n\033[1;34mDados do %dº interessado na fila de espera:\033[0m\n", i + 1);
              printf("Nome completo: %s %s\nIdade: %d\nSexo: %c",
                     fila_espera[i].nome, fila_espera[i].sobrenome,
                     fila_espera[i].idade, fila_espera[i].sexo);
            }
          }

          break;
        case 'd':
        case 'D':
          system("clear");
          // abrindo o arquivo
          pont_arq = fopen("relatorio.txt", "w+");

          fprintf(pont_arq, "Doses aplicadas: %d\nDoses disponiveis: %d\n",
                  doses_apli, doses_disp);

          if (doses_apli == 0) {
            fprintf(pont_arq, "\nNenhum paciente vacinado no dia de hoje!\n\n");
          }
          if (doses_apli > 0) {
            fprintf(pont_arq, "\n\nRelação de pessoas imunizadas:\n");
            for (int i = 0; i < doses_apli; i++) {
              fprintf(pont_arq, "\nDados do %dº vacinado:\n", i + 1);
              fprintf(pont_arq, "Nome completo: %s %s\nIdade: %d\nSexo: %c",
                      vacinados[i].nome, vacinados[i].sobrenome,
                      vacinados[i].idade, vacinados[i].sexo);
            }
          }

          if (esperando == 0) {
            fprintf(pont_arq, "\nNenhum paciente na fila de espera!\n");
          }
          if (esperando > 0) {
            fprintf(pont_arq, "\nFila de espera:");
            for (int i = 0; i < esperando; i++) {
              fprintf(pont_arq, "\n\nDados do %dº da fila de espera\n:", i + 1);
              fprintf(pont_arq, "Nome completo: %s %s\nIdade: %d\nSexo: %c",
                      fila_espera[i].nome, fila_espera[i].sobrenome,
                      fila_espera[i].idade, fila_espera[i].sexo);
            }
          }
          // fechando arquivo
          fclose(pont_arq);

          printf("\n\033[1;35mO arquivo foi gerado com sucesso!\033[0m");
          // printf("Arquivos gerados para impressão!\n");
          break;
        }
        sub_menu = EscolhaSubMenu();
      }
      printf("\n\033[1;34mRetornando ao menu anterior!\033[0m\n");
    }
    // Função para exbibição e escolha no menu
    menu = EscolhaMenu();
  }
  printf("\n\033[1;31mMenu encerrado!\033[0m");

  return 0;
}
