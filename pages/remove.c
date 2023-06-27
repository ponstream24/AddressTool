/*
    charset UTF-8
    ©︎copyright All Rights Reserved Yuki Tetsuka

    ディスプレイファイル - remove
*/

// UTF-8で出力
#pragma execution_character_set("utf-8")

// エディター用
// インスタンス
#ifdef _WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../globals.h"
#include "../color.h"
// #include "../record.c"

struct LIST;

// ユーザー削除ページ
int showRemove(){

    int id;
    struct RECORE *removeUser = NULL;
    int index = 0;

    printf("Address\n");
    printf(" -> ホーム\n");
    printf(" -> ユーザーを削除\n");
    printf("\n");
    printf("\n");

    struct LIST *temp = addressList;

    if( temp == NULL ){

            printf("%s現在登録されているユーザーがいません。%s\n", COLOR_RED_FG, TEXT_RESET);
        }

    else{

        while (temp != NULL )
        {
            printf("%d: %s %s (%s)\n", temp->data.id, temp->data.fname, temp->data.lname, temp->data.email);
            
            temp = temp->next;
        }
    }

    printf("\n");

    cprintf("Address/ホーム/ユーザー削除", "%s中止する場合は、[-q]を入力してください。%s\n", COLOR_YELLOW_FG, TEXT_RESET);

    while (1){

        cprintf("Address/ホーム/ユーザー削除", "削除するID(数字) : ");

        char _tmp[256];

        scanf("%s", _tmp);

        clearInput();

        // 確認
        if(strcmp(_tmp, "-q") == 0){

            showPage = 0;
            return 1;
        }

        // もし数字なら
        else if(isStringNumeric(_tmp) != 0){
            
            id = atoi(_tmp);

            temp = addressList;

            removeUser = NULL;

            index = 0;

            // 何番目かも取得したいので、isRECORD()を使わない
            while (temp != NULL )
            {
                // IDが存在した
                if( temp->data.id == id ){

                    removeUser = &temp->data;
                    break;
                }

                index++;
                temp = temp->next;
            }

            if( removeUser != NULL ){

                cprintf("UserCtrl","*------- User Info -------*\n");
                cprintf("UserCtrl","     ID        : %d\n", removeUser->id);
                cprintf("UserCtrl"," Last Name     : %s\n", removeUser->lname);
                cprintf("UserCtrl"," First Name    : %s\n", removeUser->fname);
                cprintf("UserCtrl"," Email Address : %s\n", removeUser->email);
                cprintf("UserCtrl","*------------------------*\n");

                char yn;

                while (1)
                {
                    cprintf("Address/ホーム/ユーザー削除", "%s以上のユーザーを削除しますか？%s[y/n]", COLOR_YELLOW_FG, TEXT_RESET);
                    
                    scanf("%c", &yn);
                    
                    clearInput();

                    if( yn == 'y' || yn == 'Y' || yn == 'n' || yn == 'N' ){
                        break;
                    }
                    else{
                        cprintf("Address/ホーム/ユーザー削除", "%s不明な文字列 -> \"%c\"%s\n", COLOR_RED_FG, yn, TEXT_RESET);
                    }
                }

                if( yn == 'y' || yn == 'Y' ){

                    removeRECORE(index);

                    cprintf("Address/ホーム/ユーザー削除", "%s以下のユーザーを削除しました。%s\n", COLOR_GREEN_FG, TEXT_RESET);

                    cprintf("UserCtrl","*------- User Info -------*\n");
                    cprintf("UserCtrl","     ID        : %d\n", removeUser->id);
                    cprintf("UserCtrl"," Last Name     : %s\n", removeUser->lname);
                    cprintf("UserCtrl"," First Name    : %s\n", removeUser->fname);
                    cprintf("UserCtrl"," Email Address : %s\n", removeUser->email);
                    cprintf("UserCtrl","*------------------------*\n");

                    printf("\n");
                    cprintf("Address/ホーム/ユーザー削除", "%sエンターキーを押して続けてください..%s", COLOR_BLUE_FG, TEXT_RESET);

                    clearInput();

                    break;
                }
                else{
                    continue;
                }
            }
        }

        cprintf("Address/ホーム/ユーザー削除", "%s%s <-は無効なIDです。%s\n", COLOR_RED_FG, _tmp, TEXT_RESET);
    }

    showPage = 0;
    
    return 1;
}