/*
*   The User-Friendly Console Calculator - ufccalc
*/

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ncurses.h>

#define MAX_BUFF 8 // input limited to 8 chars (for now)

const char operators[] = "+-*/=^"; // list of valid operators
const int y_prompt_pos = 6;
char buffer[9] = ""; // used to temporarily store and manipulate numbers
unsigned char opr; // keeps track of the last operation
unsigned char input;
double x, y; // the result will always be stored in x

void append_chr(char* str, const char c);
void reset(); // reset prompt, buffer, upper text
void calculate(); // perform the calculation and reset
void reprint_current(); // update the prompt buffer and refresh

int main()
{
    // init ncurses
    initscr();
    noecho();
    cbreak();

    // title, help and user prompt
    printw("The User-Friendly Console Calculator");
    mvprintw(y_prompt_pos - 4, 0, "Press \'n\' for negative numbers, \'b\' to erase the last digit");
    mvprintw(y_prompt_pos - 3, 0, "\'c\' to clear the screen and \'q\' to quit.");
    mvprintw(y_prompt_pos - 2, 0, "Supported operators: \'%c\' \'%c\' \'%c\' \'%c\' \'%c\' \'%c\'", 
            operators[0], operators[1], operators[2], operators[3], operators[4], operators[5]);
    mvprintw(y_prompt_pos + 1, 0, ">>> ");
    refresh();

    // main loop
    while (1) {
        if (opr) {
            // print upper text if an operator key was pressed
            mvprintw(y_prompt_pos, 0, "%f %c", x, opr);
            refresh();
        }

        input = getchar(); // read key press

        if (input == 'q') { // quit
            break;
        } else if (input == 'c') {  // clear everything
            reset();
            opr = 0;
            refresh();
        } else if (strcmp(buffer, "") && input == 'b') { // backspace
            buffer[strlen(buffer) - 1] = 0;
            reprint_current();
        } else if ((input >= '0' && input <= '9' && strlen(buffer) < MAX_BUFF) || 
                   (strcmp(buffer, "") && input == '.' && !strchr(buffer, input) 
                    && strcmp(buffer, "-"))) {
            // add digit to the buffer or insert floating point
            append_chr(buffer, input);
            reprint_current();
        } else if (!strcmp(buffer, "") && input == 'n') {
            // insert negative number
            append_chr(buffer, '-');
            reprint_current();
        } else if (strchr(operators, input)) {
            if (!strcmp(buffer, "") && opr && input != '=') {
                // allows you to change the operator before entering a new number
                opr = input;
            } else if (strcmp(buffer, "") && strcmp(buffer, "-")) {
                if (opr && input == '=') {
                    // evaluate previous operation
                    calculate();
                } else if (opr) {
                    // evaluate previous operation and update the operator
                    calculate();
                    opr = input;
                } else if (input != '=') {
                    // parse the buffer to be displayed as upper text
                    x = strtod(buffer, NULL);
                    opr = input;
                    strcpy(buffer, "");
                }
            }
        }


    }

    // end ncurses
    endwin();
    return 0;
}

void append_chr(char* str, const char c)
{
    char temp[2];
    temp[0] = c;
    temp[1] = 0;
    strcat(str, temp);
}

void reset()
{
    move(y_prompt_pos, 0);
    clrtoeol();
    move(y_prompt_pos + 1, 4);
    clrtoeol();
    strcpy(buffer, "");
}

void calculate()
{
    y = strtod(buffer, NULL); // parse the buffer
    switch (opr) {
        case '+':
            x += y;
            break;
        case '-':
            x -= y;
            break;
        case '*':
            x *= y;
            break;
        case '/':
            x /= y;
            break;
        case '^':
            x = pow(x, y); 
            break;
    }
    reset();
}

void reprint_current()
{
    move(y_prompt_pos + 1, 4);
    clrtoeol(); // clear prompt
    printw(buffer); // display new prompt
    refresh();
}

