# heimadæmi 10 - tölvutækni og forritun

## 1.
### a)
`AnyBit1` sem oneliner:  
```c 
int AnyBit1 (int x) {return x != 0;} 
```

### b)
`AnyBit0` sem oneliner:
```c
int AnyBit0 (int x) {return ~x != 0;}
```

### c)
`ThirdBit1` sem oneliner:  
```c
int ThirdBit1 (int x) {return (x >> 2) % 2 == 1;}
```

## 2.
### a)
hliðrunin er reiknuð með formúlunni $2^{(k-1)} -1 = 15$, hægt að sjá meiri rökstuðning í [þessari reiknivél](https://www.sjomli.is/fpc/?10?5)

### b)
formúla fyrir staðlaðar fleytitölur af þessari tegund væri eftirfarandi $(-1)^S+2^E+R$  
þar sem `S` er veldisbitinn, `E` er gildi veldisbita - hliðrun og `R` er restin af tölunni sem stækkar með stærð brotahlutans ,sem dæmi, á stöðluðu 5 bita, 2 veldisbita fleytitölunni `01011` væri restin $...+1*2^{-1}+1*2^{-2}$


### c)
byrjum á að finna veldið, það væri $18-15 = 3$, þá er auðvelt að finna gildið á tölunni með formúlunni: $(-1)^0+2^{3}+2^{2}=12$ 

### d)
bitastrengur stærstu fleytitölu á þessu formi væri `0111101111`, við setjum alla bita tölunar sem 1, breytum mínusbitanum í 0 til að fá plústölu og flippum síðasta bitanum sem tilheyrir veldishlutanum og við endum með þennan gullfallega 10 bita fleytistreng

<div style='page-break-after: always;'></div>

## 3. 
### a)
við sjáum að það er verið að nota einhverskonar fylkjavinnslu í línu 6, og þar er eina línan sem notar `%rdi`  
allt þar í kring sem snertir `%rdi` nota quadword og þar sem `8` er notað í fylkjareikningunum má gera ráð fyrir því að `%rdi` sé `long int[]`

### b)
```c
for (int i = 0; i <= rsi; i += 2) {}
```

### c)
þetta fall leggur saman allar oddatölunar úr fylki upp að indexi `%rsi`

## 4.
### a)
við erum með þrjár víðværar breytur:  
- `short int a = 22;` - tilheyrir `main.c`
- `short int b = 23;` - tilheyrir `main.c`
- `extern int b;` - tilheyrir `fall.c`
fyrstu tvær, þær sem eru í `main.c` eru sterkar þar sem þær eru frumstylltar  
hinsvegar er `extern int b` í `fall.c` veik víðvær breyta þar sem hún er extern

### b)
fyrri `printf` skipunin er að prenta gildi á `a` og `b` sem heiltölur, að nota `%d` inn í streng í `printf` jafngildir að hafa heiltölugildi inn í strengnum

### c)
hex gildið sem er prentað út er minnisaddressan á fallið `main` í hlaðanum, skoðum viðeigandi línu úr objdump af main fallinu:  
```asm
...
0000000000001149 <main>:
    1149:	f3 0f 1e fa     endbr64
...
```
hér er hex gildið táknað í lágendaröð, `f3 0f 1e fa` er lesið sem `fa 1e 0f f3` sem er gildið sem var prentað út úr fallinu

<div style='page-break-after: always;'></div>

## 5.
### a) og b)
> töflu time

| skrá | breyta | víðvær / staðvær / tilvísun | sterk / veik | staðsetning |
| ---- | ------ | --------------------------- | ------------ | ----------- |
| main | a      | víðvær                      | sterk        | .data       |
| main | b      | víðvær                      | sterk        | .data       |
| main | c      | víðvær                      | veik         | .bss        |
| main | d      | víðvær                      | veik         | .bss        |
| main | c      | staðvær                     | sterk        | hlaði       |
| fall | a      | víðvær                      | veik         | .bss        |
| fall | b      | víðvær                      | veik         | .bss        |
| fall | c      | víðvær                      | sterk        | .data       |
| fall | d      | víðvær                      | sterk        | .data       |
| fall | d      | staðvær                     | veik         | hlaði       |
| fall | a      | tilvísun                    | sterk        | hlaði       |
| fall | b      | tilvísun                    | sterk        | hlaði       |
| fall | c      | tilvísun                    | sterk        | hlaði       |
| fall | d      | tilvísun                    | sterk        | hlaði       |

### c)
okidoki, tökum gildin í þeirri röð sem þau eru prentuð út, byrjum á `a`

`a` er skilgreint sem sterkt víðvært static int þannig það verður ekki yfirskrifað með kalli á fall, gildið sem verður prentað út er þá `1`

`b` er skilgreint sem sterkt víðvært int, ath að hér er ekki notað static þannig og `b` er flutt yfir í `fall` skránna með `extern` þannig `b` getur verið, og er, yfirskrifað í kallinu á `fall`, útkoman verður þá `7`  

`c` er skilgreint inn í main fallinu og þessvegna staðvært í því tilfelli, c er því ekki yfirskrifað af kalli á `fall` og útkoman í prenti verður `3`

`d` er skilgreint sem extern int í `main` þannig þá getum við athugað hvernig það er skilgreint inn í `fall` sem `int d = 5;` og þar sem að tilvísunin innan `void fall() {}` er tilvísun í staðværrar breytu breytu inn í `fall()` þá yfirskrifar `fall()` ekki `d` og prentgildið verður `5`