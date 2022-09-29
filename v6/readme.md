# heimadæmi 6 - tölvutækni og forritun

## 1
með þriggja bita tölu eru aðeins `2^3`, mögulegar útkomur þannig auðvelt er að setja fram með töflu

|binary|decimal||binary|decimal|
|:---:|:---:|:---:|:---:|:---:|
|000    |0      ||100    |-0     |
|001    |1      ||101    |-1     |
|010    |inf    ||110    |-inf   |
|011    |NaN    ||111    |-NaN   |

fyrir 3-bita fleytitölu þar sem veldisstrengurinn er 1-bita langur er bias reiknaður sem $2^{1-1}-1=0$  
þar sem veldisbitinn þarf að vera `0` til þess að hægt sé að fá raunverulegt gildi út úr tölunni, ekki `NaN` eða `inf` er hægt að setja fram formúlu á forminu $-1^f*(i*2^0)$ þar sem $f$ er gildið á formerkisbitanum og $i$ er gildið á brotabitanum

## 2.
> *diane's silk dress cost $89*

`%rbx = 0x800` og `%rdx = 0xA`
* `(%rbx, %rdx)` 
  * `(2048 + 10) = 2058`
  * `0x80A`
* `$0x24 (%rbx, rdx, 2)` 
  * `0x24 + (0x800 + 2 * 0xA)`
  * `36 + (2048 + 20)`
  * `36 + 2068`
  * `2104`
  * `0x838`
* `$20(,%rbx,8)`
  * `20 + (2048 * 8)`
  * `0x14 + 0x4000`
  * `0x4014`
* `$-16(%rdx,%rdx,4)`
  * `-16 + (0x800 * 5)`
  * `-16 + (2048 * 5)`
  * `-16 + 10240`
  * `10224`
  * `10224`
  * `0x27F0`

<div style='page-break-after: always;'></div>

## 3.
### 3.1
> `movl src, dest` -  flytur 4 bæta `src` yfir í `dest`  

**skipunin er lögleg**  
`movl   %edx, (, %rbx, 4)` flytur gildið úr gistinu `%edx` yfir í gist sem er fjórum bætum fyrir ofan *(neðan?)* `%rbx` í hlaðanum, sjá innri reikningin `(, %rbx, 4)`, útkoman er fjórum sinnum gildið í `%rbx`

### 3.2
> `movzbq src, dest` - núllvíkkar bæti src yfir í 8 bæta dest  
> látum `%rax` vera `0x123456789ABCDEF`  
> `movzbq $0xAA, %rax` myndi skila `%rax = 0x0000000000000AA`

**skipunin er lögleg**  
`movzbq $-2, %r8` flytur þá 1-bæta two's complement töluna `-2`, binary: `1110`, ég veit ekki hvernig compilerinn tekur við en ef við túlkum `1110` sem hrátt binary og gerum ekki ráð fyrir two's complement þá myndi það tákna hex töluna `0x0E`  
þannig `movzbq $-2, %r8` myndi skila `%r8 = 0x000000000000000E`

### 3.3
> `movswq src, dest` - flytur 2-bæta gildi með formerkisvíkkun yfir í 8 bæta dest

**skipunin er lögleg**  
`movswq %ax, %rax` flytur 2-bæta gildið sem er í `%ax` yfir í `%rax`, seinni 2 bætin í `%rax` verða svo sett sem `0xFFFFFFFF`

### 3.4
> `movslw src, dest` - flytur eitt tvíorð með formerkisvíkkun yfir í eitt orð

**skipunin er ekki lögleg**  
miðað við skilgreininguna fyrir ofan gengur ekki upp að flytja gildi sem tekur upp stærra minnissvæði, tvíorð, yfir í gisti með minna minni, orð

<div style='page-break-after: always;'></div>

## 4.
c fallið
```c
long aogb(long a, long b) {}
```
reiknar einfalda segð útfrá a og b
`%rdi = a` og `%rsi = b`

> `leaq src, dest` - setur dest sem vistfangssegðina src  
> `leaq ($2, $3, 5), %rax` skilar `%rax = 2+3*5`

### a)
```assembly
aogb:
    leaq (%rsi,%rsi,4), %rax    # setja %rax sem 5*b
    leaq (%rdi,%rax,8), %rdx    # setja %rdx sem a+8*(5*b)
    leaq 0(,%rdx,8), %rax       # setja %rax sem %rdx*8+0
    subq %rdx, %rax             # setja %rax sem %rax-rdx
    ret
```

### b)
```c
long aogb (long a, long b) {
    long rax = b * 5;
    long rdx = a + 8 * rax;
    rax = rdx * 8;
    return rax - rdx;
}
```

## 5.
fallið í assembly:  
```asm
reikn:
  lea    0x0(,%rdi,8),%eax      # setjum %eax sem %rdi*8
  sub    %edi,%eax              # setjum %eax sem %eax-%edi
  lea    0xc(%rdi,%rdi,1),%edx  # setjum %edx sem (%rdi*2)+0xc
  sub    %edx,%eax              # setjum %eax sem %eax-%edx
  ret    
```

fallið í c:  
```c
int test(int edi)
{
    int eax = edi * 8;      // skilgreinir eax sem edi * 8
    eax -= edi;             // setur eax sem eax - edi
    int edx = 12 + edi * 2; // skilgreinir edx sem 12 + edi * 2
    return eax - edx;       // skilar eax - edx
}
```