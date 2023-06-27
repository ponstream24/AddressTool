/*
    charset UTF-8
    ©︎copyright All Rights Reserved Yuki Tetsuka

    ディスプレイファイル - top
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


// トップページ
int showTop(){

    printf("Address\n");
    printf(" -> ホーム\n");
    printf("\n");
    printf("\n");

    printf(" 1. 新規ユーザー作成\n");
    printf(" 2. ユーザーを削除\n");
    printf(" 3. ユーザーリスト\n");
    printf(" 4. 検索\n");
    // printf(" 5. Config リロード\n");
    printf(" 0. システム終了\n");
    printf("\n");

    while (1){

        cprintf("Address/ホーム", "Action : ");

        char _c;

        scanf("%c", &_c);

        clearInput();

        if( 
            _c == '1' ||
            _c == '2' ||
            _c == '3' ||
            _c == '4' ||
            // _c == '5' ||
            _c == '0'
        ){
            key = _c - 48;
            break;
        }
        else{
            cprintf("Main", "%s不明なコマンド : %c%s\n", COLOR_RED_FG, _c, TEXT_RESET);
        }
    }

    if( key == 0 ){
        cprintf("Main", "%sシステムを終了します...\n%s", COLOR_BLUE_FG, TEXT_RESET);
        return 2;
    }
    else if( 
        key == 1 ||
        key == 2 ||
        key == 3 ||
        key == 4 ||
        // key == 5 ||
        key == 0
    ){
        showPage = key;
    }
    
    return 1;
}