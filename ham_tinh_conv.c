#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int Tinh(char *s) {
    int numbers[100], numbers_count = 0;
    char operators[100];
    int operators_count = 0;
    char temp[100] = "";
    int temp_index = 0;

    for (int i = 0; i < strlen(s); ++i) {
        if (isdigit(s[i])) {
            temp[temp_index++] = s[i];
        } else {
            temp[temp_index] = '\0';
            numbers[numbers_count++] = atoi(temp);
            operators[operators_count++] = s[i];
            temp_index = 0;
        }
    }

    if (temp_index > 0) {
        temp[temp_index] = '\0';
        numbers[numbers_count++] = atoi(temp);
    }

    for (int i = 0; i < operators_count; ++i) {
        if (operators[i] == '*' || operators[i] == '/') {
            int left = numbers[i];
            int right = numbers[i + 1];
            int result = (operators[i] == '*') ? (left * right) : (left / right);
            numbers[i] = result;

            for (int j = i + 1; j < numbers_count - 1; ++j) {
                numbers[j] = numbers[j + 1];
            }
            numbers_count--;

            for (int j = i; j < operators_count - 1; ++j) {
                operators[j] = operators[j + 1];
            }
            operators_count--;
            --i;
        }
    }

    int result = numbers[0];
    for (int i = 0; i < operators_count; ++i) {
        if (operators[i] == '+') {
            result += numbers[i + 1];
        } else if (operators[i] == '-') {
            result -= numbers[i + 1];
        }
    }

    return result;
}

void Thay_The(char *s) {
    int start, end;
    char buffer[100];

    while ((start = strrchr(s, '(') - s) >= 0) {
        char *end_ptr = strchr(s + start, ')');
        if (!end_ptr) break;
        
        end = end_ptr - s;
        char subExpr[100];
        strncpy(subExpr, s + start + 1, end - start - 1);
        subExpr[end - start - 1] = '\0';

        int value = Tinh(subExpr);
        sprintf(buffer, "%d", value);

        memmove(s + start + strlen(buffer), s + end + 1, strlen(s) - end);
        memcpy(s + start, buffer, strlen(buffer));
    }
}

int main() {
    char s[100];
    printf("Nhap bieu thuc: ");
    scanf("%s", s);

    Thay_The(s);
    int result = Tinh(s);
    printf("Gia tri cua bieu thuc la: %d\n", result);

    return 0;
}
