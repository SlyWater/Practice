#include "utils.h"

int* read_numbers_from_file(const char* filename, int* count) {
    FILE* file = fopen(filename, "r");
    int capacity = 10;
    int* numbers = malloc(capacity * sizeof(int));

    int num_count = 0;
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        char* cleaned_line = strtok(line, "\n\r ");
        if (cleaned_line != NULL) {
            int number;
            if (sscanf(cleaned_line, "%d", &number) == 1) {
                if (num_count >= capacity) {
                    capacity *= 2;
                    int* new_numbers = realloc(numbers, capacity * sizeof(int));
                    numbers = new_numbers;
                }
                numbers[num_count++] = number;
            }
            else {
                fprintf(stderr, "Строка '%s' не является числом и будет пропущена.\n",
                    cleaned_line);
            }
        }
    }

    fclose(file);
    *count = num_count;
    return numbers;
}

void fill_file_with_random_numbers(const char* filename, int count, int min, int max) {
    FILE* file = fopen(filename, "w");

    srand(time(NULL));

    for (int i = 0; i < count; i++) {
        int number = min + rand() % (max - min + 1);
        fprintf(file, "%d\n", number);
    }

    fclose(file);
}

void write_file(const char* output_filename, int* numbers, int count) {
    FILE* output_file = fopen(output_filename, "w");

    for (int i = 0; i < count; i++) {
        fprintf(output_file, "%d\n", numbers[i]);
    }

    fclose(output_file);
}

void create_file_path(const char* filename, char* path) {
    snprintf(path, 50, "files/%s.txt", filename);
}

void create_path(char* input_path, char* output_path) {
    char input_filename[40];
    char output_filename[40];
    system("cls");
    printf("Введите имя файла с несортированными числами (без расширения): ");
    scanf("%255s", input_filename);
    create_file_path(input_filename, input_path);
    printf("Введите имя файла с сортированными числами (без расширения): ");
    scanf("%255s", output_filename);
    create_file_path(output_filename, output_path);
}

void selection_sort_file(const char* input_filename, const char* output_filename, char order) {
    int count;
    int* numbers = read_numbers_from_file(input_filename, &count);
    if (numbers == NULL) {
        return;
    }

    clock_t start_time = clock();
    for (int i = 0; i < count - 1; i++) {
        int min_index = i;
        if (order) {
            for (int j = i + 1; j < count; j++) {
                if (numbers[j] > numbers[min_index]) {
                    min_index = j;
                }
            }
        }
        else {
            for (int j = i + 1; j < count; j++) {
                if (numbers[j] < numbers[min_index]) {
                    min_index = j;
                }
            }
        }


        if (min_index != i) {
            int temp = numbers[i];
            numbers[i] = numbers[min_index];
            numbers[min_index] = temp;
        }
    }
    clock_t end_time = clock();
    double time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    system("cls");
    printf("Время сортировки: %.3f секунд\n", time_spent);
    write_file(output_filename, numbers, count);
    free(numbers);
    system("PAUSE");
    system("cls");
}

void display_menu() {
    printf("1. Сортировка определенного файла\n");
    printf("2. Сортировка файла с определенным количеством чисел\n");
    printf("0. Выход\n");
    printf("Выберите пункт меню: ");
}

void handle_menu_choice(int choice) {
    int count, min, max;
    char pathi[50], patho[50];

    system("cls");
    switch (choice) {
    case 1:
        create_path(pathi, patho);
        sort_by_order(pathi, patho);

        break;
    case 2:
        printf("Введите количество чисел: ");
        scanf("%d", &count);
        printf("Введите минимальное значение: ");
        scanf("%d", &min);
        printf("Введите максимальное значение: ");
        scanf("%d", &max);
        create_path(pathi, patho);
        fill_file_with_random_numbers(pathi, count, min, max);
        sort_by_order(pathi, patho);

        break;
    case 0:
        printf("Выход из программы.\n");
        break;
    default:
        printf("Неверный выбор. Пожалуйста, попробуйте снова.\n");
        break;
    }
}

void sort_by_order(const char* input_path, const char* output_path) {
    int ch;
    system("cls");
    printf("1. Обычный порядок\n2. Обратный порядок\nВыберите порядок сортировки: ");
    scanf("%d", &ch);
    switch (ch) {
    case 1:
        selection_sort_file(input_path, output_path, NORMAL);
        break;
    case 2:
        selection_sort_file(input_path, output_path, REVERSE);
        break;
    }
}
