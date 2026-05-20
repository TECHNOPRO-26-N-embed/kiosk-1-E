#ifndef PRODUCT_H
#define PRODUCT_H

// 商品名の最大長
#define PRODUCT_NAME_LENGTH 64
// 温冷区分の最大長
#define PRODUCT_TYPE_LENGTH 8
// 商品の最大登録数
#define MAX_PRODUCTS 20

// 商品情報を表す構造体
typedef struct {
    int product_id;                        // 商品ID
    char name[PRODUCT_NAME_LENGTH];        // 商品名
    unsigned int price;                    // 単価
    int stock;                             // 在庫数
    char type[PRODUCT_TYPE_LENGTH];        // 温冷区分（"冷"や"温"など）
} ProductInfo;

// 商品一覧を表示し、ユーザーに商品IDを選択させる
// 戻り値: 商品ID, キャンセル時-1, 入力エラー時-2
int select_product(void);

// 商品IDと数量の妥当性を確認する
// 戻り値: 0=OK, 1=エラー（在庫不足や不正な数量）
int confirm_selection(int product_id, int quantity);

// 在庫数を増減させる（正で入荷、負で販売）
// 戻り値: 0=成功, 1=在庫不足, 2=商品ID不正
int update_inventory(int product_id, int quantity);

// 商品情報の更新または新規追加
// 戻り値: 0=成功, 1=入力エラー, 2=商品数上限
int replace_products(ProductInfo product);

#endif
