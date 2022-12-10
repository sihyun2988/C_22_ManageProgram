typedef struct node{
    char user[80];
    int accnum;
    int pin;
    float balance;
    struct node* next;
} AccountNode;

AccountNode *head = NULL;

int acc_open();
int deposit();
int withdraw();
int all_account();
int acc_delete();
int file_read();
int file_save();