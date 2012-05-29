/*
 * debounce.c
 *
 *  Created on: 09.12.2010
 *      Author: krichevskiy
 */

#include "debounce.h"

void debounce_create(Debounce *d, deb_value_t debounce_level);
bool debounce_binary_reversible(Debounce *d, deb_value_t value);
bool debounce_level_steady(Debounce *d, deb_value_t value);

void debounce_gate_create(DebounceGate *d, deb_value_t debounce_level, deb_value_t min, deb_value_t max);
bool debounce_gate_steady(DebounceGate *d, deb_value_t value);

/*!
 * �������������� ��������� ������������ d.
 *  [in] debounce_level - ����� ������������.
 */
void debounce_create(Debounce *d, deb_value_t debounce_level)
{
	d->deb_counter = 0;
	d->deb_level = debounce_level;
	d->prev_value = 0;
}

/*!
 * ����������� ��������������� ���������
 * ���������� true ���� �������� value
 * �� �������� � ������� d.deb_level ����������������
 * ������� �������.
 */
bool debounce_level_steady(Debounce *d, deb_value_t value)
{
	if (value != d->prev_value)
	{
		d->prev_value = value;
		d->deb_counter = 0;

		return false;
	}

	if (d->deb_counter < d->deb_level)
	{
		++d->deb_counter;

		return (d->deb_counter == d->deb_level);
	}

	return true;
}

/*!
 * 	����������� ����������� ���������,
 * �������� � �������, �� ����������� ������
 * � �������� ��������� �������� (0/�� 0).
 *
 *	������� ��������, ��������� ����������
 * ��������� ������������ ������������ �
 * value, ��������� ����� ������������ �
 * ������ ��������� ����������� ���������
 * ������������.
 *
 *	���������� true ���� ������� �����������.
 */
bool debounce_binary_reversible(Debounce *d, deb_value_t value)
{
	bool result;

	if (value) {
		if (d->deb_counter < d->deb_level) {
			++d->deb_counter;
			return false;
		}
	} else {
		if (d->deb_counter) {
			--d->deb_counter;
			return false;
		}
	}

	result = (value != d->prev_value);
	d->prev_value = value;
	return result;
}

void debounce_gate_create(DebounceGate *d, deb_value_t debounce_level, deb_value_t min, deb_value_t max)
{
	d->deb_counter = 0;
	d->deb_level = debounce_level;
	d->level_bottom = min;
	d->level_top = max;
}

bool debounce_gate_steady(DebounceGate *d, deb_value_t value)
{
	if (value <= d->level_top
		&& value >= d->level_bottom)
	{
		if (d->deb_counter >= d->deb_level)
		{
			return true;
		}

		++d->deb_counter;
	}

	return false;
}
