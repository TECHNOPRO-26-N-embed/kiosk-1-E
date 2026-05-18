#include <stdio.h>
#include <string.h>

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

    char chese_name[10];
    
    printf("購入する商品名を入力してください: ");
    scanf("%s", chese_name);

    inventory(chese_name);

    // 商品がない場合は再度入力を促す
    // while (inventory(chese_name) != 0)
    // {
    //     printf("購入する商品名を入力してください: ");
    //     scanf("%s", chese_name);
        
    //     inventory(chese_name);
    // }

    return 0;
}