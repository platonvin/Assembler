in
pop rax
push 1
pop rbx

foggy:

;
;
push rax ; rax
dup ; rax rax
push 1 ; rax rax 1
je endflag ; rax

dup
push rbx ; rax-1 rbx
imul ; rbx*(rax-1)
pop rbx

push 1 ; rax 1
sub ; rax-1
pop rax ; rax-1

jmp foggy

;
;


endflag:

push rbx
out

hlt