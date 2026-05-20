#include "admin.h"

#include <stdio.h>
#include <string.h>

#define ADMIN_INVENTORY_SIZE 16

/* 管理機能で扱う商品情報（簡易版・メモリ保持）。 */
static ProductInfo inventory[ADMIN_INVENTORY_SIZE];
static int inventory_count = 0;
static int admin_logged_in = 0;

/* product_id に対応する配列インデックスを返す。未検出は -1。 */
static int find_product_index(int product_id) {
	int i;

	for (i = 0; i < inventory_count; ++i) {
		if (inventory[i].product_id == product_id) {
			return i;
		}
	}
	return -1;
}

/* 商品入れ替え入力の最小バリデーション。 */
static int validate_product(ProductInfo product) {
	if (product.product_id <= 0) {
		return 0;
	}
	if (product.name[0] == '\0') {
		return 0;
	}
	if (product.price == 0) {
		return 0;
	}
	if (product.stock < 0) {
		return 0;
	}
	if (product.type[0] == '\0') {
		return 0;
	}
	return 1;
}

/* 符号付き整数を読み取る。成功時 1、失敗時 0。 */
static int read_int(const char *prompt, int *out_value) {
	int scanned;

	if (prompt != NULL) {
		printf("%s", prompt);
	}

	scanned = scanf("%d", out_value);
	if (scanned != 1) {
		int ch;

		while ((ch = getchar()) != '\n' && ch != EOF) {
			;
		}
		return 0;
	}
	return 1;
}

/* 符号なし整数を読み取る。成功時 1、失敗時 0。 */
static int read_uint(const char *prompt, unsigned int *out_value) {
	int scanned;

	if (prompt != NULL) {
		printf("%s", prompt);
	}

	scanned = scanf("%u", out_value);
	if (scanned != 1) {
		int ch;

		while ((ch = getchar()) != '\n' && ch != EOF) {
			;
		}
		return 0;
	}
	return 1;
}

/* 1行文字列を読み取り、末尾改行を除去。空文字はエラー扱い。 */
static int read_string(const char *prompt, char *buffer, size_t buffer_size) {
	size_t length;

	if (prompt != NULL) {
		printf("%s", prompt);
	}

	if (fgets(buffer, (int)buffer_size, stdin) == NULL) {
		return 0;
	}

	length = strlen(buffer);
	if (length > 0 && buffer[length - 1] == '\n') {
		buffer[length - 1] = '\0';
	}

	return buffer[0] != '\0';
}

/* 次の入力が崩れないよう、stdin の行末まで破棄する。 */
static void clear_input_line(void) {
	int ch;

	while ((ch = getchar()) != '\n' && ch != EOF) {
		;
	}
}

/* CLI 動作確認用の簡易管理者認証。 */
static int admin_login(void) {
	int pin;

	if (admin_logged_in) {
		return 1;
	}

	if (!read_int("管理者PINを入力してください (1234): ", &pin)) {
		printf("入力が不正です。\n");
		return 0;
	}

	if (pin != 1234) {
		printf("認証に失敗しました。\n");
		return 0;
	}

	admin_logged_in = 1;
	printf("管理者ログインに成功しました。\n");
	return 1;
}

/* メモリ上の商品一覧を表示する。 */
static void show_inventory(void) {
	int i;

	printf("\n--- 商品一覧 ---\n");
	if (inventory_count == 0) {
		printf("登録されている商品はありません。\n");
		return;
	}

	for (i = 0; i < inventory_count; ++i) {
		printf(
			"商品ID:%d 商品名:%s 価格:%u 在庫:%d 温冷区分:%s\n",
			inventory[i].product_id,
			inventory[i].name,
			inventory[i].price,
			inventory[i].stock,
			inventory[i].type
		);
	}
}

/* システム状態表示（将来拡張用のプレースホルダ）。 */
static void show_system_status(void) {
	printf("\n--- システム状態 ---\n");
	printf("商品登録数: %d/%d\n", inventory_count, ADMIN_INVENTORY_SIZE);
	printf("管理者ログイン状態: %s\n", admin_logged_in ? "ログイン中" : "未ログイン");
}

/* ログ閲覧機能（将来のログモジュール連携用）。 */
static void show_logs(void) {
	printf("\n--- ログ閲覧 ---\n");
	printf("ログ閲覧機能は未接続です。\n");
}

/*
 * 商品IDが既存なら上書きし、未登録なら末尾に追加する。
 * 戻り値: 0=成功, 1=認証/入力エラー, 2=登録上限超過。
 */
int replace_products(ProductInfo product) {
	int index;

	if (!admin_logged_in) {
		return 1;
	}

	if (!validate_product(product)) {
		return 1;
	}

	index = find_product_index(product.product_id);
	if (index >= 0) {
		inventory[index] = product;
		return 0;
	}

	if (inventory_count >= ADMIN_INVENTORY_SIZE) {
		return 2;
	}

	inventory[inventory_count] = product;
	++inventory_count;
	return 0;
}

/*
 * 管理者メニューのメインループ。
 * 戻り値: 0=正常終了, 1=認証失敗。
 */
int admin_menu(void) {
	int menu;

	if (!admin_login()) {
		return 1;
	}

	for (;;) {
		printf("\n=== 管理者メニュー ===\n");
		printf("1. 商品入れ替え\n");
		printf("2. システム状態確認\n");
		printf("3. ログ閲覧\n");
		printf("0. 終了\n");

		if (!read_int("メニュー番号を選択してください: ", &menu)) {
			printf("メニュー入力が不正です。\n");
			continue;
		}

		if (menu == 0) {
			return 0;
		}

		if (menu == 1) {
			ProductInfo product;

			/* 数値入力後に残る改行を破棄してから文字列入力を行う。 */
			clear_input_line();

			if (!read_int("商品ID: ", &product.product_id)) {
				printf("商品IDの入力が不正です。\n");
				continue;
			}

			clear_input_line();
			if (!read_string("商品名: ", product.name, sizeof(product.name))) {
				printf("商品名の入力が不正です。\n");
				continue;
			}

			if (!read_uint("価格: ", &product.price)) {
				printf("価格の入力が不正です。\n");
				continue;
			}

			if (!read_int("在庫数: ", &product.stock)) {
				printf("在庫数の入力が不正です。\n");
				continue;
			}

			clear_input_line();
			if (!read_string("温冷区分 (温/冷): ", product.type, sizeof(product.type))) {
				printf("温冷区分の入力が不正です。\n");
				continue;
			}

			if (replace_products(product) == 0) {
				printf("商品情報を更新しました。\n");
				show_inventory();
			} else {
				printf("商品情報の更新に失敗しました。\n");
			}
		} else if (menu == 2) {
			show_system_status();
		} else if (menu == 3) {
			show_logs();
		} else {
			printf("存在しないメニューです。\n");
		}
	}
}