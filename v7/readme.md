# heimadæmi 7 - tölvutækni og forritun

## 1.
assembly:  
```asm
hoho:
    leaq    31(%rdi), %rax  # %rax sett sem %rdi+31
    testq   %rdi, %rdi      # setur stýrikóða út frá gildi á %rdi & %rdi
    cmovns  %rdi, %rax      # færir %rdi yfir í %rax ef testq skilaði SF=0
    sarq    $5, %rax        # bitshiftar 5 til hægri um %rax bita
    ret
```

**c:**
> prófaði að þýða þennann kóða yfir í assembly á [godbolt](https://godbolt.org) og með gcc og object dumpa og lesa hann og ég er á þeirri skoðunn að hvorugur þessara þýðenda viti neitt hvað þeir syngja  
> þessi kóði er gerður alveg útfrá línu fyrir línu skoðun, eyddi bara of löngum tíma í hann til að skila ekki inn :)
```c
long hoho(long x) {
    long y = x + 31;
    if(x > 0) y = x;
    y >>= 5;
    return y;
}
```


**c:**   
> eftir smá betri skoðun á því hvað kóðinn gerir set ég hérna oneliner sem gerir það sama **og** þýðist rétt
```c
long hoho(long x) {
    return x/32;
}
```

<div style="page-break-after:always;"></div>

## 2.

**assembly:**
```asm
whi:
    movl    $0, %eax        # núllstilla eax
    jmp     .L2             # hoppa yfir í .L2, goto
.L3:
    leaq    -1(%rdi), %rdx  # draga einn frá %rdi og setja gildið í %rdx
    andq    %rdx, %rdi      # og-að saman %rdx og %rdi og sett inn í %rdi
    xorq    $1, %rax        # 1 xor-að við %rax og sett í %rax
.l2:
    testq   %rdi, %rdi      # athugar hvort %rdi <= 0 og setur viðeigandi flögg
    jne     .L3             # stekkur ef %rdi er ekki núll
```

**c:**  
```c
long whi(long k)
{
    long i = 0;
    while (k != 0) {
        long x = k - 1;
        k = x & k;
        i = 1 ^ i;
    }
    return i;
}
```



## 3.
### a)
**assembly:**  
```asm
func:
    cmpl    $1, %edi            # setur flöggin á %edi
    jle     .L3                 # ef %edi er tómt, hoppa yfir í .L3
    pushq   %rbx                # tekur frá svæði á hlaða sem %rbx
    leal    (%rdi,%rdi,2), %ebx # margfaldar %rdi með 3 og setur í %ebx
    leal    $3(%rdi), %edx      # leggur 3 við %rdi og setur í %edx
    testl   %edi, %edi          # athugar hvort %edi =< 0 og setur viðeigandi flögg
    cmovns  %edi, %edx          # færir %edi inn í %edx ef %edi >= 0
    sarl    $2, %edx            # notar heiltöludeilingu %edx = %edx / 4 
    movl    %edx, %edi          # færir %edx í %edi
    call    func                # recursion call á func
    addl    %ebx, %eax          # lagt saman %ebx og %eax
    popq    %rbx                # %rbx poppað úr hlaðanum
    ret                         # %eax skilað  
.L3:
    movl    $1, %eax            # seta 1 sem %eax (skilagildi)
    ret                         # skila %eax
```

<div style="page-break-after:always"></div>

**c:**  
```c
int func(int n)
{
    if (n <= 1)
        return 1;
    return (n * 3) + func(n / 4);
}
```
**c kóðinn línu fyrir línu tengdur í assembly**
> `if (n <= 1)`, setur flöggin fyrir n og hoppar ef less or equal
```asm
cmpl     $1, %edi
jle      .L3
```

> `return 1`, skilar ás ef n uppfyllir skilirði í efri línunni
```asm
movl    $1, %eax
ret
```  

> `return (n * 3) + func(n / 4)`, brjótum meira niður  
> `(n * 3)`, margfaldar n með 3, notar leal
```asm
leal    (%rdi, %rdi, 2), %ebx
```  

> `func(n / 4)`, köllum func með gildinu n/4,
```asm
sarl    $2, %edx
movl    %edx, %edi
call    func
```

> `(n * 3) + func(n / 4)`
```asm
addl    %ebx, %eax
```

<div style="page-break-after:always;"></div>

### b)
![mynd af stackframe](stackframe.png)

<div style="page-break-after:always;"></div>

## 4.
> ath: í báðum þessum dumpum er ég búinn að fjarlægja línur sem eru ekki nauðsynlegar fyrir verkefnið, td. `.cfi_startproc` og `endbr64`

### a)
**assembly dump:**  
```asm
fact:
.LFB0:
	cmpq	$1, %rdi
	jg		.L8
	movl	$1, %eax
	ret
.L8:
	pushq	%rbx
	movq	%rdi, %rbx
	leaq	-1(%rdi), %rdi
	call	fact
	imulq	%rbx, %rax
	popq	%rbx
	ret
```
ástæðuna fyrir því að það þarf að nota `pushq` og `popq` í þessum endurkvæmnu dæmum er hægt að sjá í línu 4 inn í `.L8` þar sem verið er að færa `%rdi` inn í `%rbx%` til að gildið týnist ekki á meðan verið er að vinna sig áfram með endurkvæmnina  
sjá svo línu 7 þar gildið sem geymt var á hlaðanum sem `%rbx` er margfaldað með útkomunni úr síðasta fallakalli og síðan poppað því við þurfum ekki að passa upp á það lengur því svo er því skilað

### b)
**assembly dump með -O2:**
```asm
.LFB0:
        movl    $1, %eax
        cmpq    $1, %rdi
        jle     .L1
.L2:
        movq    %rdi, %rdx
        subq    $1, %rdi
        imulq   %rdx, %rax
        cmpq    $1, %rdi
        jne     .L2
.L1:
        ret
```
fyrsta sem ég sé hér er að `-O2` sleppir því að hafa tvö return og notar bara eitt inn í `.L1` sem case enda í  
annað sem er greinilegur munur er að `-O2` notar ekki `call` heldur fer með endurkvæmnina eins og það sé lykkja þar sem síðasta línan athugar hvort `%rdi` sé orðið minna eða jafnt og einn, ef svo detta inn í `.L1` og returna

<div style="page-break-after:always"></div>

## 5.

hér er c kóði sem gerir það sama og gefni assembly kóðinn:  
```c
int func(int n) {
    int out;
    switch (n)
    {
    // .L6
    case 0:
    case 2:
        out = 2*n+3;
        break;
    // .L5
    case 3:
    case 4:
        out = n+3;
        break;
    // .L3
    case 5:
        int temp = n*8;
        out = 3 - temp;
        break;
    // .L7
    default:
        out = n;
        break;
    }
    return out;
}
```

það eru nokkur tilfelli sem þarf að tala um í switchinu  
1. fyrsta sem þarf að taka eftir er að það eru í raun bara fjögur case fyrir 7 mismunandi tilfelli
   1. ef n er 0 eða 2
   2. ef n er 1
   3. ef n er 3 eða 4
   4. ef n er 5 eða stærra (líka ef n er minna en 0)  
   
2. assembly notar ekki general default fyrir switch þannig þarf að taka sérstaklega fram hvað á að gera ef `%edi`, `n`, er stærra en 5
