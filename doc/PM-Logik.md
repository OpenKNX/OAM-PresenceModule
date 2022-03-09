# PM Logik mit Logikmodul

## Kommunikationsobjekte

KO | Name | DPT | Bedeutung
:---:|:---|---:|:--
10 | Ausgang Schalten | 1.001 | Schaltausgang Lichtkanal
10 | Ausgang Dimmen absolut | 5.001 | Ausgang absoluter Dimmwert
10 | Ausgang Szene | 17.001 | Ausgang Szenennummer
11 | Ausgang Zusatzschalten | 1.001 | Zusatzausgang z.B. für Nachtlicht
12 | Eingang externer Taster kurz | 1.001 | Übersteuerung Automatikmodus
13 | Eingang externer Taster lang | 1.001 | Umschaltung manuell / Automatikmodus
14 | Eingang externe Bewegung| 1.001 | Externes Präsenzsignal (zyklisch)
15 | Eingang externe Helligkeit| 9.004 | Externes Helligkeitssignal (in lux)
16 | Eingang externe Helligkeitsschwelle| 9.004 | Vorgabe der Helligkeitsschwelle (in lux)
17 | Ausgang adaptive Helligkeitsschwelle| 9.004 | Ausgabe der adaptiven Helligkeitsschwelle (in lux)
18 | Eingang Dunkel schalten | 1.001 | Deaktivierung Helligkeitsschwelle
18 | Eingang externe Nachlaufzeit| 7.005 | Vorgabe externe Nachlaufzeit (10-65000s)
20 | Eingang Sperre Bewegungserkennung| 1.001 | Bewegungserkennung sperren
21 | Eingang Zwangsführung | 2.001 | 2bit Zwangsführung
22 | Eingang Sperrobjekt | 1.001 | PM Sperren
23 | Status Automatikbetrieb | 1.001 | Ausgabe des PM Status (manuell / Automatik)
24 | Eingang Szene | 17.001 | Szenensteuerung des PM
25 | Eingang Tag/Nacht | 1.001 | Tag/Nacht Umschaltung
26 | Ausgang Aktorkanal | 1.001 | Ausgang des ODER Gatters für den Aktorstatus
27 | Eingang 1 Lichtstatus| 1.001 | Eingang ODER Gatter für Ermittlung Lichtstatus
28 | Eingang 2 Lichtstatus| 1.001 | Eingang ODER Gatter für Ermittlung Lichtstatus
29 | Eingang 3 Lichtstatus| 1.001 | Eingang ODER Gatter für Ermittlung Lichtstatus
30 | Eingang 4 Lichtstatus| 1.001 | Eingang ODER Gatter für Ermittlung Lichtstatus
31 | Eingang 5 Lichtstatus| 1.001 | Eingang ODER Gatter für Ermittlung Lichtstatus
32 | Eingang 6 Lichtstatus| 1.001 | Eingang ODER Gatter für Ermittlung Lichtstatus
33 | Eingang 7 Lichtstatus| 1.001 | Eingang ODER Gatter für Ermittlung Lichtstatus
34 | Eingang 8 Lichtstatus| 1.001 | Eingang ODER Gatter für Ermittlung Lichtstatus



## Hauptfunktion

Helligkeit kann von TP zyklisch gesendet werden und dann über einen Eingangskonverter in ein passendes "ist dunkel"-Signal konvertiert werden. Mit Hysterese vermeidet man ein Schwingen, mit Differenzhysterese könnte man sogar eine Helligkeitsschwelle über den Bus setzen.

    Helligkeit DPT9 über Hysterese (oder Differenzhysterese) -> Dunkel D

    Merker: Adaptive Helligkeitsschwelle, um mit geringer Hysterese für Helligkeitsabschaltung arbeiten zu können. 
    Aktualisierung der adaptiven Schwelle wird durch Änderung am Statuseingang oder gesonderten Triggereingang ausgelöst

Um häufiger Bewegungstrigger zu bekommen, nehmen wir Präsenz und Bewegung vom TP, nicht den Lichtkanal. So kann man (vielleicht) Kurzzeitpräsenz auch ermöglichen.

    Präsenz und Bewegung vom TP über ein OR, wobei jedes Signal triggert -> Präsenztrigger PT

Als Grundfunktion würde man einfach ein Treppenlicht nachtriggern, dass nicht ausschaltbar ist.

    D AND PT (nur PT triggert) -> Ausgang hat ein Treppenlicht, nachtriggerbar, nicht ausschaltbar -> Lichtausgang L

----

## Sperre

Sperre (S) ist ein negiertes Tor am Ausgang, damit man klar sagen kann, was für ein Singal beim anlegen der Sperre und beim aufheben der Sperre gesendet wird.

Allerdings muss man bei der Sperre auch das Treppenlicht ausschalten, damit man beim Ausschalten der Sperre ein definiertes Verhalten hat.



Änderung zu oben:

Aus D und PT wird jetzt erstmal nur ein Lichttrigger gemacht, dass nur 1 sendet (und so ein Treppenlicht nur nachtriggern kann).

    D AND PT (nut PT triggert) -> Filter auf "nur 1 weiterleiten" -> Lichttrigger LT

Der Lichttrigger kann von einem Tor komplett unterbunden werden und so im Sperrfall direkt mit einer 0 das Treppenlicht ausschalten. Da der Lichttrigger nur 1 sendet, kann dieser das Treppenlicht niemals ausschalten.

    LT geht auf ein Tor, dass von S (negiert) geöffnet wird. Das Tor sendet immer eine 0 im geschlossenen Zustand, wird bei jedem Telegramm getriggert. Der Ausgang ist dann das Treppenlicht, ausschaltbar, nachtriggerbar -> Treppenlicht TL

Ab hier hätte man bereits ein sperrbares Treppenlichtsignal, dass aber im Falle einer Sperre nur eine 0 senden kann. Wenn das nicht reicht, schaltet man noch ein Tor hinterher, dass im Sperrfall ein gewünschtes Signal sendet. Hier kann man dann auch passend wiederholungen filtern, zyklisch senden, Ein- und Ausschaltverzögern, was immer man will.

    TL geht auf ein weiteres Tor, dass von S (negiert) geöffnet wird. Für geschlossenen Zustand kann das Tor parametrisiert werden, bei offen wird TL gesendet. Ausgang filtert alle 0 und 1 Wiederholungen -> Lichtausgang L

## Salveeingang

Eigentlich braucht man keinen weiteren Slaveeingang. Für 1-Trigger kann der selbe Eingang wie für Präsenz vom TP verwendet werden (mehrere GA an diesem KO).

Falls wir vom TP nicht nur 1, sondern auch 0-Telegramme auswerten, würde ein Slaveeingang notwendig werden.

## Statuseingang vom Aktor

Ein Statuseingang vom Aktor dient der PM-Logik dazu, über externe Schaltvorgänge des Aktors informiert zu werden. Dies adressiert vor allem unbeabsichtigte, vor allem durch automatismen verursachte Schaltvorgänge. Nehmen wir mal an, ein "Alles aus" macht mir das Licht aus, auch wenn ich noch am Lesen bin. Dann möchte ich durch z.B. einfaches "Winken" wieder das Licht anmachen können. Das ist anders bei manueller Bedienung (siehe nächster Abschnitt).

Erste Idee: das 1-Signal triggert normal wie jeder Slave, das 0-Signal schaltet das Treppenlicht aus.

So würden neue Bewegungen direkt erkannt werden und neue Aktionen auslösen.

## Manuelle Bedienung

Aus theoretischer Betrachtung lassen sich 4 Varianten einer manuellen Bedienung von PM-Zuständen (hier mal exemplarisch die Bedienung von Licht) ableiten:

* Der Benutzer möchte das Licht einschalten und es soll auf keinen Fall ausgehen. Der PM (also die Automatik) sind deaktiviert. Beim Ausschalten wird entschieden, ob dann wieder per PM (also Automatisch) geschaltet wird. Das nennen wir **Automatik AUS, Licht AN**

* Der Benutzer möchte das Licht ausschalten und es soll auf keinen Fall angehen. Der PM (also die Automatik) sind deaktiviert. Beim Einschalten wird entschieden, ob dann wieder per PM (also Automatisch) geschaltet wird. Das nennen wir **Automatik AUS, Licht AUS**

* Der Benutzer möchte das Licht einschalten, es soll aber durchaus durch den PM ausgeschaltet werden können (klassischer Fall: Es ist einem zu dunkel, der PM hat aber seine Helligkeitsschwelle zum Einschalten noch nicht erreicht). Das nennen wir **Automatik EIN, Licht EIN**

* Der Benutzer möchte das Licht ausschalten, es soll aber durchaus durch den PM eingeschaltet werden können (klassischer Fall: Der PM hat das Licht eingeschaltet, man macht es aber aus, um einen schönen Abend bei Kerzenlicht zu verbringen). Hier ist es wichtig, dass das Licht so lange aus bleibt, wie Präsenz im Raum existiert. Das nennen wir **Automatik EIN, Licht AUS**

Wenn man sich die obigen 4 Fälle anschaut, sind das genau die Fälle der Zwangsführung:

* 00 - **keine Priorität, aus** entspricht Standardverhalten+ausschalten oder bei uns **Automatik EIN, Licht AUS** (da beim PM das Standardverhalten ja "Automatik EIN" sein sollte)

* 01 - **keine Priorität, ein** entspricht Standardverhalten+einschalten oder bei uns **Automatik EIN, Licht EIN**

* 10 - **Priorität, aus** entspricht Sonderverhalten+ausschalten oder bei uns **Automatik AUS, Licht AUS** (da Priorität beim PM ja das übersteuern der Automatik ist)

* 11 - **Priorität, ein** entspricht Sonderverhalten+einschalten oder bei uns **Automatik AUS, Licht EIN**

Ob man alle 4 Varianten über ein Zwangsführungsobjekt zugänglich macht oder über 2 einzelne Bitobjekte, ist sekundär. Interessant ist die Realisierung. Bei 2 einzelnen Bitobjekten würde die bereits besprochene Sperre das Prioritätsobjekt abbilden, es käme nur noch ein EIN/AUS-Objekt hinzu.

Um es überschaubar zu gestalten, wird hier der Ansatz gewählt, dass es eine Sperre und ein manuelles EIN/AUS-Objekt (M) gibt. Ein Zwangsführungs-Eingang setzt nur die beiden Einzelobjekte intern. Das bedeutet, dass die beiden Einzelobjekte und die Zwangsführung gleichberechtigt sind. Das kann verwirrend sein. Klassischerweise hat die Zwangsführung Vorrang vor Sperre oder es kann nur eines von beiden in der Applikation ausgewählt werden.

### Automatik EIN, Ausgang EIN/AUS

Man will hier ein bestimmtes Ausgangssignal haben (EIN oder AUS), solange Präsenz ist. Danach soll der Melder wieder in seinen "normalen" Automatikmodus fallen.

Ein Impuls auf dem Einagang M muss die Helligkeitsschwelle deaktivieren, das Treppenlicht triggern und den gewünschten Wert am Ausgang senden.

Um den Impuls festzustellen:

    Eingang M normal und negiert auf ein OR, dass jedes Eingangssignal durchlässt -> Manueller Trigger MT.

Wir brauchen noch etwas, was den Manuellmodus speichert. Der Modus wird von MT gestartet. Zurückgesetzt wird er, wenn die Nachlaufzeit auf 0 geht.

    MT geht auf ein OR mit einem Eingang. Der Ausgang sendet nur bei Änderung -> Status Manueller Modul MM.

MM geht auf ein OR, das direkt hiter der Helligkeits-Hysterese sitzt. So kann man den PM helligkeitsunabhängig machen. Statt:

    D AND PT (nut PT triggert) -> Filter auf "nur 1 weiterleiten" -> Lichttrigger LT

machen wir jetzt

    D OR MM (nur senden bei Änderung) -> Dunkel neu DN

um dann

    DN AND PT (nut PT triggert) -> Filter auf "nur 1 weiterleiten" -> Lichttrigger LT

MM setzt technisch eine Sperre wie bei Automatik AUS, der Ausgang ist dann durch den Wert von M vorbelegt.

Jetzt fehlt nur noch, dass ein 0 vom Treppenlicht auch MM zurücksetzt.

    TL geht auf ein OR mit nur einem Eingang, dass nur 0 durchlässt -> Treppenlicht Aus TL0.

    TL0 geht auf den einzigen Eignang vom MM, der dann MM zurücksetzt.

### Automatik AUS, Ausgang EIN/AUS

Wir nutzen die Sperre von oben, nur wird das 2. Tor (das vom Lichtausgang L) so parametriert, dass es immer eine 0 im Sperrfall liefert. Der Ausgang dieser Logik ist jetzt auch nicht mehr der Lichtausgang, sondern der Sperrausgang SA.

    TL geht auf ein weiteres Tor, dass von S (negiert) geöffnet wird. Für geschlossenen Zustand liefert das Tor immer 0, bei offen wird TL gesendet. Ausgang filtert alle 0 und 1 Wiederholungen -> Sperrausgang SA

Der Sperrausgang SA wird jetzt auf ein OR mir dem

## Kurzzeitpräsenz

## Nachlaufzeit per KO ändern

## Totzeit
