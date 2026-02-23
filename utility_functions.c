#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"admin_allied_panel.h"
#include"admin_doctors_panel.h"
#include"admin_patients_panel.h"
#include"admin_portal.h"
#include"admin_settings_panel.h"
#include"ANSI-color-codes.h"
#include"patient_panel.h"
#include"patient_portal_sign_up.h"
#include"structures.h"
#include"utility_functions.h"
#include <ctype.h>
#include<windows.h>
// Function to simulate loading animation

void string_input_function(char *buffer, const char *prompt_color, const char *prompt)
{
    while (1) 
    {
        // Printing colored prompt
        printf("\t\t\t\t\t\t\t\t%s%s : %s", (prompt_color), (prompt), (CRESET));

        if (fgets(buffer, MAX_LENGTH, stdin) == NULL) 
        {
            buffer[0] = '\0';
            continue;
        }

        // Remove newline if present
        size_t len = strcspn(buffer, "\n");
        if (buffer[len] == '\n')
            buffer[len] = '\0';
        else {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }

        // Test for empty/whitespace-only input
        int all_whitespace = 1;
        for (size_t i = 0; buffer[i] != '\0'; i++) {
            if (!isspace((unsigned char)buffer[i])) {
                all_whitespace = 0;
                break;
            }
        }

        if (all_whitespace) {
            printf("%s%sInput cannot be empty or whitespace. Please try again.%s\n", BHRED,TAB, CRESET);
            continue;
        }

        // ❌ Reject input containing a comma
        int has_comma = 0;
        for (size_t i = 0; buffer[i] != '\0'; i++) {
            if (buffer[i] == ',') {
                has_comma = 1;
                break;
            }
        }

        if (has_comma) {
            printf("%s%sCommas are not allowed in input. Please enter again.%s\n", BHRED,TAB, CRESET);
            continue;
        }

        // Passed all checks → return
        return;
    }
}

void string_input_limited(char *buffer, int limit, const char *prompt_color, const char *prompt)
{
    while (1)
    {
        printf("\t\t\t\t\t\t\t\t%s%s : %s", prompt_color, prompt, CRESET);

        if (fgets(buffer, limit + 1, stdin) == NULL) // read limit + 1 to detect overflow
        {
            buffer[0] = '\0';
            continue;
        }

        size_t len = strlen(buffer);

        // Check if user entered more than limit - 1 characters
        if (len > 0 && buffer[len - 1] != '\n')
        {
            // Flush remaining input
            int c;
            while ((c = getchar()) != '\n' && c != EOF);

            printf("%s%sInput too long! Maximum %d characters allowed. Please try again.%s\n",
                   BHRED, TAB, limit - 1, CRESET);
            continue;
        }

        // Remove trailing newline
        if (len > 0 && buffer[len - 1] == '\n')
            buffer[len - 1] = '\0';

        // Check for whitespace-only input
        int all_whitespace = 1;
        for (size_t i = 0; buffer[i] != '\0'; i++)
        {
            if (!isspace((unsigned char)buffer[i]))
            {
                all_whitespace = 0;
                break;
            }
        }
        if (all_whitespace)
        {
            printf("%s%sInput cannot be empty or whitespace. Please try again.%s\n", BHRED, TAB, CRESET);
            continue;
        }

        // Reject commas
        if (strchr(buffer, ',') != NULL)
        {
            printf("%s%sCommas are not allowed in input. Please try again.%s\n", BHRED, TAB, CRESET);
            continue;
        }

        return; // valid input
    }
}



// int is_blank(const char *s)
// {
//     // If string is NULL, treat it as blank
//     if (s == NULL) return 1;

//     while (*s) {
//         if (!isspace((unsigned char)*s))
//             return 0;  // Found a non-whitespace character
//         s++;
//     }
//     return 1;  // All characters were whitespace
// }

// Helper function to safely read an integer in a range
int getIntInRange(const char *prompt, int min, int max) 
{
    char buffer[100];
    long value;
    char *endptr;

    while (1) {
        printf(BHMAG"\t\t\t\t\t\t%s"CRESET, prompt);

        if (!fgets(buffer, sizeof(buffer), stdin)) {
            printf(BHMAG"\t\t\t\t\t\t\t\tInput error. Try again.\n"CRESET);
            continue;
        }

        // Convert to long
        value = strtol(buffer, &endptr, 10);

        // Check if input was a valid number and fully consumed
        if (endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
            printf(BHMAG"\t\t\t\t\t\t\t\tInvalid input! Enter a number.\n"CRESET);
            continue;
        }

        // Check range
        if (value < min || value > max) {
            printf(BHMAG"%sInvalid number! Enter a number between %d and %d.\n"CRESET,TAB, min, max);
            continue;
        }

        return (int)value; // valid number
    }
}
 unsigned long long simple_hash(const char *str) 
 {
    unsigned long long hash = 5381ULL;
    //By default, integer literals in C/C++ are assigned the smallest type that can hold them.
    //by ull it automatically becomes ull
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + (unsigned char)c; // hash * 33 + c
    return hash;
 }

 void clearInputBuffer() 
 {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// int is_valid_number(const char *str, int digits)
// {
//     int count = 0;

//     // Count digits and check each char
//     for (int i = 0; str[i] != '\0'; i++)
//     {
//         if (str[i] < '0' || str[i] > '9')
//             return 0;  // non-digit found

//         count++;
//     }

//     return count == digits;
// }

void clear_screen()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
// void remove_newline(char *str) 
// {
//     str[strcspn(str, "\n")] = '\0';
// }
// Load patient names from CSV (using strtok_r)
int load_patients(Patient p[]) {
    FILE *fp = fopen("patients_biodata.csv", "r");
    if (!fp) return 0;

    char line[MAX_LINE];
    int count = 0;

    while (fgets(line, sizeof(line), fp)) {
        char buf[MAX_LINE];
        strncpy(buf, line, sizeof(buf)-1);
        buf[sizeof(buf)-1] = '\0';

        char *saveptr = NULL;
        char *token = strtok_r(buf, ",", &saveptr);  // patient_id
        if (!token) continue;
        p[count].id = atoi(token);

        token = strtok_r(NULL, ",", &saveptr);        // full_name
        if (!token) continue;

        token[strcspn(token, "\r\n")] = '\0';
        strncpy(p[count].full_name, token, sizeof(p[count].full_name)-1);
        p[count].full_name[sizeof(p[count].full_name)-1] = '\0';

        count++;
        if (count >= MAX_PATIENTS) break;
    }
    fclose(fp);
    return count;
}

// Load doctors list (using strtok_r)
int load_doctors(Doctor d[])
 {
    FILE *fp = fopen("doctors_list_sp,nm,id.csv", "r");
    if (!fp) return 0;

    char line[MAX_LINE];
    int count = 0;

    while (fgets(line, sizeof(line), fp)) {
        char buf[MAX_LINE];
        strncpy(buf, line, sizeof(buf)-1);
        buf[sizeof(buf)-1] = '\0';

        char *token;
        char *saveptr = NULL;

        token = strtok_r(buf, ",", &saveptr);
        if (!token) continue;

        d[count].id = atoi(token);       // doctor id

        token = strtok_r(NULL, ",", &saveptr);       // doctor name
        if (token) {
            token[strcspn(token, "\r\n")] = '\0';
            strncpy(d[count].name, token, sizeof(d[count].name)-1);
            d[count].name[sizeof(d[count].name)-1] = '\0';
        } else d[count].name[0] = '\0';

        token = strtok_r(NULL, ",", &saveptr);       // specialization
        if (token) {
            token[strcspn(token, "\r\n")] = '\0';
            strncpy(d[count].spec, token, sizeof(d[count].spec)-1);
            d[count].spec[sizeof(d[count].spec)-1] = '\0';
        } else d[count].spec[0] = '\0';

        count++;
        if (count >= MAX_DOCTORS) break;
    }
    fclose(fp);
    return count;
}

// Get patient full_name using ID
// char* get_patient_name(Patient p[], int total, int pid)
//  {
//     for (int i = 0; i < total; i++) {
//         if (p[i].id == pid)
//             return p[i].full_name;
//     }
//     return "Unknown Patient";
// }
// Reusable Loading Bar Function
void loading_bar(const char *message)
{
    printf(BHBLU"\n\t\t\t\t\t\t\t\t%s ["CRESET, message); // Display the message
    for (int i = 0; i < 10; i++) // 10 steps of the bar
    {
        Sleep(80); // Delay for animation
        printf(BHBLU"#"CRESET); // Print each step
    }
    printf(BHBLU"]"CRESET);
    Sleep(200); // Small pause at the end
}
// //void loading_animation(const char* message) {
//     printf(BHBLU"\n\t\t\t\t\t\t\t\t%s ["CRESET, message);
//     for (int i = 0; i < 10; i++) {
//         Sleep(80);
//         printf(BHBLU"#"CRESET);
//     }
//     printf(BHBLU"]"CRESET);
//     Sleep(200);
// }
