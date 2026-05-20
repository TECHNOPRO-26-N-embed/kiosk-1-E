
// main.c - 司令塔（全体制御・画面遷移・外部呼び出しのみ）
#include <stdio.h>
#include "admin\admin.h"  // 管理者メニューのヘッダーファイル
#include "member_login\member.h" // 会員認証・ポイント管理のヘッダーファイル

// --- main.cで実装する関数 ---
int init_system(void) {
    // システムの初期化（データ読込・初期設定・ログ保存など）
    printf("システムを初期化しました。\n");
    return 0;
}

void show_idle_screen(void) {
    printf("\n====================================\n");
    printf(" Vending Machine v1.0\n");
    printf("====================================\n");
    printf("1. 購入を開始\n");
    printf("2. 管理者メニュー\n");
    printf("9. 終了\n");
}

void show_product_page(void) {
    printf("\n------------- 商品一覧 -------------\n");
    printf("（ここに商品一覧を表示）\n");
    printf("------------------------------------\n");
}

// --- 外部実装の関数プロトタイプ宣言（コメントで明示） ---
// 商品選択・確認・金額入力・購入確定・キャンセル・在庫更新・売上保存・ログ保存・会員認証・ポイント管理・商品入れ替え・故障検知・管理者メニュー

// これらは product.c, sales.c, log.c, member.c, admin.c, fault.c などで実装
int select_product(void);        // 商品選択（product.c）
int confirm_selection(int, int); // 商品選択内容確認（product.c）
int input_money(void);           // 金額投入（sales.c）
int confirm_purchase(/*PurchaseInfo*/ void*); // 購入確定（sales.c）
int cancel_purchase(unsigned int); // キャンセル返金（sales.c）
int admin_menu(void);            // 管理者メニュー（admin.c）
// --- 会員認証・ポイント管理（member.c）---
int member_login(int member_id); // 会員認証
int update_points(int member_id, int add_point, int use_point); // ポイント付与・利用
int member_login_flow(void); // 会員認証＋ポイント利用まとめて

int main(void) {
	int menu;

	// システム初期化
	if (init_system() != 0) {
		printf("システムの初期化に失敗しました。\n");
		return 1;
	}

	// メインループ
	while (1) {
		show_idle_screen();
		printf("選択してください: ");
		if (scanf("%d", &menu) != 1) {
			printf("入力エラーです。\n");
			while (getchar() != '\n');
			continue;
		}

		if (menu == 1) {
			// --- 商品購入フロー ---
			show_product_page();
			// ↓以下は外部実装（product.c, sales.c, member.c等）
			// int product_id = select_product();
			// if (product_id < 0) { ... キャンセル・エラー処理 ... }
			// int quantity = ...; // 数量入力（外部実装）
			// int confirm = confirm_selection(product_id, quantity);
			// if (confirm != 0) { ... キャンセル・エラー処理 ... }
			int money = input_money();
			// if (money <= 0) { cancel_purchase(money); continue; }

			// --- 会員認証・ポイント利用 ---
			// 例1: 個別呼び出し
			// int member_id = ...; // 会員ID入力（外部実装 or scanf等）
			// if (member_login(member_id) != 0) { ... エラー処理 ... }
			// int add_point = ...; // 付与ポイント計算
			// int use_point = ...; // 利用ポイント入力
			// if (update_points(member_id, add_point, use_point) != 0) { ... エラー処理 ... }
			// 例2: まとめて
			// member_login_flow();

			// PurchaseInfo info = ...; // 構造体生成（外部実装）
			// int result = confirm_purchase(&info);
			// if (result != 0) { ... エラー・返金処理 ... }
		} else if (menu == 2) {
			// --- 管理者メニュー ---
			admin_menu(); // 外部実装（admin.c）
		} else if (menu == 9) {
			printf("システムを終了します。\n");
			break;
		} else {
			printf("無効なメニューです。\n");
		}
	}

	return 0;
}



// 金額投入処理（1円玉以外の硬貨・1000円札・会員ポイントのみ受付）
int input_money(void) {
	int total = 0;
	int choice = 0;
	int amount = 0;
	printf("\n--- 金額投入 ---\n");
	while (1) {
		printf("現在の投入金額: %d円\n", total);
		printf("投入するものを選択してください:\n");
		printf("1. 500円玉\n");
		printf("2. 100円玉\n");
		printf("3. 50円玉\n");
		printf("4. 10円玉\n");
		printf("5. 1000円札\n");
		printf("6. 会員ポイントを利用\n");
		printf("0. 投入終了\n");
		printf("選択: ");
		if (scanf("%d", &choice) != 1) {
			printf("入力エラーです。\n");
			while (getchar() != '\n');
			continue;
		}
		if (choice == 0) {
			break;
		} else if (choice == 1) {
			total += 500;
		} else if (choice == 2) {
			total += 100;
		} else if (choice == 3) {
			total += 50;
		} else if (choice == 4) {
			total += 10;
		} else if (choice == 5) {
			total += 1000;
		} else if (choice == 6) {
			printf("利用するポイント数を入力してください: ");
			if (scanf("%d", &amount) != 1 || amount < 0) {
				printf("正しい値を入力してください。\n");
				while (getchar() != '\n');
				continue;
			}
			total += amount;
		} else {
			printf("無効な選択です。\n");
		}
	}
	printf("合計投入金額: %d円\n", total);
	return total;
}