#include "sh_account.h"

AccountNode *head = NULL;
int newacc_accnum; //계좌개설 시 필요한 계좌번호 할당 번호(누적됨) +프로그램 시작 시, 파일에서 읽어와서 초기화

int main()
{
    int menu;
    FILE *fp = NULL;
    //data_acc.txt 읽어오고 오류 검사
    printf("프로그램 시작\n");
    fp = fopen("data_acc.txt", "r+");
    if(fp == NULL){
        printf("Failed to open file %s\n", "data_acc.txt");
        return -1;
    }
    printf("파일 읽기 시작\n");
    file_read(fp);
    printf("파일 읽기 성공\n");
    
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
                file_save(fp);
                exit(0);
        }
    }
}