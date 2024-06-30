#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <string.h>

#define REVERSE 1
#define NORMAL 0

void create_file_path(const char* filename, char* path);
// Функция для создания пути по шаблону files/%s.txt
void create_path(char* input_path, char* output_path);
// Функция для создания путей к файлам ввода и вывода
int* read_numbers_from_file(const char* filename, int* count);
// Функция для считывания массива чисел из файла
void write_file(const char* output_filename, int* numbers, int count);
// Функция для записи массива в файл
void fill_file_with_random_numbers(const char* filename, int count, int min, int max);
// Функция для заполнения файла случайными числами

void selection_sort_file(const char* input_filename, const char* output_filename, char order);
// Сортировка выбором
void sort_by_order(char* input_path, char* output_path);
// Функция для определения порядка сортировки
void display_menu();
// Функция для вывода меню
void handle_menu_choice(int choice);
// Функция для обработки действия при выборе пункта меню