#ifndef ADMIN_H
#define ADMIN_H

/* 文字列項目の固定長（終端文字込み）。 */
#define ADMIN_NAME_MAX_LEN 64
#define ADMIN_TYPE_MAX_LEN 8

/* 管理機能で扱う商品情報。 */
typedef struct {
    int product_id;                     /* 商品ID */
    char name[ADMIN_NAME_MAX_LEN];      /* 商品名 */
    unsigned int price;                 /* 単価 */
    int stock;                          /* 在庫数 */
    char type[ADMIN_TYPE_MAX_LEN];      /* 温冷区分 */
} ProductInfo;

/* 商品情報の追加/更新。戻り値: 0=成功, 1=入力/認証エラー, 2=登録上限超過 */
int replace_products(ProductInfo product);
/* 管理者メニュー本体。戻り値: 0=正常終了, 1=認証失敗 */
int admin_menu(void);

#endif