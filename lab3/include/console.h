
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			      console.h
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						    Forrest Yu, 2005
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#ifndef _ORANGES_CONSOLE_H_
#define _ORANGES_CONSOLE_H_
#define SCR_UP	1	/* scroll forward */
#define SCR_DN	-1	/* scroll backward */
#define SCREEN_SIZE		(80 * 25)
#define SCREEN_WIDTH		80


typedef struct cursor_record{
    unsigned int index;
    unsigned int len;
    unsigned int content[SCREEN_SIZE];
} CURSOR_RECORD;

typedef struct char_record{
    int index;
    int endOfNormalIndex;
    char content[SCREEN_SIZE];
} CHAR_RECORD;

typedef struct s_console
{
	unsigned int	current_start_addr;	/* 当前显示到了什么位置	  */
	unsigned int	original_addr;		/* 当前控制台对应显存位置 */
	unsigned int	v_mem_limit;		/* 当前控制台占的显存大小 */
	unsigned int	cursor;			/* 当前光标位置 */
	CURSOR_RECORD cursor_record;                 
    CHAR_RECORD char_record;                
    unsigned int endOfNormal;
}CONSOLE;



#define SCR_UP	1	/* scroll forward */
#define SCR_DN	-1	/* scroll backward */

#define SCREEN_SIZE		(80 * 25)
#define SCREEN_WIDTH		80

#define DEFAULT_CHAR_COLOR	0x07	/* 0000 0111 黑底白字 */


#endif /* _ORANGES_CONSOLE_H_ */
