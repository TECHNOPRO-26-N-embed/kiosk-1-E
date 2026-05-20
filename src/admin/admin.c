#include "admin.h"

#include <stdio.h>
#include <string.h>

#define ADMIN_INVENTORY_SIZE ADMIN_MAX_PRODUCTS

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

// 商品入れ替え入力の最小バリデーション（要件反映）
static int validate_product(ProductInfo product) {
	if (product.product_id <= 0) return 0;
	if (product.name[0] == '\0') return 0;
	if (product.price == 0 || product.price > ADMIN_MAX_PRICE) return 0;
	if (product.stock < 0 || product.stock > ADMIN_MAX_STOCK) return 0;
	if (!(product.type == 1 || product.type == 2)) return 0; // 1=温, 2=冷
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

// 管理者認証（PIN認証）
int admin_login(void) {
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
		const char *type_str = "-";
		if (inventory[i].type == 1) {
			type_str = "温";
		} else if (inventory[i].type == 2) {
			type_str = "冷";
		}

		printf(
			"商品ID:%d 商品名:%s 価格:%u 在庫:%d 温冷区分:%s\n",
			inventory[i].product_id,
			inventory[i].name,
			inventory[i].price,
			inventory[i].stock,
			type_str
		);
	}
}

/* システム状態表示（将来拡張用のプレースホルダ）。 */
static void show_system_status(void) {
	printf("\n--- システム状態 ---\n");
	printf("商品登録数: %d/%d\n", inventory_count, ADMIN_INVENTORY_SIZE);
	printf("管理者ログイン状態: %s\n", admin_logged_in ? "ログイン中" : "未ログイン");
}

// 操作ログ保存（ダミー）
void admin_save_log(const char* message) {
	// TODO: CSVファイル等にログ保存
	printf("[LOG] %s\n", message);
}

// ログ閲覧機能（将来のログモジュール連携用）
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
		admin_save_log("認証されていない操作");
		return 1;
	}

	if (!validate_product(product)) {
		admin_save_log("商品情報バリデーションエラー");
		return 1;
	}
	
    index = find_product_index(product.product_id);
	if (index >= 0) {
		inventory[index] = product;
		admin_save_log("商品情報を上書き");
		return 0;
	}
	
    if (inventory_count >= ADMIN_INVENTORY_SIZE) {
		admin_save_log("商品登録上限超過");
		return 2;
	}
	
    inventory[inventory_count] = product;
	++inventory_count;
	admin_save_log("商品情報を新規登録");
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

			// 商品ID 入力
			do {
				clear_input_line();
				if (!read_int("商品ID: ", &product.product_id) || product.product_id <= 0) {
					printf("商品IDの入力が不正です。正の整数を入力してください。\n");
				} else {
					break;
				}
			} while (1);

			// 商品名 入力
			do {
				clear_input_line();
				if (!read_string("商品名: ", product.name, sizeof(product.name)) || product.name[0] == '\0') {
					printf("商品名の入力が不正です。空欄不可です。\n");
				} else {
					break;
				}
			} while (1);

			// 価格 入力
			do {
				if (!read_uint("価格: ", &product.price) || product.price == 0 || product.price > ADMIN_MAX_PRICE) {
					printf("価格の入力が不正です。1～%dの範囲で入力してください。\n", ADMIN_MAX_PRICE);
				} else {
					break;
				}
			} while (1);

			// 在庫数 入力
			do {
				if (!read_int("在庫数: ", &product.stock) || product.stock < 0 || product.stock > ADMIN_MAX_STOCK) {
					printf("在庫数の入力が不正です。0～%dの範囲で入力してください。\n", ADMIN_MAX_STOCK);
				} else {
					break;
				}
			} while (1);

			// 温冷区分 入力
			do {
				printf("温冷区分を選択してください (1:温, 2:冷): ");
				if (!read_int(NULL, &product.type) || !(product.type == 1 || product.type == 2)) {
					printf("温冷区分の入力が不正です。1（温）または2（冷）を入力してください。\n");
				} else {
					break;
				}
			} while (1);

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