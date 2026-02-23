
#ifndef UTILITY_FUNCTIONS_H
#define UTILITY_FUNCTIONS_H
//char* get_patient_name(Patient p[], int total, int pid);
int load_doctors(Doctor d[]);
int load_patients(Patient p[]);
void clearInputBuffer(void);
unsigned long long simple_hash(const char *str);
//int is_valid_number(const char *str, int length);
void clear_screen(void);
int getIntInRange(const char *promt,int min, int max);
//int is_blank(const char *s);
//void remove_newline(char *str);
void string_input_function(char *buffer, const char *prompt_color, const char *prompt);
void string_input_limited(char *buffer, int limit, const char *prompt_color, const char *prompt);
void loading_bar(const char *message);
void loading_animation(const char* message);
//void string_input_function_limit(char *buffer,size_t size, const char *prompt_color, const char *prompt)
#endif // UTILITY_FUNCTIONS_H

