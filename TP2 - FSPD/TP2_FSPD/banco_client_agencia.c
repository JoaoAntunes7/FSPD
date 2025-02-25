#include <stdio.h>
#include <rpc/rpc.h>
#include "banco.h"

main(int argc, char *argv[]) {

    CLIENT *cl;
    double *answer;
    int *answer2;
    void *pvoid;

    record *rec = (record *) malloc(sizeof(record));

    if (argc != 4) {
        printf("Seja Bem-vindo ao Banco FBJ! [Acesso Agência]\nEste é o modo de usar nosso banco: %s server [id da conta](arg1) [Função](arg2)\n", argv[0]); 
        printf("Estas são as Funções: \n    [Deposito](0)\n    [Saque](1)\n    [Consulta](2)\n    [Criar Conta](3)\n    [Excluir Conta](4)\n");
        printf("\n(PS: As contas são de 0 a 9, criadas sequencialmente)\n");
        return (1); 
    } 

    if (!(cl = clnt_create(argv[1], BANPROG,BANCOVERS,"tcp"))) { 
        clnt_pcreateerror(argv[1]); 
        return(1); 
    } 

    float value;

    rec->id = atoi(argv[2]); 

    int n = atoi(argv[3]);

    switch(n){
        case 0: //Deposito
            printf("Insira o Valor a ser Depositado: R$");
            scanf("%f", &value);
            rec->value = value;
            answer = deposito_1(rec,cl); 
            if (*answer == -1) { 
            fprintf(stderr,"Erro na Operação - Conta Inválida\n"); 
            return(1); 
            } 

            printf("R$%0.2f Depositado\n Você possui R$%0.2f na sua conta corrente\n", value, *answer); 
            break;

        case 1: //saque
            printf("Insira o Valor a ser Retirado: R$");
            scanf("%f", &value);
            rec->value = value;
            answer = saque_1(rec,cl); 
            if (*answer == -1) { 
            fprintf(stderr,"Erro na Operação - Conta Inválida ou Saldo Insuficiente\n"); 
            return(1); 
            } 

            printf("R$%0.2f Retirado\n Você possui R$%0.2f na sua conta corrente\n", value, *answer);
            break;

        case 2: //consulta
            
            answer = consulta_conta_1(&rec->id,cl); 
            if (*answer == -1) { 
            fprintf(stderr,"Erro na Operação - Conta Inválida\n"); 
            return(1); 
            } 

            printf("Você possui R$%0.2f na sua conta corrente\n", *answer);
            break;

        case 3: //cria conta

            answer2 = cria_conta_1(pvoid,cl); 
                if (*answer2 == -1) { 
                fprintf(stderr,"Erro na Operação - Limite de contas atingido\n");
                return(1); 
            } 

            printf("Você criou a conta\nSeu Id é [%d]\n", *answer2);
            break;
        case 4: //exclui conta

            answer2 = exclui_conta_1(&rec->id,cl); 
                if (*answer2 == -1) { 
                fprintf(stderr,"Erro\n"); 
                return(1); 
            } 

            printf("Conta Excluída\n");
            break;
    }


    return (0);
} 
