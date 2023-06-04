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
0000   03 18               add bx, [bx + si]
0002   03 5E 00            add bx, [bp]
0005   83 C6 02            add si, word 2
0008   83 C5 02            add bp, word 2
000B   83 C1 08            add cx, word 8
000E   03 5E 00            add bx, [bp]
0011   03 4F 02            add cx, [bx + 2]
0014   02 7A 04            add bh, [bp + si + 4]
0017   03 7B 06            add di, [bp + di + 6]
001A   01 18               add [bx + si], bx
001C   01 5E 00            add [bp], bx
001F   01 5E 00            add [bp], bx
0022   01 4F 02            add [bx + 2], cx
0025   00 7A 04            add [bp + si + 4], bh
0028   01 7B 06            add [bp + di + 6], di
002B   80 07 22            add [bx], byte 34
002E   83 82 E8 03 1D      add [bp + si + 1000], word 29
0033   03 46 00            add ax, [bp]
0036   02 00               add al, [bx + si]
0038   01 D8               add ax, bx
003A   00 E0               add al, ah
003C   05 E8 03            add ax, 1000
003F   04 E2               add al, 226
0041   04 09               add al, 9
0043   2B 18               sub bx, [bx + si]
0045   2B 5E 00            sub bx, [bp]
0048   83 EE 02            sub si, word 2
004B   83 ED 02            sub bp, word 2
004E   83 E9 08            sub cx, word 8
0051   2B 5E 00            sub bx, [bp]
0054   2B 4F 02            sub cx, [bx + 2]
0057   2A 7A 04            sub bh, [bp + si + 4]
005A   2B 7B 06            sub di, [bp + di + 6]
005D   29 18               sub [bx + si], bx
005F   29 5E 00            sub [bp], bx
0062   29 5E 00            sub [bp], bx
0065   29 4F 02            sub [bx + 2], cx
0068   28 7A 04            sub [bp + si + 4], bh
006B   29 7B 06            sub [bp + di + 6], di
006E   80 2F 22            sub [bx], byte 34
0071   83 29 1D            sub [bx + di], word 29
0074   2B 46 00            sub ax, [bp]
0077   2A 00               sub al, [bx + si]
0079   29 D8               sub ax, bx
007B   28 E0               sub al, ah
007D   2D E8 03            sub ax, 1000
0080   2C E2               sub al, 226
0082   2C 09               sub al, 9
0084   3B 18               cmp bx, [bx + si]
0086   3B 5E 00            cmp bx, [bp]
0089   83 FE 02            cmp si, word 2
008C   83 FD 02            cmp bp, word 2
008F   83 F9 08            cmp cx, word 8
0092   3B 5E 00            cmp bx, [bp]
0095   3B 4F 02            cmp cx, [bx + 2]
0098   3A 7A 04            cmp bh, [bp + si + 4]
009B   3B 7B 06            cmp di, [bp + di + 6]
009E   39 18               cmp [bx + si], bx
00A0   39 5E 00            cmp [bp], bx
00A3   39 5E 00            cmp [bp], bx
00A6   39 4F 02            cmp [bx + 2], cx
00A9   38 7A 04            cmp [bp + si + 4], bh
00AC   39 7B 06            cmp [bp + di + 6], di
00AF   80 3F 22            cmp [bx], byte 34
00B2   83 3E E2 12 1D      cmp [4834], word 29
00B7   3B 46 00            cmp ax, [bp]
00BA   3A 00               cmp al, [bx + si]
00BC   39 D8               cmp ax, bx
00BE   38 E0               cmp al, ah
00C0   3D E8 03            cmp ax, 1000
00C3   3C E2               cmp al, 226
00C5   3C 09               cmp al, 9
00C7   75 02               jne 2
00C9   75 FC               jne -4
00CB   75 FA               jne -6
00CD   75 FC               jne -4
00CF   74 FE               je -2
00D1   7C FC               jl -4
00D3   7E FA               jle -6
00D5   72 F8               jb -8
00D7   76 F6               jbe -10
00D9   7A F4               jp -12
00DB   70 F2               jo -14
00DD   78 F0               js -16
00DF   75 EE               jne -18
00E1   7D EC               jnl -20
00E3   7F EA               jg -22
00E5   73 E8               jnb -24
00E7   77 E6               ja -26
00E9   7B E4               jnp -28
00EB   71 E2               jno -30
00ED   79 E0               jns -32
00EF   E2 DE               loop -34
00F1   E1 DC               loopz -36
00F3   E0 DA               loopnz -38
00F5   E3 D8               jcxs -40
```
