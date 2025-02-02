#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <time.h>
#include <ctype.h>
#include<regex.h>
#define PASSWORD_LENGTH 10
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20 //Make sure this is defined


bool userExists(const char *username) {
    FILE *file = fopen("users.txt", "r");
    if (!file) 
    return false;

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char storedUsername[MAX_USERNAME_LENGTH];
        char *delimiterPos = strchr(line, ','); // تغییر ':' به ','
        if (delimiterPos != NULL) {
            strncpy(storedUsername, line, delimiterPos - line);
            storedUsername[delimiterPos - line] = '\0'; // اطمینان از پایان رشته
            if (strcmp(storedUsername, username) == 0) {
                fclose(file);
                return true;
            }
        }
    }


    fclose(file);
    return false;
}

bool isValidPassword(const char *password) {
    if (strlen(password) < 7) return false;

    bool hasUpper = false, hasLower = false, hasDigit = false;
    for (int i = 0; password[i]; i++) {
        if (isupper(password[i])) hasUpper = true;
        else if (islower(password[i])) hasLower = true;
        else if (isdigit(password[i])) hasDigit = true;
    }

    return hasUpper && hasLower && hasDigit;
}
void generateRandomPassword(char *password, size_t length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (size_t i = 0; i < length - 1; i++) {
        int key = rand() % (int)(sizeof(charset) - 1);
        password[i] = charset[key];
        
    }
}

bool isValidEmail(const char *email) {
    int atPos = -1, dotPos = -1;
    for (int i = 0; email[i]; i++) {
        if (email[i] == '@') atPos = i;
        else if (email[i] == '.') dotPos = i;
    }
    if (atPos == -1 || dotPos == -1 || atPos >= dotPos) return false;
    // باقیمانده بررسی
    char domain[10];
    strncpy(domain, &email[dotPos + 1], 10); //کپی تا 10 کاراکتر
    domain[9] = '\0';

    return (strcmp(domain, "com") == 0 || strcmp(domain, "ir") == 0 || strcmp(domain, "org") == 0);
}


void createUser(WINDOW *win) {
    werase(win); // پاک کردن پنجره
    box(win, 0, 0);
    
    char username[20], password[20], email[20];
    attron(COLOR_PAIR(1));
    mvwprintw(win, 1, 2, "Enter your username: ");
    attroff(COLOR_PAIR(1));
    wgetnstr(win, username, sizeof(username) - 1);

    if (userExists(username)) {
        attron(COLOR_PAIR(2));
        mvwprintw(win, 2, 2, "Username already exists!");
        attroff(COLOR_PAIR(2));
        wrefresh(win);
        wgetch(win); // منتظر ماندن برای ورودی کلید
        return;
    }

    while (true) {
        attron(COLOR_PAIR(1));
        mvwprintw(win, 2, 2, "Enter your password: ");
        attroff(COLOR_PAIR(1));
        wgetnstr(win, password, sizeof(password) - 1);

        if (!isValidPassword(password)) {
            attron(COLOR_PAIR(2));
            mvwprintw(win, 3, 2, "invalid password!");
            mvwprintw(win, 4, 2, "do you wanna take random pass?(y or n)");
            attroff(COLOR_PAIR(2));
            wrefresh(win);
            char choice;

            choice=wgetch(win);
            if(choice=='y'||choice=='Y'){
                generateRandomPassword(password, PASSWORD_LENGTH); // تولید رمز عبور تصادفی
                break; // ادامه به مرحله بعد
            } else if (choice == 'n' || choice == 'N') {
                return; // برگشت به صفحه اصلی
            }
        } else {
            break; // رمز عبور معتبر است
        }
    }

    mvwprintw(win, 6, 2, "your password: %s", password);
    wrefresh(win);

    while (true) {
        attron(COLOR_PAIR(1));
        mvwprintw(win, 7, 2, "Enter your Email: ");
        attroff(COLOR_PAIR(1));
        wgetnstr(win, email, sizeof(email)+10);

        if (!isValidEmail(email)) {
            attron(COLOR_PAIR(2));
            mvwprintw(win, 8, 2, "Invalid email format!");
            attroff(COLOR_PAIR(2));
            wrefresh(win);
            wgetch(win); // منتظر ماندن برای ورودی کلید
        } else {
            break; // ایمیل معتبر است
        }
    }

    FILE *file = fopen("users.txt", "a");
    if (file) {
        fprintf(file, "%s,%s,%s\n", username, password, email);
        fclose(file);
        attron(COLOR_PAIR(3));
        mvwprintw(win, 9, 2, "Account created successfully!");
        attroff(COLOR_PAIR(3));
    } else {
        attron(COLOR_PAIR(2));
        mvwprintw(win, 9, 2, "Error creating account!");
        attroff(COLOR_PAIR(2));
    }
    
    wrefresh(win);
    wgetch(win); // منتظر ماندن برای ورودی کلید
}

void loginWindow(WINDOW *mainWin) {
    werase(mainWin);
    box(mainWin, 0, 0);
    attron(COLOR_PAIR(1));
    mvwprintw(mainWin, 1, 2, "Enter username:");
    attroff(COLOR_PAIR(1));
    char username[MAX_USERNAME_LENGTH + 1];
    char password[MAX_PASSWORD_LENGTH + 1];

    // گرفتن نام کاربری
    wgetnstr(mainWin, username, MAX_PASSWORD_LENGTH);
    attron(COLOR_PAIR(1));
    mvwprintw(mainWin, 2, 2, "Enter password: ");
    attroff(COLOR_PAIR(1));
    wgetnstr(mainWin, password, MAX_USERNAME_LENGTH);


    // بررسی اعتبارنامۀ کاربر
    FILE *userFile = fopen("users.txt", "r");

    char line[256]; // حداکثر طول هر خط در فایل
    bool userFound = false;
    char storedPassword[100];

    while (fgets(line, sizeof(line), userFile) != NULL) {
        // حذف newline از انتهای خط خوانده شده
        line[strcspn(line, "\n")] = 0;

        // استفاده از ',' برای جداسازی
        char *delimiterPos = strchr(line, ',');
        if (delimiterPos == NULL) 
        continue; // خط نامعتبر

        char tempUsername[MAX_USERNAME_LENGTH] = {0}; // نام کاربری موقتی
        strncpy(tempUsername, line, delimiterPos - line);
        tempUsername[delimiterPos - line] = '\0';

        strncpy(storedPassword, delimiterPos + 1, sizeof(storedPassword));
        storedPassword[sizeof(storedPassword) - 1] = '\0'; // جلوگیری از overflow

        // بررسی نام کاربری
        if (strcmp(tempUsername, username) == 0) {
            userFound = true;
            break;
        }
    }

    fclose(userFile);

    if (userFound) {
        if (strcmp(storedPassword, password) == 0) {
            attron(COLOR_PAIR(3)); //  استفاده از توابع ncurses
            mvwprintw(mainWin, 5, 2, "You have successfully entered the game:)");
            attroff(COLOR_PAIR(3));
            wrefresh(mainWin);
            napms(2000);
        } else {
            attron(COLOR_PAIR(2));
            mvwprintw(mainWin, 3, 2, "Wrong password!");
            attroff(COLOR_PAIR(2));
        }
    } else {
        attron(COLOR_PAIR(2));
        mvwprintw(mainWin, 4, 2, "Username does'nt exist!");
        attroff(COLOR_PAIR(2));
    }

    wrefresh(mainWin);
    noecho();
    attron(COLOR_PAIR(1));
    mvwprintw(mainWin, 6, 2, "1 Log in as a guest.");
    mvwprintw(mainWin, 7, 2, "2 Find your password.");
    mvwprintw(mainWin, 8, 2, "3 return to the first page.");
    attroff(COLOR_PAIR(1));
    wrefresh(mainWin);

    int ch;
    while ((ch = wgetch(mainWin)) != 'b') {
        if (ch == '1') {
            attron(COLOR_PAIR(3));
            mvwprintw(mainWin, 10, 2, "You have entered the game as a guest:)");
            attroff(COLOR_PAIR(3));
            wrefresh(mainWin);
            napms(2000); // کمی صبر کنید قبل از رفتن به بازی
            // اینجا کد ورود به بازی را قرار دهید
            break;
        } else if (ch == '2') {
            if (userFound) {
                attron(COLOR_PAIR(3));
                mvwprintw(mainWin, 10, 2, "Your password: %s (save it)", storedPassword);
                attroff(COLOR_PAIR(3));
                wrefresh(mainWin);
                napms(2000); // کمی صبر کنید تا کاربر رمز را بخواند
                mvwprintw(mainWin, 10, 2, "                              "); // پاک کردن پیام
            } else {
                attron(COLOR_PAIR(2));
                mvwprintw(mainWin, 10, 2, "Password not found.");
                attroff(COLOR_PAIR(2));
                wrefresh(mainWin);
            }
        }else if(ch=='3'){
            break;
        }
        wrefresh(mainWin);
    }
}


void mainMenu(WINDOW *win) {
    char ch;
    while (true) {
        werase(win);
        box(win, 0, 0);
        attron(COLOR_PAIR(1));
        mvwprintw(win, 1, 2, "Welcome to Nazila's Game! :)");
        mvwprintw(win, 2, 2, "1 New Account");
        mvwprintw(win, 3, 2, "2 Login");
        mvwprintw(win, 4, 2, "3 New Game");
        mvwprintw(win, 5, 2, "4 Previous Game");
        mvwprintw(win, 6, 2, "5 Score Board");
        mvwprintw(win, 7, 2, "6 Settings");
        mvwprintw(win, 8, 2, "Choose number!");
        attroff(COLOR_PAIR(1));
        wrefresh(win);

        ch = wgetch(win);
        switch (ch) {
            case '1':
                createUser(win); // تابع جدید برای ثبت‌نام
                break;
            case '2':
                loginWindow(win);// کد ورود
                break;
            case '3':
                // کد شروع بازی جدید
                break;
            case '4':
                // کد بارگذاری بازی قبلی
                break;
            case '5':
                // کد مشاهده امتیازها
                break;
            case '6':
                // کد تنظیمات
                break;
        }
    }
}

int main() {
    initscr();
    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);

    curs_set(0);

    int ymax, xmax;
    getmaxyx(stdscr, ymax, xmax);

    WINDOW *win = newwin(20, 50, 0, 0);

    mainMenu(win); // نمایش منوی اصلی

    delwin(win);
    endwin();
    return 0;
}