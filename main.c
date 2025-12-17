/*
Программа для вычисления интеграла методом левых прямоугольников.
Не использует ncurses или его аналоги, поэтому немного медленная.
*/
#include <conio.h> // Нужно для Windows, потому что C не для этой ОС.
#include <stdio.h>
#include <math.h>
// Глобальные переменные!
int selected_point = 1; // Выбранный пункт в меню
double a = -10; // Нижняя граница
double b = 10; // Верхняя граница
double h = 1; // Шаг
double err_abs; // Абсолютная ошибка
double err_rel; // Относительная ошибка
short is_main_menu_active = 1; // Для выхода из программы
// Ввести какое-то число для настройки программы.
double f(double x) { // Функция
    return 2 * pow(x, 3) - pow(x, 2) + 4 * x + 5;
}
// Вычисление интеграла методом левых прямоугольников с оценкой точности
double left_rectangle_integral(double* abs_error, double* rel_error) {
    if (h <= 0.0 || b <= a) {
        *abs_error = *rel_error = 0.0;
        return 0.0;
    }
    int n = (int)ceil((b - a) / h); // Количество интервалов
    double integral_simple = 0.0;
    double integral_double = 0.0;
    // Вычисление с шагом h
    for (int i = 0; i < n; i++) {
        double x = a + i * h;
        integral_simple += f(x) * h;
    }
    // Вычисление с шагом h/2 для оценки точности
    double h2 = h / 2.0;
    int n2 = (int)ceil((b - a) / h2);
    for (int i = 0; i < n2; i++) {
        double x = a + i * h2;
        integral_double += f(x) * h2;
    }
    // Оценка ошибок
    *abs_error = fabs(integral_double - integral_simple);
    *rel_error = (*abs_error / fabs(integral_double)) * 100.0;
    return integral_double; // Более точное значение
}
void execute() { // Исполнение и вывод.
    printf("\033[2J\033[H"); // Очищает экран и возвращает курсор.
    if (b < 0 || a < 0) {
        printf_s("Error! One of the borders is less than zero.");
    }
    else {
        double result = left_rectangle_integral(&err_abs, &err_rel);
        printf_s("Result: %.6f\n", result);
        printf_s("Absolute: %.6f\n", err_abs);
        printf_s("Relative: %.6f%%\n", err_rel);
    }
    _getch();
}
double input_number() {
    printf("\033[2J\033[H"); // Очищает экран и возвращает курсор.
    printf("Enter one number:\n");
    double result;
    scanf("%lf", &result);
    return result;
}
// Активация выполнения команды из меню после его выбора
void execute_command_from_menu() {
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
    case 4: // Выполнить
        execute();
        break;
    case 5: // Выход из программы
        is_main_menu_active = 0;
        break;
    }
}
// Ввод с клавиатуры для главного меню.
void menu_input() {
    int ch;
    ch = _getch();
    if (ch == 13) { // Клавиша Enter
        execute_command_from_menu();
    }
    else if (ch == 'q') { // Ещё можно выйти, нажав это (стандартное
        is_main_menu_active = 0; // поведение для TUI приложений)
    }
    else if (ch == 0 || ch == 224) {
        ch = _getch();
        switch (ch) {
        case 72: // Стрелочка вверх
            selected_point -= 1;
            if (selected_point < 1) {
                selected_point = 5;
            }
            break;
        case 80: // Стрелочка вниз
            selected_point += 1;
            if (selected_point > 5) {
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
        printf("1. Upper bound: %lf", b);
        break;
    case 2:
        printf("2. Lower bound: %lf", a);
        break;
    case 3:
        printf("3. Step: %lf", h);
        break;
    case 4:
        printf("4. Execute!");
        break;
    case 5:
        printf("5. Quit.");
    default:
        break;
    }
    printf("\033[0m\n"); // Сброс форматирования.
}
// Отображение главного меню
void render_menu(int current_point) {
    printf("\033[2J\033[H"); // Очищает экран и возвращает курсор.
    printf("Use arrow keys and Enter to select an option or q to quit:");
    for (int i = 0; i < 6; i++) {
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
