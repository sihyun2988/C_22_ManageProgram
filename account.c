#include <stdio.h>
#include "sh_account.h"

 /*입력: 계좌주 이름
(랜덤, 겹치는 번호있는지 확인)계좌번호 생성
계좌 개수 추가*/
int acc_open()
{
    return 0;
}

/*입금할 금액 입력
balance에 입금액 더하기*/
int deposit()
{
    return 0;
}

/*출금할 금액 입력
balance에 출금액 빼기*/
int withdraw()
{
    return 0;
}

/*정렬기준(예금주, 잔고내림차순) 선택하기
포인터만 빼와서 배열에서 정렬
계좌번호 입력
계좌잔고 출력*/
int all_account()
{
    return 0;
}

/*삭제할 계좌번호 입력
검색해서 한번더 삭제할지 확인하고 삭제하기*/
int acc_delete()
{
    return 0;
}

int file_read()
{
    if(fp == NULL){
        printf("Failed to open file %s\n", "data_acc.txt");
        return -1;
    }
    while(!feof(fp)){
        new_node = (AccountNode)malloc(sizeof(AccountNode));
        fscanf(fp, "%s %d %d\n", &new_node->name, &new_node->accnum, &new_node->balace);
    }
    return 0;
}

int file_save()
{
    return 0;
}