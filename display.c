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
#include <string.h>
#include "globals.h"
#include "color.h"
#include "pages/top.c"
#include "pages/new.c"
#include "pages/remove.c"
#include "pages/list.c"
#include "pages/search.c"
#include "pages/reload.c"
// #include "pages/header.c"

// 0なら失敗 1なら成功、2...その他アクション
int showWindow(){

    // コンソールに出力する前に、確認する

    // アドレスセット済み？
    if( addressList == NULL ){
        cprintf("ShowWindow", "%s Invalid AddressList\n%s", COLOR_RED_FG, TEXT_RESET);
        return 0;
    }

    /**
     * 出力関係
    */

    // Header
    if( showHeader() != 1 ) return 0;

    // もしtopならtopページを表示
    if( showPage == 0 ) return showTop();

    // もし新規ユーザー作成なら新規ユーザー作成ページを表示
    if( showPage == 1 ) return showNew();

    // もしユーザー削除ならユーザー削除ページを表示
    if( showPage == 2 ) return showRemove();

    // もしリストならリストページを表示
    if( showPage == 3 ) return showList();

    // もし検索なら検索ページを表示
    if( showPage == 4 ) return showSearch();

    // もしリロードならリロードページを表示
    if( showPage == 5 ) return showReload();

    return 1;
} 