
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                               proc.c
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                    Forrest Yu, 2005
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "type.h"
#include "const.h"
#include "protect.h"
#include "tty.h"
#include "console.h"
#include "string.h"
#include "proc.h"
#include "global.h"
#include "proto.h"



PUBLIC void p_process(SEMAPHORE* s){
	disable_int();
    s->value--;
    if (s->value < 0){
        p_proc_ready->blocked = 1;
        s->p_list[s->tail] = p_proc_ready;
        s->tail = (s->tail + 1) % NR_PROCS;
        schedule();
    }
	enable_int();
}



PUBLIC void v_process(SEMAPHORE* s){
	disable_int();
    s->value++;
    if (s->value <= 0){
        s->p_list[s->head]->blocked = 0; 
        s->head = (s->head + 1) % NR_PROCS;
    }
	enable_int();
}

/*======================================================================*
                              schedule
 *======================================================================*/
PUBLIC void schedule()
{
	PROCESS* p;
	int	greatest_ticks = 0;

	while (!greatest_ticks) {
		for (p = proc_table; p < proc_table+NR_TASKS+NR_PROCS; p++) {

			if (p->sleeping > 0 || p->blocked) continue; 
			// 正在睡眠/阻塞的进程不会被执行（也就是不会被分配时间片）
			if (p->ticks > greatest_ticks) {
				greatest_ticks = p->ticks;
				p_proc_ready = p;
			}
		}
		// 如果都是0，那么需要重设ticks
		if (!greatest_ticks) {
			for (p = proc_table; p < proc_table+NR_TASKS+NR_PROCS; p++) {
				if (p->ticks > 0) continue; // >0 还进入这里只能说明它被阻塞了
				p->ticks = p->priority;
			}
		}
	}
}

/*======================================================================*
                           sys_get_ticks
 *======================================================================*/
PUBLIC int sys_get_ticks()
{
	return ticks;
}

PUBLIC void sys_sleep(int milli_sec,int type)
{
	int ticks = milli_sec / 1000 * HZ * 10;  // 乘10是为了修正系统的时钟中断错误
	p_proc_ready->sleeping = ticks;
    p_proc_ready->issleep = type;
    schedule();
}

PUBLIC void sys_write_str(char* buf, int len)
{
    CONSOLE* p_con = console_table;
	for (int i = 0;i < len; i++){
		out_char(p_con, buf[i]);
	}
}
