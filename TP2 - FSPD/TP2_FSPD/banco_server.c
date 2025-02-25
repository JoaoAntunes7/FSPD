#include "banco.h"
#include <stdio.h>

struct contas{
int id;
double saldo;
};

struct contas c[10];
int n = 0;
int verify = 0;

int *cria_conta_1_svc(void *pvoid, struct svc_req *rqstp) { //Cria conta
    
    if(verify == 0){
        for(int i=0; i<10; ++i)
            c[i].id = -1;
        verify = 1;
    }
    static int result;

    if(n >= 10)
        result = -1;
    else{
    c[n].id = n;
    c[n].saldo = 0; 

    result = n;
    n++;
    }
    return &result;
}

int *exclui_conta_1_svc(int *id, struct svc_req *rqstp) { //Exclui conta

    static int result = 1;      // TODO

    c[*id].id = -1;
    c[*id].saldo = 0; 

    return &result;
}

double *saque_1_svc(record *rec, struct svc_req *rqstp){
    static double result;
    if(c[rec->id].id != -1){
        if(c[rec->id].saldo < rec->value){
            result = -1;
        }
        else{
            c[rec->id].saldo = c[rec->id].saldo - rec->value;
            result = c[rec->id].saldo;
        }
    }

    return &result;
}

double *deposito_1_svc(record *rec, struct svc_req *rqstp){
    static double result = -1;
    double valor = rec->value;
    
    if(c[rec->id].id != -1){
        c[rec->id].saldo = c[rec->id].saldo + valor;
        result = c[rec->id].saldo;
        }

    return &result;
}

double *consulta_conta_1_svc(int *id, struct svc_req *rqstp){
    static double result = -1;
    if(c[*id].id != -1){
        result = c[*id].saldo;
        }
    return &result;
}