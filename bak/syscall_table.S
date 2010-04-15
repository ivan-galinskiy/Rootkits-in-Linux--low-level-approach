ENTRY(sys_call_table)
        /* 0 - old "setup()" system call, used for restarting */
        .long sys_restart_syscall   /* 0 */
        .long sys_exit
        .long ptregs_fork
        .long sys_read
        .long sys_write
        .long sys_open              /* 5 */
        .long sys_close
        .long sys_waitpid
        .long sys_creat
        .long sys_link
        .long sys_unlink            /* 10 */
        /* Many more entries (like 300)... */