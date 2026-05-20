#ifndef ADMIN_H
#define ADMIN_H

/* 文字列項目の固定長（終端文字込み）。 */
// 商品名・温冷区分の最大長
#define ADMIN_NAME_MAX_LEN 64
// 温冷区分はint型（1=温, 2=冷）

// 商品数・在庫数の最大値（要件より）
#define ADMIN_MAX_PRODUCTS 50
#define ADMIN_MAX_STOCK 50
#define ADMIN_MAX_PRICE 9000

/* 管理機能で扱う商品情報。 */
typedef struct {
    int product_id;                     // 商品ID
    char name[ADMIN_NAME_MAX_LEN];      // 商品名
    unsigned int price;                 // 単価
    int stock;                          // 在庫数（最大50）
    int type;                           // 温冷区分（1=温, 2=冷）
    // 今後拡張用（ポイント・会員・ログ等）
} ProductInfo;


// 商品情報の追加/更新。戻り値: 0=成功, 1=入力/認証エラー, 2=登録上限超過
int replace_products(ProductInfo product);

// 管理者メニュー本体。戻り値: 0=正常終了, 1=認証失敗
int admin_menu(void);

// 操作ログ保存（ダミー）
void admin_save_log(const char* message);

// 管理者認証（PIN認証）
int admin_login(void);

#endif