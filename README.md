# (téma: Sandbox hra)
Autor: Vojtěch Krejsa

## Téma z Progtestu

Naprogramujte jednoduchou 2D sandbox hru.

Hra musí splňovat následující funkcionality

- Implementujte hráče (postava, loď, ...) a jeho stav (energie, životy, brnění, skore, ...)
- Vytvořte (soubojový) model zranění - alespoň dvě příčiny (pád z výšky, soubor s nepřítelem, pobyt v lávě, ...)
- Vytvořte jednoduchý model prostředí (gravitace, přelévání vody (lávy), růst stromů, ...)
- Naimplementujte načítání (konfigurace generátoru) mapy ze souboru a umožněte ukládat aktuální stav hry.

Kde lze využít polymorfismus? (doporučené)

- Postavy: hráč, zvířata, přítel (obchodník), nepřítel (různé druhy)
- Efekty akcí: pád, úder, kontakt s lávou
- Prostředí: vzduch, voda, hlína, uhlí, kov, láva, žebřík,...
- Uživatelské rozhraní: konzole, ncurses, SDL, OpenGL (různé varianty), ...

## Zadání hry

Cílem je vytvořit jednoduchou 2D sandbox hru, která bude hráčovi umožňovat volný pohyb po mapě,
jak už to v sandbox hrách bývá. Hráč bude u sebe mít dvě zbraně: meč a krumpáč. Každý
předmět bude účinnější v různých činnostech. Hráč totiž bude moci měnit mapu kolem sebe.
Pomocí předmětu, který bude mít aktuálně v ruce, bude moci níčit okolní bloky. Některé bloky
nepůjdou zníčit (vzduch, láva, blok ohraničující konec mapy...). Pokud bude bloky níčit
pomocí krumpáče, bude blokům udělovat větší poškození. Meč bude naopak efektivnější v boji
s monstry, která se budou na mapě vyskytovat. Tata monstra budou poměrně silná 
a hráč se s nimi utká tak, že se setkají na stejném bloku. Aby je hráč přemohl, bude muset
zpravidla nejprve získat nějakou vyšší úroveň. S vyšší úrovní se hráčovi zvyšuje poškození a 
brnění. Hráč mimo životů má také energii, která mu ubývá při souboji s monstry nebo při kopání bloků.
Životy i energie se mu automaticky doplňují. 

Mapa je reprezentována několika typy bloků. Bloky jsou: hlína, láva, kámen, blok ohraničující
konec mapy a vzduch. Hráč mimo jiné disponuje i možností bloky stavět. Stavět ale může pouze
blok hlíny a to za předpokladu, že vyskočí do vzduchu a postaví jej pod sebe. Toto ale není
jediné omezení. Blok musí být postaven na "pevnou" zem, hráč tedy nemůže pokládat bloky do vzduchu.
Hráč může i skákat, ale skákat může pouze za předpokladu, že stojí na pevném podkladu (nemůže skákat ve vzduchu).

Hra běží ve dvou základních režimech: menu a herní mód.

#### Příkazy pro menu

- `new [filename]` načte novou hru, dá uživateli na výběr načtení jedné ze 4 připravených map
- `load [filename]` načte hru ze souboru (hráč si musel mapu dříve uložit)
- `save [filename]` uloží hru do souboru
- `play` přepne z menu do herního režimu (požadavek - musí být načtena nějaká mapa)
- `?` zobrazí nápovědu
- `exit` ukončí hru

#### Příkazy pro herní mód
- `?` - vypíše nápovědu pro každý příkaz
- `a` - pohne s hráčem doprava (jestliže to mapa dovoluje (nelze procházet zdmi))
- `w` - hráč vyskočí (musí stát na pevném podkladu)
- `d` - pohne s hráčem doleva (jestliže to mapa dovoluje (nelze procházet zdmi))
- `s` - vymění hráčovi zbraně
- `h` - hráč udeří předmětem blok po jeho levici 
- `j` - hráč udeří blok předmětem pod ním
- `k` - hráč udeří předmětem blok po jeho pravici
- `u` - hráč udeří předmětem blok nad ním
- `b` - hráč postaví blok pod sebe 
- `p` - pauzne se hra - přechod do hlavního menu
