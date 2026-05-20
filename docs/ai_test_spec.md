# AIテスト仕様書（単体テスト）

## 1. 目的
本書は、基本設計書・詳細設計書で定義された関数を1つずつ単体で検証し、実施結果を記録する。

## 2. 対象
- 参照設計: docs/ai_design.md, docs/ai_detailed_design.md
- 対象コード: src 配下の C ファイル

## 3. 実施環境
- OS: Windows
- コンパイラ: gcc
- 文字コードオプション: -finput-charset=utf-8 -fexec-charset=cp932
- 実施日: 2026-05-20

## 4. 実行コマンド（実績）
### 4.1 既存テスト実行
gcc -o test_sales.exe src/test_sales.c src/sales.c src/log.c -Isrc -finput-charset=utf-8 -fexec-charset=cp932

.\test_sales.exe

### 4.2 個別関数ランナ実行（実施時に一時作成・削除）
gcc -o tmp_unit_runner.exe src/__tmp_unit_runner.c src/sales.c src/log.c -Isrc -finput-charset=utf-8 -fexec-charset=cp932

.\tmp_unit_runner.exe

## 5. 単体テスト結果（関数ごと）
| No | 関数名 | テスト観点 | 期待結果 | 実際の結果（実測） | 判定 |
| :-- | :-- | :-- | :-- | :-- | :--: |
| 1 | init_system | 関数定義の存在確認 | 定義がある | src配下の定義検索で未検出 | ✕ |
| 2 | show_idle_screen | 関数定義の存在確認 | 定義がある | src配下の定義検索で未検出 | ✕ |
| 3 | show_product_page | 関数定義の存在確認 | 定義がある | src配下の定義検索で未検出 | ✕ |
| 4 | select_product | 関数定義の存在確認 | 定義がある | src配下の定義検索で未検出 | ✕ |
| 5 | confirm_selection | 関数定義の存在確認 | 定義がある | src配下の定義検索で未検出 | ✕ |
| 6 | input_money | 関数定義の存在確認 | 定義がある | src配下の定義検索で未検出 | ✕ |
| 7 | confirm_purchase | 正常/異常（不足金） | 正常時0、不足金時2 | test_sales: 成功表示。個別ランナ: confirm_purchase=2（金額不足） | ○ |
| 8 | calculate_change | お釣り計算 | 500-450=50 | test_sales出力: お釣りは50円。個別ランナ: calculate_change=50 | ○ |
| 9 | cancel_purchase | 返金処理とログ記録 | 0を返しログ記録 | 個別ランナ: cancel_purchase=0。標準出力: Refunded amount: 300。log.csvに追記あり | ○ |
| 10 | update_inventory | 在庫更新呼び出し | 0（成功）を返す | 個別ランナ: update_inventory=0（暫定スタブ実装） | ○ |
| 11 | save_sales_data | CSV保存 | 0を返しsales.csvへ追記 | 個別ランナ: save_sales_data=0。sales.csv 行数 14→16（test_sales実行時） | ○ |
| 12 | save_log | CSV保存 | 0を返しlog.csvへ追記 | 個別ランナ: save_log=0。log.csv 行数 22→24（test_sales実行時） | ○ |
| 13 | member_login | 関数定義の存在確認 | 定義がある | src配下の定義検索で未検出 | ✕ |
| 14 | update_points | 関数定義の存在確認 | 定義がある | src配下の定義検索で未検出 | ✕ |
| 15 | replace_products | 関数定義の存在確認 | 定義がある | src配下の定義検索で未検出 | ✕ |
| 16 | detect_fault | 関数定義の存在確認 | 定義がある | src配下の定義検索で未検出 | ✕ |
| 17 | admin_menu | 関数定義の存在確認 | 定義がある | src配下の定義検索で未検出 | ✕ |

## 6. 実測ログ抜粋
### 6.1 test_sales 実行時標準出力
- 売上データ保存テスト: 成功
- 購入確定処理テスト: 成功
- お釣り計算テスト: お釣りは 50 円
- 返金処理テストを実行します。
- Refunded amount: 500

### 6.2 CSV行数の増分（test_sales実行）
- data/sales.csv: 14行 → 16行（+2）
- data/log.csv: 22行 → 24行（+2）

### 6.3 data/log.csv 末尾（個別ランナ実行後）
- 2026-05-20 15:41:40,confirm_purchase,Insufficient funds,Payment error
- 2026-05-20 15:41:40,cancel_purchase,Refund processed,Success
- 2026-05-20 15:41:40,unit_test,runner,

### 6.4 confirm_purchase 単体テストケース（正常系・異常系）
| テストID | 区分 | 入力値 (product_id, quantity, unit_price, money, member_id, use_point) | 期待結果 | 実際の結果（実測） | 判定 |
| :-- | :-- | :-- | :-- | :-- | :--: |
| CP-N01 | 正常系 | (1, 1, 120, 120, 1001, 0) | 戻り値 0 | 戻り値 0 | ○ |
| CP-N02 | 正常系 | (1, 1, 120, 500, 1001, 0) | 戻り値 0 | 戻り値 0 | ○ |
| CP-N03 | 正常系 | (1, 2, 120, 140, 1001, 100) | 戻り値 0（240-100=140） | 戻り値 0 | ○ |
| CP-E01 | 異常系 | (1, 1, 120, 100, 1001, 0) | 戻り値 2（金額不足） | 戻り値 2 | ○ |

補足（上記4ケース実行時の実測）:
- data/sales.csv: 20行 → 23行（+3）
- data/log.csv: 31行 → 35行（+4）
- 異常系 CP-E01 で log.csv に `Insufficient funds` が記録されることを確認

## 7. まとめ
- sales/log系の実装済み関数は単体テストを実施し、判定はすべて ○。
- 設計書にある未実装関数（init_system など）は定義未作成のため判定は ✕。
- 次工程では、✕の関数を実装後に同様の単体テストを追加実施すること。
