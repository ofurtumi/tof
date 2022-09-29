# tímadæmi 27. sept

## 1. 
gerið ráð fyrir því að gistið `%rax` innihaldi gildið `0x0123456789ABCDEF` og gistið `%rbx` innihaldi gildið `0x8765`. hér fyrir neðan eru nokkrar skipanir, sumar þeirra eru ólöglegar, en aðrar eru löglegar. fyrir ólöglegu skipanirnar gefið upp *lokagildi* á `%rax` eftir framkvæmd skipunarinnar. allar skipanirnar eru sjálfstæðar

1. `movb    $10, %ax`
2. `movswl  %ebx, %rax`
3. `movsbq  %bh, %rax`

### 1.1
hérna er fært þannig útkoman verður `0x0123456789ABCD0A`

### 1.2
í þessari skipun er villa, hérna erum við að taka næst-stærsta bætið og útvíkka það í `%rax`

### 1.3
???

## 2.
hér fyrir neðan er smalamálsútgáfa af fallinu 
```c
long comp(long a, long b) {...}
```
sem reiknar einfalda segð (expression) út frá viðföngum a og b. athugið að viðfangið a kemur í gistið `%rdi`, b kemur í `%rsi` og skilagildi fallsins fer í gistið `%rax`

```asm
comp:
    leaq    (%rsi, %rsi, 2), %rax
    addq    %rax, %rdi
    leaq    (%rdi, %rdi, 4), %rdx
    leaq    (%rdx, rdx), %rax
    ret
```

okok fyrsta lína er maður að margfalda `%rsi` með `2` og leggja svo einu sinni við þannig maður er með `3*%rsi` og setja það í `%rax`  
önnur lína er að leggja saman `(%rdi + %rax)` og setja gildið í `%rdi`  
þriðja lína aftur `leaq`, `%rdx = 5*%rdi`  
fjórða, `leaq` en núna án margfeldis, `%rdi = %rax + %rax$`  
fimmta og síðast skilar svo gildinu :)