#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACC_SEARCH_USER 1
#define ACC_SEARCH_NUM 2
#define ACC_SEARCH_BALANCE 3

typedef struct node{
    char user[80];
    int accnum;
    long balance;
    struct node* next;
} AccountNode;

void acc_open();
void deposit();
void withdraw();
void all_account();
void acc_delete();
int file_read(FILE *fp);
void file_save(FILE *fp);
AccountNode* accsearch(void* key, int acc_search_type, int (*func)());
int int_comp(void* a, void* b);
int float_comp(void* a, void* b);
int str_comp(void* a, void* b);
void listnode_add(AccountNode* new_node);