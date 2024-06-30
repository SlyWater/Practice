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

void fill_file_with_random_numbers(const char* filename, int count, int min,
    int max) {
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
    printf("Введите имя файла с несортированными числами (без расширения): ");
    scanf("%255s", input_filename);
    create_file_path(input_filename, input_path);
    printf("Введите имя файла с сортированными числами (без расширения): ");
    scanf("%255s", output_filename);
    create_file_path(output_filename, output_path);
}
