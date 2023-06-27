#ifndef GLOBALS_H
#define GLOBALS_H

// グローバル変数
extern struct LIST* addressList; /* アドレスリスト */
extern int profileCount; /* プロフィール数 */
extern int aiID; /* Auto Increment 使ったら+1!! */
extern int key; /* 入力されたキー */
extern int showPage; /* 表示するページ */
// 0 -> トップページ
// 1 -> 新規ユーザー作成
// 2 -> ユーザーを削除
// 3 -> ユーザーリスト
// 4 -> 検索
// 5 -> Config リロード
extern int showPage_OP; /* 表示するページのオプション */
extern int showPage_cursor; /* カーソル */

extern char ver[10]; /* バージョン */

#endif