/*
    charset UTF-8
    ©︎copyright All Rights Reserved Yuki Tetsuka

    ディスプレイファイル - reload
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
#include "../file.c"


// 新規作成ページ
int showReload(){
    
    printf("Address\n");
    printf(" -> ホーム\n");
    printf(" -> Config リロード\n");
    printf("\n");
    printf("\n");

    cprintf("Address/ホーム/Config リロード", "%sシステムを終了させないでください%s\n", COLOR_YELLOW_FG, TEXT_RESET);

    cprintf("ReloadProcess", "%sConfig Reloading...\n%s", COLOR_BLUE_FG, TEXT_RESET);

    cprintf("EndProcess", "Now Saving...\n");

    // データを書き込む
    if( SaveData() != 1 ){

        // 読み込みに失敗
        cprintf("EndProcess", "%sFailed to save the data.%s\n", COLOR_BLUE_FG, TEXT_RESET);
        exit(0);
    }

    cprintf("EndProcess", "Complete!\n");

    cprintf("StartProcess", "Hello! Now Starting...\n");

    // 初期化
    cprintf("StartProcess", "Initializing variable...\n");
    profileCount = 0;
    aiID = 0;
    cprintf("StartProcess", "Initialization complete!\n");

    // 初期化
    addressList = NULL;

    // 保存してあるデータを読み込む
    if( ReadData() != 1 ){

        // 読み込みに失敗
        cprintf("StartProcess", "%sShutting down the system.%s\n", COLOR_BLUE_FG, TEXT_RESET);
        exit(0);
    }

    cprintf("StartProcess", "Complete!\n");

    cprintf("ReloadProcess", "%sComplete!\n%s", COLOR_BLUE_FG, TEXT_RESET);

    cprintf("Address/ホーム/Config リロード", "%s設定ファイルを読み込みました。エンターキーを押して続けてください..%s", COLOR_YELLOW_FG, TEXT_RESET);

    clearInput();

    printf("\n");

    showPage = 0;
    
    return 1;
}