#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
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
/////////////////////////////////////////////////////////////////////////////////////////////////
///Default Admin Username : admin /// Password : 210706300046

void change_admin_username()
{
    FILE *f = fopen("admin_login_credentials.csv", "r");
    if (!f) 
	{ 
	printf("Error opening file!\n");
	 getchar(); 
	 return;
	}

    char line[256], saved_username[100];
    unsigned long long saved_password;

    // Read existing credentials
    
    if (fgets(line, sizeof(line), f) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';
        char *token = strtok(line, ",");
        
        if (token) strcpy(saved_username, token);
        token = strtok(NULL, ",");
        //unsigned long long int strtoull(const char *nptr, char **endptr, int base);
        if (token) saved_password = strtoull(token, NULL, 10);
    }
    fclose(f);

    clear_screen();
    printf(BHRED"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\tChange Admin Username\n"CRESET);
    printf(BHRED"%s\n"CRESET,h_line);
    // Ask for old credentials
    char old_username[100], old_password[MAX_LENGTH];
    string_input_function(old_username, BHMAG, "\tcurrent username");
    string_input_function(old_password, BHMAG, "\tcurrent password");

    unsigned long long old_hashed = simple_hash(old_password);

    if (strcmp(old_username, saved_username) != 0 || old_hashed != saved_password)
    {
        printf(BHRED"\n\t\t\t\t\t\t\t\tInvalid current credentials! Cannot change username.\n"CRESET);
        printf(BHRED"\t\t\t\t\t\t\t\tPress any key to continue..."CRESET);
        getche();
        return;
    }

    // Ask for new username
    char new_username[100];
    string_input_function(new_username, BHMAG, "\tnew username");

    // Write to temporary file
    FILE *tmp = fopen("temp.csv", "w");
    if (!tmp) { printf("Error creating temp file!\n"); getchar(); return; }

    fprintf(tmp, "%s,%llu\n", new_username, saved_password);
    fclose(tmp);

    // Replace original file
    remove("admin_login_credentials.csv");
    rename("temp.csv", "admin_login_credentials.csv");

    printf(BHGRN"\n\t\t\t\t\t\t\t\tUsername changed successfully!\n"CRESET);
    printf(BHGRN"\t\t\t\t\t\t\t\tPress any key to continue..."CRESET);
    getche();
}

//CHANGE_ADMIN_PASSWORD_FUNTIONALITY
void change_admin_password()
{
    FILE *f = fopen("admin_login_credentials.csv", "r");
    if (!f) { printf("Error opening file!\n"); getchar(); return; }

    char line[256], saved_username[100];
    unsigned long long saved_password;

    // Read existing credentials
    if (fgets(line, sizeof(line), f) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';
        char *token = strtok(line, ",");
        if (token) strcpy(saved_username, token);
        token = strtok(NULL, ",");
        if (token) saved_password = strtoull(token, NULL, 10);
    }
    fclose(f);

    clear_screen();
    printf(BHRED"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\tChange Admin Password\n"CRESET);
   printf(BHRED"%s\n"CRESET,h_line);
    // Ask for old credentials
    char old_username[100], old_password[MAX_LENGTH];
    string_input_function(old_username, BHMAG, "\tcurrent username");
    string_input_function(old_password, BHMAG, "\tcurrent password");

    unsigned long long old_hashed = simple_hash(old_password);

    if (strcmp(old_username, saved_username) != 0 || old_hashed != saved_password)
    {
        printf(BHRED"\n\t\t\t\t\t\t\t\tInvalid current credentials! Cannot change password.\n"CRESET);
        printf(BHRED"\t\t\t\t\t\t\t\tPress any key to continue..."CRESET);
        getche();
        return;
    }

    // Ask for new password
    char new_password[MAX_LENGTH];
    string_input_function(new_password, BHMAG, "\tnew password");

    unsigned long long new_hashed = simple_hash(new_password);

    // Write to temporary file
    FILE *tmp = fopen("temp.csv", "w");
    if (!tmp) { printf("Error creating temp file!\n"); getchar(); return; }

    fprintf(tmp, "%s,%llu\n", saved_username, new_hashed);
    fclose(tmp);

    // Replace original file
    remove("admin_login_credentials.csv");
    rename("temp.csv", "admin_login_credentials.csv");

    printf(BHGRN"\n\t\t\t\t\t\t\t\tPassword changed successfully!\n"CRESET);
    printf(BHGRN"\t\t\t\t\t\t\t\tPress any key to continue..."CRESET);
    getche();
}

void reset_doctors_daily_appointments()
 {

    const char *filename = "doctors_daily_appointment_record.csv";
    const char *tempfile = "temp_reset_file.csv";

   

    printf("\n\t\t\t\t\t\t\t\tAre you sure you want to reset\n\t\t\t\t\t\t\t\tappointment data? (y/n): ");
     char choice = getche();

    if (choice != 'y' && choice != 'Y') 
	{
        printf("\n\t\t\t\t\t\t\t\tReset cancelled.\n");
        getche();
        return;   // back to calling function
    }

    FILE *fin = fopen(filename, "r");
    if (!fin) {
        printf("Error: Could not open %s\n", filename);
        return;
    }

    FILE *fout = fopen(tempfile, "w");
    if (!fout) {
        printf("Error: Could not create temporary file.\n");
        fclose(fin);
        return;
    }

    char line[2048];

    while (fgets(line, sizeof(line), fin)) {

        int values[300];
        int count = 0;

        char *token = strtok(line, ",\n");
        while (token != NULL) {
            values[count++] = atoi(token);
            token = strtok(NULL, ",\n");
        }

        // Reset values > 1 (except doctor ID)
        for (int i = 1; i < count; i++) {
            if (values[i] > 1)
                values[i] = 1;
        }

        // Write updated row
        for (int i = 0; i < count; i++) {
            fprintf(fout, "%d", values[i]);
            if (i < count - 1) fprintf(fout, ",");
        }
        fprintf(fout, "\n");
    }

    fclose(fin);
    fclose(fout);

    // Delete old file
    if (remove(filename) != 0) 
	{
        printf("Error deleting original file.\n");
        return;
    }

    // Rename temp to original
    if (rename(tempfile, filename) != 0) 
	{
        printf("Error renaming temp file.\n");
        return;
    }

    printf("\n\t\t\t\t\t\t\t\tData reset successful.\n");
    printf("\n\t\t\t\t\t\t\t\tPress Any Key to Go Back.\n\t\t\t\t\t\t\t\t");
    getche();
    return;
    
}
