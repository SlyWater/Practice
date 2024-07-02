#include "utils.h"



int main() {
    setlocale(LC_ALL, "Russian");
    int choice;

    do {
        //Выводим меню и считываем выбор пользователя
        display_menu();
        scanf("%d", &choice);
        handle_menu_choice(choice);
    } while (choice != 0);
    return 0;
}