#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <conio.h>
//------------------константы и структуры-------------------------
struct marsh {
	int id; //порядковый номер
	int number; // номер маршрута
	char nap[15]; // начальный пункт
	char kop[15]; // конечный пункт
};
const int size_marsh = sizeof(marsh); //размер структуры
//---------------------прототипы функций--------------------------
int create_file(FILE* f); //запись в файл
int sort_file(FILE* f); //сортировка файла
int print_file(FILE* f); //вывод файла
int print_marsh(FILE* f); //вывод информации о маршрутах
int kor_file(FILE* f); //корректировка файла
//---------------------основная функция---------------------------
int main() {
	char c;
	setlocale(LC_ALL, "Russian");
	//Открытие существующего файла для чтения и записи в конец
	FILE* f = fopen("C:\\Users\\lehad\\Desktop\\data.dat", "rb+");
	if (!f) {
		//Создание нового файла для обновления
		f = fopen("C:\\Users\\lehad\\Desktop\\data.dat", "wb+");
		if (!f) {
			puts("Не могу открыть (создать) файл\n");
			return 1;
		}
	}
	//вывод меню и запуск соответствующих функций
	while (1) {
		puts("1- Запись в файл");
		puts("2- Корректировка данных по номеру записи");
		puts("3- Вывод файла");
		puts("4- Вывод на экран информации о маршрутах");
		puts("5- Выход");
		puts("6- Сортировка");
		puts("______________________________");
		puts("Введите номер пункта меню\n");
		c = _getch();
		switch (c) {
		case '1':
			create_file(f);
			break;
		case '2':
			kor_file(f);
			break;
		case '3':
			print_file(f);
			break;
		case '4':
			print_marsh(f);
			break;
		case '5':
			return 0;
		case '6':
			sort_file(f);
			break;
		}
	}
}
//----------------------запись в файл-----------------------------
int create_file(FILE* f) {
	marsh d;
	int q = 0, k;
	int n;
	fseek(f, 0, SEEK_END); //указатель в конец файла
	while (1) {
		k = 0;
		rewind(f); //указатель в начало файла
		do {
			n = fread(&d, size_marsh, 1, f);//чтение структуры из файла
			if (n < 1) break; //если n<1, то конец файла
			k++;
		} while (1);
		d.id = k;
		puts("Введите номер маршрута (0-exit)");
		scanf_s("%d", &d.number);
		if (d.number == 0)
			return 1;
		puts("Введите название начального пункта маршрута");
		scanf_s("%s", &d.nap);
		puts("Введите название конечного пункта маршрута");
		scanf_s("%s", &d.kop);
		fwrite(&d, size_marsh, 1, f);
	}
}
int print_file(FILE* f) {
	marsh d;
	int n;
	rewind(f); //указатель в начало файла
	puts("__________________________________");
	puts("| Порядковый номер | Номер маршрута | Начальный пункт | Конечный пункт |");
	do {
		n = fread(&d, size_marsh, 1, f);//чтение структуры из файла
		if (n < 1) break; //если n<1, то конец файла
		printf("| %-16d | %-15d| %-16s| %-15s|\n", d.id, d.number, d.nap, d.kop);
	} while (1);
	puts("_________________________________");
	puts("Нажмите любую клавишу");
	_getch();
	return 0;
}
int kor_file(FILE* f) {
	marsh d;
	int por, n, k = 0;
	int a;
	char np[15];
	char kp[15];
	printf("Введите номер записи: ");
	scanf_s("%d", &por);
	puts("__________________________________");
	puts("| Порядковый номер | Номер маршрута | Начальный пункт | Конечный пункт |");
	rewind(f); //указатель в начало файла
	do {
		n = fread(&d, size_marsh, 1, f);//чтение структуры из файла
		if (d.id == por) {
			fseek(f, k * size_marsh, SEEK_SET);
			puts("Введите номер маршрута (0-exit)");
			scanf_s("%d", &d.number);
			puts("Введите название начального пункта маршрута");
			scanf_s("%s", &d.nap);
			puts("Введите название конечного пункта маршрута");
			scanf_s("%s", &d.kop);
			fwrite(&d, size_marsh, 1, f);
			break;
		}
		k++;
	} while (1);
	puts("_________________________________");
	puts("Нажмите любую клавишу");
	_getch();
	return 0;
}


int print_marsh(FILE* f) {
	marsh d;
	int n, k = 0;
	char pol[15];
	printf("Введите начальный или конечный пункт: ");
	scanf_s("%s", pol);
	rewind(f); //указатель в начало файла
	puts("__________________________________");
	puts("| Порядковый номер | Номер маршрута | Начальный пункт | Конечный пункт |");
	do {
		n = fread(&d, size_marsh, 1, f);//чтение структуры из файла
		if (n < 1) break; //если n<1, то конец файла
		if ((strcmp(d.nap, pol) == 0) || (strcmp(d.kop, pol) == 0)) {
			k++;
			printf("| %-16d | %-15d| %-16s| %-15s|\n", d.id, d.number, d.nap, d.kop);
		}
	} while (1);
	if (k == 0) {
		printf("Данные маршруты отсутствуют\n");
	}
	puts("_________________________________");
	puts("Нажмите любую клавишу");
	_getch();
	return 0;
}
int sort_file(FILE* f) {
	long i, j;
	marsh d1, d2;
	fseek(f, 0, SEEK_END); //указатель в конец
	long len = ftell(f) / size_marsh;//определяем количество записей
	rewind(f); //указатель в начало
	//пузырьковая сортировка
	for (i = len - 1; i >= 1; i--)
		for (j = 0; j <= i - 1; j++) {
			fseek(f, j * size_marsh, SEEK_SET); //указатель на j-ую запись
			fread(&d1, size_marsh, 1, f); //читаем запись j в d1
			fread(&d2, size_marsh, 1, f); //читаем след. запись в d2
			if (d1.number > d2.number) {
				//указатель на 2 поз. назад
				fseek(f, (-2) * size_marsh, SEEK_CUR);
				//обмен значений
				fwrite(&d2, size_marsh, 1, f); //сначала записываем d2
				fwrite(&d1, size_marsh, 1, f); // затем записываем d1
			}
		}
	puts("Сортировка успешна завершена");
	_getch();
	return 0;
}
