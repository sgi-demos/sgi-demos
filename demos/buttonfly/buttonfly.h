/*
 *	Type definitions, etc for buttonfly
 */
#define random(r) (r*(float)rand()/(float)(RAND_MAX))

#define WORDLENGTH 11

typedef struct popup_struct_type
{
	char *title;
	char *action;
	struct popup_struct_type *next;
} popup_struct;

typedef struct button_struct_type
{
	char name[3][20];
	int wc;		/* word count */
	char *action;
	char *submenu;
	popup_struct *popup;

	/* RGB 0 to 1 */
	float color[3];
	float backcolor[3];
	float highcolor[3];
	float default_color[3];
	float default_backcolor[3];
	float default_highcolor[3];
	struct button_struct_type *next;
	struct button_struct_type *forward;

	short ax, ay, az;
	float tx, ty, tz;
} button_struct;

typedef struct path_struct_type {

    button_struct *current_buttons;
    button_struct *button;
    struct path_struct_type *back;

} path_struct;

#define NUM_TOKENS 5
#define MAX_SPOTS 32

extern char *dot_tokens[NUM_TOKENS];
extern int token_nums[];
extern float *spots[32];
extern button_struct *current_button;
