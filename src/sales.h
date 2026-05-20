#ifndef SALES_H
#define SALES_H

// --- 構造体定義 ---
typedef struct {
	int product_id;
	int quantity;
	int member_id;
	unsigned int use_point;
	unsigned int change;
} SalesData;

typedef struct {
	int product_id;
	int quantity;
	unsigned int unit_price;
	unsigned int money;
	int member_id;
	unsigned int use_point;
} PurchaseInfo;

// --- 関数プロトタイプ ---
int save_sales_data(SalesData sales);
int confirm_purchase(PurchaseInfo purchase);
unsigned int calculate_change(unsigned int money, unsigned int total_price);
int cancel_purchase(unsigned int money);

#endif // SALES_H