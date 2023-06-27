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
#include "header.c"

// リストページ
int showList(){

    // 0 : 昇順
    // 1 : 降順
    int updown = 1;
    char type[10];
    strcpy(type, "id");

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
        if( updown == 0 ){
            printf("%s降順%s 昇順\n",COLOR_YELLOW_FG, TEXT_RESET);
        }
        else{
            printf("降順 %s昇順%s\n",COLOR_YELLOW_FG, TEXT_RESET);
        }

        printf("⇆ : ");
        if( strcmp(type, "lname") == 0 ){
            printf("ID %s姓%s 名 メールアドレス\n",COLOR_YELLOW_FG, TEXT_RESET);
        }
        else if( strcmp(type, "fname") == 0 ){
            printf("ID 姓 %s名%s メールアドレス\n",COLOR_YELLOW_FG, TEXT_RESET);
        }
        else if( strcmp(type, "email") == 0 ){
            printf("ID 姓 名 %sメールアドレス%s\n",COLOR_YELLOW_FG, TEXT_RESET);
        }
        else{
            printf("%sID%s 姓 名 メールアドレス\n",COLOR_YELLOW_FG, TEXT_RESET);
        }
        printf("\n");
        printf("\n");
        
        struct LIST *temp = sortList(updown, type);

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

        struct termios old_settings, new_settings;
        tcgetattr(fileno(stdin), &old_settings);
        new_settings = old_settings;
        new_settings.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(fileno(stdin), TCSANOW, &new_settings);
        setbuf(stdin, NULL);

        printf("\n");
        printf("矢印キーで並べ替え変更\n");
        printf("Qキーで閉じる\n");

        while (stop == 0) {
            if (kbhit()) {

                int key = getchar();

                if(key == 'Q' || key == 'q'){

                    stop = 1;
                    break;
                }

                // エスケープキーが押された場合
                // 矢印キーが押された場合
                if (key == '\033') {

                    // バッファにデータなし
                    if (feof(stdin)) {
                        stop = 1;
                        break;
                    }

                    // '[' を飛ばす
                    if( getchar() == '[' ){

                        int arrow = getchar();

                        // 上
                        if (arrow == 'A') {
                            
                            if( updown == 0 ){
                                updown = 1;
                                break;
                            }
                        } 
                        
                        // 下
                        else if (arrow == 'B') {
                            
                            if( updown == 1 ){
                                updown = 0;
                                break;
                            }
                        } 
                        
                        // 右
                        else if (arrow == 'C') {
                            
                            if( strcmp(type, "lname") == 0 ){
                                strcpy(type, "fname");
                                break;
                            }
                            else if( strcmp(type, "fname") == 0 ){
                                strcpy(type, "email");
                                break;
                            }
                            else if( strcmp(type, "email") == 0 ){
                                // 動作なし
                            }
                            else{
                                strcpy(type, "lname");
                                break;
                            }
                        } 
                        
                        // 左
                        else if (arrow == 'D') {
                            if( strcmp(type, "lname") == 0 ){
                                strcpy(type, "id");
                                break;
                            }
                            else if( strcmp(type, "fname") == 0 ){
                                strcpy(type, "lname");
                                break;
                            }
                            else if( strcmp(type, "email") == 0 ){
                                strcpy(type, "fname");
                                break;
                            }
                            else{
                                // 動作なし
                            }
                        }
                    } 
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