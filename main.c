#include <stdio.h>
#include <stdlib.h> 
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
#include <windows.h>
#endif
#ifdef _WIN32
#include <conio.h>
#endif
int front_screen(void);
char h_line[200]  = "========================================================================================================================================================================";

/////////////////////////////////////////////////////////////////////////////////////////////////
//Main Function
//Main Function only calls the front_screen function to display the initial options
//rest of the logic is handled in other functions
int main()
{//Enabling ANSI escape codes on Windows, by enalbling virtual terminal processing
//This allows the use of colored text in the console
//Reference: https://learn.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
//https://stackoverflow.com/questions/5174814/using-ansi-color-codes-in-windows-console-applications
//https://stackoverflow.com/questions/4053837/what-is-the-correct-way-to-use-setconsolemode-for-virtual-terminal-processing
//https://stackoverflow.com/questions/14649921/how-to-enable-ansi-color-codes-in-windows-console
//Modern Windows 10 and later versions support ANSI escape codes in the console natively
//but it needs to be enabled programmatically
//This code block checks if the program is being compiled on Windows platform
//and if so, it retrieves the current console mode and enables virtual terminal processing
	
	
    #ifdef _WIN32
        // Get a handle to the standard output
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        // Handle error if unable to get console handle
        return 1;
    }

    // Get the current console mode
    DWORD dwMode;
    if (!GetConsoleMode(hConsole, &dwMode)) {
        // Handle error if unable to get console mode
        return 1;
    }

    // Enable virtual terminal processing
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hConsole, dwMode)) {
        // Handle error if unable to set console mode
        return 1;
    }
    #endif
    	printf("\n\n\n\n\n\n");
	printf(BHRED
TAB"	    	   &&&&&      &&&&&&                    \n"
TAB"                 &&&&&&&&&  &&&&&&&&&&                  \n"
TAB"                &&&&&&&&&&&&&&&&&&&&&&$                 \n"
TAB"                &&&&&&&&&&&&&&&&&&&&&&                  \n"
TAB"                 &&&&&&&&&&&&&&&&&&&&&                  \n"
TAB"                  &&&&&&&&&&&&&&&&&&;                   \n"
TAB"                    &&&&&&&&&&&&&&&                     \n"
TAB"                      &&&&&&&&&&&                       \n"
TAB"                        &&&&&&                          \n"
TAB"                           &                            \n"
CRESET);

printf(BHBLU TAB
"                                     &&&&&              \n"
CRESET);

printf(BHBLU TAB
"                 &&&&&&           &&&&&&                \n"
TAB"              &&&&&&&&&&&&&&&&&& &&&&&                  \n"
CRESET);

printf(BHBLU
TAB"            &&&&&&&&&&&&          &&                    \n"
TAB"            &&&&&&&&&&&& $&&&&&&&&                      \n"
TAB"            &&&&&&&&&&&&&&&&&&&&                        \n"
TAB"              &&&&                                    \n\n\n"
CRESET);

printf(BHMAG TAB"    WELCOME TO AL-SHIFA HOSPITAL MANAGMENT SYSTEM\n\n\n");

printf(BHMAG TAB"    Press Any Key to Continue");
getche();
    front_screen();
    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//Welcome Screen Function
int front_screen(void)
{

    while(1) //Infinite Loop to keep the program running until user decides to exit
    {        //And to Display the welcome screen again after if control returns from other functions
        clear_screen();
    printf(BHRED"\n\n\n\n\n\n\n\n\n\n\n\n%sWelcome To Al-Shifa Hospital Managment System\n"CRESET,TAB);
    printf(BHRED"%s\n"CRESET,h_line);
    printf(BHBLU"\n%sPlease Select an appropriate option\n\n"CRESET,TAB);
    printf(BHBLU"\t\t\t\t\t\t\t\t1)Patient Portal\n"CRESET);
    printf(BHBLU"\t\t\t\t\t\t\t\t2)Admin Portal\n"CRESET);
    printf(BHBLU"\t\t\t\t\t\t\t\t3)Exit The Application\n\n"CRESET);
    printf(BHRED"%s\n"CRESET,h_line);
    printf(BHGRN"\t\t\t\t\t\t\t\tPlease Enter Your Choice : "CRESET);
   // clearInputBuffer();
    int choice = getche();
    
    switch (choice)
    {
    case '1' :
    	printf(BHBLU"\n\t\t\t\t\t\t\t\tLoading Patient Portal ["CRESET);
    	for(int i=0;i<10;i++)
    	{	
			Sleep(80);
    		printf(BHBLU"#"CRESET);
		}
		printf(BHBLU"]"CRESET);
		Sleep(200);
        patient_portal(); //Forwarding control to patient portal function
        break;
     case '2' :
     	printf(BHBLU"\n\t\t\t\t\t\t\t\tLoading Admin Portal ["CRESET);
    	for(int i=0;i<10;i++)
    	{	
			Sleep(80);
    		printf(BHBLU"#"CRESET);
		}
		printf(BHBLU"]"CRESET);
		Sleep(200);
        admin_login_function(); //Forwarding control to doctor portal function
        break; 
    case '3':
    		printf(BHBLU"\n\t\t\t\t\t\t\t\tExiting The Program["CRESET);
    	for(int i=0;i<10;i++)
    	{	
			Sleep(800);
    		printf(BHBLU"#"CRESET);
		}
		printf(BHBLU"]"CRESET);
		Sleep(2000);
        exit(0); //Exiting the program
        break;
    
    default: //If user accendently enters an invalid option,it prompts the user to try again
        printf(BHMAG"\n\t\t\t\t\t\t\t\tInvalid choice!\n\t\t\t\t\t\t\t\tPress Any Key to try again...");
       // clearInputBuffer();
        getche();
        break;
    }

}
}
