#include <stdio.h>
#include <string.h>

#define MAX_INVENTORY 50        // 在庫の最大数
#define MAX_INVENTORY_Type 50   // 商品の種類の最大数

typedef struct {
    int id;
    char name[50];
    int price;
} Drink;

typedef struct InventoryData {
    int product_ID;              // 商品ID
    unsigned int quantity;       // 在庫数
} Inventory;

void calculate_change(int inserted, int price);
void cashmenu();
unsigned int cash();
int inventory(char *chese_name);

/**
 * お釣り枚数の計算
 */
void calculate_change(int inserted, int price) {
    int change = inserted - price;
    if (change < 0) {
        printf("エラー: 投入金額が足りません\n");
        return;
    }
    printf("お釣り総額: %d円\n\n", change);
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
            printf("%3d円玉: %d枚\n", coin_value, count);
        }
    }
}

void cashmenu(){
    printf("\n=== 金額の投入 ===\n");
    printf("1: 100円\n");
    printf("2: 500円\n");
    printf("3: 1000円\n");
    printf("5: 確定\n");
    printf("9: キャンセル\n");
    printf("================\n");
    printf("選択してください: ");
}

 // お金投入
unsigned int cash() {
    unsigned int cashsum = 0; 
    int choice; 
    while (1){
        cashmenu();
        if (scanf("%d", &choice) != 1) {
                printf("無効な入力です。数字を入力してください。\n");
                while (getchar() != '\n'); 
                continue;
        }
        if (choice == 1){
            cashsum += 100;
            printf("100円を投入しました。(現在:%d円)\n", cashsum);
            continue;
        }
        if (choice == 2){
            cashsum += 500;
            printf("500円を投入しました。(現在:%d円)\n", cashsum);
            continue;
        }
        if (choice == 3){
            cashsum += 1000;
            printf("1000円を投入しました。(現在:%d円)\n", cashsum);
            continue;
        }
        if (choice == 5){
            printf("金額を確定しました。\n");
            printf("投入金額の合計は %d 円です。\n", cashsum);
            return cashsum; 
        }
        if (choice == 9){
            printf("キャンセルしました。(返金:%d 円)\n", cashsum);
            return 0; 
        }
        printf("無効な選択です。もう一度入力してください。\n");
    }
}


// 在庫チェック
int inventory(char *chese_name) {
    unsigned int inventoryCount = 5;           
    char inventoryName[MAX_INVENTORY_Type][10] = {"コーラ", "お茶", "水"};      

    for (int i = 0; i < MAX_INVENTORY_Type; i++) {
        if (strcmp(chese_name, inventoryName[i]) == 0) {
            if (inventoryCount > 0) {
                printf("%sの在庫チェックOK。\n", inventoryName[i]);
                return 0; 
            } else {
                printf("%sは在庫切れです。\n", inventoryName[i]);
                return 1; 
            }
        }
    }
    printf("指定された商品は存在しません。\n");
    return 1;
}

// メイン
int main() {
    Drink menu[] = {
        {1, "コーラ", 120},
        {2, "お茶",   130},
        {3, "水",     110},
    };
    int menu_size = sizeof(menu) / sizeof(menu[0]);
    unsigned int inserted_money = 0; // 投入金額の保持

    while (1) {
        printf("\n=== メインメニュー ===\n");
        printf("現在の投入金額: %d円\n", inserted_money);
        printf("1: 商品の選択へ\n");
        printf("2: 金額の投入へ\n");
        printf("9: 返金・キャンセルして終了\n");
        printf("======================\n");
        printf("選択してください: ");

        int menu_choice;
        if (scanf("%d", &menu_choice) != 1) {
            while (getchar() != '\n');
            continue;
        }

        if (menu_choice == 1) {
            printf("\n--- 商品メニュー ---\n");
            for (int i = 0; i < menu_size; i++) {
                printf("%d. %s - %d円", menu[i].id, menu[i].name, menu[i].price);
                if (inserted_money >= menu[i].price) {
                    printf(" [購入可能]\n");
                } else {
                    printf(" [残金不足]\n");
                }
            }

            printf("\n商品を選んでください (1~%d) または 0で戻る: ", menu_size);
            int product_choice;
            scanf("%d", &product_choice);

            if (product_choice >= 1 && product_choice <= menu_size) {
                Drink selected = menu[product_choice - 1];

                if (inventory(selected.name) == 0) {
                    if (inserted_money >= selected.price) {
                        printf("%s を購入しました！\n", selected.name);
                        
                        calculate_change(inserted_money, selected.price);
                        
                        inserted_money = 0; 
                    } else {
                    
                        printf("エラー: お金が足りません。お金を投入してください。\n");
                    }
                }
            }
        }
        else if (menu_choice == 2) {
            inserted_money += cash();
        }
        else if (menu_choice == 9) {
            if (inserted_money > 0) {
                printf("返金します: %d円\n", inserted_money);
            }
            printf("ご利用ありがとうございました。\n");
            break; 
        }
        else {
            printf("無効な選択です。\n");
        }
    }

    return 0;
}