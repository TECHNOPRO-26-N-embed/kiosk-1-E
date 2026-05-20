#ifndef LOG_H
#define LOG_H

// 操作ログのCSV保存処理（3回まで自動再試行）
// 引数: operation - 操作内容, detail - 詳細, error - エラー内容
// 戻り値: 0=成功, 1=保存失敗
int save_log(const char* operation, const char* detail, const char* error);

#endif // LOG_H
