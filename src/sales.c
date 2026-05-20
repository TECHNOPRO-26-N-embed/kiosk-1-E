
#include "sales.h"
#include "log\log.h"
#include "product.h"
#include <stdio.h>
#include <stdlib.h>

// --- 暫定: 在庫更新関数 ---
int update_inventory(int product_id, int quantity);

// 売上データを保存する関数
int save_sales_data(SalesData sales) {
    FILE *file = fopen("data/sales.csv", "a");
    if (file == NULL) {
        save_log("save_sales_data", "Failed to open sales.csv", "File error");
        return 1;
    }

    fprintf(file, "%d,%d,%d,%u,%u\n", sales.product_id, sales.quantity, sales.member_id, sales.use_point, sales.change);
    fclose(file);
    return 0;
}

// 購入確定処理
int confirm_purchase(PurchaseInfo purchase) {
    // 在庫確認
    if (update_inventory(purchase.product_id, -purchase.quantity) != 0) {
        save_log("confirm_purchase", "Stock insufficient", "Inventory error");
        return 1;
    }

    // 合計金額計算
    unsigned int total_price = (unsigned int)purchase.quantity * purchase.unit_price;

    // ポイント利用分を値引き
    if (purchase.use_point >= total_price) {
        total_price = 0;
    } else {
        total_price -= purchase.use_point;
    }

    // 投入金額確認
    if (purchase.money < total_price) {
        save_log("confirm_purchase", "Insufficient funds", "Payment error");
        return 2;
    }

    // 売上データ保存
    SalesData sales = {purchase.product_id, purchase.quantity, purchase.member_id, purchase.use_point, purchase.money - total_price};
    if (save_sales_data(sales) != 0) {
        return 3;
    }

    save_log("confirm_purchase", "Purchase confirmed", "Success");
    return 0;
}

// お釣り計算
unsigned int calculate_change(unsigned int money, unsigned int total_price) {
    return money - total_price;
}

// キャンセル時の返金処理
int cancel_purchase(unsigned int money) {
    printf("Refunded amount: %u\n", money);
    save_log("cancel_purchase", "Refund processed", "Success");
    return 0;
}