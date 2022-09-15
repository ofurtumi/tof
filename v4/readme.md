# heimadæmi 4 - tölvutækni og forritun

## 1.
```c
int x = 3, y;                   // x: 3
x+= y = 5;                      // x: 5
x == (y = 3);                   // x: 5
x = y == 2;                     // x: 0
x = y == 2 ? y << 1 : y >> 1;   // x: 1  
```

## 2. 
```c
short sx = -2;      //    101
int x = -14;        // 110001
unsigned ux = sx;   // 111110
```

| Reiknisegð | Tugatala | Tvíundartala |
|:--:|:--:|:--:|
|ux|62|111110|
|x - (sx << 1)|-10|110110|
|x >> 3|-2|111110|
|(x+ux) < 0|0|000000|
|ux + sx|60|111110|

## 3.
```c
int a = k & ~(k >> 31);
```

það fer eftir því hvort heiltölubreytan `k` er jákvæð eða neikvæð hvaða gildi a tekur, bitatrixið sem verið er að beita er í nokkrum skrefum:  
- athugum fyrst `(k >> 31)` hér er verið að yfirskrifa fyrstu 31 bitana í k með `0` ef talan er jákvæð og `1` ef talan er neikvæð  
- fyrir utan svigann er svo flipper sem flippar öllum bitununm þannig `0` verður `-1` og öfugt  
- nú er komið að `&` aðgerðinni, skil ekki alveg praktísku notin fyrir hana en, sem ber saman hvern og einn bita og skilar `0` eða `1` eftir hvort báðir eru `1` eða ekki 

það gerir það að verkum að ef útkoman úr `~(k >> 31)` er `-1` þá verður `a` upprunalega `k` en ef fyrri segðin skilar `0` þá verður `a` líka `0`  

í stuttu máli skilgreinir þetta bitatrix `a` sem `0` ef `k < 0` en ef `k >= 0` þá verður `a = k`

<div style='page-break-after: always;'></div>

## 4.
### a)
#### i.

tugaform:  
$-16 + 12 = -4$

tvíundarform:  
```
  110000
+ 001100
= 111100 = 4
```
rétt útkoma í báðum tilfellum

#### ii.

tugaform:  
$-21 + -14 = -35$

tvíundarform:
```
  101001
+ 110010
= 011011 = 27
```
rétt útkoma í tugaformi, hinsvegar of stór (lítil) fyrir 6 bita tvíandhverfutölu, og yfirflæði í tvíundarformi

#### iii.

tugaform:  
$17 + 15 = 32$

tvíundarform:
```
  010001
+ 001111
= 100000 = -32
```

### b)
#### i.
```
11100011 >> 3 =
11111100 = -4
```

<div style='page-break-after: always;'></div>

#### ii.
$-29 + 2³ = -29 + 8 = -21$  
samlagning sýnd fyrst
```
  11100011
+ 00001000
= 11101011
```
svo hliðrun
```
11101011 >> 3 =
11111101 = -3
```
nú er rúnað í rétta átt :)

<!-- <div style='page-break-after: always;'></div> -->

## 5.
### a)
```
  001011 | 11  
= 011101 | 18
+ 011101 | 29
```
samlagningin virkar eins og maður býst við, enda ekkert spes við hana

### b)
```
  100101 | -5
+ 101000 | -8
= 001101 | 13
```
samlagningin yfirflæðir á mínusbitanum, ef maður sleppti honum væri útkoman rétt, en það gerir að verkum að útkoman verður eins og margfölduð með `-1`

### c)
```
  000101 |  5
+ 101001 | -9
= 101110 |-14
```
hérna er samlagningin ekki rétt en ekki vegna yfirflæðis heldur vegna þess að maður gerir ekki ráð fyrir því að munur sé á tölunum, þetta er eins og að draga `5` frá `-9` í stað þess að leggja `5` við og fá þá út -4

<div style='page-break-after: always;'></div>

### d)
```
  000101 |  5
+ 110111 | -9
= 111100 | -4
```
nú gengur samlagningin upp, vegna þess hvernig tvíandhverfukerfið er byggt upp passar það að taka tillit til formerkis tölunar sem verið er að vinna með og niðurstaðan verður rétt