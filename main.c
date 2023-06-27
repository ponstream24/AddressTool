/*
    charset UTF-8
    ©︎copyright All Rights Reserved Yuki Tetsuka

    メインファイル
*/

// UTF-8で出力
#pragma execution_character_set("utf-8")

// インスタンス
#ifdef _WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


// インクルード
#include "util.c"
#include "string.c"
#include "record.c"
#include "color.h"
#include "globals.h"
#include "process.c"
// #include "file.c"

struct LIST* addressList = NULL;
int profileCount = 0;
int aiID = 0;
int key = 0;

int showPage = 0;
int showPage_OP = 0;
int showPage_cursor = 0;

// 起動
void start(){

    cprintf("StartProcess", "Hello! Now Starting...\n");

    // 初期化
    cprintf("StartProcess", "Initializing variable...\n");
    profileCount = 0;
    aiID = 0;
    cprintf("StartProcess", "Initialization complete!\n");

    char url[255] = "api.itsystem-lab.com";

    cprintf("StartProcess", "Test Connect (%s)\n", url);

    // インターネット(API)に接続できるか確認
    if( checkInternet(url) != 1 ){

        // 接続に失敗
        cprintf("StartProcess", "%sFailed to connect to the internet.%s(%s)%s\n", COLOR_RED_FG, COLOR_GREEN_FG, url,  TEXT_RESET);
        cprintf("StartProcess", "%sShutting down the system%s\n", COLOR_BLUE_FG, TEXT_RESET);
        exit(0);
    }
    else{
        cprintf("StartProcess", "Web access OK\n");
    }

    // 初期化
    addressList = NULL;

    // 保存してあるデータを読み込む
    if( ReadData() != 1 ){

        // 読み込みに失敗
        cprintf("StartProcess", "%sShutting down the system.%s\n", COLOR_BLUE_FG, TEXT_RESET);
        exit(0);
    }

    cprintf("StartProcess", "Complete!\n");
}

void end(){

    cprintf("EndProcess", "Now Saving...\n");

    // マウスカーソル表示
    showCursor();

    // データを書き込む
    if( SaveData() != 1 ){

        // 読み込みに失敗
        cprintf("EndProcess", "%sFailed to save the data.%s\n", COLOR_BLUE_FG, TEXT_RESET);
        exit(0);
    }

    cprintf("EndProcess", "Complete!\n");

    cprintf("EndProcess", "Goooood bye!\n");
}

void ctrlC(int signal){

    if (signal == SIGINT) {

        printf("\n");

        // 終了
        end();

        exit(0);
    }
}

int main(void)
{

    // ログファイル用に改行
    cprintf("", "\n\n\n");

    // 画面リセット
    clearView();

    // カーソル表示
    showCursor();

    // windowsでもエスケープキーが使えるように
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif

    // 起動
    start();

    // Ctrl + C で終了した場合Cのシグナルハンドラを設定
    signal(SIGINT, ctrlC);

    // 起動処理完了
    cprintf("Main", "%sStartup process has been completed.%s\n", COLOR_BLUE_FG, TEXT_RESET);
    
    // いったんストップ
    printf("Press Enter key. ->");

    // ページのリセット
    showPage = 0;
    showPage_OP = 0;
    showPage_cursor = 0;

    // Enterが入力されるまで待つ
    int c;
    if ((c = getchar()) == '\n') {

        // メインプロセスを実行
        if( run() == 1 ){
            cprintf("Main", "%sShutting down the system.%s\n", COLOR_BLUE_FG, TEXT_RESET);
        }
        else{
            cprintf("Main", "%sShutting down the system.%s\n", COLOR_RED_FG, TEXT_RESET);
        }
    }

    // 終了 (保存など)
    end();

    cprintf("Main", "Goooood bye!\n");

    return 0;
}