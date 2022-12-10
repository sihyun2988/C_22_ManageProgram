#include "sh_account.h"

extern AccountNode *tail;
extern int newacc_accnum;

 /*입력: 계좌주 이름
(랜덤, 겹치는 번호있는지 확인)계좌번호 생성
계좌 개수 추가*/
void acc_open()
{
    AccountNode* new_node;

    new_node = (AccountNode*)malloc(sizeof(AccountNode));
    if (new_node == NULL){
            printf("동적 메모리 할당 오류\n");
            exit(1);
    }
    printf("        =======계좌 개설=======      \n");
    printf("예금주 이름: ");
    scanf("%s", new_node->user);
    //계좌번호 할당
    new_node->accnum = ++newacc_accnum;
    printf("입금액: ");
    scanf("%ld", &new_node->balance);
    listnode_add(new_node);
    printf("%s 님의 계좌가 개설되었습니다.\n계좌번호: %d\n잔고: %ld\n", new_node->user, new_node->accnum, new_node->balance);
}

/*입금할 금액 입력
리스트에서 해당 노드 검색
balance에 입금액 더하기*/
void deposit()
{
    int accnum;
    
    printf("         =========입금========        \n");
    printf("입금할 계좌의 계좌번호를 입력하세요.\n계좌번호(6숫자): ");
    scanf("%d", &accnum);
    
    //keynode = accsearch(&new_node->accnum, ACC_SEARCH_NUM, int_comp)

        
    
}

/*출금할 금액 입력
balance에 출금액 빼기*/
void withdraw()
{
    
}

/*정렬기준(예금주, 잔고내림차순) 선택하기
포인터만 빼와서 배열에서 정렬
계좌번호 입력
계좌잔고 출력*/
void all_account()
{
    
}

/*삭제할 계좌번호 입력
검색해서 한번더 삭제할지 확인하고 삭제하기*/
void acc_delete()
{
    
}

/*프로그램 실행할 때, 파일 모든 내용 가져와서 연결리스트에 저장*/
int file_read()
{
    AccountNode* new_node;
    FILE *fp = NULL;

    //data_acc.txt 읽어오고 오류 검사
    fp = fopen("data_acc.txt", "rt");
    if(fp == NULL){
        printf("Failed to open file %s\n", "data_acc.txt");
        return -1;
    }

    fscanf(fp, "%d", &newacc_accnum); //신규계좌번호 초기화
    fgetc(fp);
    while(!feof(fp)){
        new_node = (AccountNode*)malloc(sizeof(AccountNode));
        if (new_node == NULL){
            printf("동적 메모리 할당 오류\n");
            fclose(fp);
            exit(1);
        }
        //데이터파일 내 전체 계좌 정보 읽어와서 리스트에 저장
        fscanf(fp, "%s %d %ld", new_node->user, &new_node->accnum, &new_node->balance);
        listnode_add(new_node);
    }
    fclose(fp);
    return 0;
}

/*연결리스트 돌면서
파일에 저장하고
할당한 노드 모두 해제*/
int file_save()
{
    AccountNode *tmp_node, *head;
    FILE *fp = NULL;

    fp = fopen("data_acc.txt", "wt");
    if(fp == NULL){
        printf("Failed to open file %s\n", "data_acc.txt");
        return -1;
    }

    fprintf(fp, "%d\n", newacc_accnum); //계좌번호 할당개수 파일에 출력
    if(tail != NULL)
    {    
        head = tail->next;
        tmp_node = head;
        while(1)
        {
            if (tmp_node->next == head)
            {
                fprintf(fp, "%s %d %ld", tmp_node->user, tmp_node->accnum, tmp_node->balance);
                break;
            }
            fprintf(fp, "%s %d %ld\n", tmp_node->user, tmp_node->accnum, tmp_node->balance);
            tmp_node = tmp_node->next;
        }
    }
    if(tail != NULL)
    {    
        head = tail->next;
        tmp_node = head;
        while(1)
        {
            if (tmp_node->next == head)
            {
                free(tmp_node);
                break;
            }
            free(tmp_node);
            tmp_node = tmp_node->next;
        }
    }    
    
    fclose(fp);
    return 0;
}

//부가적 함수들

/*리스트에서 acc_search_type(계좌번호, 잔고, 예금주)을 검색기준으로 key찾는 함수*/
AccountNode* accsearch(void* key, int acc_search_type, int (*func)(void*, void*))//함수포인터 사용
{
    AccountNode* tmp = tail->next;
    
    //계좌번호, 잔고, 예금주로 나누어져서 경우마다 검색
    if (acc_search_type == ACC_SEARCH_USER){
        while(1){
            if(func(tmp->user, key)){
                return tmp; //key 찾으면 해당 주소값 반환
            }
            //tmp->next(현재 검사하는 노드의 next), tail->next(원형연결리스트라서 맨처음 노드를 가리킴)
            if((tmp->next == tail->next)){ 
                return NULL; //key 못 찾고 리스트 마지막 노드까지 가면 NULL 반환
            }
            tmp = tmp->next;
        }
    }
    if (acc_search_type == ACC_SEARCH_NUM){
        while(1){
            if(func(&tmp->accnum, key)){
                return tmp;
            }
            if((tmp->next == tail->next)){ 
                return NULL;
            }
            tmp = tmp->next;
        }
    }
    if (acc_search_type == ACC_SEARCH_BALANCE){
        while(1){
            if(func(&tmp->balance, key)){
                return tmp;
            }
            if((tmp->next == tail->next)){ 
                return NULL;
            }
            tmp = tmp->next;
        }
    }
    else
        printf("search type error\n");
}
int int_comp(void* a, void* b)//계좌번호, 잔고
{
    int* a_p = (int*)a;
    int* b_p = (int*)b; //a, b를 int형으로 형변환 왜 포인터를 형변환???

    return a == b? 1 : 0;
}
int str_comp(void* a, void* b)//예금주
{
    char* a_p = (char*)a;
    char* b_p = (char*)b;

    return !(strcmp(a, b));
}

//연결리스트 노드 추가하는 함수
void listnode_add(AccountNode* new_node)
{
    AccountNode* next;
    
    if (tail == NULL){
        tail = new_node;
        new_node->next = tail;
    }
    else{
        new_node->next = tail->next;
        tail->next = new_node;
        tail = new_node;
    }
}