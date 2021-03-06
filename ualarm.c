#include "std.h"
#ifndef HAS_UALARM
/*
 * Copyright (c) 1985 Regents of the University of California.
 * All rights reserved.
 * 重新分配
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "@(#)ualarm.c	5.5 (Berkeley) 2/23/91";
#endif				/* LIBC_SCCS and not lint */

#define	USPS	1000000		/* # of microseconds in a second 1秒 */

unsigned ualarm (register unsigned, register unsigned);

/*
 * Generate a SIGALRM signal in ``usecs'' microseconds.
 * If ``reload'' is non-zero, keep generating SIGALRM
 * every ``reload'' microseconds after the first signal.
 * 自定义的alarm信号规则，就是多少秒触发一次等等
 */
/* 参数(2000000, 0) */
unsigned ualarm(register unsigned  usecs, register unsigned  reload) {
    struct itimerval new, old;		/* 这个结构体是系统带的 */

    new.it_interval.tv_usec = reload % USPS;	/* 计时器重启动的时间间隔,若为0,则只触发一次 */
    new.it_interval.tv_sec = reload / USPS;

    new.it_value.tv_usec = usecs % USPS;		/* 计时器安装后首先启动的初始值 */
    new.it_value.tv_sec = usecs / USPS;

    if (setitimer(ITIMER_REAL, &new, &old) == 0)	/* REAL决定了发送ALARM信号 */
		return old.it_value.tv_sec * USPS + old.it_value.tv_usec;	
    /* else */
    return -1;
}
#endif
