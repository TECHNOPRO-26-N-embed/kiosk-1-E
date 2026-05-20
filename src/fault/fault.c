#include "fault.h"
#include "../log/log.h"
#include <stdio.h>

#define FAULT_SIMULATION_CASE 0

/*
 * 自販機で想定する異常シナリオ
 * 0: 正常
 * 1: 在庫切れ（在庫管理異常）
 * 2: 温度異常（冷却/加温ユニット異常）
 * 3: 投入金処理異常（硬貨詰まり等）
 * 4: メンテ扉開放（セキュリティ異常）
 */
static int evaluate_fault_scenario(int scenario, const char **detail, const char **error) {
    if (detail == NULL || error == NULL) {
        return 1;
    }

    switch (scenario) {
        case 1:
            *detail = "在庫管理異常を検知しました";
            *error = "商品ID=12 の在庫が負値です";
            return 1;
        case 2:
            *detail = "温度異常を検知しました";
            *error = "冷却温度センサー値が上限を超過しました";
            return 1;
        case 3:
            *detail = "投入金処理異常を検知しました";
            *error = "硬貨排出機構で詰まりを検知しました";
            return 1;
        case 4:
            *detail = "セキュリティ異常を検知しました";
            *error = "メンテナンス扉が開放状態です";
            return 1;
        default:
            *detail = "異常なし";
            *error = "";
            return 0;
    }
}

// 故障・異常検知処理
// 戻り値: 0=異常なし, 1=異常検知
int detect_fault(void) {
    const char *detail = "異常なし";
    const char *error = "";
    int abnormal = evaluate_fault_scenario(FAULT_SIMULATION_CASE, &detail, &error);

    if (abnormal) {
        printf("[FAULT] %s\n", detail);
        if (save_log("fault", detail, error) != 0) {
            fprintf(stderr, "[エラー] faultログの保存に失敗しました。\n");
        }
        return 1;
    }

    return 0;
}
