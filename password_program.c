#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Main function
int main() {

    // Declaring arrays to store user input and final stored username/password
    char user_password[128];
    char stored_password[128];
    char username[50];
    char stored_username[50];

    // Loop to create and validate username
    while(1){
        printf("Create a username: ");
        fgets(username, sizeof(username), stdin);  // Read username with spaces safely

        // Remove newline character at end if present
        username[strcspn(username, "\n")] = 0;

        // Check minimum length of username
        if(strlen(username) < 5){
            printf("Username should contain at least 5 characters\n");
            continue;  // Ask again if too short
        }
        else{
            strcpy(stored_username, username);  // Store valid username
            break;  // Exit loop
        }
    }

    // Loop to create and verify password with complexity requirements
    while(1){
        printf("Create a strong password: ");
        fgets(user_password, sizeof(user_password), stdin); // Read password input

        // Remove newline character at end if present
        user_password[strcspn(user_password, "\n")] = 0;

        // First check: minimum length
        if(strlen(user_password) < 8){
            printf("Password should contain minimum 8 characters!\n");
            continue;  // Ask again if too short
        }

        // Initialize complexity flags
        int hasupper = 0, haslower = 0, hasdigit = 0, hasspecial = 0;

        // Loop through each character to check for required types
        for(int i = 0; i < strlen(user_password); i++){
            if(isupper(user_password[i])){
                hasupper = 1;  // Found an uppercase letter
            }
            else if(islower(user_password[i])){
                haslower = 1;  // Found a lowercase letter
            }
            else if(isdigit(user_password[i])){
                hasdigit = 1;  // Found a digit
            }
            else{
                hasspecial = 1;  // Found a special character
            }
        }

        // Check if any requirement is missing
        if(!hasupper || !haslower || !hasspecial){
            printf("Weak password.\n");
            continue;  // Ask again if complexity conditions not met
        }

        // Password meets all criteria, now verify by re-entering
        char verify[128];
        printf("Re-enter password to verify: ");
        fgets(verify, sizeof(verify), stdin);
        verify[strcspn(verify, "\n")] = 0;

        // Compare both passwords
        if(strcmp(verify, user_password) == 0){
            printf("Password set successfully!\n");
            strcpy(stored_password, user_password);  // Store verified password
            break;  // Exit loop as password set successfully
        }
        else{
            printf("Passwords don't match. Try again.\n");
            // Loop continues to ask again
        }
    }

    return 0; // End of program
}

