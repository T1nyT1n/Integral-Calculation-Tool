/*
Программа для вычисления интеграла методом левых прямоугольников.
Не использует ncurses или его аналоги, поэтому немного медленная.
*/
#include <conio.h> // Нужно для Windows, потому что C не для этой ОС.
#include <stdio.h>
// Глобальные переменные!
int selected_point = 1; // Выбранный пункт в меню
double a = -10; // Нижняя граница
double b = 10; // Верхняя граница
double h = 1; // Шаг
double err_abs = 0.001; // Абсолютная ошибка
double err_rel = 0.001; // Относительная ошибка
short is_main_menu_active = 1; // Для выхода из программы
// Ввести какое-то число для настройки программы.
double input_number() {
    printf("\033[2J\033[H"); // Очищает экран и возвращает курсор.
    printf("Enter one number:\n");
    double result;
    scanf("%lf", &result);
    return result;
}
// Активация выполнения команды из меню после его выбора
void execute_command_from_menu() {
    printf("EXECUTE COMMAND!");
    switch (selected_point) {
    case 1: // Верхняя граница
        b = input_number();
        break;
    case 2: // Нижняя граница
        a = input_number();
        break;
    case 3: // Шаг
        h = input_number();
        break;
    case 4: // Абсолютная ошибка
        err_abs = input_number();
        break;
    case 5: // Относительная ошибка
        err_rel = input_number();
    }
}
// Ввод с клавиатуры для главного меню.
void menu_input() {
    int ch;
    ch = _getch();
    if (ch == 13) { // Клавиша Enter
        execute_command_from_menu();
    }
    if (ch == 0 || ch == 224) {
        ch = _getch();
        switch (ch) {
        case 72: // Стрелочка вверх
            selected_point -= 1;
            if (selected_point < 1) {
                selected_point = 7;
            }
            break;
        case 80: // Стрелочка вниз
            selected_point += 1;
            if (selected_point > 7) {
                selected_point = 1;
            }
            break;
        default:
            break;
        }
    }
}
// Вывод конкретного пункта меню на экран.
void print_menu_entry(int entry_number, short is_active) {
    if (is_active) {
        printf("\033[1;31m>>> "); // Выделение текущего пункта меню.
    }
    else {
        printf("    "); // Отступ для красоты.
    }
    switch (entry_number) {
    case 1:
        printf("1. Upper bound.");
        break;
    case 2:
        printf("2. Lower bound.");
        break;
    case 3:
        printf("3. Step.");
        break;
    case 4:
        printf("4. Absolute error.");
        break;
    case 5:
        printf("5. Relative error.");
        break;
    case 6:
        printf("6. Execute!");
        break;
    case 7:
        printf("7. Quit.");
    default:
        break;
    }
    printf("\033[0m\n"); // Сброс форматирования.
}
// Отображение главного меню
void render_menu(int current_point) {
    printf("\033[2J\033[H"); // Очищает экран и возвращает курсор.
    printf("Use arrow keys and Enter to select an option:");
    for (int i = 0; i < 8; i++) {
        short is_current_point_active = 0;
        if (i == current_point) {
            is_current_point_active = 1;
        }
        print_menu_entry(i, is_current_point_active);
    }
    printf("Change default values (in parentheses) if you'd like to.");
}
// ОСНОВНАЯ ПРОГРАММА!
int main() {
    // Главное меню!
    while (is_main_menu_active) {
        render_menu(selected_point);
        menu_input();
    }
    // Завершение программы.
    printf("\n"); return 0;
}
