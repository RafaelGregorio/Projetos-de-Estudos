#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>


int op;//Variavel global 

//Struct Usuario
struct Usuario
{
    char nome[10];
    char senha[10];
    int unidade;
}usuarios[10];
//Struct de Endereços
typedef struct
{
    char Logradouro[10];
    char complemento[20];
    char cep[10];
    char bairro[20];
    char cidade[20];
    char estado[3];

}End;
//Struct de pacientes
typedef struct
{
    int codigo;
    char nome[30];
    char cpf[20];
    char email[20];
    int idade;
    float peso;
    End endereco;

}Pac;
//Struct de medicos
typedef struct
{
    int codigo;
    int idade;
    char nome[30];
    char especialidade[30];
    char formacao[30];
    char email[20];
    End endereco;

}Med;
//Struct de Funcionarios
typedef struct
{
    int codigo;
    char nome[30];
    int  idade;
    char cargo[50];
    char horario[30];
    char gestor[30];
    char email[20];
    char telefone[20];

}Fun;

//struct Agendamentos
typedef struct
{
    int codigo;
    Pac paciente;
    char de[18];
    char ate[18];
}Agen;

void menu();

// Declaração das Funções de usuarios
void inicializa_usuario()
{
    int i;
    strcpy(usuarios[0].nome, "caio");
    strcpy(usuarios[0].senha, "123");
    usuarios[0].unidade = 1;// Unidade de 

    strcpy(usuarios[1].nome, "marcos");
    strcpy(usuarios[1].senha, "123");
    usuarios[1].unidade = 2; //unidade de Osasco

    strcpy(usuarios[2].nome, "eliezer");
    strcpy(usuarios[2].senha, "123");
    usuarios[2].unidade = 3; //Unidade de Barueri


    strcpy(usuarios[3].nome, "vinicius");
    strcpy(usuarios[3].senha, "123");

    for (i = 4; i < 10; i++)
        strcpy(usuarios[i].nome, "----");
}

void fgets_usuario(char* string, int pos)
{
    //Fgets que limpa o buffer
    char ch;
    fgets(string, pos, stdin);
    strtok(string, "\n");   //Esta funcao retira o '\n' do final da string

    if (strlen(string) == pos - 1)
        while ((ch = getchar()) != '\n' && ch != EOF);
}

int login(char usuario[10], char pwd[10])
{
    int i;

    for (i = 0; i < 10; i++)
    {
        if (strcmp(usuarios[i].nome, usuario) == 0 && strcmp(usuarios[i].senha, pwd) == 0)
            return i;
        else if (strcmp(usuarios[i].nome, "----") == 0)
            return -i;
    }
}


//Declaração das funções que gerencia as ações realcionadas com os pacientes
void GerenciamentoDePaciente(Pac*, int*, FILE*);
Pac cadastroDePaciente(Pac, int);
void ListarPacientes(Pac*, int);
void ordenarPacientePorOrdemAlfabetica(Pac*, int);
void buscarPaciente(Pac*, int);
void atualizarPaciente(Pac*, int);
void excluirPaciente(Pac*, int*);
void imprimirPaciente(Pac);

//Declaração das funções que gerencia as ações realcionadas aos medicos
void GerenciamentoDeMedico(Med*, int*, FILE*);
Med cadastroDeMedico(Med, int);
void ListarMedicos(Med*, int);
void ordenarMedicoPorOrdemAlfabetica(Med*, int);
void buscarMedico(Med*, int);
void atualizarMedico(Med*, int);
void excluirMedico(Med*, int*);
void imprimirMedico(Med);

//Declaração das funções que gerencia as ações realcionadas aos Funcionarios
void GerenciamentoDeFuncionario(Fun*, int*, FILE*);
Fun cadastroDeFuncionario(Fun, int);
void ListarFuncionario(Fun*, int);
void ordenarFuncionarioPorOrdemAlfabetica(Fun*, int);
void buscarFuncionario(Fun*, int);
void atualizarFuncionario(Fun*, int);
void excluirFuncionario(Fun*, int*);
void imprimirFuncionario(Fun);

//Declaração das funções que gerencia as ações realcionadas aos agendamentos
void GerenciamentoDeAgendamentos(Agen*, int*, FILE*);
Agen cadastroDeAgendamentos(Agen, int);
void ListarAgendamentos(Agen*, int);
void buscarAgendamentos(Agen*, int);
void atualizarAgendamentos(Agen*, int);
void excluirAgendamentos(Agen*, int*);
void imprimirAgendamentos(Agen);





int main()
{
    FILE* arquivo;
    Pac* paciente;
    Med* medico;
    Fun* funcionario;
    Agen* agendamento;

    struct Usuario tentativa_entrada;
    int opcao_menu, pos_usuario, i;
    int contPaciente = 0, contMedico = 0, contFuncionario = 0, contAgendamento = 0; //contadores em 0

    //alocando memória para os ponteiros
    paciente = calloc(10, sizeof(Pac));
    medico = calloc(10, sizeof(Med));
    funcionario = calloc(10, sizeof(Fun));
    agendamento = calloc(10, sizeof(Agen));

    //comceca os dados de login
    do
    {

        system("cls");

        inicializa_usuario();

        printf("\n Entre com o login: ");
        fgets_usuario(tentativa_entrada.nome, 10);

        printf("\n Entre com a senha: ");
        fgets_usuario(tentativa_entrada.senha, 10);

        pos_usuario = login(tentativa_entrada.nome, tentativa_entrada.senha);
        if (pos_usuario >= 0) {
            printf("\n Entrada de %s autorizada com sucesso!\n\n", usuarios[pos_usuario].nome);

            //comeca o menu do sistema
            menu();

            do {
                switch (op) {
                case 1:
                    GerenciamentoDePaciente(paciente, &contPaciente, arquivo);
                    break;
                case 2:
                    GerenciamentoDeMedico(medico, &contMedico, arquivo);
                    break;
                case 3:
                    GerenciamentoDeFuncionario(funcionario, &contFuncionario, arquivo);
                    break;
                case 4:
                    GerenciamentoDeAgendamentos(agendamento, &contAgendamento, arquivo);
                case 7:
                    exit(1);
                    break;


                default:
                    printf("opcao invalida! ");
                    sleep(2);
                    system("cls");
                    menu();
                }
            } while (1);

        }
        else
            printf(" Login %s Invalido!\n Por favor tente novamente...\n\n", usuarios[pos_usuario].nome);
        sleep(2);

    } while (usuarios[i].nome && usuarios[i].senha != usuarios[i].nome && usuarios[i].senha);

    return 0;
}


void menu() {
    printf("======= Menu de Gerenciamento =======\n\n");
    printf(" 1 - Gerenciar Pacientes\n");
    printf(" 2 - Gerenciar Medicos\n");
    printf(" 3 - Gerenciar Funcionarios\n");
    printf(" 4 - Gerenciar Agendamentos\n");
    printf(" 6 - Gerenciar Fedbacks\n");
    printf(" 7 - Sair\n");
    printf("\n Digite um comando pra prosseguir: ");
    scanf(" %d", &op);
    system("cls");
}

// Gerenciamento de Pacientes
void GerenciamentoDePaciente(Pac* paciente, int* contPaciente, FILE* arquivo) {
    int opcao;

    do {
        printf("\n======== Gerenciar Pacientes ========\n\n");
        printf(" 1 - Cadastrar Pacientes\n");
        printf(" 2 - Listar pacientes cadastrados\n");
        printf(" 3 - Buscar pacientes cadastrados\n");
        printf(" 4 - Atualizar pacientes cadastrados\n");
        printf(" 5 - Excluir pacientes cadastrados\n");
        printf(" 6 - Voltar ao menu de Gerenciamento\n");
        printf("\n Digite uma opcao para prosseguir: \n");
        scanf(" %d", &opcao);
        system("cls");

        switch (opcao) {
        case 1:
            arquivo = fopen("Cadastro_paciente.txt", "a+");
            if (arquivo == NULL) {
                printf("Não foi possivel abrir o arquivo.");
                return;
            }

            printf("======Cadastro de Pacientes =====\n");
            paciente[*contPaciente] = cadastroDePaciente(paciente[*contPaciente], 0);

            fprintf(arquivo, "%d;%s;%s;%s;%d;%f;%s;%s;%s;%s;%s;%s\n", paciente[*contPaciente].codigo, paciente[*contPaciente].nome,
                paciente[*contPaciente].cpf, paciente[*contPaciente].email, paciente[*contPaciente].idade, paciente[*contPaciente].peso,
                paciente[*contPaciente].endereco.cep, paciente[*contPaciente].endereco.Logradouro, paciente[*contPaciente].endereco.bairro,
                paciente[*contPaciente].endereco.cidade, paciente[*contPaciente].endereco.estado, paciente[*contPaciente].endereco.complemento);
            fclose(arquivo);

            *contPaciente += 1;
            if (*contPaciente == 10)
                paciente = realloc(paciente, (*contPaciente + 1) * sizeof(Pac));
            break;
        case 2:
            ListarPacientes(paciente, *contPaciente);
            break;
        case 3:
            buscarPaciente(paciente, *contPaciente);
            break;
        case 4:
            atualizarPaciente(paciente, *contPaciente);
            break;
        case 5:
            excluirPaciente(paciente, contPaciente);
            break;
        case 6:
            return menu();
            break;

        default:
            printf("Opcao invalida!");
            sleep(2);
            system("cls");
            continue;
        }
        break;
    } while (1);
}

Pac cadastroDePaciente(Pac paciente, int identificador) {
    //char opcao;
    char codigoPaciente[10];
    char idadePaciente[10];
    char pesoPaciente[10];


    do {
        printf("\nCodigo do Paciente: ");
        scanf(" %s", codigoPaciente);

        paciente.codigo = atoi(codigoPaciente);
        if (identificador == 0) {
            if (paciente.codigo == 0) {
                printf("\n codigo invalido!\n Apenas numeros");
                sleep(2);
                system("cls");
                printf("\n==== Cadastro de Pacientes====\n");
                continue;
            }
        }
        else {
            if (paciente.codigo == 0 && strlen(codigoPaciente) > 0) {
                printf("Codigo invalido\n");
                sleep(2);
                system("cls");
                continue;
            }
        }
        break;
    } while (1);
    printf("\nNome do Paciente: ");
    scanf(" %[^\n]s", paciente.nome);
    printf("\nCPF do Paciente: ");
    scanf(" %[^\n]s", paciente.cpf);
    printf("\nE-mail do paciente: ");
    scanf(" %[^\n]s", paciente.email);
    printf("\nIdade do Paciente: ");
    scanf(" %s", idadePaciente);
    paciente.idade = atoi(idadePaciente);
    printf("\nPeso do Paciente: ");
    scanf(" %s", pesoPaciente);
    paciente.peso = atoi(pesoPaciente);
    printf("\nEndereco do cliente:\n ");
    printf("\nCEP: ");
    scanf(" %[^\n]s", paciente.endereco.cep);
    printf("\nLogradouro: ");
    scanf(" %[^\n]s", paciente.endereco.Logradouro);
    printf("\nBairro: ");
    scanf(" %[^\n]s", paciente.endereco.bairro);
    printf("\nCidade: ");
    scanf(" %[^\n]s", paciente.endereco.cidade);
    printf("\nestado: ");
    scanf(" %[^\n]s", paciente.endereco.estado);
    printf("\ncomplemento: ");
    scanf(" %[^\n]s", paciente.endereco.complemento);

    if (identificador == 0) {
        printf("\n Cadastro realizado com sucesso!!!\n");
        sleep(2);
        system("cls");
        menu();
    }

    return paciente;
}

void ListarPacientes(Pac* paciente, int contPaciente) {

    int i;

    if (contPaciente == 0) {
        printf("Erro! Nenhum Paciente cadastrado\n");
        sleep(2);
        system("cls");
        menu();
        return;
    }

    ordenarPacientePorOrdemAlfabetica(paciente, contPaciente);

    printf("Lista de Pacientes cadastrados\n\n");
    for (i = 0; i < contPaciente; i++)
        imprimirPaciente(paciente[i]);

    //getch(); tentar usar o getchar()
    //sleep(4);
    //system("cls");

    menu();
}

void ordenarPacientePorOrdemAlfabetica(Pac* paciente, int contPaciente) {

    int i, j, marcador;
    Pac aux;

    for (i = 1; i < contPaciente; i++) {
        aux = paciente[1];
        j = i - 1;
        do {
            marcador = 0;
            if (strcmp(paciente[j].nome, aux.nome) > 0) {
                paciente[j + 1] = paciente[j];
                j--;
                marcador = 1;
            }
            if (j < 0)
                marcador = 0;

        } while (marcador);

        paciente[j + 1] = aux;
    }
}

void imprimirPaciente(Pac paciente) {

    printf(" Codigo: %d\n", paciente.codigo);
    printf(" Nome: %s\n", paciente.nome);
    printf(" CPF:  %s\n", paciente.cpf);
    printf(" E-mail: %s\n", paciente.email);
    printf(" Idade: %d\n", paciente.idade);
    printf(" Peso: %.3f\n", paciente.peso);
    printf(" CEP: %s\n", paciente.endereco.cep);
    printf(" Logradouro: %s\n", paciente.endereco.Logradouro);
    printf(" Bairro: %s\n", paciente.endereco.bairro);
    printf(" Cidade: %s\n", paciente.endereco.cidade);
    printf(" Estado: %s\n", paciente.endereco.estado);
    printf(" Complemento: %s\n\n", paciente.endereco.complemento);
}

void buscarPaciente(Pac* paciente, int contPaciente) {

    int i, marcador = 0;
    int codigoPaciente;
    char nomePaciente[30];

    printf("Digite o nome ou o codigo do paciente que deseja buscar: ");
    scanf(" %[^\n]s", nomePaciente);
    printf("\n");
    codigoPaciente = atoi(nomePaciente);

    for (i = 0; i < contPaciente; i++) {
        if (paciente[i].codigo == codigoPaciente || strcmp(paciente[i].nome, nomePaciente) == 0) {
            imprimirPaciente(paciente[i]);
            //getch();
            marcador = 1;
            break;
        }
    }
    if (!marcador) {
        printf("  ERRO!!! \nPaciente nao cadastrado\n");
        sleep(2);
        system("cls");
    }

    menu();
}

void atualizarPaciente(Pac* paciente, int contPaciente) {

    int codigo, i, marcador = 0;
    Pac aux;
    char codigoPaciente[10];

    do {
        printf("Codigo do Paciente que deseja atualizar: ");
        scanf(" %s", codigoPaciente);

        codigo = atoi(codigoPaciente);
        if (codigo == 0) {
            printf("\n  ERRO!!! \n Apenas numeros para o codigo\n");
            sleep(2);
            system("cls");
            continue;
        }
        break;
    } while (1);

    for (i = 0; i < codigoPaciente; i++) {
        if (paciente[i].codigo == codigo) {
            marcador = 1;
            break;
        }
    }

    if (!marcador)
        printf("\n Erro!!\n Paciente não cadastrado\n");

    else {
        printf("\n Entre com os daods atualizados\n");
        aux = cadastroDePaciente(aux, -1);

        if (aux.codigo > 0)
            paciente[i].codigo = aux.codigo;
        if (strlen(aux.nome) > 0)
            strcpy(paciente[i].nome, aux.nome);
        if (strlen(aux.cpf) > 0)
            strcpy(paciente[i].cpf, aux.cpf);
        if (strlen(aux.email) > 0)
            strcpy(paciente[i].email, aux.email);
        if (aux.idade > 0)
            paciente[i].idade = aux.idade;
        if (aux.peso > 0)
            paciente[i].peso = aux.peso;
        if (strlen(aux.endereco.cep) > 0)
            strcpy(paciente[i].endereco.cep, aux.endereco.cep);
        if (strlen(aux.endereco.Logradouro) > 0)
            strcpy(paciente[i].endereco.Logradouro, aux.endereco.Logradouro);
        if (strlen(aux.endereco.bairro) > 0)
            strcpy(paciente[i].endereco.bairro, aux.endereco.bairro);
        if (strlen(aux.endereco.cidade) > 0)
            strcpy(paciente[i].endereco.cidade, aux.endereco.cidade);
        if (strlen(aux.endereco.estado) > 0)
            strcpy(paciente[i].endereco.estado, aux.endereco.estado);
        if (strlen(aux.endereco.complemento) > 0)
            strcpy(paciente[i].endereco.complemento, aux.endereco.complemento);

        printf("\n  Paciente Atualizado com sucesso!\n");
    }

    sleep(2);
    system("cls");

    menu();
}

void excluirPaciente(Pac* paciente, int* contPaciente) {

    int codigo, i, marcador = 0;

    printf("Codigo do paciente que deseja excluir: ");
    scanf("%d", &codigo);

    for (i = 0; i < *contPaciente; i++) {
        if (paciente->codigo == codigo) {
            marcador = 1;
            break;
        }
    }

    if (!marcador)
        printf("\n Erro!!!\n Cliente não cadastrado\n");

    else {
        for (i; i < *contPaciente; i++)
            paciente[i] = paciente[i + 1];

        *contPaciente -= 1;
        printf("\n Cliente excluido com sucesso\n");
    }

    sleep(2);
    system("cls");

    menu();

}

// Gerenciamento de Medicos 
void GerenciamentoDeMedico(Med* medico, int* contMedico, FILE* arquivo) {

    int opcao;

    do {
        printf("\n======== Gerenciar Medicos ========\n\n");
        printf(" 1 - Cadastrar Medicos\n");
        printf(" 2 - Listar Medicos cadastrados\n");
        printf(" 3 - Buscar Medicos cadastrados\n");
        printf(" 4 - Atualizar Medicos cadastrados\n");
        printf(" 5 - Excluir Medicos cadastrados\n");
        printf(" 6 - Voltar ao menu de Gerenciamento\n");
        printf("\n Digite uma opcao para prosseguir: \n");
        scanf(" %d", &opcao);
        system("cls");

        switch (opcao) {
        case 1:
            arquivo = fopen("Cadastro_medico.txt", "a+");
            if (arquivo == NULL) {
                printf("Não foi possivel abrir o arquivo.");
                return;
            }

            printf("======Cadastro de Medicos =====\n");
            medico[*contMedico] = cadastroDeMedico(medico[*contMedico], 0);

            fprintf(arquivo, "%d;%s;%s;%s;%d;%s;%s;%s;%s;%s;%s\n", medico[*contMedico].codigo, medico[*contMedico].nome,
                medico[*contMedico].especialidade, medico[*contMedico].email, medico[*contMedico].idade, medico[*contMedico].endereco.cep,
                medico[*contMedico].endereco.Logradouro, medico[*contMedico].endereco.bairro, medico[*contMedico].endereco.cidade,
                medico[*contMedico].endereco.estado, medico[*contMedico].endereco.complemento);
            fclose(arquivo);

            *contMedico += 1;
            if (*contMedico == 10)
                medico = realloc(medico, (*contMedico + 1) * sizeof(Pac));
            break;
        case 2:
            ListarMedicos(medico, *contMedico);
            break;
        case 3:
            buscarMedico(medico, *contMedico);
            break;
        case 4:
            atualizarMedico(medico, *contMedico);
            break;
        case 5:
            excluirMedico(medico, contMedico);
            break;
        case 6:
            return menu();
            break;

        default:
            printf("Opcao invalida!");
            sleep(2);
            system("cls");
            continue;
        }
        break;
    } while (1);
}

Med cadastroDeMedico(Med medico, int identificador) {

    char codigoMedico[10];
    char idadeMedicos[10];


    do {
        printf("\nCodigo do Medico: ");
        scanf(" %s", codigoMedico);

        medico.codigo = atoi(codigoMedico);
        if (identificador == 0) {
            if (medico.codigo == 0) {
                printf("\n codigo invalido!\n Apenas numeros");
                sleep(2);
                system("cls");
                printf("\n==== Cadastro de Medicos====\n");
                continue;
            }
        }
        else {
            if (medico.codigo == 0 && strlen(codigoMedico) > 0) {
                printf("Codigo invalido\n");
                sleep(2);
                system("cls");
                continue;
            }
        }
        break;
    } while (1);
    printf("\nNome do Medico: ");
    scanf(" %[^\n]s", medico.nome);
    printf("\nEspecialidade: ");
    scanf(" %[^\n]s", medico.especialidade);
    printf("\nE-mail: ");
    scanf(" %[^\n]s", medico.email);
    printf("\nIdade: ");
    scanf(" %s", idadeMedicos);
    medico.idade = atoi(idadeMedicos);
    printf("\nEndereco:\n ");
    printf("\nCEP: ");
    scanf(" %[^\n]s", medico.endereco.cep);
    printf("\nLogradouro: ");
    scanf(" %[^\n]s", medico.endereco.Logradouro);
    printf("\nBairro: ");
    scanf(" %[^\n]s", medico.endereco.bairro);
    printf("\nCidade: ");
    scanf(" %[^\n]s", medico.endereco.cidade);
    printf("\nestado: ");
    scanf(" %[^\n]s", medico.endereco.estado);
    printf("\ncomplemento: ");
    scanf(" %[^\n]s", medico.endereco.complemento);

    if (identificador == 0) {
        printf("\n Cadastro realizado com sucesso!!!\n");
        sleep(2);
        system("cls");
        menu();
    }

    return medico;
}

void ListarMedicos(Med* medico, int contMedico) {

    int i;

    if (contMedico == 0) {
        printf("Erro! Nenhum Medico cadastrado\n");
        sleep(2);
        system("cls");
        menu();
        return;
    }

    ordenarMedicoPorOrdemAlfabetica(medico, contMedico);

    printf("Lista de Medicos cadastrados\n\n");
    for (i = 0; i < contMedico; i++)
        imprimirMedico(medico[i]);

    menu();
}

void ordenarMedicoPorOrdemAlfabetica(Med* medico, int contMedico) {

    int i, j, marcador;
    Med aux;

    for (i = 1; i < contMedico; i++) {
        aux = medico[1];
        j = i - 1;
        do {
            marcador = 0;
            if (strcmp(medico[j].nome, aux.nome) > 0) {
                medico[j + 1] = medico[j];
                j--;
                marcador = 1;
            }
            if (j < 0)
                marcador = 0;

        } while (marcador);

        medico[j + 1] = aux;
    }
}

void imprimirMedico(Med medico) {

    printf(" Codigo: %d\n", medico.codigo);
    printf(" Nome: %s\n", medico.nome);
    printf(" Especialidade: %s\n", medico.especialidade);
    printf(" E-mail: %s\n", medico.email);
    printf(" Idade: %d\n", medico.idade);
    printf(" CEP: %s\n", medico.endereco.cep);
    printf(" Logradouro: %s\n", medico.endereco.Logradouro);
    printf(" Bairro: %s\n", medico.endereco.bairro);
    printf(" Cidade: %s\n", medico.endereco.cidade);
    printf(" Estado: %s\n", medico.endereco.estado);
    printf(" Complemento: %s\n\n", medico.endereco.complemento);
}

void buscarMedico(Med* medico, int contMedico) {

    int i, marcador = 0;
    int codigoMedico;
    char nomeMedico[30];

    printf("Digite o nome ou o codigo do Medico que deseja buscar: ");
    scanf(" %[^\n]s", nomeMedico);
    printf("\n");
    codigoMedico = atoi(nomeMedico);

    for (i = 0; i < contMedico; i++) {
        if (medico[i].codigo == codigoMedico || strcmp(medico[i].nome, nomeMedico) == 0) {
            imprimirMedico(medico[i]);
            //getch();
            marcador = 1;
            break;
        }
    }
    if (!marcador) {
        printf("  ERRO!!! \n Medico nao cadastrado\n");
        sleep(2);
        system("cls");
    }

    menu();
}

void atualizarMedico(Med* medico, int contMedico) {

    int codigo, i, marcador = 0;
    Med aux;
    char codigoMedico[10];

    do {
        printf("Codigo do Medico que deseja atualizar: ");
        scanf(" %s", codigoMedico);

        codigo = atoi(codigoMedico);
        if (codigo == 0) {
            printf("\n  ERRO!!! \n Apenas numeros para o codigo\n");
            sleep(2);
            system("cls");
            continue;
        }
        break;
    } while (1);

    for (i = 0; i < codigoMedico; i++) {
        if (medico[i].codigo == codigo) {
            marcador = 1;
            break;
        }
    }

    if (!marcador)
        printf("\n Erro!!\n Medico não cadastrado\n");

    else {
        printf("\n Entre com os daods atualizados\n");
        aux = cadastroDeMedico(aux, -1);

        if (aux.codigo > 0)
            medico[i].codigo = aux.codigo;
        if (strlen(aux.nome) > 0)
            strcpy(medico[i].nome, aux.nome);
        if (strlen(aux.especialidade) > 0)
            strcpy(medico[i].especialidade, aux.especialidade);
        if (strlen(aux.email) > 0)
            strcpy(medico[i].email, aux.email);
        if (aux.idade > 0)
            medico[i].idade = aux.idade;
        if (strlen(aux.endereco.cep) > 0)
            strcpy(medico[i].endereco.cep, aux.endereco.cep);
        if (strlen(aux.endereco.Logradouro) > 0)
            strcpy(medico[i].endereco.Logradouro, aux.endereco.Logradouro);
        if (strlen(aux.endereco.bairro) > 0)
            strcpy(medico[i].endereco.bairro, aux.endereco.bairro);
        if (strlen(aux.endereco.cidade) > 0)
            strcpy(medico[i].endereco.cidade, aux.endereco.cidade);
        if (strlen(aux.endereco.estado) > 0)
            strcpy(medico[i].endereco.estado, aux.endereco.estado);
        if (strlen(aux.endereco.complemento) > 0)
            strcpy(medico[i].endereco.complemento, aux.endereco.complemento);

        printf("\n  Medico Atualizado com sucesso!\n");
    }

    sleep(2);
    system("cls");

    menu();
}

void excluirMedico(Med* medico, int* contMedico) {

    int codigo, i, marcador = 0;

    printf("Codigo do Medico que deseja excluir: ");
    scanf("%d", &codigo);

    for (i = 0; i < *contMedico; i++) {
        if (medico->codigo == codigo) {
            marcador = 1;
            break;
        }
    }

    if (!marcador)
        printf("\n Erro!!!\n Medico não cadastrado\n");

    else {
        for (i; i < *contMedico; i++)
            medico[i] = medico[i + 1];

        *contMedico -= 1;
        printf("\n Medico excluido com sucesso\n");
    }

    sleep(2);
    system("cls");

    menu();

}

// Gerenciamento de Funcionarios 
void GerenciamentoDeFuncionario(Fun* funcionario, int* contFuncionario, FILE* arquivo) {

    int opcao;

    do {
        printf("\n======== Gerenciar Funcionarios ========\n\n");
        printf(" 1 - Cadastrar Funcionarios\n");
        printf(" 2 - Listar Funcionarios cadastrados\n");
        printf(" 3 - Buscar Funcionarios cadastrados\n");
        printf(" 4 - Atualizar Funcionarios cadastrados\n");
        printf(" 5 - Excluir Funcionarios cadastrados\n");
        printf(" 6 - Voltar ao menu de Gerenciamento\n");
        printf("\n Digite uma opcao para prosseguir: \n");
        scanf(" %d", &opcao);
        system("cls");

        switch (opcao) {
        case 1:

            arquivo = fopen("Cadastro.txt", "a+");
            if (arquivo == NULL) {
                printf("Não foi possivel abrir o arquivo.");
                return;
            }

            printf("======Cadastro de Funcionarios =====\n");
            funcionario[*contFuncionario] = cadastroDeFuncionario(funcionario[*contFuncionario], 0);

            fprintf(arquivo, "%d;%s;%d;%s;%s;%s;%s;%s\n", funcionario[*contFuncionario].codigo, funcionario[*contFuncionario].nome,
                funcionario[*contFuncionario].idade, funcionario[*contFuncionario].cargo, funcionario[*contFuncionario].horario,
                funcionario[*contFuncionario].gestor, funcionario[*contFuncionario].email, funcionario[*contFuncionario].telefone);
            fclose(arquivo);

            *contFuncionario += 1;
            if (*contFuncionario == 10)
                funcionario = realloc(funcionario, (*contFuncionario + 1) * sizeof(Fun));
            break;

        case 2:
            ListarFuncionario(funcionario, *contFuncionario);
            break;
        case 3:
            buscarFuncionario(funcionario, *contFuncionario);
            break;
        case 4:
            atualizarFuncionario(funcionario, *contFuncionario);
            break;
        case 5:
            excluirFuncionario(funcionario, contFuncionario);
            break;
        case 6:
            return menu();
            break;

        default:
            printf("Opcao invalida!");
            sleep(2);
            system("cls");
            continue;

        }
        break;
    } while (1);
}

Fun cadastroDeFuncionario(Fun funcionario, int identificador) {

    char codigoFuncionario[10];
    char idadeFuncionario[10];

    do {
        printf("\nCodigo do Funcionario: ");
        scanf(" %s", codigoFuncionario);

        funcionario.codigo = atoi(codigoFuncionario);
        if (identificador == 0) {
            if (funcionario.codigo == 0) {
                printf("\n codigo invalido!\n Apenas numeros");
                sleep(2);
                system("cls");
                printf("\n==== Cadastro de Funcionarios====\n");
                continue;
            }
        }
        else {
            if (funcionario.codigo == 0 && strlen(codigoFuncionario) > 0) {
                printf("Codigo invalido\n");
                sleep(2);
                system("cls");
                continue;
            }
        }
        break;
    } while (1);
    printf("\nNome do Funcionario: ");
    scanf(" %[^\n]s", funcionario.nome);
    printf("\nIdade do Funcionario: ");
    scanf(" %s", idadeFuncionario);
    funcionario.idade = atoi(idadeFuncionario);
    printf("\nCargo: ");
    scanf(" %[^\n]s", funcionario.cargo);
    printf("\nHorario de trabalho: ");
    scanf(" %[^\n]s", funcionario.horario);
    printf("\nGestor: ");
    scanf(" %[^\n]s", funcionario.gestor);
    printf("\nE-mail: ");
    scanf(" %[^\n]s", funcionario.email);
    printf("\nTelefone: ");
    scanf(" %[^\n]s", funcionario.telefone);

    if (identificador == 0) {
        printf("\n Cadastro realizado com sucesso!!!\n");
        sleep(2);
        system("cls");
        menu();
    }
    return funcionario;
}

void ListarFuncionario(Fun* funcionario, int contFuncionario) {

    int i;

    if (contFuncionario == 0) {
        printf("Erro! Nenhum Funcionario cadastrado\n");
        sleep(2);
        system("cls");
        menu();
        return;
    }

    ordenarFuncionarioPorOrdemAlfabetica(funcionario, contFuncionario);

    printf("Lista de Funcionarios cadastrados\n\n");
    for (i = 0; i < contFuncionario; i++)
        imprimirFuncionario(funcionario[i]);

    menu();
}

void ordenarFuncionarioPorOrdemAlfabetica(Fun* funcionario, int contFuncionario) {

    int i, j, marcador;
    Fun aux;

    for (i = 1; i < contFuncionario; i++) {
        aux = funcionario[1];
        j = i - 1;
        do {
            marcador = 0;
            if (strcmp(funcionario[j].nome, aux.nome) > 0) {
                funcionario[j + 1] = funcionario[j];
                j--;
                marcador = 1;
            }
            if (j < 0)
                marcador = 0;

        } while (marcador);

        funcionario[j + 1] = aux;
    }
}

void imprimirFuncionario(Fun funcionario) {

    printf(" Codigo: %d\n", funcionario.codigo);
    printf(" Nome: %s\n", funcionario.nome);
    printf(" Idade: %d\n", funcionario.idade);
    printf(" Cargo: %s\n", funcionario.cargo);
    printf(" Horario de trabalho: %s\n", funcionario.horario);
    printf(" Gestor: %s\n", funcionario.gestor);
    printf(" E-mail: %s\n", funcionario.email);
    printf(" Telefone: %s\n", funcionario.telefone);
}

void buscarFuncionario(Fun* funcionario, int contFuncionario) {

    int i, marcador = 0;
    int codigoFuncionario;
    char nomeFuncionario[30];

    printf("Digite o nome ou o codigo do funcionario que deseja buscar: ");
    scanf(" %[^\n]s", nomeFuncionario);
    printf("\n");
    codigoFuncionario = atoi(nomeFuncionario);

    for (i = 0; i < contFuncionario; i++) {
        if (funcionario[i].codigo == codigoFuncionario || strcmp(funcionario[i].nome, nomeFuncionario) == 0) {
            imprimirFuncionario(funcionario[i]);
            marcador = 1;
            break;
        }
    }
    if (!marcador) {
        printf("  ERRO!!! \n Funcionario nao cadastrado\n");
        sleep(2);
    }

    menu();
}

void atualizarFuncionario(Fun* funcionario, int contFuncionario) {

    int codigo, i, marcador = 0;
    Fun aux;
    char codigoFuncionario[10];

    do {
        printf("Codigo do Funcionario que deseja atualizar: ");
        scanf(" %s", codigoFuncionario);

        codigo = atoi(codigoFuncionario);
        if (codigo == 0) {
            printf("\n  ERRO!!! \n Apenas numeros para o codigo\n");
            sleep(2);
            system("cls");
            continue;
        }
        break;
    } while (1);

    for (i = 0; i < codigoFuncionario; i++) {
        if (funcionario[i].codigo == codigo) {
            marcador = 1;
            break;
        }
    }

    if (!marcador)
        printf("\n Erro!!\n Funcionario não cadastrado\n");

    else {
        printf("\n Entre com os daods atualizados\n");
        aux = cadastroDeFuncionario(aux, -1);

        if (aux.codigo > 0)
            funcionario[i].codigo = aux.codigo;
        if (strlen(aux.nome) > 0)
            strcpy(funcionario[i].nome, aux.nome);
        if (aux.idade > 0)
            funcionario[i].idade = aux.idade;
        if (strlen(aux.cargo) > 0)
            strcpy(funcionario[i].cargo, aux.cargo);
        if (strlen(aux.horario) > 0)
            strcpy(funcionario[i].horario, aux.horario);
        if (strlen(aux.gestor) > 0)
            strcpy(funcionario[i].gestor, aux.gestor);
        if (strlen(aux.email) > 0)
            strcpy(funcionario[i].email, aux.email);
        if (strlen(aux.telefone) > 0)
            strcpy(funcionario[i].telefone, aux.telefone);
        printf("\n  Funcionario Atualizado com sucesso!\n");
    }
    sleep(2);
    system("cls");

    menu();
}

void excluirFuncionario(Fun* funcionario, int* contFuncionario) {

    int codigo, i, marcador = 0;

    printf("Codigo do Funcionario que deseja excluir: ");
    scanf("%d", &codigo);

    for (i = 0; i < *contFuncionario; i++) {
        if (funcionario->codigo == codigo) {
            marcador = 1;
            break;
        }
    }

    if (!marcador)
        printf("\n Erro!!!\n Funcionario não cadastrado\n");

    else {
        for (i; i < *contFuncionario; i++)
            funcionario[i] = funcionario[i + 1];

        *contFuncionario -= 1;
        printf("\n Funcionario excluido com sucesso\n");
    }
    sleep(2);
    system("cls");

    menu();

}

// Gerenciamento de Agendametos 

void GerenciamentoDeAgendamentos(Agen* agendamento, int* contAgendamento, FILE* arquivo) {
    char opcao;

    do {
        printf("\n======== Gerenciar Agendamentos ========\n\n");
        printf(" N - Novo agendamento\n");
        printf(" L - Listar agendamentos\n");
        printf(" B - Buscar agendamentos\n");
        printf(" A - Atualizar agendamentos\n");
        printf(" E - Excluir agendamentos\n");
        printf("\n Digite uma opcao para prosseguir: \n");
        scanf(" %c", &opcao);
        system("cls");

        switch (opcao) {
        case 'N':
        case 'n':
            arquivo = fopen("Cadastro_Agendamentos.txt", "a+");
            if (arquivo == NULL) {
                printf("Não foi possivel abrir o arquivo.");
                return;
            }

            printf("======Novo Agendamento =====\n");
            agendamento[*contAgendamento] = cadastroDeAgendamentos(agendamento[*contAgendamento], 0);

            fprintf(arquivo, "%d;%s;%s;%s\n", agendamento[*contAgendamento].codigo, agendamento[*contAgendamento].paciente.nome,
                agendamento[*contAgendamento].de, agendamento[*contAgendamento].ate);
            fclose(arquivo);

            *contAgendamento += 1;
            if (*contAgendamento == 10)
                agendamento = realloc(agendamento, (*contAgendamento + 1) * sizeof(Agen));
            break;
            /*
            case 'L':
            case 'l':
                ListarAgendamentos(agendamento, *contAgendamento);
                break;

            case 'B':
            case 'b':
                buscarAgendamentos(agendamento, *contAgendamento);
                break;
            case 'A':
            case 'a':
                atualizarAgendamentos(agendamento, *contAgendamento);
                break;
            case 'E':
            case 'e':
                excluirAgendamentos(agendamento, *contAgendamento);
                break;
                */
        default:
            printf("Opcao invalida!");
            sleep(2);
            system("cls");
            continue;

        }
        break;
    } while (1);
}

Agen cadastroDeAgendamentos(Agen agendamento, int identificador) {

    char codigoAgendamento[10];
    int i, marcador = 0;
    char nomePaciente[30];

    do {
        printf("\nCodigo do Agendamento: ");
        scanf(" %s", codigoAgendamento);

        agendamento.codigo = atoi(codigoAgendamento);
        if (identificador == 0) {
            if (agendamento.codigo == 0) {
                printf("\n codigo invalido!\n Apenas numeros");
                sleep(2);
                system("cls");
                printf("\n==== Novo Agendamento====\n");
                continue;
            }
        }
        else {
            if (agendamento.codigo == 0 && strlen(codigoAgendamento) > 0) {
                printf("Codigo invalido\n");
                sleep(2);
                system("cls");
                continue;
            }
        }
        break;
    } while (1);
    printf("\nDigite o Nome Paciente: ");
    scanf(" %[^\n]s", agendamento.paciente.nome);
    printf("\nInforme o periodo  DD/MM/YY HH:MM \n");
    printf("\nDe: ");
    scanf(" %[^\n]s", agendamento.de);
    printf("\nAte: ");
    scanf(" %[^\n]s", agendamento.ate);


    if (identificador == 0) {
        printf("\n Cadastro realizado com sucesso!!!\n");
        sleep(2);
        system("cls");
        menu();
    }

    return agendamento;
}