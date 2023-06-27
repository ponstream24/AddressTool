/*
    charset UTF-8
    ©︎copyright All Rights Reserved Yuki Tetsuka

    プロセスファイル
*/

// UTF-8で出力
#pragma execution_character_set("utf-8")

// エディター用
// インスタンス
#ifdef _WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include "globals.h"
#include "color.h"
#include "display.c"


/**
 * メインの実行
 * @returns 1なら正常に終了 0なら異常で終了
*/
int run(){

    int result = 1;
    
    while (1) {

        clearView();

        // 0 -> Error
        // 1 -> 通常
        // 2 -> 終了
        int show = showWindow();

        if( show == 0 ){
            cprintf("MainProcess", "%sI can't show display.%s\n", COLOR_RED_FG, TEXT_RESET);
            result = 0;
            break;
        }
        else if(show == 2){
            cprintf("MainProcess", "%s Shutdown...\n%s", COLOR_BLUE_FG, TEXT_RESET);
            result = 1;
            break;
        }

        printf("読み込み中\n");
    }


    return result;
}