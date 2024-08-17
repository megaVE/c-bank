#include <stdio.h>
#include <string.h>

#define MAX_ACCOUNTS 100

struct account{
    char name[100];
    char password[100];
    float balance;
};

int getId(char operation, int max){
    int id;
    switch(operation){
        case 'c':
            printf("[CONTA]: ");
            break;

        case 'd':
            printf("[CONTA (DEPOSITO)]: ");
            break;
        
        case 'w':
            printf("[CONTA (SAQUE)]: ");
            break;
        
        case 'a':
            printf("[CONTA (DOADOR)]: ");
            break;

        case 'b':
            printf("[CONTA (RECEPTOR)]: ");
            break;
    }
    scanf("%d", &id);

    if(id < 0 || id > max){
        puts("[ERRO] Conta inexistente");
        return -1;
    }

    return id;
}

float getValue(char operation){
    float value;
    switch(operation){
        case 'd':
            printf("[VALOR (DEPOSITO)]: ");
            break;
        
        case 'w':
            printf("[VALOR (SAQUE)]: ");
            // Mostrar o total disponivel
            break;
        
        case 't':
            printf("[VALOR (TRANSFERENCIA)]: ");
            // Mostrar o total disponivel
            break;
    }
    scanf("%f", &value);
    
    if(value <= 0.0){
        puts("[ERRO] Valor Inválido");
        return -1.0;
    }
    
    return value;
}

int checkPassword(char * correctPassword){
    char password[100];
    printf("[SENHA]: ");
    scanf("%s", password);

    int feedback = !strcmp(password, correctPassword); 

    if(!feedback) puts("[ERRO] Senha Incorreta");

    return feedback;
}

void createAccount(struct account * accountArray, int * amount){
    if(*amount < MAX_ACCOUNTS - 1){
        char name[100];
        printf("[NOME DO TITULAR]: ");
        scanf("%s", name);
        strcpy(accountArray[*amount].name, name);

        char password[100];
        printf("[SENHA]: ");
        scanf("%s", password);
        strcpy(accountArray[*amount].password, password);

        accountArray[*amount].balance = 0.0;
        ++*amount;

        puts("[OK] Conta Criada com Sucesso!");
        printf("-\tNome do Proprietario(a): %s\n", accountArray[*amount - 1].name);
        printf("-\tNumero da Conta: %d\n", *amount - 1);
        printf("\t-Senha da Conta: %s\n", accountArray[*amount - 1].password);
    }else
        puts("[ERRO] Limite de contas criadas atingido");
}

void checkBalance(struct account * accountArray, int amount){
    int id = getId('c', amount);
    if(id == -1) return;

    int password = checkPassword(accountArray[id].password);
    if(!password) return;

    printf("[OK] A conta no. %d possui titular '%s' e saldo no valor de %f$\n", id, accountArray[id].name, accountArray[id].balance);
}

void depositMoney(struct account * accountArray, int amount){
    int id = getId('d', amount);
    if(id == -1) return;

    float value = getValue('d');
    if(value == -1.0) return;

    accountArray[id].balance += value;
    printf("[OK] Deposito de %f$ na conta no. %d efetuado com sucesso!\n", value, id);
}

void withdrawMoney(struct account * accountArray, int amount){
    int id = getId('w', amount);
    if(id == -1) return;

    float value = getValue('w');
    if(value == -1.0) return;

    int password = checkPassword(accountArray[id].password);
    if(!password) return;

    if(accountArray[id].balance - value >= 0){
        accountArray[id].balance -= value;
        printf("[OK] Saque de %f$ na conta no. %d efetuado com sucesso!\n", value, id);
    }else
        puts("[ERRO] Saldo Insuficiente");
}

void transferMoney(struct account * accountArray, int amount){
    int id = getId('a', amount);
    if(id == -1) return;

    float value = getValue('t');
    if(value == -1.0) return;

    int id2 = getId('b', amount);
    if(id2 == -1) return;

    int password = checkPassword(accountArray[id].password);
    if(!password) return;

    if(accountArray[id].balance - value >= 0){
        accountArray[id].balance -= value;
        accountArray[id2].balance += value;
        printf("[OK] Tranferencia de %f$ da conta no. %d para a conta no. %d efetuada com sucesso!\n", value, id, id2);
    }else
        puts("[ERRO] Saldo Insuficiente!");
}

void endAccount(struct account * accountArray, int amount){
    int id = getId('c', amount);
    if(id == -1) return;

    int password = checkPassword(accountArray[id].password);
    if(!password) return;

    printf("[OK] A conta no. %d no nome de '%d' foi encerrada com sucesso\n", id, accountArray[id].name);
}

void showOptions(){
    puts("\n---------------------------------");
    puts("  O que voce gostaria de fazer?");
    puts("---------------------------------");
    puts("1. Criar uma Conta");
    puts("2. Checar meu Saldo");
    puts("3. Fazer um Deposito");
    puts("4. Fazer um Saque");
    puts("5. Fazer uma Transferencia");
    puts("6. Encerrar uma Conta");
    puts("0. Sair do aplicativo");
    puts("---------------------------------");
    printf("> ");
}

int main(){
    struct account accountArray[MAX_ACCOUNTS];
    struct account * accountList;
    int accountAmount = 0;

    puts("[OLA] Seja bem-vindo(a) ao CBank, o que voce deseja fazer hoje?");
    showOptions();

    int operation;
    scanf("%d", &operation);

    int quitExecution = 0;
    while(!quitExecution){
        switch(operation){
            case 0:
                quitExecution = 1;
                break;

            case 1:
                createAccount(accountArray, &accountAmount);
                break;
            
            case 2:
                checkBalance(accountArray, accountAmount);
                break;
            
            case 3:
                depositMoney(accountArray, accountAmount);
                break;

            case 4:
                withdrawMoney(accountArray, accountAmount);
                break;

            case 5:
                transferMoney(accountArray, accountAmount);
                break;

            case 6:
                endAccount(accountArray, accountAmount);
                break;

            default:
                puts("[ERRO] Operacao Invalida!");
                break;
        }

        if(!quitExecution){
            do{
                puts("------------------------------------------------");
                puts("\n  Voce gostaria de fazer mais alguma operacao?");
                puts("------------------------------------------------");
                puts("0. Sim");
                puts("1. Nao");
                puts("------------------------------------------------");
                printf("> ");
                scanf("%d", &quitExecution);
            } while(quitExecution < 0 || quitExecution > 1);
            
            if(!quitExecution){
                showOptions();
                scanf("%d", &operation);
            }
        }
    }
    return 0;
}