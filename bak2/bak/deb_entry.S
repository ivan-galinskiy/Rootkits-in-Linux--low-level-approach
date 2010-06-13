ENTRY(debug)
        RING0_INT_FRAME
        cmpl $ia32_sysenter_target,(%esp)
        jne debug_stack_correct
        FIX_STACK 12, debug_stack_correct, debug_esp_fix_insn
debug_stack_correct:
        pushl $-1                       # mark this as an int
        CFI_ADJUST_CFA_OFFSET 4
        SAVE_ALL
        TRACE_IRQS_OFF
        xorl %edx,%edx                  # error code 0
        movl %esp,%eax                  # pt_regs pointer
        call do_debug
        jmp ret_from_exception
        CFI_ENDPROC
END(debug)