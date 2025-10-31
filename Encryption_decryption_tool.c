#include <stdio.h>
#include <string.h>
#include "flushinput.h"
#include <stddef.h>
#include <stdlib.h>
	
/* Setting a encrypted password taken from user and then performing the encryption operation on the file*/
void Encrypt_Operation(const char* file1, const char* file2) {
    unsigned char user_choice_password[101] = {0};
    printf("\nCreate a strong password of max 100 characters: ");

    //Password creation & error checks
    while (1) {
        if (fgets((char*)user_choice_password, 101, stdin) != NULL) {
            size_t len = strlen((char*)user_choice_password);
            if (len > 0 && user_choice_password[len - 1] == '\n')
                user_choice_password[len - 1] = '\0';
            else
                flush_input();

            if (strlen((char*)user_choice_password) == 0 || user_choice_password[0] == ' ') {
                fprintf(stderr, "\nPassword of 0 length\nPlease create again: ");
                continue;
            } else if (strlen((char*)user_choice_password) < 8) {
                fprintf(stderr, "\nPassword too short — minimum 8 characters allowed!\nCreate again: ");
                continue;
            } else
                break;
        } else {
            fputs("\nError while reading password\n", stderr);
            exit(1);
        }
    }

    // Encrypting and saving the password
    FILE *encrypted_pass_file = fopen("/home/abhinav/pass.txt", "wb");
    if (!encrypted_pass_file) {
        perror("Error while encrypting and saving your password");
        exit(1);
    }

    // Offset Cipher based algorithm simple algorithm used
    unsigned int offset_cipher = 88;
    size_t size_of_pass = strlen((char*)user_choice_password);
    unsigned char encrypted_char_;

    for (size_t i = 0; i < size_of_pass; i++) {
        encrypted_char_ = (user_choice_password[i] + offset_cipher) % 256; // 
        fwrite(&encrypted_char_, 1, 1, encrypted_pass_file);
    }

    fclose(encrypted_pass_file);
	
    // Now encrypting the file name supplied by the user
    FILE *user_file = fopen(file1, "rb");
    FILE *user_chosed_ecfile = fopen(file2, "wb");
    if (!user_file || !user_chosed_ecfile) {
        perror("Error performing file operations");
        if (user_file) fclose(user_file);
        if (user_chosed_ecfile) fclose(user_chosed_ecfile);
        exit(1);
    }

    unsigned char character;
    while (fread(&character, 1, 1, user_file) == 1) {
        encrypted_char_ = (character + offset_cipher) % 256;
        fwrite(&encrypted_char_, 1, 1, user_chosed_ecfile);
    }
	
    printf("\nFile encrypted successfully\n");
    fclose(user_file);
    fclose(user_chosed_ecfile);
    remove(file1);// Removing the original file


}

/* Verifying the encrypted password taken from user and then performing the decryption operation on the file*/
void Decrypt_Operation(const char* file1, const char* file2) {
    unsigned char user_pass_for_verification[101];
    printf("\nEnter your previously created password to verify: ");
    while (1) {
        if (fgets((char*)user_pass_for_verification, 101, stdin) != NULL) {
            size_t len = strlen((char*)user_pass_for_verification);
            if (len > 0 && user_pass_for_verification[len - 1] == '\n')
                user_pass_for_verification[len - 1] = '\0';
            else
                flush_input();

            if (strlen((char*)user_pass_for_verification) == 0 || user_pass_for_verification[0] == ' ') {
                fprintf(stderr, "\nPassword of 0 length\nPlease enter again: ");
                continue;
            } else
                break;
        } else {
            fputs("\nError while reading verified password\n", stderr);
            exit(1);
        }
    }

    unsigned int offset_cipher = 88;
    size_t size_of_verification_pass = strlen((char*)user_pass_for_verification);
    unsigned char encrypted_char_;
    unsigned char encrypted_verified_pass[101] = {0};

    for (size_t i = 0; i < size_of_verification_pass; i++) {
        encrypted_char_ = (user_pass_for_verification[i] + offset_cipher) % 256;
        encrypted_verified_pass[i] = encrypted_char_;
    }

    unsigned char user_encrypted_pass[101] = {0};
    FILE *encrypted_pass_file = fopen("/home/abhinav/pass.txt", "rb");
    if (!encrypted_pass_file) {
        perror("Error while reading your password from encrypted file.");
        exit(1);
    }

    fread(user_encrypted_pass, 1, sizeof(user_encrypted_pass), encrypted_pass_file);
    fclose(encrypted_pass_file);

    if (memcmp(user_encrypted_pass, encrypted_verified_pass, size_of_verification_pass) == 0) {
        FILE *encrypted_file = fopen(file1, "rb");
        FILE *decrypted_file = fopen(file2, "wb");
        if (!encrypted_file || !decrypted_file) {
            perror("Error while checking password");
            if (encrypted_file) fclose(encrypted_file);
            if (decrypted_file) fclose(decrypted_file);
            exit(1);
        }

        unsigned char character;
        unsigned char decrypted_char;
        while (fread(&character, 1, 1, encrypted_file) == 1) {
            decrypted_char = (character - offset_cipher + 256) % 256;
            fwrite(&decrypted_char, 1, 1, decrypted_file);
        }
        fclose(encrypted_file);
        fclose(decrypted_file);
	remove(file1); // Removing the encrypted file
        printf("\nFile decrypted successfully.\n");
    } else {
        fprintf(stderr, "\nPassword didn't match.\n");
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <input_file> <output_file> <operation>\n", argv[0]);
        return 1;
    }
    const char* file1 = argv[1]; // Passing names of files from cli
    const char* file2 = argv[2];
	
    /* Check to find which operation is wanted to be performed by user */
    if (strcmp(argv[3], "encrypt") == 0) {
        Encrypt_Operation(file1, file2);
    } else if (strcmp(argv[3], "decrypt") == 0) {
        Decrypt_Operation(file1, file2);
    } else {
        fprintf(stderr, "Invalid operation\n");
        return 1;
    }

    return 0;
}

