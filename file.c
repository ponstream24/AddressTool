/*
    charset UTF-8
    ©︎copyright All Rights Reserved Yuki Tetsuka

    ディスプレイファイル
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

// #ifdef IGNORE_CODE
// #include "record.c"
// #endif

// 定数
#define DATAPATH "./address.txt"  /* ファイルパス */

// データを読み込み
int ReadData(){

    cprintf("LoadData","Loading Now... (%s)\n", DATAPATH);

    // ファイル
    FILE *fp;

    // 最大行数
    char buffer[256];

    fp = fopen(DATAPATH, "r");
    if (fp == NULL) {
        perror("\x1b[31mFailed to open file\x1b[0m\n");
        return 0;
    }

    // 行
    int line = 0;

    // 行ごとでファイルを読み込む
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {

        cprintf("LoadData","LINE%d: %s\n", line+1, remove_word(buffer, '\n'));

        if( line == 0 ){

            // createUserでaddされるので、スキップ
            // // プロフィール数をセット
            // profileCount = atoi(buffer);
            line++;
            continue;
        }
        else{

            // splitする文字
            const char delimiter[] = " ";
            char **result = NULL;
            int count = 0;
            int i;

            // " "(スペース)で区切る
            result = split(buffer, delimiter, &count);

            // AAAA BBBB CCCC のフォーマットじゃない
            if( count != 3 ){
                cprintf("LoadData","%sInvalid file format. (%s)%s\n", COLOR_RED_FG, buffer, TEXT_RESET);
                return 0;
            }

            // 初期化
            char _lname[64] = "";
            char _fname[64] = "";
            char _email[64] = "";

            // Name Name Mail
            for (i = 0; i < count; i++) {

                // 改行を消す
                result[i] = remove_word(result[i], '\n');

                // 各項目を抽出
                if( i == 0 ){
                    cprintf("LoadData","LINE%d: \tlname -> %s\n", line+1, result[i]);
                    strcpy(_lname, result[i]);
                }
                else if( i == 1 ){
                    cprintf("LoadData","LINE%d: \tfname -> %s\n", line+1, result[i]);
                    strcpy(_fname, result[i]);
                }
                else{
                    cprintf("LoadData","LINE%d: \temail -> %s\n", line+1, result[i]);
                    strcpy(_email, result[i]);
                }
                free(result[i]);
            }

            // ユーザー作成
            createUser(_lname, _fname, _email);

            // 削除
            free(result);
        }

        line++;
    }

    fclose(fp);

    cprintf("LoadData","Loaded! (%s)\n", DATAPATH);
    cprintf("LoadData","Create Recorded! (%d)\n", profileCount);

    return 1;
}

// データを書き込む
int SaveData(){

    cprintf("SaveData","Saving Now... (%s)\n", DATAPATH);

    // ファイル
    FILE *fp;

    // 最大行数
    char buffer[256];

    fp = fopen(DATAPATH, "w");
    if (fp == NULL) {
        perror("\x1b[31mFailed to open file\x1b[0m\n");
        return 0;
    }

    fprintf(fp, "%d\n", profileCount);

    struct LIST *temp = addressList;

    cprintf("SaveData","UserCount -> %d\n", profileCount);

    while (temp != NULL )
    {
        cprintf("SaveData","ID%d: \tlname -> %s\n", temp->data.id, temp->data.fname);
        cprintf("SaveData","ID%d: \tlname -> %s\n", temp->data.id, temp->data.lname);
        cprintf("SaveData","ID%d: \temail -> %s\n", temp->data.id, temp->data.email);
        fprintf(fp, "%s %s %s\n", 
            temp->data.fname,
            temp->data.lname,
            temp->data.email
        );
        
        temp = temp->next;
    }

    return 1;
}