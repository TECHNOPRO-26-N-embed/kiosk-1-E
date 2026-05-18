#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    int price;
} Drink;

/**
 * お釣り枚数の計算
 */
void calculate_change(int inserted, int price) {
    int change = inserted - price;
    if (change < 0) {
        printf("error: insufficient\n"); //投入金額が足りません
        return;
    }
    printf("Change: %d JPY\n\n", change); //お釣り総額
    if (change == 0) {
        printf("No change.\n");
    return;
    }
    int coins[] = {500, 100, 50, 10};
    int coin_count = sizeof(coins) / sizeof(coins[0]);
    printf("Coins dispensed:\n"); //お釣りの内訳
    for (int i = 0; i < coin_count; i++) {
        int coin_value = coins[i];
        int count = change / coin_value;
        change = change % coin_value;

        if (count > 0) {
            printf("%3d coin: %d\n", coin_value, count);
        }
    }
}
void cashmenu(){
    printf("=== 金額の投入 ===\n"); //金額の投入メニュー
    printf("1: 100円\n");
    printf("2: 500円\n");
    printf("3: 1000円\n");
    printf("5: 確定\n");
    printf("9: キャンセル\n");
    printf("================\n");
    printf("選択してください: ");
}
unsigned int cash() {
unsigned int cashsum = 0; //投入金額の合計を保持する変数
int choice; //ユーザーの選択を受け取る変数
while (1){
    cashmenu();
    if (scanf("%d", &choice) != 1) {
            printf("無効な入力です。数字を入力してください。\n");
            while (getchar() != '\n'); // 入力バッファをクリア
            continue;
    }
    if (choice == 1){
        printf("100円を投入しました。(現在:%d円)\n", cashsum + 100);
        cashsum += 100; //投入金額の合計を更新
        continue;
    }
    if (choice == 2){
        printf("500円を投入しました。(現在:%d円)\n", cashsum + 500);
        cashsum += 500; //投入金額の合計を更新
        continue;
    }
    if (choice == 3){
        printf("1000円を投入しました。(現在:%d円)\n", cashsum + 1000);
        cashsum += 1000; //投入金額の合計を更新
        continue;
    }
    if (choice == 5){
        printf("金額を確定しました。\n");
        printf("投入金額の合計は %d 円です。\n", cashsum);
        return cashsum; //投入金額の合計を返す
        break; //ループを抜けて金額の確定処理へ
    }
    if (choice == 9){
        printf("キャンセルしました。(返金:%d 円)\n", cashsum);
        cashsum = 0; //投入金額の合計をリセット
        return cashsum; //0を返す
        //メインメニューに戻る関数を後で追加
        break; //ループを抜けてキャンセル処理へ
    }
    printf("無効な選択です。もう一度入力してください。\n");
}
}


#define MAX_INVENTORY 50        // 在庫の最大数
#define MAX_INVENTORY_Type 50   // 商品の種類の最大数

typedef struct InventoryData
{
    int product_ID;              // 商品ID
    unsigned int quantity;       // 在庫数
} Inventory;


int inventory(char *chese_name) {

    // 在庫ファイルを読み込む処理
    // FILE *fp;

    // if ((fp = fopen("inventory.txt", "r")) != NULL) {
    //     // ファイルが存在する場合は在庫データを読み込む
    //     Inventory *data = fp;

    //     printf("在庫ファイルを読み込みました。\n");
    // }
    // else{
    //     // ファイルが存在しない場合はエラーメッセージを表示する
    //     printf("在庫ファイルが見つかりませんでした。\n");

    //     return 1;   // エラーコードを返す
    // }

    // fclose(fp);     // ファイルを閉じる


    unsigned int inventoryCount = 0;           // 在庫数
    char inventoryName[MAX_INVENTORY_Type][10] = {"コーラ", "お茶", "水"};      // 商品名

    // 商品を探す
    for (int i = 0; i < MAX_INVENTORY_Type; i++)
    {
        if (strcmp(chese_name, inventoryName[i]) == 0)
        {
            // 在庫を事前検査
            if (inventoryCount > 0)
            {
                // 在庫がある場合は購入処理を行う
                printf("%sを購入しました。\n", inventoryName[i]);
                inventoryCount--;
                return 0;   // 購入成功
            }
            else
            {
                // 在庫がない場合は在庫切れのメッセージを表示する
                printf("%sは在庫切れです。\n", inventoryName[i]);
                return 1;   // 在庫切れ
            }
        }
    }
}


int main() {

    while (1)
    {
        printf("=== メニュー ===\n"); //メインメニュー
        printf("1: 商品の選択へ\n");
        printf("2: 金額の投入へ\n");
        printf("9: キャンセル\n");
        printf("================\n");
        int x; //ユーザーの入力を受け取る変数
        scanf("%d", &x);
        printf("%d\n", x);

        cash();

        Drink menu[] ={
        {1, "コーラ",120},
        {2, "お茶",130},
        {3, "水",110},
        };

        int menu_size = sizeof(menu)/sizeof(menu[0]);
        int choice;
        int money = 0;

        // お金の投入
        /*printf("お金を入れてください(円):");*/
        //if (scanf("%d", &money) != 1 || money <= 0) {
            //printf("無効な金額です。終了します。\n");
            // return 1;
        //}

        printf("\n商品メニュー:\n");
        for (int i = 0; i < menu_size; i++) {
            printf("%d. %s - %d円\n", menu[i].id, menu[i].name, menu[i].price);
            if (money >= menu[i].price) {
                printf("  [購入可能]\n");
            }else{
                printf("  [残金不足]\n");
            }
        }

        // 商品の選択
        printf("\n商品を選んでください (1~%d):", menu_size);
        if (scanf("%d", &choice) ) {
        }

        char chese_name[10];
        printf("購入する商品名を入力してください: ");
        scanf("%s", chese_name);
        inventory(chese_name);

        //テスト用
        int inserted_money = 1010;
        int total_price = 210;
        printf("Inserted: %d JPY\n", inserted_money); //投入金額
        printf("Price: %d JPY\n", total_price); //商品金額
        printf("-------------------\n");
        calculate_change(inserted_money, total_price);

        FILE * fp;
        //商品の入れ替え記録
        fp = fopen("商品情報.csv", "a");
        if (fp != NULL) {
            printf("商品情報読込成功\n");
        }
        //商品入れ替え
        printf("=====商品入れ替え完了=====\n");
        fclose(fp);
        //商品の購入履歴
        FILE * fp_buy;
        fp_buy = fopen("商品情報.csv", "r");
        if (fp_buy != NULL) {
            printf("購入履歴読込成功\n");
        }
        char buf[1024];
        char* k;
        k = fgets(buf, 1024, fp_buy);
        printf("%s\n",k);
        fclose(fp_buy);
    }

    return 0;
}