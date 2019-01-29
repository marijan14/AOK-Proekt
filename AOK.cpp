#include "iostream"
#include "stdio.h"
#include "cmath"
#include "cstring"
#define MAX 1000
using namespace std;

char registers[8][16];

int convert(char *str, int n) {
    int suma = 0;
    for(int i = 0; i < n; i++)
        suma += (str[i] - '0') * pow(2, n - i - 1);
    return suma;
}

void MVI(int reg, char *value) {
    for(int i = 0; i < 16; i++)
        registers[reg][i] = value[i];
}

void MOV(int reg1, int reg2) {
    for(int i = 0; i < 16; i++)
        registers[reg1][i] = registers[reg2][i];
}

void AND(int reg1, int reg2, int reg3) {
    for(int i = 0; i < 16; i++)
        registers[reg1][i] = '0' + (registers[reg2][i] - '0') * (registers[reg3][i] - '0');
}

void OR(int reg1, int reg2, int reg3) {
    for(int i = 0; i < 16; i++)
        if(registers[reg2][i] == '1' && registers[reg3][i] == '1')
            registers[reg1][i] = '1';
        else
            registers[reg1][i] = '0' + (registers[reg2][i] - '0') + (registers[reg3][i] - '0');
}

void NOT(int reg1, int reg2) {
    for(int i = 0; i < 16; i++)
        if(registers[reg2][i] == '1')
            registers[reg1][i] = '0';
        else
            registers[reg1][i] = '1';
}

int LESS(int reg1, int reg2) {
    if(registers[reg1][0] < registers[reg2][0])
        return 0;
    else if(registers[reg1][0] > registers[reg2][0])
        return 1;

    for(int i = 1; i < 16; i++) {
        if(registers[reg1][i] > registers[reg2][i])
            return 0;
        else if(registers[reg1][i] < registers[reg2][i])
            return 1;
    }
    return 0;
}

int LEQ(int reg1, int reg2) {
    int flag = 1;
    for(int i = 0; i < 16; i++)
        if(registers[reg1][i] != registers[reg2][i]) {
            flag = 0;
            break;
        }

    if(flag)
        return 1;

    if(registers[reg1][0] < registers[reg2][0])
        return 0;
    else if(registers[reg1][0] > registers[reg2][0])
        return 1;

    for(int i = 1; i < 16; i++) {
        if(registers[reg1][i] > registers[reg2][i])
            return 0;
        else if(registers[reg1][i] < registers[reg2][i])
            return 1;
    }
    return 0;
}

int GRE(int reg1, int reg2) {
    if(registers[reg1][0] < registers[reg2][0])
        return 1;
    else if(registers[reg1][0] > registers[reg2][0])
        return 0;

    for(int i = 1; i < 16; i++) {
        if(registers[reg1][i] > registers[reg2][i])
            return 1;
        else if(registers[reg1][i] < registers[reg2][i])
            return 0;
    }
    return 0;
}

int GEQ(int reg1, int reg2) {
    int flag = 1;
    for(int i = 0; i < 16; i++)
        if(registers[reg1][i] != registers[reg2][i]) {
            flag = 0;
            break;
        }

    if(flag)
        return 1;

    if(registers[reg1][0] < registers[reg2][0])
        return 1;
    else if(registers[reg1][0] > registers[reg2][0])
        return 0;

    for(int i = 1; i < 16; i++) {
        if(registers[reg1][i] > registers[reg2][i])
            return 1;
        else if(registers[reg1][i] < registers[reg2][i])
            return 0;
    }
    return 0;
}

void PRN(int reg) {
    for(int i = 0; i < 16; i++)
        cout << registers[reg][i];
    cout << endl;
}

void SUM(int reg1, int reg2, int reg3) {
    int sum, carry = 0;

    for(int i = 15; i >= 0; i--) {
        sum = (registers[reg2][i] - '0') + (registers[reg3][i] - '0') + carry;
        if(sum == 3) {
            registers[reg1][i] = '1';
            carry = 1;
        }
        else if(sum == 2) {
            registers[reg1][i] = '0';
            carry = 1;
        }
        else {
            registers[reg1][i] = sum + '0';
            carry = 0;
        }
    }

    if(carry) {
        carry = 0;
        for(int i = 15; i >= 0; i--) {
            sum = registers[reg1][i] - '0' + 1 + carry;
            if(sum == 3) {
                registers[reg1][i] = '1';
                carry = 1;
            }
            else if(sum == 2) {
                registers[reg1][i] = '0';
                carry = 1;
            }
            else {
                registers[reg1][i] = sum + '0';
                carry = 0;
                break;
            }
        }
    }

    if(registers[reg2][0] == registers[reg3][0] && registers[reg1][0] != registers[reg2][0]){
        cout << "OVERFLOW" << endl;
        for(int i = 0; i < 16; i++)
            registers[reg1][i] = '0';
    }
}

void SL(int reg) {
    char str[16];
    for(int i = 0; i < 16; i++)
        str[i] = registers[reg][i];

    for(int i = 1; i < 15; i++)
        registers[reg][i] = str[i + 1];

    if(registers[reg][0] == '1')
        registers[reg][15] = '1';
    else
        registers[reg][15] = '0';
}

void SR(int reg) {
    char str[16];
    for(int i = 0; i < 16; i++)
        str[i] = registers[reg][i];

    for(int i = 2; i < 16; i++)
        registers[reg][i] = str[i - 1];

    if(registers[reg][0] == '1')
        registers[reg][1] = '1';
    else
        registers[reg][1] = '0';
}

int main() {
    int i, j, k;
    int N = 0;  // number of lines in the input
    char c;
    char lines[MAX][16];

    while(1) {
        scanf("%c", &c);
        if(c == '\n')
            break;
        lines[N][0] = c;
        for(i = 1; i < 16; i++)
            scanf("%c", &lines[N][i]);
        N++;
        scanf("%c", &c);
    }

    for(i = 0; i < 8; i++)
        for(j = 0; j < 16; j++)
            registers[i][j] = '0';

    for(i = 0; i < N; i++) {
        if(lines[i][3] == '1' && lines[i][4] == '1' && lines[i][5] == '1' && lines[i][6] == '1') {
            char str[3];
            strncpy(str, lines[i] + 13, 3);
            SR(convert(str, 3));
        }
        else if(lines[i][3] == '1' && lines[i][4] == '1' && lines[i][5] == '1') {
            char str[3];
            strncpy(str, lines[i] + 13, 3);
            SL(convert(str, 3));
        }
        else if(lines[i][3] == '1' && lines[i][5] == '1' && lines[i][6] == '1') {
            char str1[3], str2[3], str3[3];
            strncpy(str1, lines[i] + 7,3);
            strncpy(str2, lines[i] + 10, 3);
            strncpy(str3, lines[i] + 13, 3);
            SUM(convert(str1, 3), convert(str2, 3), convert(str3, 3));
        }
        else if(lines[i][3] == '1' && lines[i][5] == '1') {
            char str[3];
            strncpy(str, lines[i] + 13, 3);
            PRN(convert(str, 3));
        }
        else if(lines[i][3] == '1' && lines[i][6] == '1') {
            i++;
            i = convert(lines[i], 16) - 1;
        }
        else if(lines[i][3] == '1') {
            char str1[3], str2[3];
            strncpy(str1, lines[i] + 10, 3);
            strncpy(str2, lines[i] + 13, 3);
            i++;
            if(GEQ(convert(str1, 3), convert(str2, 3)) == 1)
                i = convert(lines[i], 16) - 1;
        }
        else if(lines[i][4] == '1' && lines[i][5] == '1' && lines[i][6] == '1') {
            char str1[3], str2[3];
            strncpy(str1, lines[i] + 10, 3);
            strncpy(str2, lines[i] + 13, 3);
            i++;
            if(GRE(convert(str1, 3), convert(str2, 3)) == 1)
                i = convert(lines[i], 16) - 1;
        }
        else if(lines[i][4] == '1' && lines[i][5] == '1') {
            char str1[3], str2[3];
            strncpy(str1, lines[i] + 10, 3);
            strncpy(str2, lines[i] + 13, 3);
            i++;
            if(LEQ(convert(str1, 3), convert(str2, 3)) == 1)
                i = convert(lines[i], 16) - 1;
        }
        else if(lines[i][4] == '1' && lines[i][6] == '1') {
            char str1[3], str2[3];
            strncpy(str1, lines[i] + 10, 3);
            strncpy(str2, lines[i] + 13, 3);
            i++;
            if(LESS(convert(str1, 3), convert(str2, 3)) == 1)
                i = convert(lines[i], 16) - 1;
        }
        else if(lines[i][4] == '1') {
            char str1[3], str2[3];
            strncpy(str1, lines[i] + 10, 3);
            strncpy(str2, lines[i] + 13, 3);
            NOT(convert(str1, 3), convert(str2, 3));
        }
        else if(lines[i][5] == '1' && lines[i][6] == '1') {
            char str1[3], str2[3], str3[3];
            strncpy(str1, lines[i] + 7, 3);
            strncpy(str2, lines[i] + 10, 3);
            strncpy(str3, lines[i] + 13, 3);
            OR(convert(str1, 3), convert(str2, 3), convert(str3, 3));
        }
        else if(lines[i][5] == '1') {
            char str1[3], str2[3], str3[3];
            strncpy(str1, lines[i] + 7, 3);
            strncpy(str2, lines[i] + 10, 3);
            strncpy(str3, lines[i] + 13, 3);
            AND(convert(str1, 3), convert(str2, 3), convert(str3, 3));
        }
        else if(lines[i][6] == '1') {
            char str1[3], str2[3];
            strncpy(str1, lines[i] + 10, 3);
            strncpy(str2, lines[i] + 13, 3);
            MOV(convert(str1, 3), convert(str2, 3));
        }
        else {
            char str[3];
            strncpy(str, lines[i] + 13, 3);
            i++;
            MVI(convert(str, 3), lines[i]);
        }
    }
    return 0;
}