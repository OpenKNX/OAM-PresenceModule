# Applikationsbeschreibung Präsenz

Die Applikation Präsenz erlaubt eine Parametrisierung von Kanälen mit Präsenzmelder-Funktionalität mit der ETS.

Sie ist in die Bereiche

* Allgemeine Parameter
* PM-Kanäle
* Logikkanäle

gegliedert, wobei die Präsenzkanäle wiederum in bis zu 20 Kanäle untergliedert sind. 

Alle Logikkanäle sind in der [Applikation Logik](https://github.com/OpenKNX/OAM-LogicModule/blob/main/doc/Applikationsbeschreibung-Logik.md) beschrieben.

## Änderungshistorie

Im folgenden werden Änderungen an dem Dokument erfasst, damit man nicht immer das Gesamtdokument lesen muss, um Neuerungen zu erfahren.

01.05.2022: Firmware 0.x.x, Applikation 0.x

* Erste Beta

## Einleitung

Diese Applikation realisiert alle wesentlichen Funktionen eines Präsenz- bzw. Bewegungsmelders. Sie kann mit passender Präsenz- oder Bewegungsmelder-Hardware betrieben werden oder - und das ist das Besondere - auch als "Virtueller Präsenzmelder", indem sie Präsenz- und Helligkeitsinformationen über den KNX-Bus empfängt. Somit kann diese Applikation eine Art Update für existierende Präsenzmelder-Hardware darstellen, deren Applikation alt oder ungenügend ist und die gewünschten Funktionen nicht leistet.

Auch wenn im Folgenden immer von Präsenzmelder gesprochen wird, so hängt diese Eigenschaft von der verwendeten Präsen- bzw. Bewegungserkennung ab. Somit ist aus Sicht der Applikation Präsenz- und Bewegungsmelder synonym zu sehen, die angeschlossene Hardware bestimmt durch ihre Sensitivität, ob es sich um einen Präsenz- oder Bewegungsmelder handelt.

Die Idee zu dieser Applikation ist bei der Verwendung vom True Presence Präsenzmelder entstanden. Dieser hat eine gute bis sehr gute Präsenzerkennung, mittelmäßige Helligkeitswerte und eine schlechte Applikation. In Verbindung mit dieser (virtuellen) Applikation funktioniert er wesentlich besser und kann dann sogar zusätzliche Funktionen wie Kurzzeit-Präsenz.

Diese Präsenzmelder-Applikation implementiert folgende Funktionen:

* "Normaler Präsenzmelder" mit
  * schalten bei Bewegung
  * ausschalten nach einer gewissen Nachlaufzeit
  * Helligkeitsgesteuert oder Helligkeitsunabhängig
  * 2 Ausgängen pro Kanal mit unterschiedlichen DPT

* Virtueller PM: Verwendbar mit einem oder mehreren Slaves
  * PM ist dann Master für alle Slaves
  * Das Präsenz-Signal kann schaltend oder triggernd sein
  * Helligkeit kann vom gleichen Slave kommen oder vor irgendeinem anderen Helligkeitssensor

* Tagesphasen
  * Es wird nicht nur Tag/Nacht, sondern bis zu 4 Tagesphasen unterstützt (Morgens, Tag, Abend, Nacht)
  * Tagesphasen können beliebig benannt werden
  * Jede Tagesphase unterstützt eigene Nachlaufzeiten, Helligkeiten, Kurzzeitpräsenz

* Adaptive Helligkeit
  * Erlaubt absolute oder relative Helligkeitsschwellen
  * Abschaltung bei externen Lichteinflüssen
  * Beachtet mehrere Lichtkanäle

* Automatik- und Manuell- und Sperrmodus
  * Wechsel zwischen Modi für Ein- und Zweitastenbedienung vorgesehen
  * Szenensteuerung für Modi
  * Einstellbare Rückfallzeiten für Modi

* Viele Parameter über GA modifizierbar
  * aktuelle Helligkeitsschwelle
  * aktuelle Nachlaufzeit
  * aktuelle Tagesphase
  * Sensibilität des HF-Sensors
  * Szenario für HF-Sensor

* Logikmodul mit vielen weiteren Funktionen
  * mit dem integrierten Logikmodul können weitere Funktionen in den PM integriert werden

## **Allgemeine Parameter**

![Allgemeine Parameter](pics/AllgemeineParameter.PNG)
Hier werden Einstellungen getroffen, die die generelle Arbeitsweise des Präsenzmelder-Moduls bestimmen.

## Gerätestart

### **Zeit bis das Gerät nach einem Neustart aktiv wird**

Hier kann man festlegen, wie viel Zeit vergehen soll, bis das Gerät nach einem Neustart seine Funktion aufnimmt. Dabei ist es egal, ob der Neustart durch einen Busspannungsausfall, einen Reset über den Bus, durch ein Drücken der Reset-Taste oder durch den Watchdog ausgelöst wurde.

Da das Gerät prinzipiell (sofern parametriert) auch Lesetelegramme auf den Bus senden kann, kann mit dieser Einstellung verhindert werden, dass bei einem Busneustart von vielen Geräten viele Lesetelegramme auf einmal gesendet werden und so der Bus überlastet wird.

**Anmerkung:** Auch wenn man hier technisch bis zu 16.000 Stunden Verzögerung angeben kann, sind nur Einstellungen im Sekundenbereich sinnvoll.

### **In Betrieb senden alle**

Das Gerät kann einen Status "Ich bin noch in Betrieb" über das KO 1 senden. Hier wird das Sendeintervall eingestellt.

Sollte hier eine 0 angegeben werden, wird kein "In Betrieb"-Signal gesendet und das KO 1 steht nicht zur Verfügung.

### **Uhrzeit und Datum nach einem Neustart vom Bus lesen**

Dieses Gerät kann Uhrzeit und Datum vom Bus empfangen. Nach einem Neustart können Uhrzeit und Datum auch aktiv über Lesetelegramme abgefragt werden. Mit diesem Parameter wird bestimmt, ob Uhrzeit und Datum nach einem Neustart aktiv gelesen werden.

Wenn dieser Parameter gesetzt ist, wird die Uhrzeit und das Datum alle 20-30 Sekunden über ein Lesetelegramm vom Bus gelesen, bis eine entsprechende Antwort kommt. Falls keine Uhr im KNX-System vorhanden ist oder die Uhr nicht auf Leseanfragen antworten kann, sollte dieser Parameter auf "Nein" gesetzt werden.

## **Experteneinstellungen**

Die Experteneinstellungen kommen aus der [Applikation Logik](https://github.com/OpenKNX/OAM-LogicModule/blob/main/doc/Applikationsbeschreibung-Logik.md) und können dort nachgelesen werden.

## **PM-Kanäle**

Unter diesem Tab sind alle Einstellungen für den Präsenzmelder zusammengefasst. Jeder der folgenden Tabs wird in einem eigenen Kapitel beschrieben.

### **PM-Hardware**

Auf dieser Seite können 