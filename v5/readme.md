# heimadæmi 5 - tölvutækni og forritun

## 1.
|0x100|0x101|0x102|0x103|0x104|0x105|0x106|0x107|
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|    
|`81`|`D7`|`70`|`AD`|`0D`|`E9`|`8B`|`76`|
|iii.|iii.|i.|i.|ii.|ii.|iv.|v.|

## 2.
### a)
unsigned:
$2^4 + 2^1 + 2 = 19$  

---

two's compliment:
$2^4 + 2^1 + 2 = 19$

---

floating point:  
okok, ekki mínus tala tala þannig þarf ekki að spá að í fyrsta bitann, við erum að vinna með `3` veldisbita þannig bias verður `-3` því `11` er `3`  
þá er hægt að sjá að gildið á veldisbitunum eru $4-3=1$  
tökum nú brotahlutann og margföldum með `2` í veldi gildis veldisbitana þannig $1.11*2^1=11.1$ í *"binary"* sem verður $2¹+2⁰+2^{-1}=2+1+0.5=3.5$  
svarið er **3.5**

### b)

unsigned:  
hérna viljum við bara að stærsti bitinn sem er `0` verði `1` þannig bitastrengurinn verður `110011` og gildið á honum `51`

---

signed:  
hérna er svipuð pæling nema við viljum halda tölunni jákvæðri þannig við breytum stærsta `0` bitanum sem er ekki formerkisbiti yfir í `1`  
bitastrengurinn verður `011011` og gildið `27`

---

floating point:  
til þess að hækka töluna sem mest þarf að hafa veldisbitastrenginn sem stærstann og halda henni jákvæðri, hæsta gildi sem veldisbitastrengurinn getur fengið með breytingu á einum bita er $4+2-3=2=3$  
margföldum það svo með brotinu og fáum $1*2^3+1*2^2+2=14$  
bitastrengurinn verður þá `011011` og gildið `14`

### c)

unsigned:
núna viljum við breyta stærsta `1` bitanum yfir í `0`, bitastrengurinn verður `000011` og gildið `3`

---

signed:
hérna er einfalt að setja formerkisbitann sem er `0` yfir í `1`, bitastrengurinn verður þá `110011` og gildið `-13`

---

floating point:  
sama og í signed, breytum formerkisbitanum yfir í `1` og fáum þá `110011` sem hefur gildið `-3.5`

## 3.
### a)
stærsta staðlaða talan sem er hægt að fá með 7-3 fleytitölu er 15, táknuð með `0110111`, reiknuð sem $2^3+2^2+2+1$  

---

stærsta staðlaða talan sem er hægt að fá með 7-4 fleytitölu er 224, táknuð með `0111011`, reiknuð sem $2^7+2^6+2^5$  

það sem þarf að passa mest með mismunandi stærðir á veldisbitastrengum er að reikna bíasinn aftur, er búinn að gera það alltof oft í þessu verkefni :/

### b)
ég skrifaði [reiknivél](https://sjomli.is/floating) fyrir n-bita fleytitölur þannig ég testaði mig svoldið áfram í að finna þessar tölur

byrjum á að athuga hvaða veldi af tveimur næst 12 án þess að fara yfir, það er fljótlega séð að það væri `8` eða `2^3` þannig veldisbitastrengurinn þarf að vera allaveg $3 + bias$ stór

---

í tilfelli 7-4 fleytitölunar væri það $3 + 7 = 12$ og táknað í binary `1010` og þá er bara spurning hverju þarf að bæta við `8` til þess að fá út `12`  
þetta sést líka fljótt að $8 + 4 = 12$ og $4 = 2^2$  
þannig til að fá `12` þarf að leggja saman $2^3+2^2$, vegna þess að við erum að vinna með falda bitann getum við látið brotið vera `10` því við munum reikna eins og það sé `110`, látum svo formerkisbitann `1` og út kemur `-12.0`  
í stuttu máli til að fá `-12.0` með 7-4 fleytitölu verður bitastrengurinn  `1101010`

---

í tilfelli 7-3 fleytitölunar er bíasinn `3` þannig við beitum sömu aðferð og með 7-4 fleytitöluna og fáum út að brotið þarf að vera $3 + 3 = 6$ eða `110`  
notum nú upplýsingarnar úr 7-4 og vitum að það þarf bara að hafa fyrsta bitann í brotbitastrengunum og látum hann vera `100`, gerum síðan formerkisbitann að `1` og endum með `1110100` sem er `-12.0`

## 4.

