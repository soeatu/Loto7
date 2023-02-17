#pragma once
#include "Loto7.h"

#define PRICE 300
#define LIMIT_NUMBER 38
#define LIMIT_SELECT 7

/*宝くじの抽選に必要な変数をまとめた構造体*/
typedef struct
{
	int input_number[7];				//入力された番号
	int number[7];						//抽選された番号
	int bonus_number[2];				//ボーナス数字
	int select_class[7];				//当選等級ごとのカウント変数
	int cnt;							//抽選回数
	unsigned long long int purchase_price;	//購入金額
	unsigned long long int winning_amount;	//当選金額
}Loto;

/*状態管理等を行う変数をまとめた構造体*/
typedef struct {
	int flag;							//当選等級分岐用変数
	int flag_out;						//ループアウト用変数
	int check;						//重複していないか確認
}Management;

void input_number(Management*, Loto*);
void lottery(Management*, Loto*);
void deciding_winner(Management*, Loto*, const int*);
