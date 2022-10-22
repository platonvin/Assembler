#ifndef STR_FUNCS_H
#define STR_FUNCS_H
#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

/**
 * takes a string as an argument and prints it to the standard output
 * 
 * @param str The string to print.
 * 
 * @return The first character of the string.
 */
int put_str(const char str[]);

/**
 * returns a pointer to the first occurrence of the character `ch` in the string `str`
 * 
 * @param str The string to search.
 * @param ch The character to search for.
 * 
 * @return A pointer to the first occurrence of the character ch in the string str.
 */
char* str_chr(char *str, int ch);

/**
 * returns the length of the string `str`
 * 
 * @param str The string to get the length of.
 * 
 * @return The length of the string.
 */
size_t str_length(const char *str);

/**
 * Copy the contents of the string pointed to by `src` to the string pointed to by `dest`
 * 
 * @param dest The destination string.
 * @param src The source string to copy from.
 * 
 * @return dest
 */
char *str_copy(char *dest, const char *src);

/**
 * Copy the first `count` characters from `src` to `dest` and return `dest`
 * 
 * @param dest The destination string.
 * @param src The source string.
 * @param count The number of characters to copy.
 * 
 * @return The pointer to the destination string.
 */
char *str_ncopy(char *dest, const char *src,  size_t count);

/**
 * Copies the contents of the source string to the destination string, starting at the end of the
 * destination string
 * 
 * @param dest pointer to the destination array, which should contain a C string, and be large enough
 * to contain the concatenated resulting string.
 * @param src a pointer to the string to be appended to dest.
 * 
 * @return The pointer to the first character of the string.
 */
char *str_CAT(char *dest, const char *src);

/**
 * Copies first count characters from src to the end of the dest
 * 
 * @param dest The destination string.
 * @param src The source string to copy from.
 * @param count The number of characters to copy from src to dest.
 * 
 * @return The pointer to the destination string.
 */
char *str_nCAT(char *dest, const char *src,  size_t count);

/**
 * Reads a string from a file
 * 
 * @param str The string to write to.
 * @param count The maximum number of characters to be read (including the terminating null-character).
 * @param file The file to read from.
 * 
 * @return A pointer to the first character of the string.
 */
char *f_get_s(char *str, int count, FILE *file);

/**
 * Takes a string, allocates memory for a replica of that string, copies the string into the
 * allocated memory
 * 
 * @param str The string to be copied.
 * 
 * @return pointer to the allocated memory
 */
char *str_dup(const char *str);

/**
 * Reads a line from a file, and stores it in a destination string
 * 
 * @param file The file to read from.
 * @param dest The destination string.
 * @param separator The character that separates the lines.
 * 
 * @return The file pointer.
 */
FILE *get_line(FILE *stream, char *dest, char separator = 0);

bool str_cmpr(const char *str1, const char *str2);

/**
 * The function compares two strings, ignoring non-alphabetic characters, and returns -1 if the first
 * string is less than the second, 0 if the strings are equal, and 1 if the first string is greater
 * than the second
 * 
 * @param str1 The first string to compare.
 * @param str2 The second string to compare.
 * 
 * @return -1 if the first string is less than the second, 0 if the strings are equal, 
 * and 1 if the first string is greater than the second
 */
int str_alpha_cmpr(const char *str1, const char *str2);

void delete_spaces(char *str);

void cut_first_word(char *src);

void str_do_zero(char *s);

#endif //STR_FUNCS_H