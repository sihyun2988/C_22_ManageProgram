#include <stdio.h>
#include <stdlib.h>
#include "sh_account.h"

int main()
{
    int menu;
    FILE *fp = NULL;
    fp = fopen("data_acc.txt", "r+");
    
    file_read();
    
    while (1)
    {
        printf("=========계좌 관리 프로그램=========\n");
        printf("              [메뉴]               \n");
        printf("1.계좌 개설\t2.입금\t 3.출금\n4.잔고 조회\t5.계좌 삭제\t6.종료\n");
        scanf("%d", &menu);
        
        switch (menu){
            case 1:
                acc_open();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                all_account();
                break;
            case 5:
                acc_delete();
                break;
            case 6:
                file_save();
                exit(0);
        }
    }
}