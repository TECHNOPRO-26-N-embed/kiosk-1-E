#include <stdio.h>

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


int main() {
    cash();
    return 0;
}