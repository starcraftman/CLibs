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
#include <argp.h>

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

typedef struct arguments
{
    char *args[2];
    int silent, verbose;
    char *output_file;
} arguments_t;

/**************** Static Data/Functions *******************/
const char *argp_program_version = "argp-ex3 1.0";
const char *argp_program_bug_address = "<bug-gnu-utils@gnu.org>";

static char doc[] = "Argp example #3 -- A program with options and arguments.";
static char args_doc[] = "ARG1 AEG2";

static struct argp_option options[] = {
    {"verbose", 'v', 0, 0, "Produce verbose output", 0},
    {"quiet", 'q', 0, 0, "Don't produce any output", 0},
    {"silent", 's', 0, OPTION_ALIAS, 0, 0},
    {"output", 'o', "FILE", 0, "Output to FILE instead of stdout", 0},
    {0, 0, 0, 0, 0, 0}
};

static error_t
parse_opt(int key, char *arg, struct argp_state *state)
{
    arguments_t *arguments = state->input;

    switch (key) {
        case 'q': case 's':
            arguments->silent = 1;
            break;
        case 'v':
            arguments->verbose = 1;
            break;
        case 'o':
            arguments->output_file = arg;
            break;
        case ARGP_KEY_ARG:
            /* Too many args */
            if (state->arg_num >= 2)
                argp_usage(state);
            arguments->args[state->arg_num] = arg;
            break;
        case ARGP_KEY_END:
            /* Too few args */
            if (state->arg_num < 2)
                argp_usage(state);
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }

    return 0;
}

static struct argp argp = {options, parse_opt, args_doc, doc, 0, 0, 0};

/****************** Global Functions **********************/
int main(int argc, char *argv[])
{
    arguments_t args;

    /* Defaults. */
    args.silent = 0;
    args.verbose = 0;
    args.output_file = "-";

    argp_parse(&argp, argc, argv, 0, 0, &args);

    printf("ARG1 = %s\nARG2 = %s\nOUTPUT = %s\nVERBOSE = %s\n SILENT = %s\n",
            args.args[0], args.args[1], args.output_file,
            args.verbose ? "yes" : "no",
            args.silent ? "yes" : "no");

    return 0;
}

