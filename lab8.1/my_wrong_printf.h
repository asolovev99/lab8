#pragma once

#include<stdarg.h>
#include<stdio.h>

int stay_in(char symbol, int switch_min_width_to_precision)
{
	if ((symbol >= '0') && (symbol <= '9'))
	{
		return 1;
	}
	else if (!switch_min_width_to_precision)
	{
		switch (symbol)
		{
		case '-':
			return 1;
			break;
		case '+':
			return 1;
			break;
		case '.':
			return 1;
			break;
		default:
			break;
		}
	}

	return 0;
}

int get_power(int number, int power)
{
	int result = 1;

	if (number == 0)
	{
		return 0;
	}
	else
	{
		if (power < 0)
		{
			return -1;
		}
		for (int i = 1; i <= power; i++)
		{
			result *= number;
		}
	}

	return result;
}

int get_symbol(double number, int index)
{
	if (index < 0)
	{
		for (int i = 0; i < -index; i++)
		{
			number -= (double)(int)number;
			number *= 10;
		}

		return (int)number;
	}
	else
	{
		int result = (int)number;

		for (int i = 0; i < index; i++)
		{
			result /= 10;
		}

		return result % 10;
	}
}

int max(int first, int second)
{
	if (first > second)
	{
		return first;
	}
	else
	{
		return second;
	}
}
//int int_to_char(int digit)
//{
//	return
//}

void my_printf(const char* output, ...) // % [ flags] [ Ширина] [. точность] [ Размер] тип
{
	int i = 0;

	int switch_min_width_to_precision = 0;

	int is_left_alignment = 0;
	int with_sign = 0;
	int with_zeros = 0;

	int min_width = -1;
	int precision = -1;

	char current_symbol = '\0';
	va_list param = NULL;
	va_start(param, output);

	if (output != NULL)
	{
		while (output[i] != '\0')
		{
			if (output[i] != '%')
			{
				putchar(output[i]);
			}
			else
			{
				if (output[i + 1] == '%')
				{
					putchar('%');
				}
				else
				{
					int variable_was_printed = 0;
					//char* variable = NULL;
					switch_min_width_to_precision = 0;

					is_left_alignment = 0;
					with_sign = 0;
					with_zeros = 0;

					min_width = -1;
					precision = -1;

					while (((output[i + 1] > 'z') || (output[i + 1] < 'a')) && (output[i + 1] != '\0') && stay_in(output[i + 1], switch_min_width_to_precision)) //  пока output[i + 1] != формат вывода или конец строки
					{
						if ((output[i + 1] == '-') && (!is_left_alignment))
						{
							is_left_alignment = 1;
						}
						else if ((output[i + 1] == '.') && (!switch_min_width_to_precision))
						{
							switch_min_width_to_precision = 1;
							precision = 0;
						}
						else if ((output[i + 1] == '+') && (!with_sign))
						{
							with_sign = 1;
						}
						else if ((output[i + 1] == '0') && (!with_zeros))
						{
							with_zeros = 1;
						}
						else if ((output[i + 1] >= '0') && (output[i + 1] <= '9'))
						{
							//i++;

							if (switch_min_width_to_precision)
							{
								precision = 0;
							}
							else
							{
								min_width = 0;
							}

							if (switch_min_width_to_precision)
							{
								precision *= 10;
								precision += output[i + 1] - '0';
							}
							else
							{
								min_width *= 10;
								min_width += output[i + 1] - '0';
							}

							while ((output[i + 2] >= '0') && (output[i + 2] <= '9'))
							{
								if (switch_min_width_to_precision)
								{
									precision *= 10;
									precision += output[i + 2] - '0';
								}
								else
								{
									min_width *= 10;
									min_width += output[i + 2] - '0';
								}

								i++;
							}
						}

						i++;
					}
					if ((output[i + 1] == 'd') || (output[i + 1] == 'i')) // int variable
					{
						int input = va_arg(param, int);

						int is_sign_printed = 0;
						variable_was_printed = 1;
						int length_input = 1;

						if (min_width == -1)
						{
							min_width = 1;
						}
						if (precision == -1)
						{
							precision = 1;
						}
						else
						{
							with_zeros = 0;
						}

						while (input / get_power(10, length_input) != 0)
						{
							length_input++;
						}

						if (is_left_alignment)
						{
							if (input < 0)
							{
								putchar('-');
								is_sign_printed = 1;
							}
							else if (with_sign)
							{
								putchar('+');
								is_sign_printed = 1;
							}

							for (int j = 0; j < precision - length_input; j++)
							{
								putchar('0');
							}

							for (int j = 0; j < length_input; j++)
							{
								putchar(input / get_power(10, length_input - 1 - j) % 10 + '0');
							}

							for (int j = 0; j < min_width - is_sign_printed - max(precision, length_input); j++)
							{
								putchar(' ');
							}
						}
						else
						{
							if ((input < 0) && (with_zeros))
							{
								putchar('-');
								is_sign_printed = 1;
							}
							else if ((with_sign) && (with_zeros))
							{
								putchar('+');
								is_sign_printed = 1;
							}

							for (int j = 0; j < min_width - /*is_sign_printed*/((input < 0) || (with_sign)) - max(precision, length_input); j++)
							{
								if (with_zeros)
								{
									putchar('0');
								}
								else
								{
									putchar(' ');
								}

							}

							if (!is_sign_printed)
							{
								if (input < 0)
								{
									putchar('-');
									is_sign_printed = 1;
								}
								else if (with_sign)
								{
									putchar('+');
									is_sign_printed = 1;
								}
							}

							for (int j = 0; j < precision - length_input; j++)
							{
								putchar('0');
							}

							for (int j = 0; j < length_input; j++)
							{
								putchar(input / get_power(10, length_input - 1 - j) % 10 + '0');
							}
						}
					}
					else if ((output[i + 1] == 'l') && ((output[i + 2] == 'd') || (output[i + 2] == 'i'))) // long variable
					{
						long input = va_arg(param, long);

						int is_sign_printed = 0;
						variable_was_printed = 1;
						int length_input = 1;

						if (min_width == -1)
						{
							min_width = 1;
						}
						if (precision == -1)
						{
							precision = 1;
						}
						else
						{
							with_zeros = 0;
						}

						while (input / get_power(10, length_input) != 0)
						{
							length_input++;
						}

						if (is_left_alignment)
						{
							if (input < 0)
							{
								putchar('-');
								is_sign_printed = 1;
							}
							else if (with_sign)
							{
								putchar('+');
								is_sign_printed = 1;
							}

							for (int j = 0; j < precision - length_input; j++)
							{
								putchar('0');
							}

							for (int j = 0; j < length_input; j++)
							{
								putchar(input / get_power(10, length_input - 1 - j) % 10 + '0');
							}

							for (int j = 0; j < min_width - is_sign_printed - max(precision, length_input); j++)
							{
								putchar(' ');
							}
						}
						else
						{
							if ((input < 0) && (with_zeros))
							{
								putchar('-');
								is_sign_printed = 1;
							}
							else if ((with_sign) && (with_zeros))
							{
								putchar('+');
								is_sign_printed = 1;
							}

							for (int j = 0; j < min_width - /*is_sign_printed*/((input < 0) || (with_sign)) - max(precision, length_input); j++)
							{
								if (with_zeros)
								{
									putchar('0');
								}
								else
								{
									putchar(' ');
								}
							}

							if (!is_sign_printed)
							{
								if (input < 0)
								{
									putchar('-');
									is_sign_printed = 1;
								}
								else if (with_sign)
								{
									putchar('+');
									is_sign_printed = 1;
								}
							}

							for (int j = 0; j < precision - length_input; j++)
							{
								putchar('0');
							}

							for (int j = 0; j < length_input; j++)
							{
								putchar(input / get_power(10, length_input - 1 - j) % 10 + '0');
							}
						}

						i++; // To avoid print 'd' or 'i'
					}
					else if (output[i + 1] == 'f') // float/double variable
					{
						double input = va_arg(param, double);

						variable_was_printed = 1;
						int is_sign_printed = 0;
						int length_input = 1;

						if (precision == -1)
						{
							precision = 6;
						}
						if (min_width == -1)
						{
							min_width = 1;
						}

						while ((input / get_power(10, length_input) >= 1.0) || (input / get_power(10, length_input) <= -1.0))
						{
							length_input++;
						}

						if (is_left_alignment) // Выравнивание по левому краю
						{
							if (input < 0)
							{
								putchar('-');
								is_sign_printed = 1;
							}
							else if (with_sign)
							{
								putchar('+');
								is_sign_printed = 1;
							}

							for (int j = 0; j < length_input; j++)
							{
								putchar(((int)input / get_power(10, length_input - 1 - j) % 10) + '0');
							}

							if (precision > 0)
							{
								//putchar(((int)input % 10) + '0');

								putchar('.');

								for (int j = 1; j < precision + 1; j++) // Вывод дробной части, кроме последней цифры
								{
									putchar(/*(int)(input * get_power(10, j)) % 10*/get_symbol(input, -j) + '0');
								}

								//if ((int)(input * get_power(10, precision + 1)) % 10 < 5) // Вывод последней цифры дробной части
								//{
								//	putchar(/*input* get_power(10, precision)) % 10*/get_symbol(input, -precision) + '0');
								//}
								//else
								//{
								//	putchar(/*input* get_power(10, precision)) % 10*/get_symbol(input, -precision) + '0' + 1);
								//}
							}
							else
							{
								//if (get_symbol(input, -1) < 5) // Вывод последней цифры дробной части
								//{
								//	putchar(((int)input % 10) + '0');
								//}
								//else
								//{
								//	putchar(((int)input % 10) + '0' + 1);
								//}
							}

							for (int j = 0; j < min_width - is_sign_printed - length_input - (precision > 0) - precision; j++)
							{
								putchar(' ');
							}
						}
						else // Выравнивание по правому краю
						{
							if ((input < 0) && (with_zeros))
							{
								putchar('-');
								is_sign_printed = 1;
							}
							else if ((with_sign) && (with_zeros))
							{
								putchar('+');
								is_sign_printed = 1;
							}

							for (int j = 0; j < min_width - /*is_sign_printed*/((input < 0) || (with_sign)) - length_input - (precision > 0) - precision; j++)
							{
								if (with_zeros)
								{
									putchar('0');
								}
								else
								{
									putchar(' ');
								}
							}

							if (!is_sign_printed)
							{
								if (input < 0)
								{
									putchar('-');
									is_sign_printed = 1;
								}
								else if (with_sign)
								{
									putchar('+');
									is_sign_printed = 1;
								}
							}


							for (int j = 0; j < length_input; j++)
							{
								putchar(((int)input / get_power(10, length_input - 1 - j) % 10) + '0');
							}

							if (precision > 0)
							{
								//putchar(((int)input % 10) + '0');

								putchar('.');

								for (int j = 1; j < precision + 1; j++) // Вывод дробной части, кроме последней цифры
								{
									putchar(/*(int)(input * get_power(10, j)) % 10*/get_symbol(input, -j) + '0');
								}

								//if ((int)(input * get_power(10, precision + 1)) % 10 < 5) // Вывод последней цифры дробной части
								//{
								//	putchar(/*input* get_power(10, precision)) % 10*/get_symbol(input, -precision) + '0');
								//}
								//else
								//{
								//	putchar(/*input* get_power(10, precision)) % 10*/get_symbol(input, -precision) + '0' + 1);
								//}
							}
							else
							{
								//if (get_symbol(input, -1) < 5) // Вывод последней цифры дробной части
								//{
								//	putchar(((int)input % 10) + '0');
								//}
								//else
								//{
								//	putchar(((int)input % 10) + '0' + 1);
								//}
							}



						}

					}

					if (variable_was_printed)
					{
						i++;
					}
				}
			}

			i++;
		}
	}

	va_end(param);
}