#ifndef MEMBER_H
#define MEMBER_H

// 会員認証・ポイント管理処理
// 引数: member_id - 入力された会員ID
// 戻り値: 0=認証成功, 1=認証失敗
int member_login(int member_id);

// ポイント付与・利用処理
// 引数: member_id - 会員ID, add_point - 付与ポイント, use_point - 利用ポイント
// 戻り値: 0=成功, 1=残高不足, 2=更新失敗
int update_points(int member_id, int add_point, int use_point);

// 会員ログインからポイント利用確認までを順序実行する
// 戻り値: 0=成功, 1=認証失敗, 2=ポイント更新失敗, 3=入力エラー
int member_login_flow(void);

#endif // MEMBER_H