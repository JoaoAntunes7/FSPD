/** 
    Author: Avelino F. Zorzo
    avelino.zorzo@pucrs.br

    Date: 10.03.2001
    Modified: 10.03.2012

   This code will be translated into the needed stubs and headers
   Use: rpcgen banco.x

**/

struct record {       /* arguments for RPC must be one single */
  int id;      /* value or a structure of values */
  double value;     /*  */
}; 

program BANPROG {                /* value to register the program */
    version BANCOVERS {            /* version must be assigned a value */
        int CRIA_CONTA(void) = 1;  /* this is a service function */
        int EXCLUI_CONTA(int) = 2;  /* this is a service function */              
        double SAQUE(record)      = 3;           /* this is a service function */  
        double DEPOSITO(record) = 4;          /* this is a service function */  
        double CONSULTA_CONTA(int) = 5;          /* this is a service function */  
    } =1;                          /* version value */
} = 0x20000003;                    /* program value */   
