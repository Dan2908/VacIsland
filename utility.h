#ifndef H_UTILITY
#define H_UTILITY

/**
 * Returns a string (char*) allocated dynamically, use free() to free memory
 * @return char pointer to text contents read from file. NULL if there were
 * errors.
 * @param fileName Path to file. 
*/
char *read_file(const char *fileName);

#endif