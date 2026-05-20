#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
int Sales_num(FILE *p_buy){
    char buf_a[1024];
    int max_zaiko = 50;
    int min_zaiko = 0;
    int total = 0;
    while (fgets(buf_a, sizeof(buf_a), p_buy) != NULL) {
        char *id_x = strtok(buf_a, ",");
        char *value_x = strtok(NULL, ",");
        char *zaiko_x = strtok(NULL, ",");
        int id_y = atoi(id_x);
        int value_y = atoi(value_x);
        int zaiko_y = atoi(zaiko_x);
        total += value_y;
    }
    printf("売上総額:%d\n", total);
}
int main(void){
    FILE * p_info;
    //商品の入れ替え記録
    p_info = fopen("商品情報.csv", "a");
    if (p_info != NULL) {
        printf("商品情報読込成功\n");
    }    
    //商品入れ替え
    printf("追加する商品の情報を入力してください\n");
    printf("商品ID 単価 在庫数(半角スペース区切り)\n");
    int p_id, p_value, p_zaiko, p_data;
    p_data = scanf("%d %d %d", &p_id, &p_value, &p_zaiko);
    if (p_data != 3){
        printf("入力エラーです\n");
        fclose(p_info);
    }
    if (p_info != NULL){
        fprintf(p_info, "%d,%d,%d\n", p_id, p_value, p_zaiko);
        printf("=====商品入れ替え完了=====\n");
    }
    fclose(p_info);
    //商品の購入履歴
    FILE * p_buy;
    p_buy = fopen("購入履歴.csv", "a");
    if (p_buy != NULL) {
        printf("購入履歴読込成功\n");
    }
    //売上計算
    Sales_num(p_buy);
    fclose(p_buy);
/*
    //商品購入の書き込み
    FILE *p_buy_1;
    p_buy_1 = fopen("購入履歴.csv", "a");
    if (p_buy_1 != NULL) {
        printf("Success\n");
    }
    fprintf(p_buy_1, "%d,%d,%d\n", p_id, p_value, p_zaiko);//p_id、p_value、p_zaikoの変数名は適宜変更
    fclose(p_buy_1);*/
    return 0;
}