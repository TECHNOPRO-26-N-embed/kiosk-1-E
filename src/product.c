

#include "product.h"
#include <stdio.h>
#include <string.h>

// 商品データはこのモジュール内で静的に保持する
static Product g_products[MAX_PRODUCTS]; // 商品情報配列
static int g_product_count = 0;              // 商品数

// scanf失敗時に入力バッファの残りを読み捨てる関数
static void clear_stdin_line(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        // 何もしない（バッファクリア）
    }
}

// 商品IDから配列インデックスを検索する
// 見つからなければ-1を返す
static int find_product_index_by_id(int product_id) {
    int i;
    for (i = 0; i < g_product_count; i++) {
        if (g_products[i].product_id == product_id) {
            return i;
        }
    }
    return -1;
}

// 初期商品データを1回だけセットする
// 既に初期化済みなら何もしない
static void initialize_default_products(void) {
    if (g_product_count != 0) {
        return;
    }
    // サンプル商品データを登録
    g_products[0].product_id = 1;
    strcpy(g_products[0].name, "コーラ");
    g_products[0].price = 120;
    g_products[0].stock = 10;
    strcpy(g_products[0].type, "冷");

    g_products[1].product_id = 2;
    strcpy(g_products[1].name, "お茶");
    g_products[1].price = 130;
    g_products[1].stock = 8;
    strcpy(g_products[1].type, "温");

    g_products[2].product_id = 3;
    strcpy(g_products[2].name, "水");
    g_products[2].price = 100;
    g_products[2].stock = 15;
    strcpy(g_products[2].type, "冷");

    g_products[3].product_id = 4;
    strcpy(g_products[3].name, "コーヒー");
    g_products[3].price = 150;
    g_products[3].stock = 5;
    strcpy(g_products[3].type, "温");

    g_products[4].product_id = 5;
    strcpy(g_products[4].name, "紅茶");
    g_products[4].price = 140;
    g_products[4].stock = 7;
    strcpy(g_products[4].type, "温");

    g_products[5].product_id = 6;
    strcpy(g_products[5].name, "スポーツドリンク");
    g_products[5].price = 160;
    g_products[5].stock = 12;
    strcpy(g_products[5].type, "冷");

    g_products[6].product_id = 7;
    strcpy(g_products[6].name, "エナジードリンク");
    g_products[6].price = 200;
    g_products[6].stock = 6;
    strcpy(g_products[6].type, "冷");

    g_products[7].product_id = 8;
    strcpy(g_products[7].name, "ミルク");
    g_products[7].price = 180;
    g_products[7].stock = 9;
    strcpy(g_products[7].type, "冷");

    g_products[8].product_id = 9;
    strcpy(g_products[8].name, "オレンジジュース");
    g_products[8].price = 170;
    g_products[8].stock = 10;
    strcpy(g_products[8].type, "冷");

    g_products[9].product_id = 10;
    strcpy(g_products[9].name, "リンゴジュース");
    g_products[9].price = 170;
    g_products[9].stock = 10;
    strcpy(g_products[9].type, "冷");

    g_products[10].product_id = 11;
    strcpy(g_products[10].name, "グレープジュース");
    g_products[10].price = 170;
    g_products[10].stock = 10;
    strcpy(g_products[10].type, "冷");

    g_products[11].product_id = 12;
    strcpy(g_products[11].name, "いちごミルク");
    g_products[11].price = 180;
    g_products[11].stock = 8;
    strcpy(g_products[11].type, "冷");

    g_products[12].product_id = 13;
    strcpy(g_products[12].name, "炭酸水");
    g_products[12].price = 110;
    g_products[12].stock = 20;
    strcpy(g_products[12].type, "冷");

    g_products[13].product_id = 14;
    strcpy(g_products[13].name, "ホットチョコレート");
    g_products[13].price = 190;
    g_products[13].stock = 5;
    strcpy(g_products[13].type, "温");

    g_products[14].product_id = 15;
    strcpy(g_products[14].name, "抹茶ラテ");
    g_products[14].price = 200;
    g_products[14].stock = 4;
    strcpy(g_products[14].type, "温");

    g_product_count = 15;
}

// 商品一覧を表示し、ユーザーに商品IDを入力させて返す
// 戻り値: 商品ID, キャンセル時-1, 入力エラー時-2
int select_product(void) {
    int selected_id;
    int i;

    initialize_default_products(); // 必要なら初期化

    printf("\n=== 商品一覧 ===\n");
    for (i = 0; i < g_product_count; i++) {
        printf("ID:%d 名前:%s 価格:%u 在庫:%d 区分:%s\n",
               g_products[i].product_id,
               g_products[i].name,
               g_products[i].price,
               g_products[i].stock,
               g_products[i].type);
    }
    printf("商品IDを選択してください (0:キャンセル): ");

    if (scanf("%d", &selected_id) != 1) {
        clear_stdin_line(); // 入力エラー時バッファクリア
        return -2;
    }

    clear_stdin_line();

    if (selected_id == 0) {
        return -1; // キャンセル
    }

    if (find_product_index_by_id(selected_id) < 0) {
        return -2; // 存在しないID
    }

    return selected_id;
}

// 商品IDと数量の妥当性を確認する
// 戻り値: 0=OK, 1=エラー（在庫不足や不正な数量）
int confirm_selection(int product_id) {
    int index;

    initialize_default_products();

    index = find_product_index_by_id(product_id);
    if (index < 0) {
        return 1; // 商品ID不正
    }

    //if (quantity <= 0 || quantity > g_products[index].stock) {
    //    return 1; // 数量不正または在庫不足
    //}

    printf("選択内容: ID:%d\t名前:%s\t合計:%u円\n",
           g_products[index].product_id,
           g_products[index].name,
    
           g_products[index].price);

    return 0;
}

// 在庫数を増減させる。結果がマイナスになる場合は失敗
// quantity: 正で入荷、負で販売
// 戻り値: 0=成功, 1=在庫不足, 2=商品ID不正
int update_inventory(int product_id, int quantity) {
    int index;
    int new_stock;

    initialize_default_products();

    index = find_product_index_by_id(product_id);
    if (index < 0) {
        return 2; // 商品ID不正
    }

    new_stock = g_products[index].stock + quantity;
    if (new_stock < 0) {
        return 1; // 在庫不足
    }

    g_products[index].stock = new_stock;
    return 0;
}

// 商品情報の更新または新規追加
// 戻り値: 0=成功, 1=入力エラー, 2=商品数上限
// int replace_products(Product product) {
//     int index;

//     initialize_default_products();

//     // 入力値チェック
//     if (product.product_id <= 0 || product.price == 0 || product.stock < 0) {
//         return 1;
//     }
//     if (product.name[0] == '\0' || product.type[0] == '\0') {
//         return 1;
//     }

//     index = find_product_index_by_id(product.product_id);

//     if (index >= 0) {
//         // 既存商品を上書き
//         g_products[index] = product;
//         return 0;
//     }

//     if (g_product_count >= MAX_PRODUCTS) {
//         return 2; // 商品数上限
//     }

//     // 新規商品を追加
//     g_products[g_product_count] = product;
//     g_product_count++;
//     return 0;
// }
