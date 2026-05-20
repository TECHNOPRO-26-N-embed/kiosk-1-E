#include "member.h"
#include <stdio.h>
#include <string.h>
#define MEMBER_CSV_PATH_PRIMARY "member.csv"
#define MEMBER_CSV_PATH_FALLBACK "member.csv"
#define MEMBER_MAX 1024

typedef struct {
    int member_id;
    char name[32];
    unsigned int points;
} MemberInfo;

// scanfの直接利用を避け、1行入力を安全に整数へ変換する。
static int read_non_negative_int(const char *prompt, int *out_value) {
    char buf[64];
    int value = 0;
    char extra = '\0';
    printf("%s", prompt);
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        printf("入力の読み取りに失敗しました。\n");
        return 1;
    }
    if (sscanf(buf, " %d %c", &value, &extra) != 1 || value < 0) {
        printf("正しく入力してください。\n");
        return 1;
    }
    *out_value = value;
    return 0;
}

static int load_members(MemberInfo members[], int *count) {
    // 実行場所の差異に対応するため、data配下を優先しつつフォールバックする。
    FILE *fp_member1;
    char line[256];
    int index = 0;
    fp_member1 = fopen("member.csv", "r");
    if (fp_member1 != NULL) {
        printf("読込成功\n");
    }
    while (fgets(line, sizeof(line), fp_member1) != NULL) {
        int id = 0;
        char name[32] = {0};
        unsigned int points = 0;
        if (line[0] == '\n' || line[0] == '\r') {
            continue;
        }
        if (sscanf(line, "%d,%31[^,],%u", &id, name, &points) != 3) {
            // 形式不正行は読み飛ばして処理継続する。
            continue;
        }
        if (index >= MEMBER_MAX) {
            break;
        }
        members[index].member_id = id;
        strncpy(members[index].name, name, sizeof(members[index].name) - 1);
        members[index].name[sizeof(members[index].name) - 1] = '\0';
        members[index].points = points;
        index++;
    }
    fclose(fp_member1);
    *count = index;
    return 0;
}

static int save_members(const MemberInfo members[], int count) {
    // loadと同じ探索順で保存先を決定する。
    FILE *fp_member2 = fopen("member.csv", "w");
    int i;
    if (fp_member2 != NULL) {
        printf("読込成功\n");
    }
    for (i = 0; i < count; ++i) {
        fprintf(fp_member2, "%d,%s,%u\n", members[i].member_id, members[i].name, members[i].points);
    }
    fclose(fp_member2);
    return 0;
}

// 会員認証・ポイント管理処理
int member_login(int member_id) {
    MemberInfo members[MEMBER_MAX];
    int count = 0;
    int i;
    if (load_members(members, &count) != 0) {
        return 1;
    }
    for (i = 0; i < count; ++i) {
        if (members[i].member_id == member_id) {
            // 認証成功時に、購入画面で使う会員情報を表示する。
            printf("==========\n");
            printf("会員ID: %d, 名前: %s, ポイント: %u\n", members[i].member_id, members[i].name, members[i].points);
            printf("==========\n");
            return 0;
        }
    }
    printf("会員IDが見つかりません。\n");
    return 1;
}

// ポイント付与・利用処理
int update_points(int member_id, int add_point, int use_point) {
    MemberInfo members[MEMBER_MAX];
    int count = 0;
    int i;
    if (add_point < 0 || use_point < 0) {
        printf("ポイント値が不正です。\n");
        return 2;
    }
    if (load_members(members, &count) != 0) {
        return 2;
    }
    for (i = 0; i < count; ++i) {
        if (members[i].member_id == member_id) {
            if (members[i].points < (unsigned int)use_point) {
                printf("ポイント残高が不足しています。\n");
                return 1;
            }
            // 付与分を加算後、利用分を減算する。
            members[i].points += (unsigned int)add_point;
            members[i].points -= (unsigned int)use_point;
            if (save_members(members, count) != 0) {
                return 2;
            }
            printf("==========\n");
            printf("ポイント更新後: %u\n", members[i].points);
            printf("==========\n");
            return 0;
        }
    }
    printf("会員IDが見つかりません。\n");
    return 2;
}

int member_login_flow(void) {
    int member_id = 0;
    int use_point_menu = 0;
    int use_point = 0;
    int result = 0;
    // 1) 会員ID入力
    if (read_non_negative_int("会員IDを入力してください: ", &member_id) != 0) {
        return 3;
    }

    // 2) 会員検索（失敗時は中断）
    result = member_login(member_id);
    if (result != 0) {
        return 1;
    }

    // 3) ポイント利用有無の確認
    if (read_non_negative_int("ポイントを利用しますか？ (1:利用する 0:利用しない): ", &use_point_menu) != 0) {
        return 3;
    }
    if (use_point_menu == 0) {
        return 0;
    }
    if (use_point_menu != 1) {
        printf("正しく入力してください。\n");
        return 3;
    }
    // 4) 利用ポイント入力と残高更新
    if (read_non_negative_int("利用ポイントを入力してください: ", &use_point) != 0) {
        return 3;
    }
    result = update_points(member_id, 0, use_point);
    if (result != 0) {
        return 2;
    }
    return 0;
}