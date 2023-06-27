/*
    charset UTF-8
    ©︎copyright All Rights Reserved Yuki Tetsuka

    ディスプレイファイル - new
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
#include "../globals.h"
#include "../color.h"


// 新規作成ページ
int showNew(){

    char lname[64];
    char fname[64];
    char email[64];

    printf("Address\n");
    printf(" -> ホーム\n");
    printf(" -> 新規ユーザー作成\n");
    printf("\n");
    printf("\n");

    cprintf("Address/ホーム/新規ユーザー作成", "%s中止する場合は、[-q]を入力してください。%s\n", COLOR_YELLOW_FG, TEXT_RESET);

    // 名字
    while (1){
        cprintf("Address/ホーム/新規ユーザー作成", "名字 : ");

        scanf("%s", lname);

        clearInput();

        // 確認
        if(strcmp(lname, "-q") == 0){
            showPage = 0;
            return 1;
        }
        else if(strcmp(lname, "\n") != 0){
            break;
        }

        cprintf("Address/ホーム/新規ユーザー作成", "%s%s <-は無効な名字です。%s", COLOR_RED_FG, lname, TEXT_RESET);
    }

    // 名前
    while (1){
        cprintf("Address/ホーム/新規ユーザー作成", "名前 : ");

        scanf("%s", fname);

        clearInput();

        // 確認
        if(strcmp(fname, "-q") == 0){
            showPage = 0;
            return 1;
        }
        else if(strcmp(lname, "\n") != 0){
            break;
        }

        cprintf("Address/ホーム/新規ユーザー作成", "%s%s <-は無効な名前です。%s", COLOR_RED_FG, fname, TEXT_RESET);
    }

    // メールアドレス
    while (1){
        cprintf("Address/ホーム/新規ユーザー作成", "メールアドレス : ");

        scanf("%s", email);

        clearInput();

        if(strcmp(email, "-q") == 0){
            showPage = 0;
            return 1;
        }

        // 確認
        int check = checkMail(email);

        // 有効
        if(check == 1) break;
        
        // 構文のみ有効
        else if(check == 2){
            
            char yn;

            while (1)
            {
                cprintf("Emailチェッカー", "%sメールアドレスの構文は正しいですが、使われていないメールアドレスの可能性があります。それでも登録しますか？%s[y/n]", COLOR_RED_FG, TEXT_RESET);
                
                scanf("%c", &yn);

                clearInput();

                if( yn == 'y' || yn == 'Y' || yn == 'n' || yn == 'N' ){
                    break;
                }
                else{
                    cprintf("Emailチェッカー", "%s不明な文字列 -> \"%c\"%s", COLOR_RED_FG, yn, TEXT_RESET);
                }
            }
            
            if( yn == 'y' || yn == 'Y' ){
                break;
            }
            else{
                continue;
            }
        }

        // エラー発生
        else if(check == -1){
            char yn;

            while (1)
            {
                cprintf("Emailチェッカー", "%sメールの有効性の確認に失敗しました。メールアドレスを正しいものとしてそのまま登録を続けますか？%s[y/n]", COLOR_YELLOW_FG, TEXT_RESET);
                
                scanf("%c", &yn);
                
                clearInput();

                if( yn == 'y' || yn == 'Y' || yn == 'n' || yn == 'N' ){
                    break;
                }
                else{
                    cprintf("Emailチェッカー", "%s不明な文字列 -> \"%c\"%s", COLOR_RED_FG, yn, TEXT_RESET);
                }
            }
            
            if( yn == 'y' || yn == 'Y' ){
                break;
            }
            else{
                continue;
            }
        }

        cprintf("Address/ホーム/新規ユーザー作成", "%s%s <-は無効なメールアドレスです。%s\n", COLOR_RED_FG, email, TEXT_RESET);
    }

    cprintf("UserCtrl","*------- User Info -------*\n");
    cprintf("UserCtrl","     ID        : <作成後付与>\n");
    cprintf("UserCtrl"," Last Name     : %s\n", lname);
    cprintf("UserCtrl"," First Name    : %s\n", fname);
    cprintf("UserCtrl"," Email Address : %s\n", email);
    cprintf("UserCtrl","*------------------------*\n");

    char yn;

    while (1)
    {
        cprintf("Address/ホーム/新規ユーザー作成", "%s上記の情報でユーザーを新規作成しますか？%s[y/n]", COLOR_YELLOW_FG, TEXT_RESET);
        
        scanf("%c", &yn);
        
        clearInput();

        if( yn == 'y' || yn == 'Y' || yn == 'n' || yn == 'N' ){
            break;
        }
        else{
            cprintf("Address/ホーム/新規ユーザー作成", "%s不明な文字列 -> \"%c\"%s", COLOR_RED_FG, yn, TEXT_RESET);
        }
    }
    
    if( yn == 'y' || yn == 'Y' ){
        // ユーザー作成
        createUser(lname, fname, email);

        cprintf("Address/ホーム/新規ユーザー作成", "%sユーザーを作成しました!エンターキーを押して続けてください..%s", COLOR_BLUE_FG, TEXT_RESET);
    }
    else{
        cprintf("Address/ホーム/新規ユーザー作成", "%sユーザーの作成を中断しました。エンターキーを押して続けてください..%s", COLOR_YELLOW_FG, TEXT_RESET);
    }

    clearInput();

    printf("\n");

    showPage = 0;
    
    return 1;
}