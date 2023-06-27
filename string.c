/*
    charset UTF-8
    ©︎copyright All Rights Reserved Yuki Tetsuka

    文字列操作系ファイル
*/

// UTF-8で出力
#pragma execution_character_set("utf-8")

// インスタンス
#ifdef _WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <string.h>

// インクルード


// sのoldをnewに変換
char* replace(char* s, const char* old, const char* new) {

    // 初期化
    char* result;
    int i, count = 0;
    size_t newlen = strlen(new);
    size_t oldlen = strlen(old);

    // 元の文字列中にoldが何回現れるか
    for (i = 0; s[i] != '\0'; i++) {

        // 一致
        if (strstr(&s[i], old) == &s[i]) {
            count++;
            i += oldlen - 1;
        }
    }

    // 変換後のメモリを確保
    result = (char*)malloc(i + count * (newlen - oldlen) + 1);

    // 再利用
    i = 0;

    // ループ
    while (*s) {

        // oldの部分文字列があったら
        if (strstr(s, old) == s) {
            
            // コピー
            strcpy(&result[i], new);
            i += newlen;
            s += oldlen;
        }
        else {
            result[i++] = *s++;
        }
    }
    result[i] = '\0';

    return result;
}

// 文字を除外
char *remove_word(char *str, char word) {
    int len = strlen(str);
    if (len > 0 && str[len-1] == word) {
        str[len-1] = '\0';
    }

    return str;
}


/**
 * 文字列を分割
 * @param str 文字列
 * @param delimiter 区切る文字列
*/
char **split(char *str, const char *delimiter, int *count) {

    // 初期化
    char **result = NULL;
    char *token = NULL;
    int i = 0;

    // 分割
    token = strtok(str, delimiter);

    // tokenがNULLになるまで
    while (token != NULL) {

        // メモリ領域を変更
        result = (char **)realloc(result, sizeof(char *) * (i+1));

        // メモリを割り当てる
        result[i] = (char *)malloc(sizeof(char) *(strlen(token) + 1));

        // tokenをコピー
        strcpy(result[i], token);

        // 次の文字列を取得
        token = strtok(NULL, delimiter);

        i++;
    }

    // 個数をセット
    *count = i;

    return result;
}

/**
 * 文字列の最後に追加
 * @param str 文字列
 * @param c 文字
*/
void appendString(char* str, char c) {
    int len = strlen(str);
    str[len] = c;
    str[len + 1] = '\0';
}

/**
 * 文字列の最後を削除
 * @param str 文字列
*/
void removeLastString(char* str) {
    int len = strlen(str);
    if (len > 0) {
        str[len - 1] = '\0';
    }
}

/**
 * 文字列を比較
 * @param str1 検索先
 * @param str2 検索ワード
 * @param type 0 : 完全一致, 1 : 一部一致
 * @return 0 : 不一致, 1 : 一致
*/
int comparisonString(char* str1, char* str2, int type){

    if( str1 == NULL || str2 == NULL ){
        return 0;
    }

    int result = 0;

    if( type == 0 ){

        if( strcmp(str1, str2) == 0 ){
            return 1;
        }
        else{ 
            return 0;
        }
    }

    else{

        if( strstr(str1, str2) != NULL ){
            return 1;
        }
        else{ 
            return 0;
        }
    }

    return 0;
}