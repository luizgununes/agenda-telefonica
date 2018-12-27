/*

* Programa: Agenda Telefônica
* Data de Criação: 20/11/2017
* Criado por: Luiz Gustavo Nunes

*/

#include <stdio.h> // Biblioteca para usar printf, gets, fread...
#include <stdlib.h> // Biblioteca para usar o system("cls").
#include <ctype.h> // Biblioteca para usar o toupper.
#include <conio.h> // Biblioteca para usar o getche.
#include <string.h> // Biblioteca para usar o strcmp e strcpy.
#include <locale.h> // Biblioteca para usar o setlocale.
#include <windows.h> // Biblioteca para usar o SetConsoleTitle.

// Declaração da estrutura: 
typedef struct agenda
{
    char nome[50];
    char fone[20];
    int telefone;
    int dia,mes,ano;
}agenda;

// Variáveis Globais:
FILE *arq;
agenda contato;

// Função menu, apresentando as opções ao usuário:
char menu()
{
    system("cls");
	printf("**************************************************************************\n");
    printf("**                       = Agenda Telefônica 1.0 =                      **\n");
    printf("**************************************************************************\n");
    printf("**                  [1]  Adicionar um novo contato. [1]                 **\n");                             
    printf("**                  [2]  Mostrar lista de contatos. [2]                 **\n");
    printf("**                  [3]  Buscar contato pelo nome.  [3]                 **\n");
    printf("**                  [4]    Modificar um contato.    [4]                 **\n");
    printf("**                  [5]     Remover um contato.     [5]                 **\n");
    printf("**                  [0]           Sair.             [0]                 **\n");
    printf("**************************************************************************\n");
    printf("\n");
    printf("> ");
    return (toupper(getche()));
}

// Função que verifica se no arquivo "agenda.dad", já existe nome do contato, retornando 1:
int verifica(char nome[])
{
    fread(&contato,sizeof(agenda),1,arq);
    while(!feof(arq))
    {
        if (strcmp(contato.nome,nome) == 0)

        {
            fseek(arq,-sizeof(agenda),SEEK_CUR);
            return 1;
        }
        fread(&contato,sizeof(agenda),1,arq);
    }

    return 0;
}

// Função para adicionar contatos na agenda:
void adicionar()
{
    char nome[50];

    arq = fopen("agenda.dad","a+b");
    if (arq == NULL)
    {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    printf("\n\n");
    printf("Digite o nome: ");
    fflush(stdin);
    gets(nome);

    if (verifica(nome) == 1)
    {

        printf("\nNome já existente.\n");
    }
    else
    {
        strcpy(contato.nome,nome);
        printf("Digite o telefone: ");
        scanf("%d", &contato.telefone);
        printf("Digite a data de nascimento: ");
        scanf("%d/%d/%d", &contato.dia, &contato.mes, &contato.ano);
        fwrite(&contato,sizeof(agenda),1,arq);
    }
    fclose(arq);
}

// Função para editar um contato:
void modificar()
{
    char nome[50];

    arq = fopen("agenda.dad","r+b");
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("\n\n");
    printf("Digite  o nome do contato que deseja alterar: ");
    fflush(stdin);
    gets(nome);

    if (verifica(nome) == 1)
    {
        printf("\nDigite um novo nome: ");
        fflush(stdin);
        gets(nome);
        strcpy(contato.nome,nome);
        printf("\nDigite um novo número de telefone: ");
        scanf("%d", &contato.telefone);
        printf("\nDigite uma nova data de nascimento: ");
        scanf("%d/%d/%d", &contato.dia, &contato.mes, &contato.ano);
        fwrite(&contato,sizeof(agenda),1,arq);
    }

    else
    {
        printf("\nContato Inexistente.\n");
    }

    fclose(arq);
}

// Função para remover um contato:
void remover()
{
    char nome[50];
    FILE *tmp;

    arq = fopen("agenda.dad","r+b");
    if (arq == NULL)
    {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    tmp = fopen("agenda.txt","a+b");

    printf("\n\n");
    printf("Digite o nome do contato: ");
    fflush(stdin);
    gets(nome);

    fread(&contato,sizeof(agenda),1,arq);
    while (!feof(arq))
    {

        if (strcmp(contato.nome,nome) != 0) // Compara o nome.
        
        {
           fwrite(&contato,sizeof(agenda),1,tmp); // Grava no arquivo temporário.
        }
        fread(&contato,sizeof(agenda),1,arq); // Lê o arquivo.

    }
    fclose(arq);
    fclose(tmp);

    system("del agenda.dad");
    system("ren agenda.txt agenda.dad");
}

// Função para procurar um contato pelo nome:
void buscar()
{
    char nome[50];

    arq = fopen("agenda.dad","r+b");
    if (arq == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    printf("\n\n");
    printf("Digite o nome: ");
    fflush(stdin);
    gets(nome);

    if (verifica(nome) == 1)
    {
        fread(&contato,sizeof(agenda),1,arq);
        printf("\n\n");
        printf("--------------------------------------------------------------------------\n");
        printf("Nome:                          Telefone:               Data de Nascimento: \n");
        printf("--------------------------------------------------------------------------\n");
        printf("%-20s          %10d    \t\t   %d/%d/%d\n", contato.nome,contato.telefone,contato.dia,contato.mes,contato.ano);
        printf("--------------------------------------------------------------------------\n");

    }

    else
    {
        printf("\nContato não existe.\n");
    }

    fclose(arq);
}

// Função que lista os contatos: 
void listar()
{
    arq = fopen("Agenda.dad","r+b");
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("\n\n");
    printf("--------------------------------------------------------------------------\n");
    printf("Nome:                          Telefone:               Data de Nascimento: \n");
    printf("--------------------------------------------------------------------------\n");

    fread(&contato,sizeof(agenda),1,arq);
    while (!feof(arq))
    {
        printf("%-20s          %10d    \t\t   %d/%d/%d\n", contato.nome,contato.telefone,contato.dia,contato.mes,contato.ano);
        fread(&contato,sizeof(agenda),1,arq);
    }
    printf("--------------------------------------------------------------------------\n");

    fclose(arq);
}

// Função Principal:
int main()
{
    
    setlocale(LC_ALL, "Portuguese"); // Comando de regionalização.
  
    SetConsoleTitle("Agenda Telefonica"); // Permite nomear a janela do programa.
    
    char op;

    do
    {
        op = menu();

        switch(op)
        {
            case '1': adicionar(); break;
            case '2': listar(); break;
            case '3': buscar(); break;
            case '4': modificar(); break;
            case '5': remover(); break;
        }

        printf("\n");
        system("pause");

    }while (op != '0');

    return 0;
}
