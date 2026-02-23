#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <ctype.h>
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
#ifdef _WIN32
#include <conio.h>
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////
void admin_login_function()

{
    FILE *f_alc = fopen("admin_login_credentials.csv","r");
    if (f_alc == NULL)
    {
        printf("Error opening file!\n");
        printf("Press Enter to return to Welcome Screen...");
        getchar();
        return;
    }

    char line[256];
    char saved_username[100];
    unsigned long long saved_password;

    if (fgets(line, sizeof(line), f_alc) != NULL) 
    {
    	int occurance = strcspn(line, "\n");
        line[strcspn(line, "\n")] = '\0';

        char *token = strtok(line, ",");
        if (token != NULL) 
            strcpy(saved_username, token);

        token = strtok(NULL, ",");
        if (token != NULL) 
        	//string to unsignled long long
            saved_password = strtoull(token, NULL, 10);
    }
    fclose(f_alc); // close file after reading

    char username[MAX_LENGTH];
    char password[MAX_LENGTH];

    while (1) 
    {
        clear_screen();
        printf(BHRED"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tWelcome To Admin Login Portal\n"CRESET);
printf(BHRED"%s\n"CRESET,h_line);

        string_input_function(username, BHMAG, "username");
        string_input_function(password, BHMAG, "password");

        unsigned long long hashed_password = simple_hash(password);

        if (strcmp(username, saved_username) == 0 && saved_password == hashed_password)
        {
            printf(BHRED"\n\t\t\t\t\t\t\t\tLogin Successful!\n"CRESET);
            printf(BHRED"\t\t\t\t\t\t\t\tPress Any Key to continue..."CRESET);
            getche();

            admin_panel(); // Calling Admin Panel Function
            break;        // Exit login loop
        }
        else
        {
            printf(BHRED"\n\t\t\t\t\t\t\t\tInvalid credentials!\n\t\t\t\t\t\t\t\tPress Enter to try again...\n\t\t\t\t\t\t\t\tOr press Escape to go back to Welcome Screen..."CRESET);
            char c = getche();
            if (c != 27) // ASCII Escape
            {
                continue; // try again
            }
            else
            {
                return;   // go back to Welcome Screen
            }
        }
    }
}

void admin_panel()
{
    while(1)
	{
    char admin_choice;
 clear_screen();
  printf(BHRED"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tWelcome Dear Admin!\n"CRESET);
printf(BHRED"%s\n"CRESET,h_line);
printf(BHBLU"\n\t\t\t\t\t\t\t\tPlease Select an appropriate option\n\n"CRESET);

printf(BHBLU"\t\t\t\t\t\t\t\t1) Doctors' Panel\n"CRESET);
printf(BHBLU"\t\t\t\t\t\t\t\t2) Patients' Panel\n"CRESET);
printf(BHBLU"\t\t\t\t\t\t\t\t3) Paramedics and Allied Staff Panel\n"CRESET);
printf(BHBLU"\t\t\t\t\t\t\t\t4) Admin Panel Settings\n"CRESET);
printf(BHBLU"\t\t\t\t\t\t\t\t5) Return to Admin Login Screen\n"CRESET);
printf(BHBLU"\t\t\t\t\t\t\t\t6) Exit Application\n\n"CRESET);
printf(BHRED"%s\n"CRESET,h_line);

printf(BHGRN"\t\t\t\t\t\t\t\tPlease Enter Your Choice: "CRESET);

    admin_choice = getche();
    switch (admin_choice)
    {
        case '1':
           admin_panel_doctors_panel();
            break;
        case '2':
            admin_panel_patient_panel();
            break;
        case '3':
            admin_panel_allied_panel();
            break;
        case '4':
            admin_panel_admin_settings();
			 break;
        case '5':
            return;  // Logout and return to welcome screen
             break;
           case '6':
           	clear_screen();
    		printf(BHRED"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tGood Bye!\n"CRESET);
            exit(0);
             break; // Exit application
        default:
            printf("Invalid choice!\nPress Any Key to try again...");
            getche();
            break;
    }   
}
}
void admin_panel_doctors_panel()
{
    while(1)
	{
    char choice;
 clear_screen();

printf(BHRED"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tWelcome Dear Admin to the Doctors' Affairs Panel!\n"CRESET);
printf(BHRED"%s\n"CRESET,h_line);
printf(BHBLU"\n\t\t\t\t\t\t\t\tPlease Select an appropriate option\n\n"CRESET);

printf(BHBLU"\t\t\t\t\t\t\t\t1) Check Doctors' Schedule\n"CRESET);
printf(BHBLU"\t\t\t\t\t\t\t\t2) Change Doctors' Schedule\n"CRESET);
printf(BHBLU"\t\t\t\t\t\t\t\t3) List All Doctors\n"CRESET);
printf(BHBLU"\t\t\t\t\t\t\t\t4) Return To Admin Panel\n"CRESET);
printf(BHBLU"\t\t\t\t\t\t\t\t5) Exit\n\n"CRESET);

printf(BHRED"%s\n"CRESET,h_line);
printf(BHGRN"\t\t\t\t\t\t\t\tPlease Enter Your Choice: "CRESET);

    choice = getche();
    switch (choice)
    {
    case '1' :
        doctors_schedule_for_admin(); 
        break;
     case '2' :
        change_doctors_schedule(); 
        break; 
    case '3':
        list_all_doctors();
        break;
    case '4':
        return;  
        break;
    case '5':
    	clear_screen();
    		printf(BHRED"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tGood Bye!\n"CRESET);
        exit(0);
        break;  
    default: //If user accendently enters an invalid option,it prompts the user to try again
        printf("Invalid choice!\nPress Any Key to try again...");
        getche();
        break;
    }

}
}
void admin_panel_patient_panel()
{
    while(1){
  clear_screen();
    char choice;
  printf(BHRED"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tWelcome Dear Admin to the Patients' Affairs Panel!\n"CRESET);
printf(BHRED"%s\n"CRESET,h_line);

printf(BHBLU"\n\t\t\t\t\t\t\t\tPlease Select an appropriate option\n\n"CRESET);

printf(BHBLU"\t\t\t\t\t\t\t\t1) List All Patients\n"CRESET);
printf(BHBLU"\t\t\t\t\t\t\t\t2) Search Patient by ID\n"CRESET);
printf(BHBLU"\t\t\t\t\t\t\t\t3) Search Patient by Username\n"CRESET);
printf(BHBLU"\t\t\t\t\t\t\t\t4) Return To Admin Panel\n"CRESET);
printf(BHBLU"\t\t\t\t\t\t\t\t5) Exit\n"CRESET);


printf(BHRED"%s\n%s"CRESET,h_line,TAB);
printf(BHGRN"\n\t\t\t\t\t\t\t\tPlease Enter Your Choice: "CRESET);

    choice = getche();
    switch (choice)
    {
    case '1' :
        list_all_patients(); //Forwarding control to patient portal function
        break;
     case '2' :
        search_patient_by_id(); //Forwarding control to doctor portal function
        break; 
    case '3':
    	clearInputBuffer();
        search_patient_by_username(); //Exiting the program
        break;
    case   '4':
        return;
        break;
    case '5':
           clear_screen();
    		printf(BHRED"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tGood Bye!\n"CRESET);
            exit(0);
        break;

    default: //If user accendently enters an invalid option,it prompts the user to try again
        printf("Invalid choice!\nPress Enter to try again...");
        getche();
        break;
    }
}
} 
void admin_panel_allied_panel()
{
    while(1)
	{
    // loadHospitalCSV("hospital.csv"); 
    // hospitalMenu();                   // optional interactive menu
    // saveHospitalCSV("hospital.csv");  // save changes
    // return 0;
 clear_screen();
    char choice;
  printf(BHRED"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tWelcome Dear Admin to the Paramedics \n\t\t\t\t\t\t\t\t   and Allied Staff Affairs Panel!\n"CRESET);
printf(BHRED"%s\n"CRESET,h_line);

printf(BHBLU"\n\t\t\t\t\t\t\t\tPlease Select an appropriate option\n\n"CRESET);

printf(BHBLU"\t\t\t\t\t\t\t\t1) List All Paramedics and Allied Staff\n"CRESET);
printf(BHBLU"\t\t\t\t\t\t\t\t2) Remove Paramedic or Allied Staff\n"CRESET);
printf(BHBLU"\t\t\t\t\t\t\t\t3) Add New Paramedic or Allied Staff\n"CRESET);
printf(BHBLU"\t\t\t\t\t\t\t\t4) Return To Admin Panel\n"CRESET);
printf(BHBLU"\t\t\t\t\t\t\t\t5) Exit\n\n"CRESET);

printf(BHRED"%s\n"CRESET,h_line);
printf(BHGRN"\t\t\t\t\t\t\t\tPlease Enter Your Choice: "CRESET);

    choice = getche();
    
    switch (choice)
    {
    case '1' :
        list_all_allied_staff(); 
        break;
     case '2' :
		 mark_staff_vacant();
        break; 
    case '3':
         fill_vacant_staff_position(); 
        break;
    case '4':
            return;
        break;
    case '5':
    		clear_screen();
    		printf(BHRED"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tGood Bye!\n"CRESET);
            exit(0);
        break;
    default: //If user accendently enters an invalid option,it prompts the user to try again
        printf("\n"TAB"Invalid choice!\nPress Enter to try again...");
        getchar();
        break;
    }


}
}

void admin_panel_admin_settings()
{
    while(1)
	{
clear_screen();
    printf(BHRED"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tWelcome Dear Admin to the Admin Settings Panel!\n"CRESET);
printf(BHRED"%s\n"CRESET,h_line);
printf(BHBLU"\n\t\t\t\t\t\t\t\tPlease Select an appropriate option\n\n"CRESET);

printf(BHBLU"\t\t\t\t\t\t\t\t1) Change Admin Login Username\n"CRESET);
printf(BHBLU"\t\t\t\t\t\t\t\t2) Change Admin Login Password\n"CRESET);
printf(BHBLU"\t\t\t\t\t\t\t\t3) Reset Week\n"CRESET);
printf(BHBLU"\t\t\t\t\t\t\t\t4) Return To Admin Panel\n"CRESET);
printf(BHBLU"\t\t\t\t\t\t\t\t5) Exit Application\n\n"CRESET);

printf(BHRED"%s\n"CRESET,h_line);
printf(BHGRN"\t\t\t\t\t\t\t\tPlease Enter Your Choice: "CRESET);
    char choice;
    choice = getche();
    switch (choice)
    {
    case '1' :
        change_admin_username(); 
        break;
     case '2' :
        change_admin_password(); 
        break;
    case '3':
       reset_doctors_daily_appointments();
        break;
    case '4':
            return;
        break;
    case '5':
    	clear_screen();
    		printf(BHRED"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tGood Bye!\n"CRESET);
            exit(0);
        break;
    default: //If user accendently enters an invalid option,it prompts the user to try again
        printf("Invalid choice!\nPress Any Key to try again...");
        getche();
        break;
    }
}
}
    
