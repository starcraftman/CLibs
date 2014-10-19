/**
 * Template C file.
 */
/********************* Header Files ***********************/
/* C Headers */
#include <stdio.h>
#include <string.h>
#include <stdlib.h> /* atof, rand, malloc... */
//#include <stddef.h> /* size_t, NULL */
//#include <stdarg.h> /* Variable argument functions */
//#include <ctype.h> /* Character check functions */
//#include <limits.h>
//#include <assert.h>
//$include <math.h>
//$include <stdint.h> /* C11, standard u_int16 & such */

/* Project Headers */
#include "libxml/parser.h"
#include "libxml/tree.h"

/******************* Constants/Macros *********************/


/******************* Type Definitions *********************/
/* For enums: Try to namesapce the common elements.
 * typedef enum {
 *	VAL_,
 * } name_e;
 */

/* For structs:
 * typedef struct nam_s {
 *	int index;
 * } name_t;
 */


/**************** Static Data/Functions *******************/
static void 
example1Func(const char *filename) {
    xmlDocPtr doc;

    doc = xmlReadFile(filename, NULL, 0);
    if (doc == NULL) {
        fprintf(stderr, "Failed to parse %s\n", filename);
        return;
    }
    xmlFreeDoc(doc);
}

/****************** Global Functions **********************/
int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;

    LIBXML_TEST_VERSION

    example1Func(argv[1]);
    xmlCleanupParser();
    xmlMemoryDump();

    return 0;
}

