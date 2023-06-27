/*
    charset UTF-8
    ©︎copyright All Rights Reserved Yuki Tetsuka

    utilファイル
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
#include <time.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdarg.h>
#include <ctype.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096


// カスタムprintf
void cprintf(char prefix[], const char *format, ...) {

    // 初期化
    va_list arg;
    time_t t;
    struct tm *tmp;
    char time_buffer[50];
    FILE* fp;

    // 現在時刻を取得する
    t = time(NULL);
    tmp = localtime(&t);

    // 時刻を文字列に変換する
    strftime(time_buffer, sizeof(time_buffer), "[%H:%M:%S] ", tmp);

    // 時間
    printf("%s", time_buffer);

    // プレフィックス
    printf("[%s] ", prefix);

    // argを初期化
    va_start(arg, format);

    // 可変長引数の出力
    vfprintf(stdout, format, arg);

    // argをクリア
    va_end(arg);

    // ログファイルがないなら生成
    if ((fp = fopen("address.log", "r")) == NULL) {
        fp = fopen("address.log", "w");
        fclose(fp);
    }

    // ファイルを開く
    fp = fopen("address.log", "a");

    // 時間
    fprintf(fp, "%s", time_buffer);

    // プレフィックス
    fprintf(fp, "[%s] ", prefix);

    // argを初期化
    va_start(arg, format);

    // 可変長引数の出力
    vfprintf(fp, format, arg);

    // argをクリア
    va_end(arg);

    // ファイルを閉じる
    fclose(fp);
}


// 画面のリセット
void clearView(){

#ifdef _WIN32
    system("cls");
#else
    // system("clear");
    system("reset");
#endif
}


// host名に接続できるか確認
int checkInternet(const char *url) {

    // 初期化
    int sockfd;
    struct addrinfo hints, *res, *p;
    int status;
    char ipstr[INET6_ADDRSTRLEN];

    // hintsのメモリをゼロに初期化
    memset(&hints, 0, sizeof hints);

    // IPv4 IPv6 OK
    hints.ai_family = AF_UNSPEC;

    // TCP
    hints.ai_socktype = SOCK_STREAM;

    // IPに変換
    if ((status = getaddrinfo(url, "http", &hints, &res)) != 0) {

        // エラー発生
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        return 0;
    }

    // 各情報を取り出す
    for (p = res; p != NULL; p = p->ai_next) {

        // 初期化
        void *addr;
        char *ipver;

        // IPv4 IPv6か
        if (p->ai_family == AF_INET) {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        } else {
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }

        // ipstrに文字列で保存
        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
        cprintf("InterNet", "%s: %s\n", ipver, ipstr);

        // ソケットを作成
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (sockfd == -1) {
            perror("socket error");
            continue;
        }

        // ソケットを使ってURLに接続
        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            perror("connect error");

            // ソケットを閉じる
            close(sockfd);
            continue;
        }

        // ソケットを閉じる
        close(sockfd);

        // メモリの解放
        freeaddrinfo(res);
        return 1;
    }

    // メモリの解放
    freeaddrinfo(res);
    return 0;
}


int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

// valueを取得
int getValue(const char *json, const char *key, char *value, int value_size) {

    // 検索
    const char *start = strstr(json, key);
    if (start == NULL)
        return 0;

    // keyの後の[: ]をスキップ
    start += strlen(key) + 2;

    // 検索
    const char *end = strchr(start, ',');
    if (end == NULL) {
        end = strchr(start, '}');
        if (end == NULL)
            return 0;
    }


    int length = end - start;
    if (length >= value_size)
        return 0;

    // 複製
    strncpy(value, start, length);
    value[length] = '\0';

    return 1;
}

// メールアドレスの有効性を確認する
// -1 -> エラー
// 0 -> 無効なアドレス
// 1 -> 正常
// 2 -> 構文のみOK 
int checkMail(char email[64]){

    char request[100];

    int mail_status = 0;
    int mail_syntax = 0;

    strcpy(request, "GET /emailCheck/");
    strcat(request, email);
    strcat(request, " HTTP/1.1\r\nHost: api.itsystem-lab.com\r\n\r\n");

    char *url = "api.itsystem-lab.com";

    // 初期化
    int sockfd;
    struct addrinfo hints, *res, *p;
    int status;
    char ipstr[INET6_ADDRSTRLEN];

    // hintsのメモリをゼロに初期化
    memset(&hints, 0, sizeof hints);

    // IPv4 IPv6 OK
    hints.ai_family = AF_UNSPEC;

    // TCP
    hints.ai_socktype = SOCK_STREAM;

    // IPに変換
    if ((status = getaddrinfo(url, "http", &hints, &res)) != 0) {

        // エラー発生
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        return -1;
    }

    // 各情報を取り出す
    for (p = res; p != NULL; p = p->ai_next) {

        // 初期化
        void *addr;
        char *ipver;

        // IPv4 IPv6か
        if (p->ai_family == AF_INET) {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        } else {
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }

        // ipstrに文字列で保存
        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);

        // ソケットを作成
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (sockfd == -1) {
            perror("socket error");
            continue;
        }

        // ソケットを使ってURLに接続
        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            perror("connect error");

            // ソケットを閉じる
            close(sockfd);
            continue;
        }

        // リクエストを送信
        if (send(sockfd, request, strlen(request), 0) < 0) {
            perror("Send request failed");
            continue;
        }

        // レスポンスを受信
        char response_buffer[BUFFER_SIZE];

        // response_bufferのメモリをゼロに初期化
        memset(response_buffer, 0, sizeof(response_buffer));

        ssize_t bytes_received;

        // ヘッダーの終了位置
        int header_end = -1;

        while ((bytes_received = recv(sockfd, response_buffer, sizeof(response_buffer) - 1, 0)) > 0) {

            // レスポンスのヘッダーとボディを切り分ける
            response_buffer[bytes_received] = '\0';
            char *header_body_separator = "\r\n\r\n";

            // header_body_separatorを検索
            char *body_start = strstr(response_buffer, header_body_separator);

            if (body_start != NULL) {
                header_end = (int)(body_start - response_buffer) + strlen(header_body_separator);
                break;
            }

            // response_bufferのメモリをゼロに初期化
            memset(response_buffer, 0, sizeof(response_buffer));
        }

        // 応答がない
        if (bytes_received < 0) {
            perror("Receive response failed");

            break;
        }

        // ボディを取得
        if (header_end != -1) {

            char *body = response_buffer + header_end;

            char _status[] = "false";
            char _syntax[] = "false";

            // 有効性を取得
            getValue(body, "\"status\"", _status, sizeof(_status));
            if(strcmp("true", _status) == 0){
                mail_status = 1;
            }
            else if(strcmp("false", _status) == 0){
                mail_status = 0;
            }
            else{
                return -1;
            }

            // 構文チェックを取得
            getValue(body, "\"syntax\"", _syntax, sizeof(_syntax));
            if(strcmp("true", _syntax) == 0){
                mail_syntax = 1;
            }
            else if(strcmp("false", _syntax) == 0){
                mail_syntax = 0;
            }
            else{
                return -1;
            }
        }

        // ソケットを閉じる
        close(sockfd);

        // メモリの解放
        freeaddrinfo(res);

        if( mail_status != 0 ) return 1;
        if( mail_syntax != 0 ) return 2;

        return 0;
    }

    // メモリの解放
    freeaddrinfo(res);
    return -1;
}

// 入力のバッファをクリアする
void clearInput(){
    // \nを読み捨てる
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// 文字列が数字か確認
int isStringNumeric(const char* str) {

    // 終了コードまで繰り返す
    for (int i = 0; str[i] != '\0'; i++) {

        // もし数字じゃないなら
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

// カーソルを非表示
void hideCursor() {
    printf("\e[?25l");
}

// カーソルを表示
void showCursor() {
    printf("\e[?25h");
}