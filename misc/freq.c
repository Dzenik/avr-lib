#include "freq.h"

#include <stdlib.h>

unsigned int cs0_table[8] = {1, 1, 8, 64, 256, 1024, 1, 1};	//������������
unsigned int cs1_table[8] = {1, 1, 8, 32, 64, 128, 256, 1024};	//������������

unsigned char fit_prescaler(unsigned long freq, unsigned int* top);

/*
	����� ������������ ������������
	� ������� ������� ��� �������� �������.
*/
unsigned char fit_prescaler(unsigned long freq, unsigned int* top, timer_prescalers_enum tps)
{
	const unsigned int* cs_table;
	unsigned long prescaled_freq;		// ������� ����� ������������
	unsigned long pwm_top;				// ���������� ��������
	unsigned int pwm_freq;				// ����������� ������� ���

	unsigned int delta;					// �������� �������� � ����������� ������
	unsigned int best_delta = 0xFFFF;	// ���������� �������� �������� � ����������� ������
	unsigned char best_prescaler = 0;	// ������ ������������
	unsigned int best_top;

	unsigned char i;

	if (freq == 0)
	{
		return 0;
	}

	if (tps == TIMER_0_1_PS) {
		cs_table = cs0_table;
	} else {
		cs_table = cs1_table;
	}

	for (i = 1; i < 8; ++i)
	{
		prescaled_freq = F_CPU/cs_table[i];

		if (freq <= prescaled_freq)			//���� freq > prescaled_freq �� ��������� 0
		{
			pwm_top = prescaled_freq/freq;	//������� ���

			if (pwm_top <= 0xFFFF)			//���� ������ - �� �� ������ � ��������
			{
				pwm_freq = prescaled_freq/pwm_top;	//����������� ������� (���������� ����������)
				
				delta = abs(freq - pwm_freq);
				if (delta < best_delta)
				{
					best_delta = delta;
					best_top = pwm_top;
					best_prescaler = i;
				}
			}
		}
	}
	
	*top = best_top - 1;
	return best_prescaler;		//���� ������ ����������� - ������� ��������.
}
