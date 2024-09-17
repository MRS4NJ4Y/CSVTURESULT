#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

#define LOCAL_VERSION "V1.1.0"
#define VERSION_URL "https://raw.githubusercontent.com/MRS4NJ4Y/CSVTURESULT/main/version.txt"
#define VERSION_FILE "version.txt"
#define REPO_URL "https://github.com/MRS4NJ4Y/CSVTURESULT"
    
const char *green_bold = "\033[1;32m"; 
const char *yellow_bold = "\033[1;33m"; 
const char *magenta_bold = "\033[1;35m";
const char *cyan_bold = "\033[1;36m";
const char *color_end = "\033[0m";   

void clear_screen() {
    system("cls");
}

void printLogo() {
   
    printf("%s", cyan_bold);
    printf("  ______    ______   __     __  ________  __    __       \n");
    printf(" /      \\  /      \\ |  \\   |  \\|        \\|  \\  |  \\      \n");
    printf("|  $$$$$$\\|  $$$$$$\\| $$   | $$ \\$$$$$$$$| $$  | $$      \n");
    printf("| $$   \\$$| $$___\\$$| $$   | $$   | $$   | $$  | $$      \n");
    printf("| $$       \\$$    \\  \\$$\\ /  $$   | $$   | $$  | $$      \n");
    printf("| $$   __  _\\$$$$$$\\  \\$$\\  $$    | $$   | $$  | $$      \n");
    printf("| $$__/  \\|  \\__| $$   \\$$ $$     | $$   | $$__/ $$      \n");
    printf(" \\$$    $$ \\$$    $$    \\$$$      | $$    \\$$    $$      \n");
    printf("  \\$$$$$$   \\$$$$$$      \\$        \\$$     \\$$$$$$.exe     \n");
    printf("%s", color_end);
}

void download_file(const char *url, const char *output) {
#ifdef _WIN32
    char command[256];
    snprintf(command, sizeof(command), "powershell -Command \"Invoke-WebRequest -Uri '%s' -OutFile '%s'\"", url, output);
    printf("Running command: %s\n", command);
    system(command);
#elif __APPLE__
    char command[256];
    snprintf(command, sizeof(command), "curl -o %s %s", output, url);
    printf("Running command: %s\n", command);
    system(command);
#else
    char command[256];
    snprintf(command, sizeof(command), "wget -q -O %s %s", output, url);
    printf("Running command: %s\n", command);
    system(command);
#endif
}
int check_version_and_redirect() {
    char remote_version[100] = "";
    download_file(VERSION_URL, VERSION_FILE);
    FILE *file = fopen(VERSION_FILE, "r");
    if (file == NULL) {
        printf("\033[1;31mError: Could not open %s\033[0m\nn", VERSION_FILE);
        return 1;
    }
    if (fgets(remote_version, sizeof(remote_version), file) != NULL) {
        remote_version[strcspn(remote_version, "\n")] = 0;
    }
    fclose(file);
    if (strcmp(LOCAL_VERSION, remote_version) != 0) {
        printLogo();
        printf("\033[1;31m\nVersion mismatch! Local version: %s, Remote version. %s\n\n\033[0m", LOCAL_VERSION, remote_version);
        printf("\033[1;35mDownload the new version from the repository and open it.\n\n\033[0m");
        printf("\033[1;35mRedirecting to the repository for requesting to download new version and check what's new...\n\n\033[0m");
#ifdef _WIN32
        system("start " REPO_URL);
#elif __APPLE__
        system("open " REPO_URL);
#else
        system("xdg-open " REPO_URL);
#endif
        printf("\033[1;35mOpen the downloaded program after downloading the latest version from the repository.\n\n\033[0m");
        getch();
        return 1;
    } else {
        printf("\n\033[1;34m Version is up to date: %s\033[0m\n\n", LOCAL_VERSION);
        return 0;
    }
}

int main() {
    printLogo();
    char connection='y';
    printf("\n\n\033[1;35mIf you do not have a good Internet connection, the program will not open.\n\033[0");
    printf("\n\033[1;33mAre you connected to the internet(y/n):\033[0");
    scanf("%c", &connection);
    if (connection == 'y'|| connection =='Y') {
        printf("\n\033[1;35mVerifying your Internet connection...\n\033[0");
    }else{
        printf("\n\033[1;35mConnect to the Internet and press any key.\n\033[0");
        getch();
    }
    if (check_version_and_redirect() != 0) {
        return 1;
    }
    char roll_no[100];
    char command[300];
    int option, year, semster, session;
    char choice = 'y';
    int loop=1, count;
    
    while(loop!=0) {
        clear_screen();
        printLogo();
        printf("\n\n\033[1;34m *********************Version %s Copyright (c) 2024**********************\033[0m\n\n\n",LOCAL_VERSION);
        printf("\033[1;32m 1. How to use\n 2. Admit Card \n 3. Result \n 4. All PYQ\n 5. Issue/Feedback \n 6. About \n 0. Exit\033[0m\n\n");
        printf("\033[1;33mselect Options:\033[0m ");
        scanf("%d", &option);
        choice = 'y';

        switch (option) {
            case 1:{
                printf("\n\033[1;34m******************************How to use********************************\033[0m\n\n");
                printf("%s",magenta_bold);
                printf("This is a simple program to help B.Tech students developed by MRS4NJ4Y.\n\n");
                printf("if you want to know using process of program, visit the repository.\n");
                printf("%s", color_end);
                printf("\033[1;33mDo you want to vist repository(y/n): \033[0m");
                scanf(" %c", &choice);
                if (choice == 'y' || choice == 'Y') {
                    system("start " REPO_URL);
                }
            }
            break;
            case 2: {
                printf("\033[1;31m*You need to be logged in to CSVTU Digiversity website in the default browser to use this feature.\n\033[0m");
                printf("\033[1;33m*Are you logged in to CSVTU website in the default browser?(y/n);\033[0m");
                scanf(" %c", &choice);
                if (choice == 'y' || choice == 'Y') {
                    printf("\n\033[1;35mIf your login status is failed then I am redirecting to login page,\nand when I open CSVTU Digiversity login page you have to login otherwise it will not work.\033[0m\n");
                } else {
                    printf("\n\033[1;31mPlease log in to the CSVTU Digiversity website in the default browser I have opened,\notherwise you will not be able to use it.\n\033[0m");
                    snprintf(command, sizeof(command), "start \"\" \"https://csvtu.digivarsity.online/WebApp/Result/SemesterResult.aspx?\"");
                    system(command);
                }
                printf("\n\033[0;34m***********************************Admit Card**********************************\n\n\033[0m");
                printf("\033[1;33m Enter year of Admit Card in Format(YYYY): \033[0m");
                scanf("%d", &year);
                printf("%s",green_bold);
                printf(" 1. 1st semester \n 2. 2nd semester \n 3. 3rd semester \n 4. 4th semester \n 5. 5th semester \n 6. 6th semester \n 7. 7th semester \n 8. 8th semester \n ");
                printf("%s", color_end);
                printf("\033[1;33mSelect the semester: \033[0m");
                scanf("%d", &semster);
                choice = 'y';
                
                switch (semster){
                    case 1:{
                        printf("\033[1;32m 1. Apr-May \n 2. Nov-Dec \n\033[0m");
                        printf("%s",yellow_bold);
                        printf("Select the session: ");
                        scanf("%d", &session);
                        choice = 'y';

                        switch(session){
                            case 1:{
                                while (choice == 'y' || choice == 'Y') {
                                printf("Enter your roll number: ");
                                scanf("%s", roll_no);
                                snprintf(command, sizeof(command), "start \"\" \"https://csvtu.digivarsity.online/WebApp/Examination/AdmitCard.aspx?RollNo=%s&ExamSession=Apr-May%%20%d&Semester=1%%20Semester\"", roll_no, year);
                                system(command);
                                printf("Do you want to enter another? (y/n): ");
                                    scanf(" %c", &choice);
                                }
                            }
                            break;
                            case 2:{
                                while (choice == 'y' || choice == 'Y') {
                                printf("Enter your roll number: ");
                                scanf("%s", roll_no);
                                snprintf(command, sizeof(command), "start \"\" \"https://csvtu.digivarsity.online/WebApp/Examination/AdmitCard.aspx?RollNo=%s&ExamSession=Nov-Dec%%20%d&Semester=1%%20Semester\"", roll_no, year);
                                system(command);
                                printf("Do you want to enter another? (y/n): ");
                                    scanf(" %c", &choice);
                                }
                            }
                            printf("%s",color_end);
                            break;
                            default:{
                                printf("\033[1;31mInvalid session!\n\033[0m");
                                break;
                            }
                        }
                    }
                    break;
                    case 2:{
                        printf(" \033[1;32m1. Apr-May \n 2. Nov-Dec \n\033[0m");
                        printf("%s",yellow_bold);
                        printf("Select the session: ");
                        scanf("%d", &session);
                        choice = 'y';
                        
                        switch(session){
                            case 1:{
                                while (choice == 'y' || choice == 'Y') {
                                printf("Enter your roll number: ");
                                scanf("%s", roll_no);
                                snprintf(command, sizeof(command), "start \"\" \"https://csvtu.digivarsity.online/WebApp/Examination/AdmitCard.aspx?RollNo=%s&ExamSession=Apr-May%%20%d&Semester=2%%20Semester\"", roll_no, year);
                                system(command);
                                printf("Do you want to enter another? (y/n): ");
                                    scanf(" %c", &choice);
                                }
                            }
                            break;
                            case 2:{
                                while (choice == 'y' || choice == 'Y') {
                                printf("Enter your roll number: ");
                                scanf("%s", roll_no);
                                snprintf(command, sizeof(command), "start \"\" \"https://csvtu.digivarsity.online/WebApp/Examination/AdmitCard.aspx?RollNo=%s&ExamSession=Nov-Dec%%20%d&Semester=2%%20Semester\"", roll_no, year);
                                system(command);
                                printf("Do you want to enter another? (y/n): ");
                                    scanf(" %c", &choice);
                                }
                            }
                            printf("%s",color_end);
                            break;
                            default:{
                                printf("\033[1;31mInvalid session!\n\033[0m");
                                break;
                            }
                        }
                    }
                    break;
                    case 3: {
                        printf(" \033[1;32m1. Apr-May \n 2. Nov-Dec \n\033[0m");
                        printf("%s",yellow_bold);
                        printf("Select the session: ");
                        scanf("%d", &session);
                        choice = 'y';
                        
                        switch(session){
                            case 1:{
                                while (choice == 'y' || choice == 'Y') {
                                printf("Enter your roll number: ");
                                scanf("%s", roll_no);
                                snprintf(command, sizeof(command), "start \"\" \"https://csvtu.digivarsity.online/WebApp/Examination/AdmitCard.aspx?RollNo=%s&ExamSession=Apr-May%%20%d&Semester=3%%20Semester\"", roll_no, year);
                                system(command);
                                printf("Do you want to enter another? (y/n): ");
                                    scanf(" %c", &choice);
                                }
                            }
                            break;
                            case 2:{
                                while (choice == 'y' || choice == 'Y') {
                                printf("Enter your roll number: ");
                                scanf("%s", roll_no);
                                snprintf(command, sizeof(command), "start \"\" \"https://csvtu.digivarsity.online/WebApp/Examination/AdmitCard.aspx?RollNo=%s&ExamSession=Nov-Dec%%20%d&Semester=3%%20Semester\"", roll_no, year);
                                system(command);
                                printf("Do you want to enter another? (y/n): ");
                                    scanf(" %c", &choice);
                                }
                            }
                            printf("%s",color_end);
                            break;
                            default:{
                                printf("\033[1;31mInvalid session!\n\033[0m");
                                break;
                            }
                        }
                    }
                    break;
                    case 4: {
                        printf(" \033[1;32m1. Apr-May \n 2. Nov-Dec \n\033[0m");
                        printf("%s",yellow_bold);
                        printf("Select the session: ");
                        scanf("%d", &session);
                        choice = 'y';
                        
                        switch(session){
                            case 1:{
                                while (choice == 'y' || choice == 'Y') {
                                printf("Enter your roll number: ");
                                scanf("%s", roll_no);
                                snprintf(command, sizeof(command), "start \"\" \"https://csvtu.digivarsity.online/WebApp/Examination/AdmitCard.aspx?RollNo=%s&ExamSession=Apr-May%%20%d&Semester=4%%20Semester\"", roll_no, year);
                                system(command);
                                printf("Do you want to enter another? (y/n): ");
                                    scanf(" %c", &choice);
                                }
                            }
                            break;
                            case 2:{
                                while (choice == 'y' || choice == 'Y') {
                                printf("Enter your roll number: ");
                                scanf("%s", roll_no);
                                snprintf(command, sizeof(command), "start \"\" \"https://csvtu.digivarsity.online/WebApp/Examination/AdmitCard.aspx?RollNo=%s&ExamSession=Nov-Dec%%20%d&Semester=4%%20Semester\"", roll_no, year);
                                system(command);
                                printf("Do you want to enter another? (y/n): ");
                                    scanf(" %c", &choice);
                                }
                            }
                            printf("%s",color_end);
                            break;
                            default:{
                                printf("\033[1;31mInvalid session!\n\033[0m");
                                break;
                            }
                        }
                    }
                    break;
                    case 5: {
                        printf(" \033[1;32m1. Apr-May \n 2. Nov-Dec \n\033[0m");
                        printf("%s",yellow_bold);
                        printf("Select the session: ");
                        scanf("%d", &session);
                        choice = 'y';
                        
                        switch(session){
                            case 1:{
                                while (choice == 'y' || choice == 'Y') {
                                printf("Enter your roll number: ");
                                scanf("%s", roll_no);
                                snprintf(command, sizeof(command), "start \"\" \"https://csvtu.digivarsity.online/WebApp/Examination/AdmitCard.aspx?RollNo=%s&ExamSession=Apr-May%%20%d&Semester=5%%20Semester\"", roll_no, year);
                                system(command);
                                printf("Do you want to enter another? (y/n): ");
                                    scanf(" %c", &choice);
                                }
                            }
                            break;
                            case 2:{
                                while (choice == 'y' || choice == 'Y') {
                                printf("Enter your roll number: ");
                                scanf("%s", roll_no);
                                snprintf(command, sizeof(command), "start \"\" \"https://csvtu.digivarsity.online/WebApp/Examination/AdmitCard.aspx?RollNo=%s&ExamSession=Nov-Dec%%20%d&Semester=5%%20Semester\"", roll_no, year);
                                system(command);
                                printf("Do you want to enter another? (y/n): ");
                                    scanf(" %c", &choice);
                                }
                            }
                            printf("%s",color_end);
                            break;
                            default:{
                                printf("\033[1;31mInvalid session!\n\033[0m");
                                break;
                            }
                        }
                    }
                    break;
                    case 6: {
                        printf(" \033[1;32m1. Apr-May \n 2. Nov-Dec \n\033[0m");
                        printf("%s", yellow_bold);
                        printf("Select the session: ");
                        scanf("%d", &session);
                        choice = 'y';
                        
                        switch(session){
                            case 1:{
                                while (choice == 'y' || choice == 'Y') {
                                printf("Enter your roll number: ");
                                scanf("%s", roll_no);
                                snprintf(command, sizeof(command), "start \"\" \"https://csvtu.digivarsity.online/WebApp/Examination/AdmitCard.aspx?RollNo=%s&ExamSession=Apr-May%%20%d&Semester=6%%20Semester\"", roll_no, year);
                                system(command);
                                printf("Do you want to enter another? (y/n): ");
                                    scanf(" %c", &choice);
                                }
                            }
                            break;
                            case 2:{
                                while (choice == 'y' || choice == 'Y') {
                                printf("Enter your roll number: ");
                                scanf("%s", roll_no);
                                snprintf(command, sizeof(command), "start \"\" \"https://csvtu.digivarsity.online/WebApp/Examination/AdmitCard.aspx?RollNo=%s&ExamSession=Nov-Dec%%20%d&Semester=6%%20Semester\"", roll_no, year);
                                system(command);
                                printf("Do you want to enter another? (y/n): ");
                                    scanf(" %c", &choice);
                                }
                            }
                            printf("%s",color_end);
                            break;
                            default:{
                                printf("\033[1;31mInvalid session!\n\033[0m");
                                break;
                            }
                        }
                    }
                    break;
                    case 7:{
                        printf(" \033[1;32m1. Apr-May \n 2. Nov-Dec \n\033[0m");
                        printf("%s", yellow_bold);
                        printf("Select the session: ");
                        scanf("%d", &session);
                        choice = 'y';
                        
                        switch(session){
                            case 1:{
                                while (choice == 'y' || choice == 'Y') {
                                printf("Enter your roll number: ");
                                scanf("%s", roll_no);
                                snprintf(command, sizeof(command), "start \"\" \"https://csvtu.digivarsity.online/WebApp/Examination/AdmitCard.aspx?RollNo=%s&ExamSession=Apr-May%%20%d&Semester=7%%20Semester\"", roll_no, year);
                                system(command);
                                printf("Do you want to enter another? (y/n): ");
                                    scanf(" %c", &choice);
                                }
                            }
                            break;
                            case 2:{
                                while (choice == 'y' || choice == 'Y') {
                                printf("Enter your roll number: ");
                                scanf("%s", roll_no);
                                snprintf(command, sizeof(command), "start \"\" \"https://csvtu.digivarsity.online/WebApp/Examination/AdmitCard.aspx?RollNo=%s&ExamSession=Nov-Dec%%20%d&Semester=7%%20Semester\"", roll_no, year);
                                system(command);
                                printf("Do you want to enter another? (y/n): ");
                                    scanf(" %c", &choice);
                                }
                            }
                            printf("%s",color_end);
                            break;
                            default:{
                                printf("\033[1;31mInvalid session!\n\033[0m");
                                break;
                            }
                        }
                    }
                    break;
                    case 8:{
                        printf(" \033[1;32m1. Apr-May \n 2. Nov-Dec \n\033[0m");
                        printf("%s", yellow_bold);
                        printf("Select the session: ");
                        scanf("%d", &session);
                        choice = 'y';
                        
                        switch(session){
                            case 1:{
                                while (choice == 'y' || choice == 'Y') {
                                printf("Enter your roll number: ");
                                scanf("%s", roll_no);
                                snprintf(command, sizeof(command), "start \"\" \"https://csvtu.digivarsity.online/WebApp/Examination/AdmitCard.aspx?RollNo=%s&ExamSession=Apr-May%%20%d&Semester=8%%20Semester\"", roll_no, year);
                                system(command);
                                printf("Do you want to enter another? (y/n): ");
                                    scanf(" %c", &choice);
                                }
                            }
                            break;
                            case 2:{
                                while (choice == 'y' || choice == 'Y') {
                                printf("Enter your roll number: ");
                                scanf("%s", roll_no);
                                snprintf(command, sizeof(command), "start \"\" \"https://csvtu.digivarsity.online/WebApp/Examination/AdmitCard.aspx?RollNo=%s&ExamSession=Nov-Dec%%20%d&Semester=8%%20Semester\"", roll_no, year);
                                system(command);
                                printf("Do you want to enter another? (y/n): ");
                                    scanf(" %c", &choice);
                                }
                            }
                            printf("%s",color_end);
                            break;
                            default:{
                                printf("\033[1;31mInvalid session!\n\033[0m");
                                break;
                            }
                        }
                    }
                    break;
                    default:{
                        printf("\033[1;31mInvalid Option!\n\033[0m");
                        break;
                    }
                }
            }
            break;
            case 3:{
                printf("\033[1;31m*You need to be logged in to CSVTU Digiversity website in the default browser to use this feature.\n\033[0m");
                printf("\033[1;33m*Are you logged in to CSVTU website in the default browser?(y/n);\033[0m");
                scanf(" %c", &choice);
                if (choice == 'y' || choice == 'Y') {
                    printf("\n\033[1;35mIf your login status is failed then I am redirecting to login page,\nand when I open CSVTU Digiversity login page you have to login otherwise it will not work.\033[0m\n");
                } else {
                    printf("\n\033[1;31mPlease log in to the CSVTU Digiversity website in the default browser I have opened,\notherwise you will not be able to use it.\n\033[0m");
                    snprintf(command, sizeof(command), "start \"\" \"https://csvtu.digivarsity.online/WebApp/Result/SemesterResult.aspx?\"");
                    system(command);
                }
                printf("\n\033[1;34m*********************************Result**********************************\n\n\033[0m");
                printf("\033[1;33m Enter year of Result in Format(YYYY):\033[0m ");
                scanf("%d", &year);
                printf("%s",green_bold);
                printf(" 1. 1st semester \n 2. 2nd semester \n 3. 3rd semester \n 4. 4th semester \n 5. 5th semester \n 6. 6th semester \n 7. 7th semester \n 8. 8th semester \n ");
                printf("%s",color_end );
                printf("\033[1;33mSelect the semester: \033[0m");
                scanf("%d", &semster);
                int resulttype;
                char resultString[100];
                printf("\033[1;32m1. Regular\n2. RTRV\n3. RRV\n4. Others\n\033[0m");
                printf("\033[1;33mSelect Result Type: \033[0m");
                scanf("%d", &resulttype);
                if (resulttype == 1) {
                    strcpy(resultString, "Regular");
                } 
                else if (resulttype == 2) {
                    strcpy(resultString, "RTRV");
                } 
                else if (resulttype == 3) {
                    strcpy(resultString, "RRV");
                } 
                else if (resulttype == 4) {
                    printf("\033[1;33mEnter result type: \033[0m");
                    scanf("%s", resultString);
                } 
                else {
                    printf("\033[1;31mInvalid result type!\n\033[0m");
                    return 1;
                }         
                switch (semster){
                    case 1:{
                        printf("\033[1;32m 1. Apr-May \n 2. Nov-Dec \n\033[0m");
                        printf("%s", yellow_bold);
                        printf("Select the session: ");
                        scanf("%d", &session);
                        choice = 'y';

                        switch(session){
                            case 1:{while (choice == 'y' || choice == 'Y') {
                                printf("Enter your roll number: ");
                                scanf("%s", roll_no);
                                snprintf(command, sizeof(command), "start \"\" \"https://csvtu.digivarsity.online/WebApp/Result/SemesterResult.aspx?S=1%%20SEMESTER&E=Apr-May%%20%d&R=%s&T=%s\"",year, roll_no, resultString);
                                system(command);printf("Do you want to enter another? (y/n): ");
                                    scanf(" %c", &choice);
                                }
                            }
                            break;
                            case 2:{
                                while (choice == 'y' || choice == 'Y') {
                                printf("Enter your roll number: ");
                                scanf("%s", roll_no);
                                snprintf(command, sizeof(command), "start \"\" \"https://csvtu.digivarsity.online/WebApp/Result/SemesterResult.aspx?S=1%%20SEMESTER&E=Nov-Dec%%20%d&R=%s&T=%s\"",year, roll_no, resultString);
                                system(command);
                                printf("Do you want to enter another? (y/n): ");
                                    scanf(" %c", &choice);
                                }
                            }
                            printf("%s",color_end);
                            break;
                            default:{
                                printf("\033[1;31mInvalid session!\n\033[0m");
                                break;
                            }
                        }
                    }
                    break;
                    case 2:{
                        printf("\033[1;32m 1. Apr-May \n 2. Nov-Dec \n\033[0m");
                        printf("%s", yellow_bold);
                        printf("Select the session: ");
                        scanf("%d", &session);
                        choice = 'y';
                        
                        switch(session){
                            case 1:{
                                while (choice == 'y' || choice == 'Y') {
                                printf("Enter your roll number: ");
                                scanf("%s", roll_no);
                                snprintf(command, sizeof(command), "start \"\" \"https://csvtu.digivarsity.online/WebApp/Result/SemesterResult.aspx?S=2%%20SEMESTER&E=Apr-May%%20%d&R=%s&T=%s\"",year, roll_no, resultString);
                                system(command);
                                printf("Do you want to enter another? (y/n): ");
                                    scanf(" %c", &choice);
                                }
                            }
                            break;
                            case 2:{
                                while (choice == 'y' || choice == 'Y') {
                                printf("Enter your roll number: ");
                                scanf("%s", roll_no);
                                snprintf(command, sizeof(command), "start \"\" \"https://csvtu.digivarsity.online/WebApp/Result/SemesterResult.aspx?S=2%%20SEMESTER&E=Nov-Dec%%20%d&R=%s&T=%s\"",year, roll_no, resultString);
                                system(command);
                                printf("Do you want to enter another? (y/n): ");
                                    scanf(" %c", &choice);
                                }
                            }
                            printf("%s",color_end);
                            break;
                            default:{
                                printf("\033[1;31mInvalid session!\n\033[0m");
                                break;
                            }
                        }
                    }
                    break;
                    case 3: {
                        printf("\033[1;32m 1. Apr-May \n 2. Nov-Dec \n\033[0m");
                        printf("%s", yellow_bold);
                        printf("Select the session: ");
                        scanf("%d", &session);
                        choice = 'y';
                        
                        switch(session){
                            case 1:{
                                while (choice == 'y' || choice == 'Y') {
                                printf("Enter your roll number: ");
                                scanf("%s", roll_no);
                                snprintf(command, sizeof(command), "start \"\" \"https://csvtu.digivarsity.online/WebApp/Result/SemesterResult.aspx?S=3%%20SEMESTER&E=Apr-May%%20%d&R=%s&T=%s\"",year, roll_no, resultString);
                                system(command);
                                printf("Do you want to enter another? (y/n): ");
                                    scanf(" %c", &choice);
                                }
                            }
                            break;
                            case 2:{
                                while (choice == 'y' || choice == 'Y') {
                                printf("Enter your roll number: ");
                                scanf("%s", roll_no);
                                snprintf(command, sizeof(command), "start \"\" \"https://csvtu.digivarsity.online/WebApp/Result/SemesterResult.aspx?S=3%%20SEMESTER&E=Nov-Dec%%20%d&R=%s&T=%s\"",year, roll_no, resultString);
                                system(command);
                                printf("Do you want to enter another? (y/n): ");
                                    scanf(" %c", &choice);
                                }
                            }
                            printf("%s",color_end);
                            break;  
                            default:{
                                printf("\033[1;31mInvalid session!\n\033[0m");
                                break;
                            }
                        }
                    }
                    break;
                    case 4: {
                        printf("\033[1;32m 1. Apr-May \n 2. Nov-Dec \n\033[0m");
                        printf("%s", yellow_bold);
                        printf("Select the session: ");
                        scanf("%d", &session);
                        choice = 'y';
                        
                        switch(session){
                            case 1:{
                                while (choice == 'y' || choice == 'Y') {
                                printf("Enter your roll number: ");
                                scanf("%s", roll_no);
                                snprintf(command, sizeof(command), "start \"\" \"https://csvtu.digivarsity.online/WebApp/Result/SemesterResult.aspx?S=4%%20SEMESTER&E=Apr-May%%20%d&R=%s&T=%s\"",year, roll_no, resultString);
                                system(command);
                                printf("Do you want to enter another? (y/n): ");
                                    scanf(" %c", &choice);
                                }
                            }
                            break;
                            case 2:{
                                while (choice == 'y' || choice == 'Y') {
                                printf("Enter your roll number: ");
                                scanf("%s", roll_no);
                                snprintf(command, sizeof(command), "start \"\" \"https://csvtu.digivarsity.online/WebApp/Result/SemesterResult.aspx?S=4%%20SEMESTER&E=Nov-Dec%%20%d&R=%s&T=%s\"",year, roll_no, resultString);
                                system(command);
                                printf("Do you want to enter another? (y/n): ");
                                    scanf(" %c", &choice);
                                }
                            }
                            printf("%s",color_end);
                            break;
                            default:{
                                printf("\033[1;31mInvalid session!\n\033[0m");
                                break;
                            }
                        }
                    }
                    break;
                    case 5: {
                        printf("\033[1;32m 1. Apr-May \n 2. Nov-Dec \n\033[0m");
                        printf("%s", yellow_bold);
                        printf("Select the session: ");
                        scanf("%d", &session);
                        choice = 'y';
                        
                        switch(session){
                            case 1:{
                                while (choice == 'y' || choice == 'Y') {
                                printf("Enter your roll number: ");
                                scanf("%s", roll_no);
                                snprintf(command, sizeof(command), "start \"\" \"https://csvtu.digivarsity.online/WebApp/Result/SemesterResult.aspx?S=5%%20SEMESTER&E=Apr-May%%20%d&R=%s&T=%s\"",year, roll_no, resultString);
                                system(command);
                                printf("Do you want to enter another? (y/n): ");
                                    scanf(" %c", &choice);
                                }
                            }
                            break;
                            case 2:{
                                while (choice == 'y' || choice == 'Y') {
                                printf("Enter your roll number: ");
                                scanf("%s", roll_no);
                                snprintf(command, sizeof(command), "start \"\" \"https://csvtu.digivarsity.online/WebApp/Result/SemesterResult.aspx?S=5%%20SEMESTER&E=Nov-Dec%%20%d&R=%s&T=%s\"",year, roll_no, resultString);
                                system(command);
                                printf("Do you want to enter another? (y/n): ");
                                    scanf(" %c", &choice);
                                }
                            }
                            printf("%s",color_end);
                            break;
                            default:{
                                printf("\033[1;31mInvalid session!\n\033[0m");
                                break;
                            }
                        }
                    }
                    break;
                    case 6: {
                        printf("\033[1;32m 1. Apr-May \n 2. Nov-Dec \n\033[0m");
                        printf("%s", yellow_bold);
                        printf("Select the session: ");
                        scanf("%d", &session);
                        choice = 'y';
                        
                        switch(session){
                            case 1:{
                                while (choice == 'y' || choice == 'Y') {
                                printf("Enter your roll number: ");
                                scanf("%s", roll_no);
                                snprintf(command, sizeof(command), "start \"\" \"https://csvtu.digivarsity.online/WebApp/Result/SemesterResult.aspx?S=6%%20SEMESTER&E=Apr-May%%20%d&R=%s&T=%s\"",year, roll_no, resultString);
                                system(command);
                                printf("Do you want to enter another? (y/n): ");
                                    scanf(" %c", &choice);
                                }
                            }
                            break;
                            case 2:{
                                while (choice == 'y' || choice == 'Y') {
                                printf("Enter your roll number: ");
                                scanf("%s", roll_no);
                                snprintf(command, sizeof(command), "start \"\" \"https://csvtu.digivarsity.online/WebApp/Result/SemesterResult.aspx?S=6%%20SEMESTER&E=Nov-Dec%%20%d&R=%s&T=%s\"",year, roll_no, resultString);
                                system(command);
                                printf("Do you want to enter another? (y/n): ");
                                    scanf(" %c", &choice);
                                }
                            }
                            printf("%s",color_end);
                            break;
                            default:{
                                printf("\033[1;31mInvalid session!\n\033[0m");
                                break;
                            }
                        }
                    }
                    break;
                    case 7:{
                        printf("\033[1;32m 1. Apr-May \n 2. Nov-Dec \n\033[0m");
                        printf("%s", yellow_bold);
                        printf("Select the session: ");
                        scanf("%d", &session);
                        choice = 'y';
                        
                        switch(session){
                            case 1:{
                                while (choice == 'y' || choice == 'Y') {
                                printf("Enter your roll number: ");
                                scanf("%s", roll_no);
                                snprintf(command, sizeof(command), "start \"\" \"https://csvtu.digivarsity.online/WebApp/Result/SemesterResult.aspx?S=7%%20SEMESTER&E=Apr-May%%20%d&R=%s&T=%s\"",year, roll_no, resultString);
                                system(command);
                                printf("Do you want to enter another? (y/n): ");
                                    scanf(" %c", &choice);
                                }
                            }
                            break;
                            case 2:{
                                while (choice == 'y' || choice == 'Y') {
                                printf("Enter your roll number: ");
                                scanf("%s", roll_no);
                                snprintf(command, sizeof(command), "start \"\" \"https://csvtu.digivarsity.online/WebApp/Result/SemesterResult.aspx?S=7%%20SEMESTER&E=Nov-Dec%%20%d&R=%s&T=%s\"",year, roll_no, resultString);
                                system(command);
                                printf("Do you want to enter another? (y/n): ");
                                    scanf(" %c", &choice);
                                }
                            }
                            printf("%s",color_end);
                            break;
                            default:{
                                printf("\033[1;31mInvalid session!\n\033[0m");
                                break;
                            }
                        }
                    }
                    break;
                    case 8:{
                        printf("\033[1;32m 1. Apr-May \n 2. Nov-Dec \n\033[0m");
                        printf("%s", yellow_bold);
                        printf("Select the session: ");
                        scanf("%d", &session);
                        choice = 'y';
                        
                        switch(session){
                            case 1:{
                                while (choice == 'y' || choice == 'Y') {
                                printf("Enter your roll number: ");
                                scanf("%s", roll_no);
                                snprintf(command, sizeof(command), "start \"\" \"https://csvtu.digivarsity.online/WebApp/Result/SemesterResult.aspx?S=8%%20SEMESTER&E=Apr-May%%20%d&R=%s&T=%s\"",year, roll_no, resultString);
                                system(command);
                                printf("Do you want to enter another? (y/n): ");
                                    scanf(" %c", &choice);
                                }
                            }
                            break;
                            case 2:{
                                while (choice == 'y' || choice == 'Y') {
                                printf("Enter your roll number: ");
                                scanf("%s", roll_no);
                                snprintf(command, sizeof(command), "start \"\" \"https://csvtu.digivarsity.online/WebApp/Result/SemesterResult.aspx?S=8%%20SEMESTER&E=Nov-Dec%%20%d&R=%s&T=%s\"",year, roll_no, resultString);
                                system(command);
                                printf("Do you want to enter another? (y/n): ");
                                    scanf(" %c", &choice);
                                }
                            }
                            printf("%s", color_end);
                            break;
                            default:{
                                printf("\033[1;31mInvalid session!\n\033[0m");
                                break;
                            }
                        }
                        break;
                        default:{
                            printf("\033[1;31mInvalid Option!\n\033[0m");
                            break;
                        }
                    }
                }
            }
            break;
            case 4:{
                printf("\n\033[1;34m*******************************ALL PYQ*******************************\033[0m\n\n");
                snprintf(command, sizeof(command), "start \"\" \"https://drive.google.com/drive/folders/1kc-yIBuUdd3IL0QCNw53fhvmxWW4leOV\"");
                printf("%s", magenta_bold);
                printf("Check Google Drive link which I have opened to get PYQ.\n\n");
                printf("%s", color_end);
                system(command);
                printf("\033[1;33mDo you want to join Telegram groups for get all updates(y/n): \033[0m");
                scanf(" %c", &choice);
                if (choice == 'y' || choice == 'Y') {
                    snprintf(command, sizeof(command), "start \"\" \"https://t.me/rcetr1\"");
                    system(command);
                }
            }
            break;
            case 5:{
                printf("\n\033[1;34m****************************issue/Feedback**************************\033[0m\n\n");
                printf("%s", magenta_bold);
                printf("Note:\n");
                printf("1. If you are facing any issue, first check your Internet connection and try again.\n");
                printf("2. Make sure you are logged in to the CSVTU website in the default browser.\n");
                printf("3. Make sure you have downloaded the latest version.\n");
                printf("4. Make sure you have given the correct inputs into the program.\n");
                printf("5. If you are good and not seeing the result/admit card then it may be that they are not declared,\n   please wait and try again later.\n\n");
                printf("If you have any issue/feedback regarding this program then you can go to Telegram groups.\n");
                printf("%s", color_end);
                printf("\033[1;33mDo you want to vist Telegram groups(y/n): \033[0m");
                scanf(" %c", &choice);
                if (choice == 'y' || choice == 'Y') {
                    snprintf(command, sizeof(command), "start \"\" \"https://t.me/rcetr1\"");
                    system(command);
                }
            }
            break;
            case 6:{
                printf("\n\033[1;34m************************************About******************************\n\033[0m");
                printf("\033[1;34m                          Version 1.0 Copyright (c) 2024               \n\033[0m");
                printf("\033[1;34m                            Developed by MRS4NJ4Y.\n          \n\n\033[0m");
                printf("%s",magenta_bold);
                printf("this program is free, you can redistribute it and/or modify it under the terms of GNU General Public License v3.0.\n");
                printf("This program is only for B.Tech. Is for. Which works on PC.\n");
                printf("This program is more efficient and faster than online websites.\n");
                printf("Using this program you can check any previous (Nov-Dec-2021) to current result/admit card\n");
                printf("You can check result/admit card of anyone using roll number.\n\n");
                printf("If you want more information about these programs visit the repository\n");
                printf("%s", color_end);
                printf("\033[1;33mDo you want to visit repository(y/n): \033[0m");
                scanf(" %c", &choice);
                if (choice == 'y' || choice == 'Y') {
                    system("start " REPO_URL);
                }
            }
            break;
            case 0:{
                printf("\033[1;35mThank you for using this program.\n\033[0m");
                loop=0;
            }
            break;
            default:{
                printf("\033[1;31mInvalid Option!\n\033[0m");
                break;
            }
        }
        if(loop!=0){
            printf("\033[1;32m 1. Main Menu\n 2. Exit \n\033[0m");
            scanf(" %d", &count);
            if(count == 1){
                system("cls");
            }
            else if(count == 2){
                printf("\033[1;35mThank you for using this program.\n\033[0m");
                loop=0;
            }
            else{
                printf("\033[1;31mInvalid Option!\n\033[0m");
            }
        }
        
    }
    return 0;
}