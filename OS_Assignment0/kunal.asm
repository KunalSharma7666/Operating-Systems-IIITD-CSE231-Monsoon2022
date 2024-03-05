section .data
        format1 db "%d",0
        format2 db "%s",0
        output1 db "%d",0x0a,0
        output2 db "%s",0x0a,0


        
section .text
        global main
        extern printf
        extern scanf


main:

       push rbp
       mov rbp, rsp
       sub rsp, 16
       lea rdi, [format1]
       xor eax, eax
       call scanf
       lea rdi, [output1]
       xor eax, eax
       call printf
       mov eax, 0
       lea rdi, [format2]
       lea rsi, [string]
       xor eax, eax
       call scanf
       mov eax, 0
       lea rdi, [output2]
       lea rsi, [string]
       call printf
       add rsp, 16
       leave
       ret 


section .bss
        string: resb 32