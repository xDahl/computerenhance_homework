# computerenhance homework - 8086 MOV instructions.
Just some homework I did for the course at computerenhance.com\
My code here is fairly hacky, and shouldn't be used for anything other than an overview!

I finished the extra listing (40) just for fun, there is still one case I haven't dealt with, but I think that's fine.

The output from running this:
```asm
; Homework 0037
mov cx, bx

; Homework 0038
mov cx, bx
mov ch, ah
mov dx, bx
mov si, bx
mov bx, di
mov al, cl
mov ch, ch
mov bx, ax
mov bx, si
mov sp, di
mov bp, ax

; Homework 0039
mov si, bx
mov dh, al
mov cl, 12
mov ch, 244
mov cx, 12
mov cx, 65524
mov dx, 3948
mov dx, 61588
mov al, [bx + si]
mov bx, [bp + di]
mov dx, [bp]
mov ah, [bx + si + 4]
mov al, [bx + si + 4999]
mov [bx + di], cx
mov [bp + si], cl
mov [bp], ch

; Homework 0040
mov ax, [bx + di + 219]
mov [si + 65236], cx
mov dx, [bx + 224]
mov [bp + di], byte 7
mov [di + 901], word 347
mov bp, [5]
mov bx, [3458]
mov ax, [2555]
mov ax, [16]
mov [2554], ax
mov [15], ax

; Homework 0041
add bx, [bx + si]
add bx, [bp]
add si, word 2
add bp, word 2
add cx, word 8
add bx, [bp]
add cx, [bx + 2]
add bh, [bp + si + 4]
add di, [bp + di + 6]
add [bx + si], bx
add [bp], bx
add [bp], bx
add [bx + 2], cx
add [bp + si + 4], bh
add [bp + di + 6], di
add [bx], byte 34
add [bp + si + 1000], word 29
add ax, [bp]
add al, [bx + si]
add ax, bx
add al, ah
add ax, 1000
add al, 226
add al, 9
sub bx, [bx + si]
sub bx, [bp]
sub si, word 2
sub bp, word 2
sub cx, word 8
sub bx, [bp]
sub cx, [bx + 2]
sub bh, [bp + si + 4]
sub di, [bp + di + 6]
sub [bx + si], bx
sub [bp], bx
sub [bp], bx
sub [bx + 2], cx
sub [bp + si + 4], bh
sub [bp + di + 6], di
sub [bx], byte 34
sub [bx + di], word 29
sub ax, [bp]
sub al, [bx + si]
sub ax, bx
sub al, ah
sub ax, 1000
sub al, 226
sub al, 9
cmp bx, [bx + si]
cmp bx, [bp]
cmp si, word 2
cmp bp, word 2
cmp cx, word 8
cmp bx, [bp]
cmp cx, [bx + 2]
cmp bh, [bp + si + 4]
cmp di, [bp + di + 6]
cmp [bx + si], bx
cmp [bp], bx
cmp [bp], bx
cmp [bx + 2], cx
cmp [bp + si + 4], bh
cmp [bp + di + 6], di
cmp [bx], byte 34
cmp [4834], word 29
cmp ax, [bp]
cmp al, [bx + si]
cmp ax, bx
cmp al, ah
cmp ax, 1000
cmp al, 226
cmp al, 9
jne 2
jne -4
jne -6
jne -4
je -2
jl -4
jle -6
jb -8
jbe -10
jp -12
jo -14
js -16
jne -18
jnl -20
jg -22
jnb -24
ja -26
jnp -28
jno -30
jns -32
loop -34
loopz -36
loopnz -38
jcxs -40
```
