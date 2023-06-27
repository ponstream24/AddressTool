/*
    charset UTF-8
    ©︎copyright All Rights Reserved Yuki Tetsuka

    Record/List系ファイル
*/

// UTF-8で出力
#pragma execution_character_set("utf-8")

// エディター用
// インスタンス
#ifdef _WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <time.h>
#include "globals.h"
#include "color.h"

// ユーザー
struct RECORE{

    int id;         /* 管理ID */
    char lname[64]; /* 性 */
    char fname[64]; /* 名 */
    char email[64]; /* メールアドレス */
};

// リスト
struct LIST{

    struct RECORE data; /* データ */
    struct LIST *next;   /* 次のデータへのポインタ */
};

// リストを生成
struct LIST *createLIST(struct RECORE data){

    // メモリを割り当て
    struct LIST *newLIST = (struct LIST *)malloc(sizeof(struct LIST));

    // データをLISTに格納
    newLIST->data = data;

    // 次のデータへのポインタをnullに
    newLIST->next = NULL;

    // リストを返す
    return newLIST;
}

// リストに追加
void addLIST(struct LIST **head, struct RECORE data){

    // 新しくリストを生成
    struct LIST *netLIST = createLIST(data);

    // 先頭のリストが空なら先頭に設定
    if (*head == NULL){

        *head = netLIST;
        return;
    }

    // リストの末尾まで移動
    struct LIST *temp = *head;
    while (temp->next != NULL){

        temp = temp->next;
    }

    // 新しいリストを最後尾に設定
    temp->next = netLIST;
}

// 指定されたインデックスのRECOREを削除
void removeRECORE(int index) {

    // もし先頭なら
    if (index == 0) {

        // 先頭取得
        struct LIST* temp = addressList;

        // 先頭を変更
        addressList = addressList->next;

        // 元先頭を削除
        free(temp);
    } 

    else {

        // index
        int i = 0;

        // current
        struct LIST* current = addressList;

        // currentが亡くなるまで
        while (current != NULL) {

            // もし、iが指定されていた数 - 1なら
            if (i == index - 1) {

                // 次のaddressを取得
                struct LIST* temp = current->next;

                // 次のaddressを 次のaddressの次のaddressにする
                current->next = temp->next;

                // 開放
                free(temp);

                // ループ脱
                break;
            }
            i++;
            current = current->next;
        }
    }

    profileCount--;
}


// ユーザーを作成　-1なら失敗、それ以外は管理ID
int createUser(char lname[64], char fname[64], char email[64]){

    int result = -1;

    cprintf("UserCtrl","Registering user...\n");

    // 情報に欠陥がある
    if( lname == NULL || fname == NULL || email == NULL ){

        cprintf("UserCtrl","%sInvalid value.%s\n", COLOR_RED_FG, TEXT_RESET);
        return -1;
    }

    // メモリを割り当て
    struct RECORE newUser;

    // データの格納
    strcpy(newUser.lname, lname);
    strcpy(newUser.fname, fname);
    strcpy(newUser.email, email);
    newUser.id = aiID++;

    // ユーザーをリストに追加
    addLIST(&addressList, newUser);
    profileCount++;

    cprintf("UserCtrl","*------- User Info -------*\n");
    cprintf("UserCtrl","     ID        : %d\n", newUser.id);
    cprintf("UserCtrl"," Last Name     : %s\n", newUser.lname);
    cprintf("UserCtrl"," First Name    : %s\n", newUser.fname);
    cprintf("UserCtrl"," Email Address : %s\n", newUser.email);
    cprintf("UserCtrl","*-------------------------*\n");

    cprintf("UserCtrl","User registered.\n");

    return result;
}

// ユーザーが存在するか
/**
 * @param id ユーザーID
 * @return RECORD
*/
struct RECORE *getRECORD(struct LIST *temp, int id){

    struct RECORE *target = NULL;

    while (temp != NULL ){

        // IDが存在した
        if( temp->data.id == id ){

            target = &temp->data;
            break;
        }

        temp = temp->next;
    }

    return target;
}

struct LIST *putList(struct LIST **head, struct LIST *netLIST, int position){

    if (position == 0) {
        netLIST->next = *head;
        *head = netLIST;
    } else {

        struct LIST* current = *head;
        int i;
        for (i = 0; i < position - 1 && current != NULL; i++) {
            current = current->next;
        }
        if (current == NULL) {
            printf("指定された位置が無効です。\n");
            return *head;
        }
        netLIST->next = current->next;
        current->next = netLIST;
    }
    return *head;
}

// ソートしたリスト
/**
 * @param updown 0 : 降順, 1 : 昇順
 * @param type lname, fname, email, id
*/
struct LIST *sortList(int updown, char type[]){

    struct LIST *head = NULL;

    struct LIST *temp = addressList;
    struct RECORE *target = NULL;

    // リストを繰り返す
    while (temp != NULL ){

        // 新しくリストを生成
        struct LIST *newLIST = createLIST(temp->data);

        // 最初
        if( head == NULL ){
            
            head = newLIST;
        }

        else{

            // 既にセットしてあるリスト
            struct LIST *tm = head;

            // putする場所
            int position = 0;

            // 最大比較数
            int maxLoop = 64;

            int i;

            // リストを繰り返す
            while (tm != NULL ){
                
                if( strcmp(type, "lname") == 0){

                    for ( i = 0; i < maxLoop; i++)
                    {
                        // i文字目を比較 降順
                        if( updown == 0 && tm->data.lname[i] < newLIST->data.lname[i] ){
                            position++;
                            break;
                        }

                        // i文字目を比較 昇順
                        else if( updown == 1 && tm->data.lname[i] > newLIST->data.lname[i] ){
                            position++;
                            break;
                        }

                        // i文字目が一緒なら
                        else if( tm->data.lname[i] == newLIST->data.lname[i] ){
                            continue;
                        }
                        
                        // i文字目を比較
                        else{
                            break;
                        }
                    }
                }
                
                else if( strcmp(type, "fname") == 0){

                    for ( i = 0; i < maxLoop; i++)
                    {
                        // i文字目を比較 降順
                        if( updown == 0 && tm->data.fname[i] < newLIST->data.fname[i] ){
                            position++;
                            break;
                        }

                        // i文字目を比較 昇順
                        else if( updown == 1 && tm->data.fname[i] > newLIST->data.fname[i] ){
                            position++;
                            break;
                        }

                        // i文字目が一緒なら
                        else if( tm->data.fname[i] == newLIST->data.fname[i] ){

                            continue;
                        }
                        
                        // i文字目を比較
                        else{
                            break;
                        }
                    }
                }

                else if( strcmp(type, "email") == 0){

                    for ( i = 0; i < maxLoop; i++)
                    {
                        // i文字目を比較 降順
                        if( updown == 0 && tm->data.email[i] < newLIST->data.email[i] ){
                            position++;
                            break;
                        }

                        // i文字目を比較 昇順
                        else if( updown == 1 && tm->data.email[i] > newLIST->data.email[i] ){
                            position++;
                            break;
                        }

                        // i文字目が一緒なら
                        else if( tm->data.email[i] == newLIST->data.email[i] ){
                            continue;
                        }
                        
                        // i文字目を比較
                        else{
                            break;
                        }
                    }
                }
                
                else {

                    // idを比較 降順
                    if( updown == 0 && tm->data.id < newLIST->data.id ){
                        position++;
                    }

                    // idを比較 昇順
                    else if( updown == 1 && tm->data.id > newLIST->data.id ){
                        position++;
                    }

                }

                tm = tm->next;
            }

            // 追加
            putList(&head, newLIST, position);
        }

        temp = temp->next;
    }

    return head;
}

// 検索した結果リスト
/**
 * @param keywords 検索ワード
 * @param type 0 : 完全一致(複 : かつ), 1 : 一部一致(複 : または)
 * @param kinds 0 : 単語検索, 1 : 複語検索(スペースで区切る)
*/
struct LIST *searchList(char keywords[], int type, int kinds){

    struct LIST *head = NULL;

    struct LIST *temp = addressList;

    // 単語検索
    if( kinds == 0 ){

        // リストを繰り返す
        while (temp != NULL ){

            char id[256];
            sprintf(id, "%d", temp->data.id);  // 数値を文字列に変換

            if( 
                comparisonString(temp->data.email, keywords, type)  ||
                comparisonString(temp->data.fname, keywords, type)  ||
                comparisonString(temp->data.lname, keywords, type)  ||
                comparisonString(id, keywords, type)
            ){
                // 追加
                addLIST(&head, temp->data);
            }

            temp = temp->next;
        }
    }

    // 複語検索
    else{

        // splitする文字
        const char delimiter[] = " ";
        char **result = NULL;
        int count = 0;
        int i;
        char keys[256];
        
        strcpy(keys, keywords);

        // " "(スペース)で区切る
        result = split(keys, delimiter, &count);

        // 「又は」
        if(type == 1){

            for (i = 0; i < count; i++) {

                // 先頭に戻す
                temp = addressList;

                // リストを繰り返す
                while (temp != NULL ){

                    char id[256];
                    sprintf(id, "%d", temp->data.id);  // 数値を文字列に変換

                    if( 
                        comparisonString(temp->data.email, result[i], 1)  ||
                        comparisonString(temp->data.fname, result[i], 1)  ||
                        comparisonString(temp->data.lname, result[i], 1)  ||
                        comparisonString(id, result[i], 1)
                    ){
                        // 「まだ追加されていない」
                        if(getRECORD(head, temp->data.id) == NULL ){

                            // 追加
                            addLIST(&head, temp->data);
                        }
                    }

                    temp = temp->next;
                }
            }
        }

        else{

            int _check[profileCount];

            for ( i = 0; i < profileCount; i++)
            {
                _check[i] = 1;
            }
            

            for (i = 0; i < count; i++) {

                int n = 0;

                // 先頭に戻す
                temp = addressList;

                // リストを繰り返す
                while (temp != NULL ){

                    char id[256];
                    sprintf(id, "%d", temp->data.id);  // 数値を文字列に変換

                    // 含まれていないなら
                    if( 
                        !comparisonString(temp->data.email, result[i], 1)  &&
                        !comparisonString(temp->data.fname, result[i], 1)  &&
                        !comparisonString(temp->data.lname, result[i], 1)  &&
                        !comparisonString(id, result[i], 1)
                    ){
                        _check[n] = 0;
                    }

                    temp = temp->next;
                    n++;
                }
            }

            // 先頭に戻す
            temp = addressList;

            int n = 0;

            // リストを繰り返す
            while (temp != NULL ){

                if( _check[n] == 1 ){

                    // 追加
                    addLIST(&head, temp->data);
                }
                
                temp = temp->next;
                n++;
            }
        }
    }

    return head;
}