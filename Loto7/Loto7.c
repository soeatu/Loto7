#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"Loto7.h"

/*入力関数*/
void input_number(Management* Mng, Loto* Tkj) {

	int i, j;

	printf("〜〜〜〜〜〜〜〜Loto7!〜〜〜〜〜〜〜〜\n");
	printf("1から%dまでの数字を%d個選んでください\n", LIMIT_NUMBER, LIMIT_SELECT);
	for (i = 0; i < LIMIT_SELECT; i++) {
		do {
			Mng->check = 0;
			printf("%d番目の数字:", i + 1);
			scanf_s("%d", &Tkj->input_number[i]);
			if (!(Tkj->input_number[i] > 0 && Tkj->input_number[i] < LIMIT_NUMBER)) {
				printf("1〜%dの数字を入力してください!\n", LIMIT_NUMBER);
			}
			for (j = 0; j < i; j++) {
				if (Tkj->input_number[j] == Tkj->input_number[i]) {
					printf("同じ数字が入力されています！\n");
					Mng->check = 1;
				}
			}
		} while (!(Tkj->input_number[i] > 0 && Tkj->input_number[i] < LIMIT_NUMBER) || Mng->check == 1);
	}

	printf("何回抽選を行いますか?:");
	scanf_s("%d", &Tkj->cnt);
	Tkj->purchase_price = Tkj->cnt * PRICE;

	printf("-----------------------------------\n");
	printf("|あなたが選んだ数字は...           |\n");
	printf("|  %2d : %2d : %2d : %2d : %2d : %2d: %2d |\n",
		Tkj->input_number[0], Tkj->input_number[1], Tkj->input_number[2], Tkj->input_number[3], Tkj->input_number[4],
		Tkj->input_number[5], Tkj->input_number[6]);
	printf("-----------------------------------\n");
}

/*抽選を行う関数*/
void lottery(Management* Mng, Loto* Tkj) {

	int j, k;

	for (j = 0; j < LIMIT_SELECT; j++) {
		do
		{
			Mng->check = 0;
			Tkj->number[j] = (rand() % LIMIT_NUMBER - 1) + 1;
			for (k = 0; k < j; k++) {
				if (Tkj->number[k] == Tkj->number[j]) {
					Mng->check = 1;
				}
			}
		} while (Mng->check == 1);
	}

	for (j = 0; j < LIMIT_SELECT; j++) {
		for (k = 0; k < LIMIT_SELECT; k++) {
			if (Tkj->input_number[j] == Tkj->number[k]) {
				Mng->flag++;
			}
		}
	}

	for (j = 0; j < 2; j++) {
		do
		{
			Mng->check = 0;
			Tkj->bonus_number[j] = (rand() % LIMIT_NUMBER - 1) + 1;
			for (k = 0; k < LIMIT_SELECT; k++) {
				if (Tkj->bonus_number[j] == Tkj->number[k]) {
					Mng->check = 1;
				}
				if (j == 1) {
					if (Tkj->bonus_number[0] == Tkj->bonus_number[1]) {
						Mng->check = 1;
					}
				}
			}
		} while (Mng->check == 1);
	}
}

/*当選等級を判断する関数*/
void deciding_winner(Management* Mng, Loto* Tkj, const int* i) {

	int k;

	switch (Mng->flag) {
	case 7: Tkj->select_class[0]++;	Tkj->winning_amount += 400000000; break;
	case 6: for (k = 0; k < 7; k++) {
		if (Tkj->input_number[k] == Tkj->bonus_number[0] || Tkj->input_number[k] == Tkj->bonus_number[1]) {
			Tkj->select_class[1]++;	Tkj->winning_amount += 10000000;
		} else {
			Tkj->select_class[2]++;	Tkj->winning_amount += 1000000;
		}
	}
		  break;

	case 5: Tkj->select_class[3]++;	Tkj->winning_amount += 12500; break;
	case 4: Tkj->select_class[4]++;	Tkj->winning_amount += 2000; break;
	case 3: for (k = 0; k < 7; k++) {
		if (Tkj->input_number[k] == Tkj->bonus_number[0] || Tkj->input_number[k] == Tkj->bonus_number[1]) {
			Tkj->select_class[5]++;	Tkj->winning_amount += 1000;
		}
	}
		  break;
	default:	break;
	}
	Mng->flag = 0;
	printf("試行回数:%d回 1等:%f%% 2等:%f%% 3等:%f%% 4等:%f%% 5等:%f%% 6等:%f%%  当選金額:%lld円\r", *i,
		Tkj->select_class[0] * 100.0 / (float)*i, Tkj->select_class[1] * 100.0 / (float)*i,
		Tkj->select_class[2] * 100.0 / (float)*i, Tkj->select_class[3] * 100.0 / (float)*i,
		Tkj->select_class[4] * 100.0 / (float)*i, Tkj->select_class[5] * 100.0 / (float)*i,
		Tkj->winning_amount);
}

/*main関数*/
int Loto_main(void) {

	int i;					//ループ変数

	/*構造体変数宣言*/
	Management mng = { 0 };
	Loto tkj = { 0 };

	srand(time(NULL));	//乱数の種を設定

	input_number(&mng, &tkj);


	for (i = 0; i <= tkj.cnt; i++) {
		lottery(&mng, &tkj);
		deciding_winner(&mng, &tkj, &i);
	}
	putchar('\n');
	printf("購入金額:%lld円 当選金額:%lld円 差額%lld円", tkj.purchase_price, tkj.winning_amount, (signed long long)tkj.winning_amount - (signed long long)tkj.purchase_price);

	return 0;
}
