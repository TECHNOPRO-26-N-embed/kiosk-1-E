#include <stdio.h>

void calculate_change(int inserted, int price);

/*
int main(void) {
    //テスト用
    int inserted_money = 1010;
    int total_price = 210;              // お釣り: 800円

    printf("投入金額: %d 円\n", inserted_money); 
    printf("商品金額: %d 円\n", total_price); 
    printf("-------------------\n");

    calculate_change(inserted_money, total_price); 

    return 0;
}
*/

/**
 * お釣り枚数の計算
 */
void calculate_change(int inserted, int price) {
    int change = inserted - price;

    if (change < 0) {
        printf("エラー: 投入金額が足りません\n");
        return;
    }

    printf("お釣り総額: %d 円\n\n", change);

    if (change == 0) {
        printf("お釣りはありません。\n");
    return;
    }

    int coins[] = {500, 100, 50, 10};
    int coin_count = sizeof(coins) / sizeof(coins[0]);

    printf("お釣りの内訳:\n");

    for (int i = 0; i < coin_count; i++) {
        int coin_value = coins[i];
        int count = change / coin_value;
        change = change % coin_value;

        if (count > 0) {
            printf("%3d 円玉: %d 枚\n", coin_value, count);
        }
    }
}