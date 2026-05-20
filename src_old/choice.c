#include <stdio.h>
typedef struct {
int id;
char name[50];
int price;
} Drink;
int main() {
Drink menu[] ={
{1, "コーラ",120},
{2, "お茶",130},
{3, "水",110},
{1, "コーラ",120},
{2, "お茶",130},
{3, "水",110},
{4, "コーヒー",150},
{5, "サイダー",140},
{6, "スポーツドリンク",160},
{7, "エナジードリンク",200},
{8, "紅茶",130},
{9, "ミルクティー",120},
{10, "フルーツジュース",180},
{11, "リンゴジュース",180},
{12, "オレンジジュース",180},
{13, "グレープジュース",180},
{14, "いちごミルク",180},
{15, "牛乳",180},
{16, "ココア",180},
{17, "コンポタージュ",180}
};
int menu_size = sizeof(menu)/sizeof(menu[0]);
int choice;
int money = 0;
// お金の投入
/*printf("お金を入れてください(円):");
  if (scanf("%d", &money) != 1 || money <= 0) {
    printf("無効な金額です。終了します。\n");
    return 1;
  }*/
printf("\n商品メニュー:\n");
for (int i = 0; i < menu_size; i++) {
printf("%d. %s - %d円\n", menu[i].id, menu[i].name, menu[i].price);
if (money >= menu[i].price) {
printf(" [購入可能]\n");
}else{
printf(" [残金不足]\n");
}
}

// 商品の選択
printf("\n商品を選んでください (1~%d):", menu_size);
if (scanf("%d", &choice) ) {

}
return 0;
}