#include "log.h"
#include <stdio.h>
#include <string.h>

#define LOG_FILE "log.csv"
#define MAX_RETRY 3


/**
 * 操作ログのCSV保存処理
 *
 * operation 操作内容（例: "fault", "purchase" など）
 * detail    詳細内容
 * error     エラー内容（エラーがなければ空文字列）
 * return    0=成功, 1=保存失敗
 *
 * 3回まで自動再試行し、保存に失敗した場合は1を返します。
 */
int save_log(const char* operation, const char* detail, const char* error) {
    int retry = 0;
    FILE *fp;
    while (retry < MAX_RETRY) {
        fp = fopen(LOG_FILE, "a");
        if (fp) {
            fprintf(fp, "\"%s\",\"%s\",\"%s\"\n", operation, detail, error);
            fclose(fp);
            return 0;
        }
        fprintf(stderr, "[警告] ログ保存の再試行 %d/%d に失敗しました。\n", retry + 1, MAX_RETRY);
        retry++;
    }
    fprintf(stderr, "[エラー] ログ保存は %d 回の再試行後も失敗しました。\n", MAX_RETRY);
    return 1;
}
