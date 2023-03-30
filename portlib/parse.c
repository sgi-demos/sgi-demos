/*
 *	parse -
 *		A feedback parsing package.
 *
 *				Henry Moreton - 1985
 *
 */
#include "gl.h"
#include "stdio.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "uc4.h"

typedef struct {
    char	*fbcstring;
    int		two_d_count;
    int		three_d_count;
    int		(*handler)();
} Feedbacktable;

#include "parsetab.h"

static	short	*buff_ptr;
static	short	debugging;
static  int	buff_count;
static  int	word_no;
static  char	parse_not_done;


parsefb(buffer, count, zbuff, depthcue)
    short		*buffer;
    int 		count;
    int			zbuff, depthcue;
{

    int		(*handling_routine)();
    char	*FBCstring;
    short	in_3d;
    char	no_error = TRUE;
    short	opcode;
    short	highbyte;
    short	passthroughcount;
    int		paramcount;

    word_no = 0;
    parse_not_done = TRUE;
    buff_count = count;
    buff_ptr = buffer;
    in_3d = zbuff || (depthcue<<1);

    while (parse_not_done && no_error) {
	opcode = 0xff & (highbyte = getfbword());
	highbyte = highbyte >> 8;
	if ((opcode < TABLE_END) && parse_not_done) {
	    switch (opcode) {
		case FBCdrawmode :
		    if (buff_ptr[1])
			in_3d |= 1;
		    else 
			in_3d &= (~1);
		    break;
	        case FBCconfig :
		    if (*buff_ptr & UC_DEPTHCUE)
			in_3d |= 2;
		    else
			in_3d &= (~2);
		    break;
		case FBCforcecompletion :
		    passthroughcount = highbyte;
		    break;
	    }

	    handling_routine = feedbacktable[opcode].handler;
	    FBCstring = feedbacktable[opcode].fbcstring;
	    if (in_3d)
		paramcount = feedbacktable[opcode].three_d_count;
	    else
		paramcount = feedbacktable[opcode].two_d_count;
	    if (paramcount == -1)
		paramcount = passthroughcount;
	    (*handling_routine)(paramcount, opcode, FBCstring);
	} else
	    no_error = FALSE;
    }
    if (parse_not_done)
	return FALSE;
    else
	return TRUE;
}

static char *UNDEFINED = {"ignored"};

static FILE *output;

static parsefdback(count, opcode, fbcstring)
    int		count;
    int		opcode;
    char 	*fbcstring;
{
    int i;
    int inputword;

    if (debugging)
	fprintf(output,"#%d: %s : 0x%x\n", 
	    word_no, (fbcstring?fbcstring:UNDEFINED), 0xffff&opcode);

    for (i = 0; i < count; i++) {
	inputword = getfbword();
	if (debugging)
	    fprintf(output,"\t\t#%d: %d:0x%x\n", word_no, inputword, 0xffff&inputword);
    }
}

getfbword()
{
    if (!(buff_count--))
	parse_not_done = FALSE;
    word_no++;
    return(*buff_ptr++);
}


extern end;

setfbdebugging(flag, file)
int flag;
FILE *file;
{
    int i;
    struct stat buf;

    debugging = flag;
    output = stderr;
    /* check the reality of this pointer */
    if (((int)file >= (int)stdin) && ((int)file <= (end - sizeof(FILE)))) {
	i = fileno(file);
	if (fstat(i, &buf) != -1) 
	    output = file;
    }
}

bindfbfunc(entryno, function)
int entryno;
int (*function)();
{
    if ((entryno >= 0) && (entryno < TABLE_END)) {
        feedbacktable[entryno].handler = function;
	return TRUE;
    } else
	return FALSE;
}
