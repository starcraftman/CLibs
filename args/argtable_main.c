/**
 * Template C file.
 */
/********************* Header Files ***********************/
/* C Headers */
#include <stdio.h>
//#include <string.h>
//#include <stdlib.h> /* atof, rand, malloc... */
//#include <stddef.h> /* size_t, NULL */
//#include <stdarg.h> /* Variable argument functions */
//#include <ctype.h> /* Character check functions */
//#include <limits.h>
//#include <assert.h>
//$include <math.h>
//$include <stdint.h> /* C11, standard u_int16 & such */

/* Project Headers */
#include "argtable2.h"

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
int report(int l, int R, int k, const char **defines, int ndefines,
        const char *outfile, int v,
        const char **infiles, int ninfiles)
{
    int i;

    if (l > 0)
        printf("list files (-l)\n");
    if (R > 0)
        printf("recurse directories (-R)\n");
    if (v > 0)
        printf("verbose is enabled (-v)\n");
    printf("scalar k=%d\n", k);
    printf("output is \"%s\"\n", outfile);

    for (i = 0; i < ndefines; ++i)
    {
        printf("user defined macro \"%s\"\n", defines[i]);
    }

    for (i = 0; i < ninfiles; ++i)
    {
        printf("infile[%d]=\"%s\"\n", i, infiles[i]);
    }

    return 0;
}

/****************** Global Functions **********************/
int main(int argc, char **argv)
{
    struct arg_lit *help = arg_lit0(NULL, "help", "print this help and exit");
    struct arg_lit *list = arg_lit0("lL", NULL, "list files");
    struct arg_lit *recurse = arg_lit0("R", NULL, "recurse sub directories");
    struct arg_lit *verbose = arg_lit0("v", "verbose,debug", "verbose messages");
    struct arg_lit *version = arg_lit0(NULL, "version", "print version information and exit");
    struct arg_int *repeat = arg_int0("k", "scalar", NULL, "define scalar value (default is 3)");
    struct arg_str *defines = arg_strn("D", "define", "MACRO", 0, argc + 2, "macro definitions");
    struct arg_file *outfile = arg_file0("o", NULL, "<output>", "output files, default stdout");
    struct arg_file *infiles = arg_filen(NULL, NULL, NULL, 1, argc + 2, "input files");

    /* arg_end used for error reporting and terminatint below void * ptr */
    struct arg_end *end = arg_end(20);

    void *argtable[] = { help, list, recurse, verbose, version, repeat, defines, outfile, infiles, end };
    const char * const progname = "Argtable";
    int nerrors;
    int exitcode = 0;

    if (arg_nullcheck(argtable) != 0)
    {
        printf("%s: insufficient memor\n", progname);
        exitcode = 1;
        goto exit;
    }

    /* Default values should be set before parsing. */
    repeat->ival[0] = 3;
    outfile->filename[0] = "-";

    /* Parsing here. */
    nerrors = arg_parse(argc, argv, argtable);

    if (help->count > 0)
    {
        printf("Usage: %s", progname);
        arg_print_syntax(stdout, argtable, "\n");
        printf("This program demonstrates the use of the argtable2 library\n");
        printf("for parsing command line arguments. Argtable accepts integers\n");
        printf("in decimal (123), hexadecimal (0xff), octal (0o123) and binary\n");
        printf("(0b101101) formats. Suffixes KB, MB and GB are also accepted.\n");
        arg_print_glossary(stdout, argtable, "  %-25s %s\n");
        exitcode = 0;
        goto exit;
    }

    if (version->count > 0)
    {
        printf("%s example program for the argtable parse.\n", progname);
        printf("Done by starcraftman\n");
        exitcode = 0;
        goto exit;
    }

    if (nerrors > 0)
    {
        arg_print_errors(stdout, end, progname);
        printf("Try %s --help for moreinformation\n", progname);
        exitcode = 1;
        goto exit;
    }

    if (argc == 1)
    {
        printf("Try %s --help for moreinformation\n", progname);
        exitcode = 1;
        goto exit;
    }

    exitcode = report(list->count, recurse->count, repeat->ival[0],
            defines->sval, defines->count, outfile->filename[0],
            verbose->count, infiles->filename, infiles->count);

exit:
    arg_freetable(argtable, sizeof(argtable)/sizeof(argtable[0]));

    return exitcode;
}

