#include <stdio.h>
#include <string.h>

void remove_spaces(char *expression);
int parse_number(const char *expression, int *index);
int evaluate_expression(const char *expression, int *index);

// Hàm xóa khoảng trắng trong chuỗi
void remove_spaces(char *expression) {
    char *p1 = expression, *p2 = expression;
    while (*p2) {
        if (*p2 != ' ') {
            *p1++ = *p2;
        }
        p2++;
    }
    *p1 = '\0';
}

// Hàm chuyển chuỗi thành số nguyên
int parse_number(const char *expression, int *index) {
    int result = 0;
    while (expression[*index] >= '0' && expression[*index] <= '9') {
        result = result * 10 + (expression[*index] - '0');
        (*index)++;
    }
    return result;
}

// Hàm tính toán với thứ tự phép toán và dấu ngoặc
int evaluate_expression(const char *expression, int *index) {
    int result = 0;
    int current_value = 0;
    char operator = '+'; // Khởi tạo phép toán là cộng

    while (expression[*index] != '\0' && expression[*index] != ')') {
        if (expression[*index] == '(') {
            (*index)++;
            current_value = evaluate_expression(expression, index);
        } else if (expression[*index] >= '0' && expression[*index] <= '9') {
            current_value = parse_number(expression, index);
        }

        if (operator == '+') {
            result += current_value;
        } else if (operator == '-') {
            result -= current_value;
        } else if (operator == '*') {
            result *= current_value;
        } else if (operator == '/') {
            result /= current_value;
        }

        // Đọc toán tử tiếp theo
        operator = expression[*index];
        if (operator == '*' || operator == '/' || operator == '+' || operator == '-') {
            (*index)++;
        }
    }

    if (expression[*index] == ')') {
        (*index)++; // Bỏ qua dấu ")"
    }

    return result;
}

// Hàm main
int main() {
    char expression[100];
    printf("Nhập biểu thức: ");
    fgets(expression, sizeof(expression), stdin);

    remove_spaces(expression);

    int index = 0;
    int result = evaluate_expression(expression, &index);
    printf("Kết quả: %d\n", result);

    return 0;
}
