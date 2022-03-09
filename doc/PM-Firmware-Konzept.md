# PM Firmware Grobkonzept

Dieses Dokument basiert auf den ersten Ideen, die entstanden sind, um eine PM-Applikation mit dem Logikmodul zu realisieren.

Da aber jetzt eine eigene Firmware geschrieben wird, die auch mehr Möglichkeiten bietet, wird dieses Dokument zum Brainstorming genutzt.

Initial werden alle Diskussionspunkte aus dem Dokument [PM-Logik.md](PM-Logik.md) übernommen, allerdings ohne Realisierungsüberlegungen mit dem Logikmodul.

## Hauptfunktion

Es soll eine PM-Applikation entstehen, die Präsenz und Helligkeit von außen bekommt (von einem PM mit einer ungenügenden Applikation, wie z.B. dem TP von Steinel) und dann eine passende PM-Parametrierung erlaubt. Es werden 10-20 PM-Kanäle angestrebt.

Damit diese Applikation auch mit einer PM-fähigen Hardware vom Masifi (mit PIR-, Helligkeitssensor und Signal-LEDs) genutzt werden kann, können die PM-Kanäle alternativ auch Helligkeit und Präsenz von lokalen Sensoren empfangen.

Um eventuelle Signalverläufe der externen PM zu korrigieren oder die Ausgänge der PM-Kanäle an weitere Szenarien anzupassen, wird auch das Logikmodul mit so vielen Kanälen wie es möglich und sinnvoll ist eingebunden.

## Lokale Präsenzhardware

Falls es lokale Präsenzhardware gibt (PIR, Helligkeitssensor, LEDs), wird diese so eingebunden, dass die vorhandenen Präsenzkanäle Präsenz oder Helligkeit statt vom Bus auch von der lokalen Hardware erhalten können. Eventuelle LEDs können zur Signalisierung von Präsenz oder weiteren Informationen verwendet werden.

## Helligkeit (pro Kanal)

Helligkeit kann extern zyklisch gesendet werden und/oder bei Bedarf sogar über einen ReadRequest gelesen werden.

Helligkeitsanpassung (Anhebung oder Absenkung des Lux-Wertes) passiert bereits beim Sender, nicht pro PM-Kanal.

Helligkeitsschwellwerte zum Einschalten und ein Hysteresewert (um wie viel darf es heller werden) zum Ausschalten werden natürlich pro Kanal definiert. Alternativ kann der Schwellwert zum Einschalten über den Bus gesetzt werden. **Der zum Ausschalten auch?**

### Adaptive Helligkeitsschwelle

Als Ausbaustufe kann man eine Adaptive Helligkeitsschwelle implementieren, um mit geringer Hysterese für Helligkeitsabschaltung arbeiten zu können.

Dabei wird die Helligkeit nach dem Einschalten gemessen und
von da an mit dem gemessenen Hysteresewert verglichen. Wird dieser überschritten, wird wieder ausgeschaltet.

Um zu vermeiden, dass das Einschalten weiterer Lichtquellen im Raum den Hysteresewert überschreitet, wird es pro Kanal einen Trigger-Eingang geben, der mit dem Status einer jeden Lichtquelle verbunden wird (hörende GA). Jede 1 auf diesem Eingang führt zur Reevaluation der Lichtschwelle (gleiches Verfahren wie beim ersten Einschalten vom Licht).

**B:** Könnte hier eventuell die Statusauswertung des Lichtstatus über ein OR Gatter bereits das Triggersignal liefern?

**W:** Das OR haben wir "wegdiskutiert" und werden erstmal veruchen, es über Logik zu lösen. Erst wenn das zu kompliziert ist, wird es in den PM eingebaut.

**B:** Nach einem Wechsel einer Lichtquelle muss die Abschaltung über Helligkeitsschwelle unterdrückt werden, bis eine stabile neue Schwelle vorliegt.

**W:** Sehe ich auch so, aber es gibt noch einiges zu klären, deswegen die folgenden Unterkapitel...

### Adaptive Helligkeitsschwelle zum abschalten

Grundidee ist super: Beim Einschalten einer Lichtquelle wird der PM Getriggert und rechnet eine neue Lichtschwelle aus.

Bei mehreren Lichtkreisen muss man ein paar Sachen durchdenken.

Gegeben sei ein Raum mit 3 Lichtkreisen und einem kleinen Fenster. Auch bei vollem Tageslicht wird es nicht heller als mit allen Lichtquellen. Wir haben die Größen:

    **L1** Helligkeit bei nur einer Lichtquelle
    **L2** Helligkeit bei zwei Lichtquellen
    **L3** Helligkeit bei drei Lichtquellen
    **R** Helligkeit im Raum (ist entweder L*n* oder T)
    **T** Helligkeit bei Tageslicht

Ferner gibt es noch die Schwellwerte:

    **L1s** Schwelle bei nur einer Lichtquelle
    **L2s** Schwelle bei zwei Lichtquellen
    **L3s** Schwelle bei drei Lichtquellen
    **Ts** Schwelle bei Tageslicht
    **S** berechnete Ausschaltschwelle

Wir wissen:

    **L1** < **L2** < **Max(T)** < **L3**

Wir nehmen an:

    **L1** < **L1s** < **L2** < **L2s** < **L3** < **L3s**

#### Fall 1: Abschalten erhöht Lichtschwelle

Es sind 2 Lichtquellen an, Sonne scheint, im Raum ist es heller als **L2**, aber die Ausschaltschwelle ist noch nicht erreicht:

    **L2** < **R** = **T** < **S** = **L2s**

Wenn jetzt eine Lichtquelle abgeschaltet wird, wird es nicht dunkler, aber **L2s** wird neu berechnet und wird größer:

    **S** = **Ts** > **L2s**

Hypothese: Wenn beim Abschalten die neue Schwelle größer ist, wird die alte beibehalten.

Weitere Fälle folgen...

#### Szenenwechsel/Dimmen

Was ist, wenn gleichzeitig mehrere Lichtkreise durchgedimmt werden (potentiell ohne Schalttrigger)?

## Präsenzinformation (pro Kanal)

Die Präsenzkanäle werden ein externes Präsenzsignal erhalten. In erster Näherung kann man das wie ein klassisches Slave-Signal bei anderen Meldern betrachten. Hier sollen auch Alternativen betrachtet werden.

Es gibt 2 Konzepte, um ein externes Präsenzsignal auszuwerten. Beide Konzepte haben ihre Vor- und Nachteile.

### Präsenz als Triggersignal

Präsenz als Trigger ist der klassische Ansatz. Die Präsenzquelle sendet zyklisch eine Präsenzinformation als EIN-Telegramm. Dieses Signal sollte min. doppelt so oft eintreffen wie die Nachlaufzeit des PM-Kanals ist.

Man wertet nur EIN-Telegramme aus und jedes EIN-Telegramm triggert erneut die Nachlaufzeit.

Die Vorteile dieses Ansatzes:

* relativ einfach zu realisieren
* man kann an einen Slave-Eingang beliebig viele Slaves anschließen
* Bei Telegrammverlusten/Ausfall des Slave wird sicher abgeschaltet (nach dem Ablauf der Nachlaufzeit)

Demgegenüber steht als Nachteil:

* Der Quell-PM muss ein zyklisches Senden unterstützen
* Man hat "überflüssige" Telegramme auf dem Bus, die einfach nur den Status Quo (immer noch Präsenz) bestätigen
* Änderungen der Nachlaufzeit beim PM-Kanal müssen immer auch bei allen Slaves (1/2 Zykluszeit) nachgezogen werden
* Je kürzer die Nachlaufzeit, desto mehr Buslast erfährt man duch "überflüssige" Telegramme.

### Präsenz als Schaltsignal

Man kann das Präsenzsignal auch schaltend betrachten: Ein EIN-Telegramm signalisiert Präsenz, die mit einem AUS-Telegramm beendet wird. Die Nachlaufzeit wird erst beim AUS-Telegramm gestartet und würde durch ein neues EIN-Telegramm abgebrochen werden. Ein erneutes AUS-Telegramm während der Nachlaufzeit würde die Nachlaufzeit nachtriggern.

Vorteile:

* Rein schaltende Quellen (z.B. Schalter, Stromüberwacher) könnten als Slave dienen.
* Man vermeidet bzw. reduziert überflüssige Telegramme (kein zyklisches Senden notwendig)
* Es sind sehr kurze Nachlaufzeiten möglich
* Änderungen der Nachlaufzeiten beim Master haben keinen Einfluss auf die Slaves

Nachteile:

* Telgrammverlust (hier spezeill AUS-Telegramme) könnte ein Ausschalten verhindern.
* Obiges könnte man durch ein Lesetelegramm vor dem Ausschalten verhindern, doch dann gibt es wieder "Überflüssige" Telegramme (aber weniger, weil nur "on demand").

### Warum überhaupt Gedanken um schaltende Slaves?

Weil es sich anbietet, beim TP die beiden Präsenz-Rohdaten-Ausgänge "Präsenz" und "Bewegung" zu nehmen, die sind aber von ihrem Verhalten her schaltend.
Und einige Slaves, die man zum Triggern von Präsenz nutzen will, senden nicht zyklisch (Strommesskanäle).
Ferner wäre die Option "Schalter als Slave" eine einfache Möglichkeit der PM-Überbrückung, ohne sich Sperren und Zwangsführung zu kümmern.
Und ein triggernder Slave kann genau so über schaltende Logik implementiert werden, indem intern nach der triggernden 1 sofort eine 0 erzeugt wird.

Aktuelle Tendenz: Implementierung von schaltenden Slaves, 2 Slave-Eingänge. So können einfach die Rohdaten-Ausgänge Präsenz und Bewegung vom TP genutzt werden. Weitere Eingänge können durch das Logikmodul relaisiert werden.

In der Applikation wird man pro Eingang einstellen können, ob er schaltend oder triggernd ist. Ein triggernder Eingang wird einfach nach dem Empfang eines EIN-Telegramms intern sofort ein AUS erzeugen und eingehende AUS-Telegramme ignorieren.

## Sperre (pro Kanal)

Das Setzen einer Sperre sollte den Präsenzeingang auf AUS setzen, die Nachlaufzeit sofort beenden und einen definierten Zustand (EIN oder AUS, in der Applikation wählbar) am Ausgang realisieren.
**Diskussion Alternative:** Sperre hält den Schaltausgang konstant. Nach dem Aufheben der Sperre werden die Nachlauftimer neu gesetzt.
Erst nach dem zurücknehmen der Sperre sollte der Kanal wieder seine Funktion aufnehmen.

## Slaveeingang

Weitere Slaves werden durch das Logikmodul realisiert.

Ein schaltender Slave wird durch ein OR, das jedes Telegramm durchlässt (also alle EIN- und AUS-Wiederholungen).

Ein triggernder Slave bekommt einen Logikkanal mit einem Treppenlicht von 0.1 Sekunden, so dass immer eine EIN-AUS-Kombination ereugt wird.

## Statuseingang vom Aktor

Ein Statuseingang vom Aktor dient der PM-Logik dazu, über externe Schaltvorgänge des Aktors informiert zu werden. Dies adressiert vor allem unbeabsichtigte, vor allem durch automatismen verursachte Schaltvorgänge. Nehmen wir mal an, ein "Alles aus" macht das Licht aus, auch wenn man noch am Lesen ist. Dann möchte die Person durch z.B. einfaches "Winken" wieder das Licht anmachen können. Das ist anders bei manueller Bedienung (siehe nächster Abschnitt). Umgekehrt sollte beim unbeabsichtigten Einschalten des Aktors ohne Präsenz das Licht irgendwann wieder ausgehen, sinnvollerweise nach Ablauf der Nachlaufzeit.

Erste Idee: Wenn der Aktorstatus ungleich dem Schaltausgang des PM ist, dann wird  der Präsenzeingang auf AUS gesezt, die Nachlaufzeit sofort beendet und der Modus auf Auto gesetzt. **Diskussion Alternative** Wenn der PM Ausgang AUS ist, aber der Statuseingang EIN, wird noch Präsenz und Nachlaufzeit abgewartet, bis der Ausgang AUS geschaltet wird. Vorteil: Eine Szene bzw. EIN Signal kann direkt vom Taster zum Aktor gesandt werden (Ausfallsicherheit), ohne das der PM das Licht sofort deaktiviert.

Ist der Aktorstatus AUS, wird auch der PM-Kanal auf AUS gesetzt, ohne die Nachlaufzeit zu triggern. **Evtl. Totzeit einplanen?** Es wird auch kein AUS-Telegramm gesendet, da der Aktor schon AUS ist.
Ist der Aktorstatus EIN, wird der PM-Kanal auf EIN gesetzt und die Nachlaufzeit getriggert, also das ganz normale EINschaltverhalten, allerdings wird kein EIN-Telegramm gesendet, da der Aktror schon EIN ist.

## Manuelle Bedienung

Aus theoretischer Betrachtung lassen sich 4 Varianten einer manuellen Bedienung von PM-Zuständen (hier mal exemplarisch die Bedienung von Licht) ableiten:

* Der Benutzer möchte das Licht einschalten und es soll auf keinen Fall ausgehen. Der PM (also die Automatik) sind deaktiviert. Beim Ausschalten wird entschieden, ob dann wieder per PM (also Automatisch) geschaltet wird. Das nennen wir **Manuell AN**

* Der Benutzer möchte das Licht ausschalten und es soll auf keinen Fall angehen. Der PM (also die Automatik) sind deaktiviert. Beim Einschalten wird entschieden, ob dann wieder per PM (also Automatisch) geschaltet wird. Das nennen wir **Manuell AUS**

* Der Benutzer möchte das Licht einschalten, es soll aber durchaus durch den PM ausgeschaltet werden können (klassischer Fall: Es ist einem zu dunkel, der PM hat aber seine Helligkeitsschwelle zum Einschalten noch nicht erreicht). Das nennen wir **Automatik EIN**

* Der Benutzer möchte das Licht ausschalten, es soll aber durchaus durch den PM eingeschaltet werden können (klassischer Fall: Der PM hat das Licht eingeschaltet, man macht es aber aus, um einen schönen Abend bei Kerzenlicht zu verbringen). Hier ist es wichtig, dass das Licht so lange aus bleibt, wie Präsenz im Raum existiert. Das nennen wir **Automatik AUS**

Wenn man sich die obigen 4 Fälle anschaut, sind das genau die Fälle der Zwangsführung:

* 00 - **keine Priorität, aus** entspricht Standardverhalten+ausschalten oder bei uns **Automatik AUS** (da beim PM das Standardverhalten ja "Automatik EIN" sein sollte)

* 01 - **keine Priorität, ein** entspricht Standardverhalten+einschalten oder bei uns **Automatik EIN**

* 10 - **Priorität, aus** entspricht Sonderverhalten+ausschalten oder bei uns **Manuell AUS** (da Priorität beim PM ja das übersteuern der Automatik ist)

* 11 - **Priorität, ein** entspricht Sonderverhalten+einschalten oder bei uns **Manuell EIN**

**hier braucht es nochmal Brainstorming, wie man das mit der Sperre in Einklang bringt, s.u.**
Ob man alle 4 Varianten über ein Zwangsführungsobjekt zugänglich macht oder über 2 einzelne Bitobjekte, ist sekundär. Interessant ist die Realisierung. Bei 2 einzelnen Bitobjekten würde die bereits besprochene Sperre das Prioritätsobjekt abbilden, es käme nur noch ein EIN/AUS-Objekt hinzu.

Um es überschaubar zu gestalten, wird hier der Ansatz gewählt, dass es eine Sperre und ein manuelles EIN/AUS-Objekt (M) gibt. Ein Zwangsführungs-Eingang setzt nur die beiden Einzelobjekte intern. Das bedeutet, dass die beiden Einzelobjekte und die Zwangsführung gleichberechtigt sind. Das kann verwirrend sein. Klassischerweise hat die Zwangsführung Vorrang vor Sperre oder es kann nur eines von beiden in der Applikation ausgewählt werden.

## Kurzzeitpräsenz

Der Melder sollte auch Kurzzeitpräsenz erkennen können. Der Gang zum Kühlschrank sollte das Licht anmachen, aber nach kurzer Zeit auch wieder ausmachen. Hierzu muss man angeben, welche Zeitspanne noch als kurze Präsenz gilt. Ferner muss man auch angeben, welche Nachlaufzeit bei Kurzzeitpräsenz gelten soll.

## Nachlaufzeit per KO ändern

Man wird die Nachlaufzeit (der Langzeitpräsenz) auch per KO ändern können. Dies wirkt sich auf bereits laufende Nachlaufzeiten direkt aus. Wenn also eine Nachlaufzeit von 5 Minuten bereits 3 Minuten läuft und die Nachlaufzeit wird auf 2 Minuten geändert, wird die laufende Nachlaufzeit sofort beendet. Ebenso würde eine Änderung auf 10 Minuten dazu führen, dass die Nachlaufzeit noch weitere 7 Minuten andauert.

## Totzeit

Totzeit dient dazu, ein erneutes Einschalten während der Abschaltphase zu verhindern, weil eine sich abkühlende Lichtquelle von manchen PM als Bewegung erkannt wird.

Da die Totzeit eigentlich hardwarebezogen ist, muss man bei Problemen die Totzeit am Quell-PM einstellen.

Muss der virtuelle PM von der Totzeit wissen? Arbeitshypthese: Nein. Wird sich aber bei der Erstellung der Firmware noch zeigen und muss dann potentiell hinzugefügt werden.
**B:** Totzeit sollte auch im PM Modul vorgesehen wqerden, um bei manuellen Ausschaltvorgängen noch den Raum verlassen zu können, ohne erneut auszulösen
**W:** Für diesen Usecase würde ich lieber noch ein paar Gedanken Richtung "Nachlaufzeit AUS kürzer als Nachlaufzeit EIN" spendieren. Ist meiner Meinung nach sparter, aber schwerer zu realisieren.

## Tagesphase (Tag-Nacht-Objekt)

Anstatt mit einem Tag-Nacht-Objekt zu arbeiten gibt es ein Szenenobjekt, dass bis zu 5 Tagesphasen zulässt (Morgen-Mittag-Dämmerung-Abend-Nacht-Objekt). Falls es nur 2 Phasen sind, wird ein klassisches DPT1-KO angeboten.
**Vorschlag** Implementation im ersten Step mit 1bit (Tag/Nacht) später Erweiterung auf bis zu 3bit.
**W:** Wie besprochen machen wir gleich 4 Tagesphasen. Der Mehraufwand ist überschaubar und maist ist es aufwändiger, später von einem 2-Stufigen (bool) auf ein mehrstufiges Konzept zu wechseln (andersrum ist immer einfacher).

## Reset

Für Präsenzmessung gibt es Situationen, in denen man feststellen will, ob gerade jetzt eine Präsenz im Raum gegeben ist (z.B. das Haus wird verlassen, ist noch jemand drin?). Mit PM und Nachlaufzeiten ist das schwer zu realisieren, denn man weiß erst nach der Nachlaufzeit (bei mehreren PM nach dem Maximum aller Nachlaufzeiten), ob Präsenz vorhanden ist oder nicht.

Eine Alternative ist, einen PM zurückzusetzen und ihm ein Zeitfenster zu geben, in dem er eine Präsenz ermitteln kann (Wenn ab jetzt innerhalb der nächsten 15 Sekunden keine Präsenz festgestellt wird, dann ist wohl keiner da). Dazu muss man den PM samt seiner Nachlaufzeit zurücksetzen können. Dafür ist die Reset-Logik. Diese nutzt bei einer abstrakten PM-Applikation nichts, wenn man nicht auch den Quell-PM entsprechend zurücksetzen kann. Ob und wie das geht, hängt von dessen Hardware ab. Einige PM machen einen internen Reset durch setzen und zurücksetzen der Sperre kurz hintereinander. Das könnte man auch hier erwägen und das KO sparen.

**Diskussion** weitere Alternative: Präsenzausgang des Lichtkanals, ohne oder mit sehr kurzen Nachlaufzeiten (ggf. Beobachtungsfenster, über mehrere Präsenzeingänge)
**W:** Das bekommt man nicht hin, wenn der PM extern ist und man die PIR Rohdaten nicht bekommt.

Der Reset würde auch immer in den Automatikmodus zurückkehren und könnte somit auch als externes Rücksetzen vom Manuellmodus genutzt werden (unabhängig von der Rückfallzeit). **Gibt es noch weitere Usecases für einen Reset?**

## KO (statisch)

Die folgenden KO werden einmalig (global für die gesamte PM-Applikaiton, also für alle Kanäle) angeboten. Derzeit exponieren sie eine eventuell vorhandene PM-Hardware.

KO | Name | DPT | Bedeutung
:---:|:---|---:|:--
20 | Helligkeit | 9.004 | Ausgang: Hellikeit bei lokaler Hardware
21 | Präsenz    | 1.001 | Ausgang: Präsenz bei lokaler Hardware (schaltend?)
22 | LED rot    | 1.001 | Eingang/Status: Rote LED über Bus schalten
23 | LED gelb   | 1.001 | Eingang/Status: Gelbe LED über Bus schalten

## KO (pro Kanal)

Derzeit würde ich die Kanalabhängigen KO bei 30 starten lassen.
Bei 15 KO pro Kanal und 20 Kanälen würde man auf 300 KO kommen, also bis 329.

Falls das Logikmodul bei 80 Kanälen bleibt, würden weitere 240 KO hinzukommen, 330-569. Das müsste man testen, wird potentiell knapp (bei angenommenen 500 KO Geasmtkapazität).

Sonst hätte man 500 - 330 = 170 KO für Logik, was 57 Kanäle ermöglicht -> sollte auch reichen (ergibt 501 KO).

In der folgenden Tabelle ist die KO-Nummer nur ein Offset zu einem Anfangs-KO *n*, das für den Kanal berechnet wird.

KO | Name | DPT | Bedeutung
:---:|:---|---:|:--
0  | Helligkeit     | 9.004       | Eingang: Helligkeit extern
1  | Präsenz A      | 1.001       | Eingang: Präsenzinfo Quelle 1
2  | Präsenz B      | 1.001       | Eingang: Präsenzinfo Quelle 2
3  | Automatik übersteuern | 1.001       | Eingang: Aktuellen Schaltwert im Automatikmodus setzen
4  | Manuell übersteuern   | 1.001       | Eingang: Aktuellen Schaltwert im Manuellmodus setzen
5  | Aktorstatus    | 1.001       | Eingang: Status des geschalteten Aktors
6  | Lichtschwellenberechnung | 1.001       | Eingang: EIN triggert Berechnung adaptiver Lichtschwelle
7  | Sperre         | 1.001       | Eingang/Status: Sperre
7  | Zwangsführung  | 2.001       | Eingang/Status: Zwangsführung
8  | Reset Nachlauf | 1.001       | Präsenz neu ermitteln
9  | Tagesphase     | 5.010 / 17.001 | Eingang: Tagesphase (Zahl oder Szene?)
9  | Tag/Nacht      | 1.001       | Eingang: Tag-/Nacht-Objekt (Alternative zu Tagesphase)
10 | Helligkeitsschwelle | 9.004  | Eingang: Helligkeitsschwelle
11 | Nachlaufzeit   | 7.005       | Eingang: Nachlaufzeit
12 | Szenensteuerung | 17.001     | Eingang/Status: PM über Szene steuern
13 | Schaltausgang  | 1.001       | Ausgang: Schaltend
13 | Dimmausgang    | 5.001       | Ausgang: Dimmen
13 | Szenenausgang  | 17.001      | Ausgang: Szene
14 | Schaltausgang 2 | 1.001      | Ausgang: 2. Schaltausgang
14 | Dimmausgang 2   | 5.001       | Ausgang: 2. Dimmen
14 | Szenenausgang 2 | 17.001      | Ausgang: 2. Szene
15 | Status Automatikbetrieb | 1.001 | Ausgabe des PM Status (manuell / Automatik)
16 | Manuell Relativ Dimmen | 3.007 | Eingang: Es wurde manuell am Taster gedimmt
17 | Manuell Absolut Dimmen | 5.001 | Eingang: Es wurde manuell über Absolutwert gedimmt
18 | Manuell Szene Dimmen | 17.001 | Eingang: Es wurde manuell über Szene gedimmt
19 | Frei für Erweriterung |       | Belegt nur einen passendes KO

## Offene Punkte

### Steuerung des Quell-PM

Werden wir eventuell KO (Ausgänge) brauchen, die den Quell-PM steuern, um bestimmte Funktionen zu ermöglichen (z.B. Reset der Quelle, um definiertes Verhalten zu bekommen)? **Erste Vermutung** Nein

### Abgrenzung Manuell und Sperre

Manuell und Sperre sind sehr ähnlich. Die Abgrenzung der beiden muss noch diskutiert werden.

Sperre hat höhere Prio, deswegen braucht man auch Sperre/Zwangsführung.

### Manuelle Bedienung über weitere Stellgrößen

Bisher wurde die manuelle Bedienung nur unter dem Aspekt "Schalten" betrachtet. Allerdings werden gerade Lichtquellen auch noch mittels dimmen und Szenen gesteuert. Und dies kann natürlich auch zu einer Änderung des Schaltzustands führen (z.B. runterdimmen, bis die Lampe AUS ist, oder Szene, die auf 50% einschaltet). Wie soll ein PM auf solche Aktionen reagieren und wie soll er solche Aktionen überhaupt mitbekommen?

Arbeitshypothese: Die korrekte Reaktion erfolgt über den Aktorstatuseingang.

Wenn eine Lichtquelle über die Szene 50% eingeschaltet wird, dann sendet der Aktor auch seinen EIN-Status an den PM. Dieser verläßt einen möglichen Manuell-Modus, triggert die Nachlaufzeit, sendet aber kein EIN-Signal vom PM an den Aktor (siehe Aktorstatus). Ein EIN-Telegramm muss in einem solchen Falle unterdrückt werden, weil es Dimmer gibt, die bei einem EIN auf den Schalteingang wieder auf 100% gehen.

Wenn eine Lichtquelle über relatives Dimmen auf 0% gedimmt wird, dann sendet der Aktor auch seinen AUS-Status an den PM. Dieser verläßt einen möglichen Manuell-Modus, triggert NICHT die Nachlaufzeit, sendet auch kein AUS-Signal vom PM an den Aktor (siehe Aktorstatus).

Das Problem ist aber, dass man im letzteren Fall eine Nachlaufzeit wünschen würde. Andernfalls würde - bei einem manuellen runterdimmen auf 0% in dem Raum selbst - das Licht sofort wieder angehen, weil man ja noch im Raum ist (Das ist die "ich bin auf dem Klo, das Licht ist aus und ich winke kurz"-Situation).

Kurz gesagt: Die Veränderung des Schaltstatus über einen manuellen Eingriff (Schalten, relatives Dimmen, absolutes Dimmen oder Szene) ist eher wie Taste kurz zu betrachten, aber ohne dass der PM erneut schaltet.

Eine unvorhergesehene Schaltung sollte wie unter Aktorstatus beschrieben betrachtet werden.

Einwand: Was ist mit mehreren Dimmkanälen? Multiple Lichtkreise sind ja schon an anderen Stellen adressiert, muss man hier auch durchdenken.

### Nachlaufzeit bei AUS kürzer als Nachlaufzeit bei EIN

### Sperren Bewegung - Usecase?

Kein Usecase gefunden, lassen wir erstmal weg.

### Dunkelschalten - Usecase?

Arbeitshypothese: Kann man auch über Helligkeitsschwelle auf max Lux setzen lösen. Geht über Logikmodul auch als DPT1-Signal.

### Halbautomat ist noch nicht adressiert

### Rückfall

Zumindest bei Sperre und Zwangsführung, aber auch bei Manuell AUS/EIN sollte es einen Rückfall über Zeit und über Reset geben. Gleiche Zeit für beide oder einzeln?

### Doppelbetätigung von Tastern

Es kann passieren, dass die Tastereingänge für Automatik EIN/AUS und Manuell EIN/AUS auch mehrmals das gleiche Telegramm empfangen:

* man sendet ein EIN auf Taster kurz -> führt zu Automatik EIN
* jetzt sendet man erneut ein EIN auf Taster kurz -> passiert jetzt was? Wird daraus jetzt Manuell EIN (Intention: Es ist schon an, man will also den Automatikmodus wechseln ohne Aus- und Einschalten zu müssen)?
* An sich könnte man das ja auch direkt durch Manuell EIN-Signal erreichen. Obiger Ansatz würde aber Tasten sparen.

Eigentlich hängt das nicht von Doppelbetätigung ab, sondern von einem erneuten EIN/AUS-Signal auf einen Zustand, in dem sich die Statemachine bereits befindet.
