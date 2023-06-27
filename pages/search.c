/*
    charset UTF-8
    ©︎copyright All Rights Reserved Yuki Tetsuka

    ディスプレイファイル - search
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

// 検索ページ
int showSearch(){

    char keywords[256] = "";
    int type = 0;  // 0 : 完全一致(複 : かつ), 1 : 一部一致(複 : または)
    int kinds = 0; // 0 : 単語検索, 1 : 複語検索(スペースで区切る)

    hideCursor();

    int stop = 0;

    while (1)
    {
        // clearView();
        system("clear");

        showHeader();

        printf("Address\n");
        printf(" -> ホーム\n");
        printf(" -> リスト\n");
        printf("\n");
        printf("\n");

        printf("↑↓ : ");

        // 単語検索
        if( kinds == 0 ){
            if( type == 0 ){
                printf("%s完全一致%s 一部一致\n",COLOR_YELLOW_FG, TEXT_RESET);
            }
            else{
                printf("完全一致 %s一部一致%s\n",COLOR_YELLOW_FG, TEXT_RESET);
            }
        }

        // 複語検索
        else{
            if( type == 0 ){
                printf("%s  且つ  %s   又は\n",COLOR_YELLOW_FG, TEXT_RESET);
            }
            else{
                printf("  且つ   %s  又は%s\n",COLOR_YELLOW_FG, TEXT_RESET);
            }
        }

        printf("⇆  : ");
        if( kinds == 0 ){
            printf("%s単語検索%s 複語検索\n",COLOR_YELLOW_FG, TEXT_RESET);
        }
        else{
            printf("単語検索 %s複語検索%s\n",COLOR_YELLOW_FG, TEXT_RESET);
        }

        printf("\n");
        
        printf("+-----------------------------------------------------------------+\n");
        if( strcmp(keywords, "") == 0 ){
            printf("| 🔍 | (キーを押して検索ワードを入力してください)\n");
        }
        else{
            printf("| 🔍 | %s_\n", keywords);
        }
        printf("+-----------------------------------------------------------------+\n");

        printf("\n");
        printf("\n");
        
        struct LIST *temp = searchList(keywords, type, kinds);

        if( temp == NULL ){

            printf("%s条件に一致するユーザーがいません。%s\n", COLOR_RED_FG, TEXT_RESET);
        }

        else{
            while (temp != NULL )
            {
                printf("%d: %s %s (%s)\n", temp->data.id, temp->data.fname, temp->data.lname, temp->data.email);
                
                temp = temp->next;
            }
        }

        struct termios old_settings, new_settings;
        tcgetattr(fileno(stdin), &old_settings);
        new_settings = old_settings;
        new_settings.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(fileno(stdin), TCSANOW, &new_settings);
        setbuf(stdin, NULL);

        printf("\n");
        printf("↑↓キーで検索方法変更\n");
        printf("⇆ キーで検索種類変更\n");
        printf("Ctrl + Aで閉じる\n");

        while (stop == 0) {
            if (kbhit()) {

                int key = getchar();

                // Ctrl + A
                if(key == 1){

                    stop = 1;
                    break;
                }

                // 一文字削除
                else if(key == 127){

                    if( strcmp(keywords, "") != 0 ){

                        // 検索ワードを削除
                        removeLastString(keywords);
                        break;
                    }
                }

                // エスケープキーが押された場合
                // 矢印キーが押された場合
                else if (key == '\033') {

                    // '[' を飛ばす
                    if( getchar() == '[' ){

                        int arrow = getchar();

                        // 上
                        if (arrow == 'A') {
                            
                            if( type == 0 ){
                                type = 1;
                                break;
                            }
                        } 
                        
                        // 下
                        else if (arrow == 'B') {
                            
                            if( type == 1 ){
                                type = 0;
                                break;
                            }
                        } 
                        
                        // 右
                        else if (arrow == 'C') {
                            
                            if( kinds == 0 ){
                                kinds = 1;
                                break;
                            }
                        } 
                        
                        // 左
                        else if (arrow == 'D') {

                            if( kinds == 1 ){
                                kinds = 0;
                                break;
                            }
                        }
                    } 
                }

                else{

                    // 検索ワードに追加
                    appendString(keywords, key);

                    break;
                }
            }
        }

        tcsetattr(fileno(stdin), TCSANOW, &old_settings);

        if( stop == 1 ){
            break;
        }
    }
    
    showCursor();

    // clearInput();

    printf("\n");

    showPage = 0;
    
    return 1;
}