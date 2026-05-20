# 関数とファイルの対応整理

## main.c (神谷)
- main関数（全体制御・画面遷移）
- init_system
- show_idle_screen
- show_product_page

## product.c / product.h　(永塚)
> 商品選択・商品管理関連の関数
- select_product
- confirm_selection
- update_inventory
- replace_products

## member.c / member.h (竹下)
> 会員・ポイント管理関連の関数
- member_login
- update_points

## sales.c / sales.h (松波)
> 売上・CSV保存関連の関数
- confirm_purchase
- calculate_change
- save_sales_data
- cancel_purchase

## log.c / log.h (呉)
> ログ保存・エラー処理関連の関数
- save_log

## admin.c / admin.h (呉)
> 管理者メニューや商品入れ替え関連の関数
- admin_menu

## fault.c / fault.h (呉)
> システム故障・異常検知処理の関数
- detect_fault

---

### 備考
- 構造体（ProductInfo, SalesData, PurchaseInfoなど）は関連するヘッダファイル（例：product.h, sales.h）で定義し、必要に応じて共通ヘッダ（types.h等）にまとめても良い。
- 各.cファイルで実装し、.hファイルで関数プロトタイプ・構造体定義を記述。
- main.cは全体の流れと各機能呼び出しのみを記述し、詳細処理は各モジュールに分離。
