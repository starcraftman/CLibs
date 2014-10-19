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
#include "libxml/xmlreader.h"

/******************* Constants/Macros *********************/
#define XML_FILE "res/libxml/test3.xml"

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
#ifdef LIBXML_READER_ENABLED

static void 
processNode(xmlTextReaderPtr reader) {
    const xmlChar *name, *value;

    name = xmlTextReaderConstName(reader);
    if (name == NULL) 
        name = BAD_CAST "--";

    value = xmlTextReaderConstValue(reader);

    printf("%d %d %s %d %d",
            xmlTextReaderDepth(reader),
            xmlTextReaderNodeType(reader),
            name,
            xmlTextReaderIsEmptyElement(reader),
            xmlTextReaderHasValue(reader));

    if (value == NULL) {
        printf("\n");
    } else {
        if (xmlStrlen(value) > 40) {
            printf(" %.40s...\n", value);
        } else {
            printf(" %s\n", value);
        }
    }
}

static void
streamFile(const char *filename) {
    xmlTextReaderPtr reader;
    int ret;

    reader = xmlReaderForFile(filename, NULL, 0);
    if (reader != NULL) {
        ret = xmlTextReaderRead(reader);

        while(ret == 1) {
            processNode(reader);
            ret = xmlTextReaderRead(reader);
        }

        xmlFreeTextReader(reader);
        if (ret != 0) {
            fprintf(stderr, "%s : failed to parse\n", filename);
        }
    } else {
        fprintf(stderr, "Unable to open %s\n", filename);
    }
}

/****************** Global Functions **********************/
int main(void)
{
    LIBXML_TEST_VERSION

    streamFile(XML_FILE);
    xmlCleanupParser();
    xmlMemoryDump();

    return 0;
}

#else 
int main(void) {
    fprintf(stderr, "XInclude support not compiled in\n");
    exit(1);
}
#endif 

