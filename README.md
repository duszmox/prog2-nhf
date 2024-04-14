```

██╗    ██╗ ██████╗ ██████╗ ██████╗ ██╗     ███████╗
██║    ██║██╔═══██╗██╔══██╗██╔══██╗██║     ██╔════╝
██║ █╗ ██║██║   ██║██████╔╝██║  ██║██║     █████╗
██║███╗██║██║   ██║██╔══██╗██║  ██║██║     ██╔══╝
╚███╔███╔╝╚██████╔╝██║  ██║██████╔╝███████╗███████╗
 ╚══╝╚══╝  ╚═════╝ ╚═╝  ╚═╝╚═════╝ ╚══════╝╚══════╝


```

---

## A Program Célja 🏁

A program a a 2021-ben felkapottá vált és később a NYT által felvásárolt ugyanezen néven futó játékot fogja imitálni pár apróbb változtatással.

### Az eredeti

Azoknak akik nem ismerik az eredetit, itt egy rövid összefoglaló. A játék lényege, hogy van egy öt betűs szó, amire van a felhasználónak hat próbálkozása kitalálni. Minden nap van egy adott szó, amit mindenkinek ki kell találnia. Hatszor lehet tippelni, és minden alkalommal, ha talál a játékos egy olyan betűt, ami benne van a szóban, azt vizuálisan jelzi a felhasználónak. Ha egy részleges találata van, azaz a betű megtalálható a szóban, de rossz helyen, akkor sárga hátteret kap a betű, ha pedig teljes találata van, akkor zöld színű kiemelést. Ha eltalálta a szót a játékos, akkor minden betű zöld, és egy prompt jelzi neki, hogy győzött. Ezen kívül a böngészős játék sütikben tárolja a felhasználó statisztikáit, azt, hogy milyen gyorsan, hány tipp alatt találta ki minden nap a szavakat.

### A saját megvalósításom

Az én megvalósításomban nem lesz korlátozva napi egy szóra a játék. Két file lesz, egy az elfogadható szavakat tartalmazó file (possible), ami rengeteg angol szót tartalmaz, elég kacifántosakat is, és egy megoldások file (answerlist), amik sokkal ismertebb angol szavak, ezzel könnyítve a játékot. A megoldás file-ból beolvasott szavak közül véletlen szerűen fog a program választani egyet, minden új kör indításakor. Ezen kívül a statisztikákat egy másik file-ban fogja tárolni, és egy menüpontból elő lehet majd hozni. Ezen felül minden tipp után, a játék ki fogja írni hány lehetséges szó van még a megoldások file-ban, ami megfelel azoknak a részleges és teljes találatok kombinációjának, amiket eddig eltalált a játékos. A játékban kitalálható szavak csak az angol ábécé betűit tartalmazhatják. Kis és nagy betűk egyaránt lehetnek a szavakban, ez a programot nem fogja zavarni.

## A Program Használata ▶️

A játék terminál alapú lesz, és a különböző menüpontok között a billentyűzeten található számokkal tud majd a felhasználó navigálni. Az `Enter` billentyű lenyomása nem szükséges a menüpontba lépéshez.

### Menüpontok

Minden menü tetején lesz megtalálható az az ASCII art, ami ennek a dokumentum tetején is van. Ezen felül a `0` billentyű lenyomása mindig a visszalépést vagy a programból való kilépést fogja eredményezni. Egy szám a sor elején csak akkor jelent kattinthatóságot, ha az gömbölyded zárójelekkel van körülvéve.

#### Főmenü

```
(1) Új Játék
(2) Statisztikák
(0) Kilépés
```

#### Statisztikák

```
Találatok száma (%)
1 ▒░░░░░░░░░░░░ 2%
2 ██▒░░░░░░░░░░ 20%
3 ███████▓░░░░░ 60%
4 █▓░░░░░░░░░░░ 15%
5 ░░░░░░░░░░░░░ 0%
6 ▒░░░░░░░░░░░░ 3%
X ░░░░░░░░░░░░░ 0%

(0) Vissza
```

Ez a statisztika oldal azt mutatja, hogy a játékos összes játékából arányosan hány tippre volt szüksége, hogy kitalálja a szót. Az X az elvesztett köröket szimbolizálja

#### A játék 🎮

```
Lehetséges szavak száma: 417

[C] [R] [A] [V] [E]
[B] [R] [A] [I] [L]
[S] [A] [I] [N] [T]
[|] [ ] [ ] [ ] [ ]
[ ] [ ] [ ] [ ] [ ]
[ ] [ ] [ ] [ ] [ ]

(0) Játék megszakítása
```

A program ebbe a menüpontba lépéskor kiválszt egy véletlenszerű szót a megoldások file-ból, amit majd ki kell találnia a játékosnak. A felhasználó a rublikákba tudja a tippjeit beleírni. Csak az angol ábécé karaktereit tudja leütni a billentyűzetén, és ha mind az öt betűt beírta, akkor az `Enter` lenyomásával tudja beküldeni a tippjét. Ha a possible file-ban ilyen szó nem szerepel, akkor A megszakítás gomb és a játéktábla közötti helyen egy hibaüzenetet fog kíírni a program a következő billentyű lenyomásig, ami közli a felhasználóval, hogy nincs ilyen szó. Ha ellenben létezik ilyen szó, akkor a következő sorra átteszi a kurzort szimbolizáló `|` karaktert és az előző tippjeinek részleges és teljes találatainak hátterét beszinezi. Minden tipp után a felsősorban található lehetséges szavak száma frissül az új mennyiséggel. Ha a felhasználó eltalálja a szót, akkor minden betű háttérszíne zöld lesz és a játék megszakítása helyett egy `(1) Újra` és egy `(0) vissza` gomb fog megjelenni. Ha a játékos hat tippből nem találta el a szót, akkor ugyanezek a gombok fognak megjelenni.

## File formátumok 📄

### possible.csv

```
aahed
aalii
.
.
.
zygal
zygon
zymes
zymic
```

A lehetséges szavak listája. A ... csak egy rövidítés, ott mind szavak szerepelnek. Minden szó `\n` karakterrel van elválasztva a többitől. Nem feltétlen csak öt betű hosszúak lehetnek a szavak. Mindig a szavak hosszát az első szó hossza fogja meghatározni, ha később talál a program egy rövidebb/hosszabb számot, akkor hibával fog visszatérni. Ezt a file-t a felhasználónak kell létrehoznia.

### answerlist.csv

```
awake
blush
focal
.
.
.
artsy
rural
shave
```

Nagyon hasonló az előző file-hoz, csak ez a lehetséges megoldásokat tartalmazza. Ezt a file-t a felhasználónak kell létrehoznia.

### stats.csv

```
3 rural
4 blush
X tower
6 pizza
.
.
.
```

Ez a statisztikákat tartalmazó file. Az első szám a tippelések számát jelzi, a második a megoldás szavát. Ha a játékos nem találta el a szót, akkor az X karakter fogja kezdeni a sort. Minden bejegyzés `\n` karakterrel van elválasztva a többitől. Ezt a file-t a program fogja generálni.
