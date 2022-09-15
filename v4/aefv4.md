# æfingardæmi, vika 4

skilar (n\*2³) + (n\*2²) + n
```c
int fun1(int n) {
    return (n<<3) + (n<<2) + n;
}
```

notast við reiknihliðrun, í stað þess að setja 0 setur formerkisbita  
setur formerkjabitann inn fyrir öll (31 í int) sæti tölunnar  
n verður þá annaðhvort 0 (00...0) eða -1 (11...1)
& notar bitwise and þ.e. breytir öllum 0 í 0 og skilur alla 1 eftir sem 1

```c
int fun2(int n) {
    return (n>>31) & 0xF;
}
```

```c
int fun3(int n) {
    return (n<<16) | ((n>>16) & 0xFFFF);
}