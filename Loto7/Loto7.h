#pragma once
#include "Loto7.h"

#define PRICE 300
#define LIMIT_NUMBER 38
#define LIMIT_SELECT 7

/*�󂭂��̒��I�ɕK�v�ȕϐ����܂Ƃ߂��\����*/
typedef struct
{
	int input_number[7];				//���͂��ꂽ�ԍ�
	int number[7];						//���I���ꂽ�ԍ�
	int bonus_number[2];				//�{�[�i�X����
	int select_class[7];				//���I�������Ƃ̃J�E���g�ϐ�
	int cnt;							//���I��
	unsigned long long int purchase_price;	//�w�����z
	unsigned long long int winning_amount;	//���I���z
}Loto;

/*��ԊǗ������s���ϐ����܂Ƃ߂��\����*/
typedef struct {
	int flag;							//���I��������p�ϐ�
	int flag_out;						//���[�v�A�E�g�p�ϐ�
	int check;						//�d�����Ă��Ȃ����m�F
}Management;

void input_number(Management*, Loto*);
void lottery(Management*, Loto*);
void deciding_winner(Management*, Loto*, const int*);
