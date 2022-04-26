#include <stdio.h>
#include <stdlib.h>
#include <string.h> // elimina o '/n' durante o gets() por conta do espaço entre os inputs do usuário
#include <ctype.h>

// #include "cadastroPessoasV0.h"
//#include "opcoesMenuV0.h"

//  Variáveis Globais  
int cont =0, contd =0, verificador_menu_inicial = 1, cadastrar_novamente = 2, excluir_novamente = 2, atualizar_novamente = 2;//opcao = escolha do menu inicial
int comp, classificacao, contam = 0;
long long int matricula_exclusao;
#define TAM 5 //contador geral do vetor pessoas para o cadastro
#define TAMD 5

// variáveis de Menu
int opcao, opcao_cadastro, opcao_cadastro_aluno, opcao_cadastro_professor, opcao_cadastro_disciplina, opcao_relatorio;
int opcao_matricula, escolha_problema=0;


//********************************************
// Verificadores
//********************************************

// Verificador data de nascimento
int valida_data (int d,int m,int a){//passar parametros para função (pessoas[].dia, pessoas[].mes, pessoas[].ano)
    int mes_fev;
    // Verificar se é Ano Bisexto
    if( (a%4==0)||((a%100==0)&&(a%400==0)) ){
        mes_fev = 29;
    } else{
        mes_fev = 28;
    }

    // Definir valor máximo de dias pors meses
    if( ((m == 1) || (m ==3) || (m == 5) || (m == 7) || (m == 8) || (m == 10) || (m == 12)) && (d <= 31) ){
        return 0;

    } else if( (m==2) && (d <= mes_fev) ){
        return 0;

    } else if( ((m == 4) || (m ==6) || (m == 9) || (m ==11)) && (d <= 30) ){
        return 0;

    }
    else{
        printf("\n* Data invalida! *");
        return -1; //
    } 
}

// Verificador CPF
int valida_cpf(char cpf[12]){
    int icpf[12];  
    int i, somador=0, digito1, result1, result2, digito2, valor;    
      
    for(i=0;i<11;i++){  //Efetua a conversao de array de char para um array de int pela tabela ASCII.
        icpf[i]=cpf[i]-48;  
    }  

    //Verificação do primeiro digito.    
    for(i=0;i<9;i++){  
        somador+=icpf[i]*(10-i);  
    }    
    result1=somador%11;    
    if( (result1==0) || (result1==1) ){  
        digito1=0;  
    } else{  
        digito1 = 11-result1;  
    }  
    
    //Verificação do segundo digito.
    somador=0;
    for(i=0;i<10;i++){  
        somador+=icpf[i]*(11-i);  
    }  
    valor=(somador/11)*11;  
    result2=somador-valor;
    
    if( (result2==0) || (result2==1) ){  
        digito2=0;  
    } else{  
        digito2=11-result2;  
    }  
    
    //RESULTADOS DA VALIDACAO FINAl DO CPF.  
    if((digito1==icpf[9]) && (digito2==icpf[10])){  
        return 0;  
    } else{  
        printf("\n* CFP Inválido! *\n");
        return -1;  
    }   
}


//**********************************************
// Struct Módulo cadastro Pessoas e Disciplinas
//**********************************************

//  Struct de cadatro de Alunos e Professores
typedef struct 
{
    long long int matricula;
    char nome[50];
    char sexo; // M , F
    int dia_nascimento;
    int mes_nascimento;
    int ano_nascimento; 
    char cpf[12];
    int classificacao; // 0 - professor / 1 - aluno
    int qtd_materias_pessoa;
    int dias_relativo; 
} dados_pessoa;

dados_pessoa pessoas[TAM];//u será a variavel do vetor de pessoas[u].

//  Struct de cadatro das Disciplinas
typedef struct 
{
    char nome_disciplina[50];
    char codigo_disciplina[7];
    int semestre;
    long long int matricula_professor;
    char nome_professor[50];
    long long int alunos_matriculados[60];
    int qtd_alunos_matriculados;
} dados_disciplina;

dados_disciplina disciplina[TAM];

//**********************************************
// Funções de Cadastro de Pessoas e Disciplinas
//**********************************************

//  função de cadatro de Disciplinas
int cadastro_disciplina(int cadastrar_novamente){
    getchar();  // absorve o '\n' que o scanf não leu
    printf("\nNome da Disciplina: \n>>> ");    
    fflush(stdin);
    fgets(disciplina[contd].nome_disciplina, 50, stdin);
    for(int i=0; disciplina[contd].nome_disciplina[i]; i++) if(disciplina[contd].nome_disciplina[i]=='\n') disciplina[contd].nome_disciplina[i]=0;
    printf("Código da Disciplina (6 dígitos): \n>>> ");
    scanf("%s", &disciplina[contd].codigo_disciplina);
    // disciplina[contd].codigo_disciplina = toupper(disciplina[contd].codigo_disciplina); teste
    
    do
    {
        printf("Semestre da Disciplina: \n>>> ");
        scanf("%i", &disciplina[contd].semestre);
        if ( !((disciplina[contd].semestre > 0) || (disciplina[contd].semestre <= 10)) ){
            printf("\n***** Semestre Inválido! *****\n");
        }
    } while ( !((disciplina[contd].semestre > 0) || (disciplina[contd].semestre <= 10)) );
    
    int veri_matri_prof = 0;
    do
    {
        printf("Digite o Numero da Matricula do Professor (11 Digitos):\n>>> ");
        scanf("%lld", &disciplina[contd].matricula_professor);
        getchar();  // absorve o '\n' que o scanf não leu
        for (int i=0; i < cont; i++){
            if (disciplina[contd].matricula_professor == pessoas[i].matricula){
                veri_matri_prof ++;
            }
        }
        if (veri_matri_prof == 0){
                printf("\n***** Não Existe Professor com a Matricula Informada! *****\n");
            }
    } while (veri_matri_prof == 0);
    for (int i = 0; i <cont; i++){
        if(disciplina[contd].matricula_professor == pessoas[i].matricula){
            strcpy(disciplina[contd].nome_professor, pessoas[i].nome);

        }
    }
    printf("Nome da Disciplina: %s, Código da Disciplina: %s, Matrícula Professor: %lld, Nome Professor: %s\n", disciplina[contd].nome_disciplina, disciplina[contd].codigo_disciplina, disciplina[contd].matricula_professor, disciplina[contd].nome_professor);
    printf("\n*****     Cadastro realizado com sucesso!     *****\n");
    contd++;
    do
    {
        printf("\nDeseja cadastrar outra Disciplina?\n  (1 - Sim / 0 - Não)\n>>> ");
        scanf("%d", &cadastrar_novamente);
        if (!(cadastrar_novamente == 1 || cadastrar_novamente == 0)){
            printf("\n***** Opcao Invalida! ****\n");
        }
    } while (!(cadastrar_novamente == 1 || cadastrar_novamente == 0));
    return cadastrar_novamente;
}

//  função de cadatro de Alunos e Professores
int cadastro_pessoa (int opcao_cadastro, int cadastrar_novamente) { 
    //char tipo_pessoa[15];
    char *tipo_pessoa;        
    if (opcao_cadastro == 1){
            tipo_pessoa = "Aluno";
            classificacao = 1;
        }
    else if (opcao_cadastro == 2){
            tipo_pessoa = "Professor";
            classificacao = 0;
        }

    printf("\nDigite o Numero da Matricula (11 Digitos):\n>>> ");
    scanf("%lld", &pessoas[cont].matricula);
    getchar();  // absorve o '\n' que o scanf não leu
    printf("\nDigite o Nome do %s:\n>>> ", tipo_pessoa); 
    fflush(stdin);
    fgets(pessoas[cont].nome, 50, stdin);
    for(int i=0; pessoas[cont].nome[i]; i++) if(pessoas[cont].nome[i]=='\n') pessoas[cont].nome[i]=0;

    do
    {
        printf("\nDigite o sexo (F / M):\n>>> ");    
        scanf("%c", &pessoas[cont].sexo);
        pessoas[cont].sexo = toupper(pessoas[cont].sexo);
        if (!(pessoas[cont].sexo == 'F' || pessoas[cont].sexo == 'M')){
            printf("\n***** Opcao Invalida! ****\n");
            getchar();
        }
    } while (!(pessoas[cont].sexo == 'F' || pessoas[cont].sexo == 'M'));

    int check_data = -1;
    do
    {
        printf("\nDigite a Data de Nascimento (dd/mm/aaaa)\n>>> ");
        scanf("%d/%d/%d", &pessoas[cont].dia_nascimento, &pessoas[cont].mes_nascimento, &pessoas[cont].ano_nascimento);
        check_data = valida_data(pessoas[cont].dia_nascimento, pessoas[cont].mes_nascimento, pessoas[cont].ano_nascimento);//validaçao da data
    } while (check_data==-1);

<<<<<<< HEAD:ProjetoEscolaV0/projEscolaGeralV3.c
    pessoas[cont].dias_relativo = ((pessoas[cont].ano_nascimento * 365) + (pessoas[cont].mes_nascimento * 30) - pessoas[cont].dia_nascimento);
=======
    pessoas[cont].dias_relativo = ((ano_nascimento * 365)+(mes_nascimento * 30)-dias_nascimento);
>>>>>>> origin/main:ProjetoEscolaV0/projEscolaGeralV320220328

    int check_cpf = -1;
    do
    {
        getchar();
        printf("\nDigite o CPF (sem pontos ou tracos):\n>>> ");
        fflush(stdin);
        fgets(pessoas[cont].cpf, 12, stdin);
        for(int i=0; pessoas[cont].cpf[i]; i++) if(pessoas[cont].cpf[i]=='\n') pessoas[cont].cpf[i]=0;
        check_cpf = valida_cpf(pessoas[cont].cpf);

    } while (check_cpf == -1);
    pessoas[cont].classificacao = classificacao;

        //dados cadastrados
    printf("Nome: %s, Matrícula: %lld, Sexo: %c, data de nascimento: %d/%d/%d, CPF: %s\n", pessoas[cont].nome, pessoas[cont].matricula, pessoas[cont].sexo, pessoas[cont].dia_nascimento, pessoas[cont].mes_nascimento, pessoas[cont].ano_nascimento, pessoas[cont].cpf);
    printf("\n*****     Cadastro realizado com sucesso!     *****\n");
    cont++;

    do
    {
        printf("\nDeseja cadastrar outro %s?\n  (1 - Sim / 0 - Não)\n>>> ", tipo_pessoa);
        scanf("%d", &cadastrar_novamente);
        if (!(cadastrar_novamente == 1 || cadastrar_novamente == 0)){
            printf("\n***** Opcao Invalida! ****\n");
        }
    } while (!(cadastrar_novamente == 1 || cadastrar_novamente == 0));
    return cadastrar_novamente;
}

// função Excluir Alunos e Professores
int excluir_pessoa(int opcao_cadastro, int excluir_novamente){ //função de excluir cadastro
    char *tipo_pessoa;
    int u = 0, classificacao;
   
    if (opcao_cadastro == 1){
        opcao_relatorio = 1;
        tipo_pessoa = "Aluno";
        classificacao = 1;

    }
    else if (opcao_cadastro == 2){
        opcao_relatorio = 2;
        tipo_pessoa = "Professor";
        classificacao = 0;
        
    }
    listagem_pessoas(opcao_relatorio);

    printf("\n********************************************************************\n");
    printf("Digite a matricula do %S que deseja excluir.\n>>> ", tipo_pessoa);
    scanf("%lld", &matricula_exclusao);

    int mat = 0; // contador que identifica quantas vezes o else if foi acessado para saber se a matricula existe ou não
    for(u ; u <= cont; u++){
        if( (pessoas[u].classificacao ==  classificacao) && (matricula_exclusao == pessoas[u].matricula) ){
            pessoas[u].matricula *= (-1);
            u = cont;
        }else if( (pessoas[u].classificacao ==  classificacao) && (matricula_exclusao != pessoas[u].matricula) ){
            mat++;
        }
    }
    if ((mat == cont)){
        printf("\n***** Matrícula não Encontrada! *****\n");

    } else if ( (u == cont) && (mat < cont)){
        printf("\n***** Matrícula Excluida! *****\n");
    }

    do
    {
        printf("\nDeseja excluir outra matrícula de %s?\n  (1 - Sim / 0 - Não)\n>>> ", tipo_pessoa);
        scanf("%d", &excluir_novamente);
        if (!(excluir_novamente == 1 || excluir_novamente == 0)){
            printf("\n***** Opcao Invalida! ****\n");
        }
    } while (!(excluir_novamente == 1 || excluir_novamente == 0));
    return excluir_novamente;
}

// função Alterar Alunos e Professores
int atualizar_pessoa(opcao_cadastro, atualizar_novamente){ ///função de atualizar cadastro
    int matricula_alterar;
    int u = 0, verificador_alterar;
    int campo_alterar;
    char *tipo_pessoa; 

    if (opcao_cadastro == 1){
        tipo_pessoa = "Aluno";
        classificacao = 1;
    }
    else if (opcao_cadastro == 2){
        tipo_pessoa = "Professor";
        classificacao = 0;
    }
    
    do
    {
        printf("Digite A matricula do %s que voce deseja alterar:\n>>> ", tipo_pessoa);
        scanf("%d",& matricula_alterar);
        do
        {        
            if(matricula_alterar == pessoas[u].matricula){      
                if(pessoas[u].classificacao == classificacao){
                    verificador_alterar = 1;
                } else{
                    printf("Matrícula Inválida! Não pertence a um %s\n", tipo_pessoa);
                    verificador_alterar = 2;
                }       
            }u++;
        } while ( (u <= cont) && (verificador_alterar == 0) );
    } while (verificador_alterar == 2); 

    u--;
    int check_data = -1;
    int check_cpf = -1;
    if (verificador_alterar == 1){
        do
        {
            do
            {
                printf("0 - Voltar\n1 - Matricula: %d\n2 - Nome: %s\n3 - Sexo: %c\n4 - Data de Nascimento: %d/%d/%d\n5 - CPF: %s\n", pessoas[u].matricula, pessoas[u].nome, pessoas[u].sexo, pessoas[u].dia_nascimento, pessoas[u].mes_nascimento, pessoas[u].ano_nascimento, pessoas[u].cpf);
                printf("Digite o campo que deseja alterar:\n>>> ");
                scanf("%d", &campo_alterar);
                if ( (campo_alterar < 0) || (campo_alterar > 6) ){
                    printf("\n***** Opcao Invalida! ****\n");
                }
            } while ( (campo_alterar < 0) || (campo_alterar > 6) );

            switch(campo_alterar){
            case 0:
                menu_cadastro();
            case 1: // matricula
                printf("\nDigite a nova matricula:\n>>> ");
                scanf("%d",&pessoas[u].matricula);
                printf("\nMatricula Alterada!\n");
                break;
            case 2: // nome
                getchar();
                printf("Digite o novo nome:\n>>> ");                
                fgets(pessoas[u].nome, 50, stdin);
                size_t len = strlen(pessoas[u].nome)-1;
                if (pessoas[u].nome[len] == '\n'){
                    pessoas[u].nome[len] = '\0';
                }
                printf("\nNome Alterado!\n");
                break;
            case 3: // sexo
                printf("\nDigite o sexo (M / F):\n>>> ");
                scanf("%c", pessoas[u].sexo);
                printf("\nSexo Alterado!\n");
                break;
            case 4: // data
                do
                {
                    printf("\nDigite a nova Data de Nascimento (dd/mm/aaaa)\n>>> ");
                    scanf("%d/%d/%d", &pessoas[u].dia_nascimento, &pessoas[u].mes_nascimento, &pessoas[u].ano_nascimento);
                    check_data = valida_data(pessoas[u].dia_nascimento, pessoas[u].mes_nascimento, pessoas[u].ano_nascimento);//validaçao da data
                } while (check_data==-1);
<<<<<<< HEAD:ProjetoEscolaV0/projEscolaGeralV3.c
                pessoas[u].dias_relativo = ((pessoas[u].ano_nascimento * 365) + (pessoas[u].mes_nascimento * 30) - pessoas[u].dia_nascimento);
=======
                pessoas[u]dias_relativo = ((ano_nascimento * 365)+(mes_nascimento * 30)-dias_nascimento);
>>>>>>> origin/main:ProjetoEscolaV0/projEscolaGeralV320220328
                break;
            case 5: //cpf
                do
                {
                    getchar();
                    printf("\nDigite o novo CPF (sem pontos ou tracos):\n>>> ");
                    fflush(stdin);
                    fgets(pessoas[u].cpf, 12, stdin);
                    for(int i=0; pessoas[u].cpf[i]; i++) if(pessoas[u].cpf[i]=='\n') pessoas[u].cpf[i]=0;
                    check_cpf = valida_cpf(pessoas[u].cpf);
                } while (check_cpf == -1);
                break;
            }

            do
            {
                printf("\nDeseja atualizar outro campo de %s?\n  (1 - Sim / 0 - Não)\n>>> ", pessoas[u].nome);
                scanf("%d", &verificador_alterar);
                if (!(verificador_alterar == 1 || verificador_alterar == 0)){
                    printf("\n***** Opcao Invalida! ****\n");
                }
            } while (!(verificador_alterar == 1 || verificador_alterar == 0));            
            
        } while (verificador_alterar == 1);
    }  

    do
    {
        printf("\nDeseja atualizar outro cadastro de %s?\n  (1 - Sim / 0 - Não)\n>>> ", tipo_pessoa);
        scanf("%d", &atualizar_novamente);
        if (!(atualizar_novamente == 1 || atualizar_novamente == 0)){
            printf("\n***** Opcao Invalida! ****\n");
        }
    } while (!(atualizar_novamente == 1 || atualizar_novamente == 0));
    return atualizar_novamente, opcao_cadastro;
}

// função para matricular um aluno em uma determinada disciplina
int matricula(){
    char codigo[7];
    long long int comparador;
    int seletor_disciplina = -1;
    int seletor_matricula = -2;
    int repetidor = 0;
    int opcao;
    int u = 0;
    
    do{
        printf("Digite o Código da Disciplina:\n>>> ");
        scanf("%s", &codigo);

        for (u=0; u<contd; u++){
            comparador = strcmp(codigo, disciplina[u].codigo_disciplina); 
            if(comparador == 0){
                seletor_disciplina = u;
                u = contd;
                repetidor ++;
            }
        }repetidor++;
    }while(repetidor == 0);
    if(seletor_disciplina == -1){
        printf("\n* Disciplina não encontrada! *\n");
        do
        {
            printf("Deseja voltar ao Menu anterior ou tentar novamente?\n  (0 - Voltar / 1 - Tentar)\n>>> ");
            scanf("%d", &escolha_problema);
            if (escolha_problema==0){
                menu_matricular();
            } else if (escolha_problema==1){
                matricula();
            }
        } while (!(escolha_problema==0) || (escolha_problema==1));
    }
    repetidor = 0;
    do{
        printf("Disciplina %s\n", disciplina[seletor_disciplina].nome_disciplina);
        printf("Digite a Matricula do aluno que você deseja Matricular na Disciplina:\n>>> ");
        scanf("%lld", &comparador);
        for(u=0; u<cont; u++){
            if (comparador == pessoas[u].matricula){
                seletor_matricula = u;
                u = cont;
                repetidor ++;
            }        
        }
        repetidor ++;
    }while(repetidor == 0);
    if(seletor_matricula == -2){
        printf("\n* Aluno não encontrado! *\n");
        matricula();
    }
    repetidor = 0;
    do{
        printf("Voce Deseja Matricular o aluno %s na Disicplina %s?\n  (1 - Sim / 0 - Não)\n>>> ", pessoas[seletor_matricula].nome, disciplina[seletor_disciplina].nome_disciplina);
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                disciplina[seletor_disciplina].alunos_matriculados[contam] = pessoas[seletor_matricula].matricula;
                pessoas[seletor_matricula].qtd_materias_pessoa ++;
                disciplina[seletor_disciplina].qtd_alunos_matriculados ++;
                contam++;
                repetidor ++;
            case 2:
                menu_matricular();
            default:
                printf("\n***** Opcao Invalida! ****\n");
        }
    } while(repetidor == 0);
}

// função para excluir um aluno de uma disciplina
int excluir_matricula(void){
    char codigo[7];
    int comparador;
    int seletor_disciplina = -1;
    long long int seletor_matricula = -2;
    int repetidor = 0;
    int opcao;
    int u = 0;
    
    do{
        printf("Digite o Código da Disciplina:\n>>> ");
        scanf("%s", &codigo);
        for (u=0; u<contd; u++){
            comparador = strcmp(codigo, disciplina[u].codigo_disciplina);
            if(comparador == 0){
                seletor_disciplina = u;
                u = contd;
                repetidor ++;
            }
        }repetidor++;
    }while(repetidor == 0);
    if(seletor_disciplina == -1){
        printf("\n* Disciplina não encontrada! *\n");
        do
        {
            printf("Deseja voltar ao Menu anterior ou tentar novamente?\n  (0 - Voltar / 1 - Tentar)\n>>> ");
            scanf("%d", &escolha_problema);
            if (escolha_problema==0){
                menu_matricular();
            } else if (escolha_problema==1){
                excluir_matricula();
            }
        } while (!(escolha_problema==0) || (escolha_problema==1));        
    }
    repetidor = 0;
    do{
        printf("Disciplina %s\n", disciplina[seletor_disciplina].nome_disciplina);
        printf("Digite a Matricula do aluno que você deseja excluir da disciplina:\n>>> ");
        scanf("%lld", &comparador);
        for(u=0; u<contam; u++){
            if ((comparador == disciplina[seletor_disciplina].alunos_matriculados[u])&&(disciplina[seletor_disciplina].alunos_matriculados[u]>0)){
                seletor_matricula = u;
                u = contam;
                repetidor ++;
            }        
        }
        repetidor ++;
    }while(repetidor == 0);
    if(seletor_matricula == -2){
        printf("Aluno não encontrado!");
        matricula();
    }
    repetidor = 0;
    do{
        printf("Voce Deseja Excluir o aluno %s na Disicplina %s?\n  (1 - Sim / 0 - Não)\n>>> ", pessoas[seletor_matricula].nome, disciplina[seletor_disciplina].nome_disciplina);
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                disciplina[seletor_disciplina].alunos_matriculados[seletor_matricula] = -1; //transforma a matricula do aluno matriculado apenas no vetor da materia em - 1
                pessoas[seletor_matricula].qtd_materias_pessoa --;
                disciplina[seletor_disciplina].qtd_alunos_matriculados --;
                repetidor ++;
            case 2:
                menu_matricular();
            default:
                printf("\n***** Opcao Invalida! ****\n");
        }
    } while(repetidor == 0);
}


//**********************************************
// Módulo de Relatórios
//**********************************************

<<<<<<< HEAD:ProjetoEscolaV0/projEscolaGeralV3.c
// 1 - Listar de Alunos
=======
>>>>>>> origin/main:ProjetoEscolaV0/projEscolaGeralV320220328
int listagem_pessoas(int opcao_relatorio){
    char *tipo_pessoa;
    if (opcao_relatorio == 1){
        opcao_cadastro = 1;
        tipo_pessoa = "Aluno";

<<<<<<< HEAD:ProjetoEscolaV0/projEscolaGeralV3.c
=======

>>>>>>> origin/main:ProjetoEscolaV0/projEscolaGeralV320220328
    } else if(opcao_relatorio == 2){
        opcao_cadastro = 0;
        tipo_pessoa = "Professor";

<<<<<<< HEAD:ProjetoEscolaV0/projEscolaGeralV3.c
=======
    }

    printf("\n*****************************************\n");
    printf(  "          Lista de %s               ", tipo_pessoa);
    printf("\n*****************************************\n"); 

    int i = 0, tam;
    tam = cont;
    while (i < tam){
        if( (pessoas[i].matricula > 0) && (pessoas[i].classificacao == opcao_cadastro) ){
            printf("Aluno: %s, Matrícula: %lld\n", pessoas[i].nome, pessoas[i].matricula);     
        }
        i++;
    }
}


/*
//**********************************************
int lista_alunos(void){
    printf("\n****************************\n");
    printf(  "*     Lista de Alunos:     *");
    printf("\n****************************\n");
    int u = 0, tam;
    tam = cont;
    while (u < tam){
        if( (pessoas[u].matricula > 0) && (pessoas[u].classificacao == 1) ){
            printf("Aluno: %s, Matrícula: %lld\n",pessoas[u].nome, pessoas[u].matricula);     
        }
        u++;
>>>>>>> origin/main:ProjetoEscolaV0/projEscolaGeralV320220328
    }

    printf("\n*****************************************\n");
    printf(  "          Lista de %s               ", tipo_pessoa);
    printf("\n*****************************************\n"); 

    int i = 0;
    while (i < cont){
        if( (pessoas[i].matricula > 0) && (pessoas[i].classificacao == opcao_cadastro) ){
            printf("%s: %s, Matrícula: %lld\n", tipo_pessoa, pessoas[i].nome, pessoas[i].matricula);     
        }
        i++;
    }
}


<<<<<<< HEAD:ProjetoEscolaV0/projEscolaGeralV3.c
// 2 - Listar de Professores
    // Feito no item 01
=======
*/
>>>>>>> origin/main:ProjetoEscolaV0/projEscolaGeralV320220328

// 3 - Listar Disciplinas
int lista_disciplinas(void){
    printf("\n****************************\n");
    printf(  "*     Lista Disciplinas    *");
    printf("\n****************************\n");

    for (int d = 0; d < contd; d++){
        printf("Nome: %s, Codigo: %s, Semestre: %d, Matrícula Professor: %lld, Nome Professor: %s\n",disciplina[d].nome_disciplina, disciplina[d].codigo_disciplina, disciplina[d].semestre, disciplina[d].matricula_professor, disciplina[d].nome_professor);
    }
}

// 4 - Listar Disciplinas Específica mostrando seus dados e os alunos matriculados
int buscar_disciplina(){
    printf("\n**********************************\n");
    printf(  "*  Menu de Busca de Disciplinas  *");
    printf("\n**********************************\n");
    char codigo_disciplina[7];
    int verificador;
    do
    {
        verificador = 0;
        printf("\nInforme o Código da Disciplina (6 digitos):\n>>> ");
        scanf("%s", &codigo_disciplina);
        for (int d = 0; d < contd; d++){
            if (strcmp(disciplina[d].codigo_disciplina, codigo_disciplina)==0){
                printf("Matéria: %s, Codigo: %s, Semestre: %d, Matrícula Professor: %lld, Nome Professor: %s\n",disciplina[d].nome_disciplina, disciplina[d].codigo_disciplina, disciplina[d].semestre, disciplina[d].matricula_professor, disciplina[d].nome_professor);
                for(int i = 0; i < cont; i++){
                    for( int k = 0; k < cont; k++){
                        if(disciplina[d].alunos_matriculados[i] == pessoas[k].matricula){
                            printf("\nAluno : %s  Matricula: %lld", pessoas[k].nome, pessoas[k].matricula);
                        }
                    }
                }
                d == contd;
                verificador = 0;
            } else{
                verificador ++;
            }
        }
        if (verificador == contd){
            printf("\nCódigo %d incorreto!", codigo_disciplina);
            do
            {
                printf("\nDeseja tentar novamente? (1 - Sim / 0 - Não)");
                scanf("%d", &verificador);
                if (verificador > 1){
                    printf("\n***** Opcao Invalida! ****\n");
                }                
            } while (verificador > 1);            
            
            if (verificador == 1){
                verificador = 1;

            } else if(verificador == 0){
                verificador = 0;
            }
        }
    } while (verificador != 0);    
}

// 5 - Listar Alunos por Sexo (M/F)
int pessoas_porsexo(int opcao_relatorio){
  char opsexo;
  char *tipo_pessoa;
    if (opcao_relatorio == 5){
        opcao_cadastro = 1;
        tipo_pessoa = "Aluno";

    } else if(opcao_relatorio == 8){
        opcao_cadastro = 0;
        tipo_pessoa = "Professor";

    }
    
  printf("\n***********************************\n");
  printf("  * Listagem por sexo - %s    *", tipo_pessoa);
  printf("\n***********************************\n");

  do {
        getchar();
        printf("Informe a opcao de sexo para busca (M/F): \n>>> ");
        scanf("%c", &opsexo);
        opsexo = toupper(opsexo);
        if (!(opsexo == 'F' || opsexo == 'M')){
            printf("\n***** Opcao Invalida! ****\n");
        }
    } while (!(opsexo == 'F' || opsexo == 'M'));

  for (int u=0; u < cont; u++){
    if ( (pessoas[u].sexo == opsexo) && ( pessoas[u].classificacao == opcao_cadastro) ){
      printf("\nNome: %s, Matricula: %lld", pessoas[u].nome, pessoas[u].matricula);
    }  
  }
}

// 6 - Listar Alunos Ordenados por Nome
int ordenar_pessoas_nome(int opcao_relatorio){
    typedef struct{
        char ordenador_pessoas[50];
    }ordena;
    ordena ordenar[cont];
    char auxiliar[50];
    char *tipo_pessoa;        
    if (opcao_relatorio == 6){
        classificacao = 1;
        tipo_pessoa = "Aluno";

    } else if(opcao_relatorio == 9){
        classificacao = 0;
        tipo_pessoa = "Professor";

    }
    printf("\n******************************************************\n");
    printf(  "Lista %s Ordenado por Nome    ", tipo_pessoa);
    printf("\n******************************************************\n");

    for(int u = 0; u < cont; u++){ 
        if( (pessoas[u].classificacao == classificacao) && (pessoas[u].matricula > 0) ){
            strcpy(ordenar[u].ordenador_pessoas, pessoas[u].nome);

        }        
    }
    for(int k = 0; k< cont-1; k++) {
        for(int i = 0; i < cont-k-1; i++) {
            if(strcmp(ordenar[i].ordenador_pessoas, ordenar[i+1].ordenador_pessoas) > 0){
                strcpy(auxiliar, ordenar[i].ordenador_pessoas);
                strcpy(ordenar[i].ordenador_pessoas,ordenar[i+1].ordenador_pessoas);
                strcpy(ordenar[i+1].ordenador_pessoas,auxiliar);

            }
        }
    }

    for(int i = 0; i < cont; i++){
        for(int k = 0; k < cont; k++){
            if(strcmp(ordenar[i].ordenador_pessoas, pessoas[k].nome)==0){
                printf("\nAluno: %s  Matricula: %lld", pessoas[k].nome, pessoas[k].matricula);
            }
        }
    }
}

// 7 - Listar Alunos Ordenados por Data de Nascimento
 int lista_data_nasc(int opcao_relatorio){
    printf("\n*****************************************\n");
    printf(  "* Menu Ordenação por Data de Nascimento *");
    printf("\n*****************************************\n");    

    if (opcao_relatorio == 7){
        opcao_cadastro = 1;

    } else if(opcao_relatorio == 10){
        opcao_cadastro = 0;

    }

    typedef struct{
        int matref;
        int dias_de_vidaref;
    }referencia;
    typedef struct{
        int mattemp;
        int dias_de_vidatemp;
    }temporario;

    referencia ref[cont];
    temporario temp;

    for(int i = 0; i<cont; i++){
        ref[i].matref = pessoas[i].matricula;
        ref[i].dias_de_vidaref = pessoas[i].dias_relativo;
    }
    for(int k = 0; k< cont-1; k++) {
        // (n-k-1) is for ignoring comparisons of elements which have already been compared in earlier iterations
        for(int i = 0; i < cont-k-1; i++) {
            if(ref[i].dias_de_vidaref > ref[i+1].dias_de_vidaref ) {
                temp.mattemp = ref[i].matref;
                temp.dias_de_vidatemp = ref[i].dias_de_vidaref;
                ref[i] = ref[i+1];
                ref[i + 1].matref = temp.mattemp;
                ref[i + 1].dias_de_vidaref = temp.dias_de_vidatemp;
            }
        }
    }

    int d = 1;
    for(int i = 0; i<cont; i++){
        for(int k = 0; k<cont; k++){
            if( (ref[i].matref == pessoas[k].matricula) && (pessoas[k].classificacao == opcao_cadastro)){
                printf("\n%d: %s - %d/%d/%d", (d), pessoas[k].nome, pessoas[k].dia_nascimento, pessoas[k].mes_nascimento, pessoas[k].ano_nascimento);
                d++;
            }
        }
    }
}

// 8 - Listar Professores por Sexo (M/F)
        // feito no item 5

// 9 - Listar Professores Ordenados por Nome
        // >>> feito no item 6

// 10 - Listar Professores Ordenados por Data de Nascimento
        // feito no item 7

// 11 - Aniversariantes do Mês
int lista_aniversariantes(){
    int mes;

    printf("\n********************************\n");
    printf("  * Busca Aniversariantes do mês *");
    printf("\n********************************\n");

    do
    {
    printf("Informe o mês desejado para a busca (1 a 12):\n>>> ");
    scanf("%d", &mes);
    if ( !(mes > 0 || mes <= 12) ){
        printf("\n***** Opcao Invalida! ****\n");
    }
    } while (!(mes > 0 || mes <= 12));

    switch (mes){
    case 1:
        impressao_aniversario(mes);    
        break;

    case 2:
        impressao_aniversario(mes);    
        break;

    case 3:
        impressao_aniversario(mes);    
        break;

    case 4:
        impressao_aniversario(mes);    
        break;

    case 5:
        impressao_aniversario(mes);    
        break;

    case 6:
        impressao_aniversario(mes);    
        break;

    case 7:
        impressao_aniversario(mes);    
        break;

    case 8:
        impressao_aniversario(mes);    
        break;

    case 9:
        impressao_aniversario(mes);    
        break;

    case 10:
        impressao_aniversario(mes);    
        break;

    case 11:
        impressao_aniversario(mes);    
        break;

    case 12:
        impressao_aniversario(mes);    
        break;

    }
}

int impressao_aniversario(int mes){
    int verificador = 0;
    printf("\n****************************\n");
    printf(  "*  Aniversariantes do mês  *");
    printf("\n****************************\n");
    for (int u = 0; u < cont; u++){
        if (pessoas[u].mes_nascimento == mes){
        printf("Nome: %s, Matricula: %lld, Data de Aniversário: %d/%d\n", pessoas[u].nome, pessoas[u].matricula, pessoas[u].dia_nascimento, pessoas[u].mes_nascimento);
        verificador ++;
        }  
    }
    if (verificador == (cont - 1)){
        printf("\n* Não foram econtrados aniversariantes! *\n");
    }
}

// 12 - Buscar (Professor / Aluno) por Parte do Nome
int buscar_pessoa(void){
    #define LENGTH 50
    //char tipo_pessoa[15];
    char *tipo_pessoa;
    int buscalen, len, u = 0;
    char busca[50];
    char *pont_busca;
    printf("\n****************************\n");
    printf(  "*       Menu de Busca      *");
    printf("\n****************************\n");
    printf("Digite pelo menos 3 letras do nome da pessoa para busca-la:\n>>> ");
    getchar();
    fgets(busca, 50, stdin);
    do
    {
        memset(busca, 0, LENGTH);
        printf("Digite pelo menos 3 letras do nome da pessoa para busca-la:\n>>> ");
        getchar();
        fgets(busca, 50, stdin);
    } while (strlen(busca) < 2);

    for(int i=0; busca[i]; i++) if(busca[i]=='\n') busca[i]=0;
    do{        	
        pont_busca = strstr(pessoas[u].nome, busca);

        if( pont_busca != NULL ){
            if( pessoas[u].classificacao == 1){
                //char tipo_pessoa[] = "Aluno";
                tipo_pessoa = "Aluno";
            } else if(pessoas[u].classificacao == 0){
                //char tipo_pessoa[] = "Professor";
                tipo_pessoa = "Professor";
            }
            printf("Nome do %s: %s, Matricula: %lld\n", tipo_pessoa, pessoas[u].nome, pessoas[u].matricula);
        }
        u++;
    } while (u <= cont);
}

// 13 - Lista de Alunos Matriculados em Menos de 3 Disciplinas
int menos_de_3(){
    printf("\n*************************************\n");
    printf(  "* Alunos com Menos de 3 Disciplinas *");
    printf("\n*************************************\n"); 
    for (int i = 0; i < cont; i++){
        if(pessoas[i].classificacao == 1){
            if(pessoas[i].qtd_materias_pessoa < 3){
                printf("\nAluno: %s Matricula:%lld", pessoas[i].nome, pessoas[i].matricula);
            }
        }
    }
}

// 14 - Listar Disciplinas, com nome do professor, que Extrapolam 40 Vagas
int disciplinas_prof_mais40(){
    printf("\n************************************\n");
    printf(  "*   Disciplina mais de 40 alunos   *");
    printf("\n************************************\n"); 

    int verificador = 0;
    for(int i = 0; i < contd; i++){
        if(disciplina[i].qtd_alunos_matriculados > 40){ // TESTE modificar o tamanho de 2 para 40
            printf("\nDisciplina: %s, Código: %s, Nome Professor: %s", disciplina[i].nome_disciplina, disciplina[i].codigo_disciplina, disciplina[i].nome_professor);
            verificador ++;
        } else if(verificador == (contd - 1)){
            printf("\n* Não há Disciplinas com mais de 40 Alunos Matriculados *\n");
        }
    }
}

//**********************************************
// Módulo de Menus
//**********************************************

//   Menu Inicial
int menu_inicial(){
    printf("\n****************************\n");
    printf(  "*       Menu inicial       *");
    printf("\n****************************\n");
    printf("Digite a opcao desejada.\n");
    printf("0 - Encerrar Programa.\n");
    printf("1 - Menu Cadastro.\n");
    printf("2 - Menu Relatórios.\n>>> ");
    scanf("%d", &opcao);

    switch (opcao){
    case 0: // Encerrar Programa
        printf("\n*       Programa Encerrado       *\n");
        return 0;

    case 1: //Menu Cadastro        
        menu_cadastro();
    
    case 2: // Menu Relatórios
        menu_relatorio();
    
    default:
        printf("\n***** Opcao Invalida! ****\n");
        break;
    }
}

//   Menu de Cadastros
int menu_cadastro(){    
    printf("\n****************************\n");
    printf(  "*      Menu Cadastro       *");
    printf("\n****************************\n");
    printf("Digite a opcao desejada.\n");
    printf("0 - Retornar ao Menu Anterior.\n");
    printf("1 - Cadastro de Aluno.\n");
    printf("2 - Cadastro de Professor.\n");
    printf("3 - Cadastro de Disciplina.\n");
    printf("4 - Matricula de Aluno.\n>>> ");
    scanf("%d", &opcao_cadastro);

    switch (opcao_cadastro){
    case 0: //Retornar ao Menu Anterior.
        menu_inicial();

    case 1: //Cadastro de Aluno.     
        menu_cadastro_aluno(opcao_cadastro);    

    case 2: //Cadastro de Professor.
        menu_cadastro_professor(opcao_cadastro);        

    case 3: //Cadastro de Disciplina.
        menu_cadastro_disciplina();

    case 4: //Matricular Aluno
        menu_matricular();

    default:
        printf("\n* Opcao Inválida! *\n");
        menu_cadastro();
    }
}

// Menu cadastro Aluno
int menu_cadastro_aluno(){
    printf("\n****************************\n");
    printf(  "*   Menu Cadastro Aluno    *");
    printf("\n****************************\n");
    printf("Digite a opcao desejada.\n");
    printf("0 - Retornar ao Menu Anterior.\n");
    printf("1 - Cadastrar Novo Aluno.\n");
    printf("2 - Excluir Aluno.\n");
    printf("3 - Alterar Aluno.\n>>> ");
    scanf("%d", &opcao_cadastro_aluno);

    switch (opcao_cadastro_aluno){
    case 0: // Retornar ao Menu Anterior
        menu_cadastro();    

    case 1: // Cadastrar Novo Aluno         
        do
        {   
            cadastrar_novamente = cadastro_pessoa(opcao_cadastro, cadastrar_novamente);
            
        } while (cadastrar_novamente == 1);
        menu_cadastro_aluno();
    
    case 2: // Excluir Aluno
        do 
        {
            excluir_novamente = excluir_pessoa(opcao_cadastro, excluir_novamente);
        } while (excluir_novamente == 1);
        menu_cadastro_aluno();

    case 3: // Alterar Aluno
        do
        {
            atualizar_novamente = atualizar_pessoa(opcao_cadastro, atualizar_novamente);
        } while (atualizar_novamente == 1);         
        menu_cadastro_aluno();

    default:
        printf("\n* Opcao Invalida! *\n");
        menu_cadastro_aluno();
    }
}

// Menu Cadastro professor
int menu_cadastro_professor(opcao_cadastro_professor){
    printf("\n****************************\n");
    printf(  "* Menu Cadastro Professor  *");
    printf("\n****************************\n");
    printf("Digite a opcao desejada.\n");
    printf("0 - Retornar ao Menu Anterior.\n");
    printf("1 - Cadastrar Novo Professor.\n");
    printf("2 - Excluir Professor.\n");
    printf("3 - Alterar Professor.\n>>> ");
    scanf("%d", &opcao_cadastro_professor);

    switch (opcao_cadastro_professor){
    case 0: // Retornar ao Menu Anterior
        menu_cadastro(); 

    case 1: // Cadastrar Novo Professor       
        do
        {   
            cadastrar_novamente = cadastro_pessoa(opcao_cadastro, cadastrar_novamente);
            
        } while (cadastrar_novamente == 1);
        menu_cadastro_professor(); 

    case 2: // Excluir Professo
        do 
        {
            excluir_novamente = excluir_pessoa(opcao_cadastro, excluir_novamente);
        } while (excluir_novamente == 1);
        menu_cadastro_professor(); 
    
    case 3: // Alterar professor
        do
        {
            atualizar_novamente = atualizar_pessoa(opcao_cadastro, atualizar_novamente);
        } while (atualizar_novamente == 1);         
        menu_cadastro_professor();

    default:
        printf("\n* Opcao Inválida! *\n");
        menu_cadastro_professor();
    }
}

// Menu Cadastro Disciplina
int menu_cadastro_disciplina(opcao_cadastro_disciplina){
    printf("\n****************************\n");
    printf(  "* Menu Cadastro Disciplina *");
    printf("\n****************************\n");
    printf("Digite a opcao desejada.\n");
    printf("0 - Retornar ao Menu Anterior.\n");
    printf("1 - Cadastrar Nova Disciplina.\n");
    printf("2 - Excluir Disciplina.\n");
    printf("3 - Alterar Disciplina.\n>>> ");
    scanf("%d", &opcao_cadastro_disciplina);

    switch (opcao_cadastro_disciplina){
    case 0: // Retornar ao Menu Anterior
        menu_cadastro();    

    case 1: // Cadastrar Nova Disciplina    
        do
        {   
            cadastrar_novamente = cadastro_disciplina(cadastrar_novamente);
            
        } while (cadastrar_novamente == 1);
        menu_cadastro_disciplina();

    case 2: // Excluir Disciplina
        menu_cadastro_disciplina();

    case 3: // Alterar Disciplina
        menu_cadastro_disciplina();

    default:
        printf("\n* Opcao Inválida! *\n");
        menu_cadastro_disciplina();
    }
}

// Menu Matricular Aluno
int menu_matricular(){
    printf("\n****************************\n");
    printf(  "*   Menu Matricular Aluno  *");
    printf("\n****************************\n");
    printf("Digite a opcao desejada:\n0 - Retornar ao menu Inicial.\n1 - Matricular Aluno.\n2 - Excluir aluno de Disciplina.\n>>> ");
    scanf("%d", &opcao_matricula);
    switch(opcao_matricula){
        case 0:
            menu_cadastro();
        case 1:
            matricula();
            menu_matricular();
        case 2:
            excluir_matricula();
            menu_matricular();
        
        default:
            printf("\n* Opcao Inválida! *\n");
            menu_matricular();
    }
}


// Menu de Listas/Relatórios
int menu_relatorio(void){
    printf("\n****************************\n");
    printf(  "*      Menu Relatorio      *");
    printf("\n****************************\n");
    printf("Digite a opcao desejada.\n");
    printf("0  - Retornar ao Menu Anterior.\n");
    printf("1  - Listar Alunos.\n");
    printf("2  - Listar Professores.\n");
    printf("3  - Listar Disciplinas.\n");
    printf("4  - Listar Disciplinas Especifica.\n");
    printf("5  - Listar Alunos por Sexo (M/F).\n");
    printf("6  - Listar Alunos Ordenados por Nome.\n");
    printf("7  - Listar Alunos Ordenados por Data de Nascimento.\n");
    printf("8  - Listar Professores por Sexo (M/F).\n");
    printf("9  - Listar Professores Ordenados por Nome.\n");
    printf("10 - Listar Professores Ordenados por Data de Nascimento.\n");
    printf("11 - Aniversariantes do Mes.\n");
    printf("12 - Buscar (Professor / Aluno) por Parte do Nome.\n");
    printf("13 - Lista de Alunos Matriculados em Menos de 3 Disciplinas.\n");
    printf("14 - Listar Disciplinas que Extrapolam 40 Vagas.\n>>> ");
    scanf("%d", &opcao_relatorio);

    switch (opcao_relatorio){
    case 0: // Retornar ao Menu Anterior.
        menu_inicial();

    case 1: // Listar Alunos
        listagem_pessoas(opcao_relatorio);
        //lista_alunos();
        menu_relatorio();
    
    case 2: // Listar Professores
        listagem_pessoas(opcao_relatorio);
        //lista_professores();
        menu_relatorio();
    
    case 3: // Listar Disciplinas
        lista_disciplinas();
        menu_relatorio();

    case 4: // Listar Disciplinas Específica mostrando seus dados e os alunos matriculados
        buscar_disciplina();
        menu_relatorio();

    case 5: // Listar Alunos por Sexo (M/F)
        pessoas_porsexo(opcao_relatorio);
        menu_relatorio();

    case 6: //ordenar(opcao_relatorio);
        ordenar_pessoas_nome(opcao_relatorio);
        menu_relatorio();

    case 7: // Listar Alunos Ordenados por Data de Nascimento.
        lista_data_nasc(opcao_relatorio);
        menu_relatorio();

    case 8: // Listar Professores por Sexo (M/F)
        pessoas_porsexo(opcao_relatorio);
        menu_relatorio();

    case 9: // Listar Professores Ordenados por Nome
        ordenar_pessoas_nome(opcao_relatorio);
        menu_relatorio();

    case 10: // Listar Professores Ordenados por Data de Nascimento
        lista_data_nasc(opcao_relatorio);
        menu_relatorio();

    case 11: // Aniversariantes do Mês
        lista_aniversariantes();
        menu_relatorio();

    case 12: // Buscar (Professor / Aluno) por Parte do Nome
        buscar_pessoa();
        menu_relatorio();

    case 13: // Lista de Alunos Matriculados em Menos de 3 Disciplinas
        menos_de_3();
        menu_relatorio();

    case 14: // Listar Disciplinas que Extrapolam 40 Vagas
        disciplinas_prof_mais40();
        menu_relatorio();

    default:
        break;
    }
}


//**********************************************
//   Main Function 
//**********************************************

int main(){

    while (verificador_menu_inicial == 1){
        verificador_menu_inicial = menu_inicial();
               
    }
}
