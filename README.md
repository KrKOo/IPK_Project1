# IPK Projekt 1

## HTTP Server

Program poskytujúci informácie o systéme prostredíctvom protokolu HTTP. Projekt je implementovaný v jazyku C++ za pomoci knižnice `sys/socket.h`

## Spustenie servera

### Pomocou `make`

`make run PORT=<PORT>`

napr.

`make run PORT=12345`

### Bez `make`

`./hinfosvc <PORT>`

napr.

`./hinfosvc 12345`

## Dotazy

### `/hostname`

Vracia sieťové meno počítača vrátane domény tj. obsah súboru `/proc/sys/kernel/hostname`

### `/cpu-name`

Vracia informácie o procesore tj. `model name` zo súboru `/proc/cpuinfo`

### `/load`

Vracia informáciu o aktuálnej záťaži procesora. Záťaž je vypočítaná z hodnôt uvedených v súbore `/proc/stat`.

Výpočet: https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux

## Odpovede

V prípade že je dotaz korektný, server pošle odpoveď s návratovou hodnotou `200 OK` v nasledujúcom formáte:

```
HTTP/1.1 200 OK\r\n
Content-Type: text/plain\r\n
Content-Length: 3\r\n
\r\n
7%\n
```

V inom prípade sa návratová hodnota nastaví na `404 Not Found`
