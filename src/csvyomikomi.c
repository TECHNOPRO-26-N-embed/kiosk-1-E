#include <stdio.h>
#include <string.h>
int main(void){
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
    return 0;
}