#include "headers.h"
/**
 * @author Daniel Thompson
 */


/**
 * @param string the string to convert to ISO8859-1
 * @return The string in ISO8859-1 or NULL if there is an error 
 */
char *toAscii(const char *string) {
    size_t inputStringLength = strlen(string);
    size_t outputStringLength = inputStringLength + 1;
    char *newStr = malloc(outputStringLength);
    
    // Convert from EBCDIC to ISO8859-1
    iconv_t convert = iconv_open("ISO8859-1", "IBM-1047");
    if (convert == (iconv_t)-1) {
        fprintf(stderr, "%s\n", strerror(errno));
        iconv_close(convert);
        return NULL;   
    }
    // ptr for iconv
    char *outptr = newStr;

    iconv(convert, &string, &inputStringLength, &outptr, &outputStringLength);
    // Null terminate converted string
    *outptr = '\0';
    iconv_close(convert);

    // Return converted string
    return newStr;
}
