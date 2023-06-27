/*
    charset UTF-8
    ©︎copyright All Rights Reserved Yuki Tetsuka

    ディスプレイファイル
*/

// UTF-8で出力
#pragma execution_character_set("utf-8")
#include <stdio.h>
#include "../color.h"

int showHeader(){

    char c1[] = COLOR_RED_FG;
    char c2[] = COLOR_BLUE_FG;
    char c3[] = COLOR_BLUE_FG;
    char c4[] = COLOR_GREEN_FG;
    char c5[] = COLOR_CYAN_FG;
    char c6[] = COLOR_YELLOW_FG;
    char c7[] = COLOR_YELLOW_FG;

    printf("*---------------------------------------------------------------------------------------*\n");
    printf("            %s **      %s***       %s***       %s****      %s****      %s****      %s****%s     \n", c1, c2, c3, c4, c5, c6, c7, TEXT_RESET );
    printf("            %s*  *     %s*  *      %s*  *      %s*   *     %s*         %s*         %s*   %s     \n", c1, c2, c3, c4, c5, c6, c7, TEXT_RESET );
    printf("            %s****     %s*  *      %s*  *      %s****      %s***       %s****      %s****%s     \n", c1, c2, c3, c4, c5, c6, c7, TEXT_RESET );
    printf("            %s*  *     %s*  *      %s*  *      %s*  *      %s*         %s   *      %s   *%s     \n", c1, c2, c3, c4, c5, c6, c7, TEXT_RESET );
    printf("            %s*  *     %s***       %s***       %s*   *     %s****      %s****      %s****%s     \n", c1, c2, c3, c4, c5, c6, c7, TEXT_RESET );
    printf("*---------------------------------------------------------------------------------------*\n");
    printf("\n");

    return 1;
}