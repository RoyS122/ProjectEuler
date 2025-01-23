
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

typedef struct
{
	char *array;
	unsigned int length;
} DynString;

typedef struct
{
	unsigned int *array;
	unsigned int length;
	unsigned int max;
	unsigned int min;
} DynArray;

void wait()
{
	printf("Press Enter to exit...\n");
	getchar();
}

void append(DynArray *da, unsigned int val)
{

	if (da->length == 0)
	{
		da->min = val;
		da->max = val;
		da->array = (unsigned int *)malloc(sizeof(unsigned int));
	}
	else
	{
		da->array = (unsigned int *)realloc(da->array, (da->length + 1) * sizeof(unsigned int));
	}

	if (val > da->max)
	{
		da->max = val;
	}
	else
	{
		if (val < da->min)
		{
			da->min = val;
		}
	}
	da->array[da->length] = val;
	da->length++;
}

unsigned int count(DynArray *da, unsigned int val)
{
	unsigned int res = 0;
	if (da->max < val || da->min > val)
	{
		return res;
	}

	for (unsigned int i = 0; i < da->length; i++)
	{
		if (da->array[i] == val)
		{
			res += 1;
		}
	}
	return res;
}

DynString new_string(char str[])
{
	DynString res;
	res.length = strlen(str);
	res.array = (char *)malloc((res.length + 1) * sizeof(char));
	strcpy(res.array, str);
	return res;
}

void append_int(DynString *dynstr, char str[])
{
	int l_str = strlen(str);
	dynstr->array = (char *)realloc(dynstr->array, (dynstr->length + l_str + 1) * sizeof(char));
	for (int i = 0; i < l_str; i++)
	{
		dynstr->array[dynstr->length] = str[i];
		dynstr->length += 1;
	}
	dynstr->array[dynstr->length] = '\0';
}

void append_char(DynString *dynstr, char c)
{
	dynstr->array = (char *)realloc(dynstr->array, (dynstr->length + 2) * sizeof(char));
	dynstr->array[dynstr->length] = c;
	dynstr->length += 1;
	dynstr->array[dynstr->length] = '\0';
}

int wordValue(DynString *dynstr)
{
	int res = 0;
	for (unsigned int i = 0; i < dynstr->length; i++)
	{
		res += dynstr->array[i] - 'A' + 1;
		// printf("%d, %d\n", 'A', dynstr->array[i] - 'A');
	}
	return res;
}

int main()
{
	char *filename = "0042_words.txt";
	FILE *fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Error: could not open file %s", filename);
		return 1;
	}
	char c;
	DynString w = new_string("");
	DynArray arr_values = {NULL, 0};
	while ((c = fgetc(fp)) != EOF)
	{
		if (c != '"' && c != ',')
		{
			append_char(&w, c);
		}
		else
		{
			if (w.length > 0)
			{
				int value = wordValue(&w);
				append(&arr_values, value);
				free(w.array);
				w = new_string("");
			}
		}
	}
	fclose(fp);
	if (w.length > 0)
	{
		int value = wordValue(&w);
		append(&arr_values, value);
		free(w.array);
	}

	unsigned int last = 0;
	unsigned int total_triangle_word_count = 0;

	for (unsigned int i = 0; last < arr_values.max; i++)
	{
		last = 0.5 * i * (i + 1);
		total_triangle_word_count += count(&arr_values, last);
	}
	printf("number of triangle words: %d\n", total_triangle_word_count);
	wait();
	return 0;
}