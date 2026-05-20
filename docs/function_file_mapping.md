# 関数とファイルの対応整理

## main.c
- main関数（全体制御・画面遷移）
- init_system
- show_idle_screen
- show_product_page

## product.c / product.h
- select_product
- confirm_selection
- update_inventory
- replace_products

## member.c / member.h
- member_login
- update_points

## sales.c / sales.h
- confirm_purchase
- calculate_change
- save_sales_data
- cancel_purchase

## log.c / log.h
- save_log

## admin.c / admin.h
- admin_menu

## fault.c / fault.h
- detect_fault

---

### 備考
- 構造体（ProductInfo, SalesData, PurchaseInfoなど）は関連するヘッダファイル（例：product.h, sales.h）で定義し、必要に応じて共通ヘッダ（types.h等）にまとめても良い。
- 各.cファイルで実装し、.hファイルで関数プロトタイプ・構造体定義を記述。
- main.cは全体の流れと各機能呼び出しのみを記述し、詳細処理は各モジュールに分離。
