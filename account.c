#include "sh_account.h"

extern AccountNode *tail;
extern int newacc_accnum;

/*입력: 계좌주 이름
(랜덤, 겹치는 번호있는지 확인)계좌번호 생성
계좌 개수 추가*/
void acc_open()
{
    AccountNode* new_node;
    char user[80];
    
    while(1){
        printf("\n        =======계좌 개설=======      \n");
        printf("메뉴로 돌아가려면 -1을 입력하세요.\n\n");
        printf("예금주 이름(영문): ");
        scanf("%s", user);
        if (!(strcmp(user, "-1"))) return; //입력이 -1이면 함수 종료
        
        new_node = (AccountNode*)malloc(sizeof(AccountNode));
        if (new_node == NULL){
                printf("동적 메모리 할당 오류\n");
                exit(1);
        }
        strcpy(new_node->user, user);
        //계좌번호 할당
        new_node->accnum = ++newacc_accnum;
        printf("입금액: ");
        scanf("%ld", &new_node->balance);
        if(new_node->balance < 0){
                printf("입금액 입력 오류\n");
                continue;
        }
        listnode_add(new_node);
        printf("\n%s 님의 계좌가 개설되었습니다.\n계좌번호: %d\n잔고: %ld\n", new_node->user, new_node->accnum, new_node->balance);
    }
}

/*입금할 금액 입력
리스트에서 해당 노드 검색
balance에 입금액 더하기*/
void deposit()
{
    int accnum;
    int money;
    AccountNode *key_node, *deposit_node;
    
    while(1){
        printf("\n         =========입금========        \n");
        printf("메뉴로 돌아가려면 -1을 입력하세요.\n입금할 계좌의 계좌번호를 입력하세요.\n\n계좌번호(6숫자): ");
        scanf("%d", &accnum);
        if (accnum == -1) return; //입력이 -1이면 함수 종료

        deposit_node = accsearch(tail->next, &accnum, ACC_SEARCH_NUM, int_comp); //accsearch함수로 반환된 tmp를 keynode에 저장
         //변경할 노드주소값이 NULL이면 다음 반복으로 넘어감
        if (deposit_node == NULL){
            printf("*입력하신 계좌번호는 존재하지 않는 번호입니다.*\n*다시 입력해주세요.*\n");
            continue;
        }
        while(1){
            printf("\n현재 잔고: %ld원\n", deposit_node->balance);
            printf("입금할 금액을 입력하세요.\n입금액: ");
            scanf("%d", &money);
            
            if(money < 0){
                printf("입금액 입력 오류\n");
                continue;
            }
            else{
                deposit_node->balance += money;
                printf("출금이 정상적으로 처리되었습니다.\n현재 잔고: %ld원\n", deposit_node->balance);
                break;
            }
        }
    }
}

/*출금할 금액 입력
balance에 출금액 빼기*/
void withdraw()
{
    int accnum;
    int money;
    AccountNode *key_node, *withdraw_node;

    while(1)
    {
        printf("\n         =========출금========        \n");
        printf("메뉴로 돌아가려면 -1을 입력하세요.\n출금할 계좌의 계좌번호를 입력하세요.\n\n계좌번호(6숫자): ");
        scanf("%d", &accnum);
        if (accnum == -1) return; //입력이 -1이면 함수 종료

        withdraw_node = accsearch(tail->next, &accnum, ACC_SEARCH_NUM, int_comp); //accsearch함수로 반환된 tmp를 keynode에 저장
        //변경할 노드주소값이 NULL이면 다음 반복으로 넘어감
        if (withdraw_node == NULL){
            printf("*입력하신 계좌번호는 존재하지 않는 번호입니다.*\n*다시 입력해주세요.*\n");
            continue;
        }
        while(1){
            printf("\n현재 잔고: %ld원\n", withdraw_node->balance);
            printf("출금할 금액을 입력하세요.\n출금액: ");
            scanf("%d", &money);
            if(money > withdraw_node->balance){
                printf("*출금액이 예금액을 초과할 수 없습니다.*\n");
                continue;
            }
            else if(money < 0){
                printf("출금액 입력 오류\n");
                continue;
            }
            else{
                withdraw_node->balance -= money;
                printf("출금이 정상적으로 처리되었습니다.\n현재 잔고: %ld원\n", withdraw_node->balance);
                break;
            }
        }        
    }
}

/*계좌번호로 입력받아서 검색 -> 잔고 조회하는 함수*/
void bal_check()
{
    int menu;
    int accnum;
    char user[80];
    int cnt = 0; //찾은 계좌 개수(한 예금주 당)
    AccountNode *balcheck_node;
    AccountNode *search_start;
    
    while(1){
        printf("\n       =======예금액 조회=======      \n");
        printf("                [메뉴]                 \n");
        printf("1. 예금주로 조회\n2. 계좌번호로 조회\n3. 이전메뉴로\n\n메뉴 선택: ");
        scanf("%d", &menu);
        switch(menu){
            case 1://예금주 조회(한 예금주에 속한 모든 계좌 조회하도록)
                printf("예금주(영문): ");
                scanf("%s", user);
                printf("\n\n예금주    계좌번호   예금액\n");

                search_start = tail->next;
                while(1){
                    balcheck_node = accsearch(search_start, user, ACC_SEARCH_USER, int_comp);
                    
                    if (balcheck_node != NULL) //예금주의 계좌 노드를 찾은 경우
                    {
                        printf("%s    %d    %ld원\n", balcheck_node->user, balcheck_node->accnum, balcheck_node->balance);
                        cnt++;
                        if (balcheck_node == tail) //끝에서 찾은 경우
                        {
                            printf("%s 님의 계좌는 총 %d건입니다.", user, cnt);
                            break;

                        }
                        else //중간에서 찾은 경우
                        {
                            search_start = balcheck_node->next; //다음 반복에서 찾기 시작할 위치를 설정
                            continue;
                        }
                    }
                    
                    else //예금주의 계좌 노드가 더이상 없는 경우
                    {
                        if(cnt > 0) //앞에서 찾은 경우
                        {
                            printf("%s 님의 계좌는 총 %d건입니다.", user, cnt);
                        }
                        else //앞에서도 한번도 찾지 못한 경우
                        {
                            printf("%s 님의 계좌는 총 %d건입니다.\n", user, cnt);
                            printf("%s 님의 계좌를 찾지 못했습니다.\n", user);
                        }
                        break;
                    }
                }
                break;
            case 2:
                while(1){
                    printf("계좌번호(6숫자): ");
                    scanf("%d", &accnum);

                    balcheck_node = accsearch(tail->next, &accnum, ACC_SEARCH_NUM, int_comp); //accsearch함수로 반환된 tmp를 keynode에 저장
                    //변경할 노드주소값이 NULL이면 다음 반복으로 넘어감
                    if (balcheck_node == NULL)
                    {
                        printf("*입력하신 계좌번호는 존재하지 않습니다.*\n*다시 입력해주세요.*\n");
                        continue;
                    }
                    else
                    {
                        printf("\n\n예금주    계좌번호   예금액\n");
                        printf("%s    %d    %ld원\n", balcheck_node->user, balcheck_node->accnum, balcheck_node->balance);
                        break;
                    }
                }
                break;
            case 3:
                return;
            default:
                printf("\n*잘못된 메뉴 선택입니다.*\n");
                do{
                    getchar();
                }
                while (getchar() != '\n');
        }
    }
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

/*리스트에서 acc_search_type(계좌번호, 예금주)을 검색기준으로 key찾는 함수
start_node 매개변수 = 검색을 시작할 위치*/
AccountNode* accsearch(AccountNode* start_node, void* key, int acc_search_type, int (*func)(void*, void*))//함수포인터 사용
{
    AccountNode* tmp = start_node;
    
    //계좌번호, 예금주로 나누어져서 경우마다 검색
    if (acc_search_type == ACC_SEARCH_USER){
        while(1){
            if(func(tmp->user, key)){
                return tmp; //key 찾으면 해당 주소값 반환
            }
            //tmp->next(현재 검사하는 노드의 next), tail->next(원형연결리스트라서 맨처음 노드를 가리킴)
            else
            {
                if((tmp == tail)){ 
                return NULL; //key 못 찾고 리스트 마지막 노드까지 가면 NULL 반환
                }
            }
            tmp = tmp->next;
        }
    }
    if (acc_search_type == ACC_SEARCH_NUM){
        
        while(1){
            if(func(&tmp->accnum, key)){
                return tmp;
            }
            if((tmp == tail)){ 
                return NULL;
            }
            tmp = tmp->next;
        }
    }
    /*if (acc_search_type == ACC_SEARCH_BALANCE){
        while(1){
            if(func(&tmp->balance, key)){
                return tmp;
            }
            if((tmp == tail)){ 
                return NULL;
            }
            tmp = tmp->next;
        }
    }*/
    else
        printf("search type error\n");
}
int int_comp(void* a, void* b)//계좌번호
{
    return *((int*)a) == *((int*)b)? 1 : 0; //a, b를 int 포인터형으로 형변환 후, 값 비교
}
int str_comp(void* a, void* b)//예금주
{
    return !(strcmp( (char*)a, (char*)b) ); //a, b를 char 포인터형으로 형변환 후, 비교
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