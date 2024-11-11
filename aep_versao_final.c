#include <stdio.h>

#include <stdlib.h>

#include <string.h>

int totalUsuarios = 0;
#define CHAVE_XOR 0x5A

char credito1[50] = "Bernardo Fiorese Perly. 24087537-2";
char credito2[50] = "Luiz Miguel Plaza de Souza. 23149095-2 ";
char credito3[50] = "Julio Cezar Dos Santos Kamke. 24058066-2";

struct referencia {
  char nome0[50];
  char nome1[50];
}
CA[600];

void xorCipher(char * str) {
  int i;
  for (i = 0; str[i] != '\0'; i++) {
    str[i] ^= CHAVE_XOR;
  }
}

void salvarUsuarios() {
  FILE * file = fopen("users.txt", "w");
  int i;

  if (file == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  for (i = 0; i < totalUsuarios; i++) {
    char nomeCripto[50], senhaCripto[50];

    strcpy(nomeCripto, CA[i].nome0);
    strcpy(senhaCripto, CA[i].nome1);
    xorCipher(nomeCripto);
    xorCipher(senhaCripto);

    fprintf(file, "%s %s\n", nomeCripto, senhaCripto);
  }

  fclose(file);
}

void carregarUsuarios() {
  FILE * file = fopen("users.txt", "r");
  if (file != NULL) {
    while (fscanf(file, "%49s %49s", CA[totalUsuarios].nome0, CA[totalUsuarios].nome1) != EOF) {
      xorCipher(CA[totalUsuarios].nome0);
      xorCipher(CA[totalUsuarios].nome1);
      totalUsuarios++;
    }
    fclose(file);
  }
}

// Função principal
int main() {
  int opcao;
  carregarUsuarios();

  do {
    system("cls");
    printf("\t\t\t SEJA BEM-VINDO AO MENU, SELECIONE A SUA OPÇÃO ABAIXO \n");
    printf("[1] - CADASTRAR NOVO USUÁRIO \n");
    printf("[2] - EXIBIR USUÁRIOS CADASTRADOS \n");
    printf("[3] - ALTERAR DADOS DE UM USUÁRIO \n");
    printf("[4] - REMOVER UM USUÁRIO \n");
    printf("[5] - SAIR\n");
    printf("[6] - CRÉDITOS\n");
    printf("-------------------------------------------------------------------------------- \n");

    scanf("%d", & opcao);

    switch (opcao) {
    case 1: {
      system("cls");
      int novosUsuarios, j;
      printf("Quantos usuários você gostaria de cadastrar? \n");
      scanf("%d", & novosUsuarios);

      for (j = totalUsuarios; j < totalUsuarios + novosUsuarios; j++) {
        system("cls");
        printf("Qual é o nome do usuário? (Máximo 50 caracteres) \n");
        while (getchar() != '\n');
        scanf("%[^\n]s", CA[j].nome0);
        printf("Qual é a senha do usuário? (Máximo 50 caracteres) \n");
        while (getchar() != '\n');
        scanf("%[^\n]s", CA[j].nome1);

        printf("Usuário %d cadastrado com sucesso.\n", j + 1);
        system("pause");
      }

      totalUsuarios += novosUsuarios;
      salvarUsuarios();
      break;
    }

    case 2: {
      int i;
      system("cls");
      if (totalUsuarios == 0) {
        printf("Nenhum usuário cadastrado.\n");
      } else {
        printf("\t\t\t EXIBINDO OS USUÁRIOS CADASTRADOS: \n");
        printf("-------------------------------\n");
        for (i = 0; i < totalUsuarios; i++) {
          printf("Usuário [%d]\n", i + 1);
          printf("Nome: %s\n", CA[i].nome0);
          printf("Senha: %s\n", CA[i].nome1);
          printf("-------------------------------\n");
        }
      }
      printf("Pressione qualquer tecla para voltar ao menu...\n");
      while (getchar() != '\n');
      getchar();
      break;
    }

    case 3: {
      int i, usuarioEscolhido, opcao1;
      system("cls");
      if (totalUsuarios == 0) {
        printf("Nenhum usuário cadastrado para editar.\n");
      } else {
        printf("Qual usuário você gostaria de editar? (lista abaixo)\n");
        printf("-------------------------------\n");
        for (i = 0; i < totalUsuarios; i++) {
          printf("[%d] - Nome: %s\n", i + 1, CA[i].nome0);
        }
        printf("-------------------------------\n");

        printf("Digite o número do usuário que deseja editar: ");
        scanf("%d", & usuarioEscolhido);

        if (usuarioEscolhido < 1 || usuarioEscolhido > totalUsuarios) {
          printf("Usuário inválido.\n");
        } else {
          usuarioEscolhido--;
          system("cls");
          printf("Qual informação do usuário deseja alterar? \n");
          printf("[1] - Nome do usuário \n");
          printf("[2] - Senha do usuário \n");
          scanf("%d", & opcao1);

          switch (opcao1) {
          case 1:
            printf("Digite o novo nome do usuário: ");
            while (getchar() != '\n');
            scanf("%[^\n]s", CA[usuarioEscolhido].nome0);
            printf("Nome alterado com sucesso.\n");
            break;

          case 2:
            printf("Digite a nova senha: ");
            while (getchar() != '\n');
            scanf("%[^\n]s", CA[usuarioEscolhido].nome1);
            printf("Senha atualizada com sucesso.\n");
            break;

          default:
            printf("Opção inválida.\n");
            break;
          }

          salvarUsuarios();
        }
      }
      system("pause");
      break;
    }

    case 4: {
      int i, usuarioRemover;
      system("cls");
      if (totalUsuarios == 0) {
        printf("Nenhum usuário cadastrado para remover.\n");
      } else {
        printf("Qual usuário você gostaria de remover? (lista abaixo)\n");
        printf("-------------------------------\n");
        for (i = 0; i < totalUsuarios; i++) {
          printf("[%d] - Nome: %s\n", i + 1, CA[i].nome0);
        }
        printf("-------------------------------\n");

        printf("Digite o número do usuário que deseja remover: ");
        scanf("%d", & usuarioRemover);

        if (usuarioRemover < 1 || usuarioRemover > totalUsuarios) {
          printf("Usuário inválido.\n");
        } else {
          usuarioRemover--;

          for (i = usuarioRemover; i < totalUsuarios - 1; i++) {
            CA[i] = CA[i + 1];
          }

          totalUsuarios--;
          printf("Usuário removido com sucesso.\n");

          salvarUsuarios();
        }
      }
      system("pause");
      break;
    }

    case 6: {
      system("cls");
      printf("\t\t\t ESSE PROGRAMA FOI FEITO DO ZERO PELOS ALUNOS:\n");
      printf("%s\n", credito1);
      printf("%s\n", credito2);
      printf("%s\n", credito3);
      printf("-------------------------------\n");
      printf("Pressione qualquer tecla para voltar ao menu...\n");
      system("pause");
      break;
    }

    }
  } while (opcao != 5);

  return 0;
}