Ninja Virtual Machine v1.4

0 Vorwort
Die NinjaVM ist lediglich ein Projekt des Fachmoduls 'Konzepte systemnaher Programmierung' (kurz: KSP) und keinerweise
für den öffentlichen Gebrauch gedacht.

1 Die Ausführung
Bevor die NinjaVM zum Gebrauch bereit ist, muss vorher das Programm kompiliert werden. Dazu ist die Datei 'mknjvm' gedacht.
Ausgeführt wird dieses Skript mit folgendem Befehl:
  com@com:~/verz/ ./mknjvm
Dadurch wird mit dem GNU C Compiler (gcc) die NinjaVM kompiliert und die ausführbaren Datei 'njvm' erzeugt.
Wie folgt wird dann die NinjaVM gestartet:
  com@com:~/verz/ ./njvm
Zusätzlich gibt es Program Flags, Programmoptionen die ausgewählt werden können:
  --help :     Ruft die Hilfefunktion auf und zeigt Ihnen mögliche Flags
  --version:   Zeigt Ihnen die aktuelle auf dem Rechner verfügbare Version der NinjaVM
  --debug:     Führt eine zusätzlich angehongene Datei im Debugger Modus aus
  --debughelp: Zeigt die Debugger Hilfe an
Bei --debug ist eine ausführbare Datei (*.bin) mit Pfad vom aktuellen Verzeichnis anzuhängen, es ist ein absoluter, sowie relativer Pfad möglich,
damit die VM weiß, welche Datei sie auszuführen hat. Alle weiteren Flags benötigen keine zusätzliche Datei, da sie nur Informationen anzeigen
und dann die VM wieder schliessen.
Möchten Sie die VM ausserhalb des Debuggers starten, geben Sie einfach nach ./njvm die Datei mit Pfad vom aktuellen Verzeichnis an.
  Format: ./njvm <input file> (ohne die Spitzen Klammern ( < > )
Es können mehrere Programmargumente übergeben werden, jedes wird einzeln abgearbeitet, jedoch nicht nach der eingegebenen, sondern
nach einer festen Reihenfolge, wie folgt:
  VERSION
  HELP
  DEBUGHELP
  DEBUG
  INPUT FILE
  
2 Der Debugger
Der Debugger verfügt mehrere Optionen, um das aktuelle Programm zu debuggen, anhand des Assembler Codes.
Folgende Optionen stehen zur Verfügung:
  step:           Sie gehen Schritt für Schritt das Programm durch
  list:           Listet den kompletten Programm Code an
  run:            Debugger wird geschlossen und führt das Programm im Standard Modus aus
  inspect stack:  Zeigt den Status des Stacks
  quit:           Schliesst die komplette NinjaVM
 optional
  inspect_all:    Geht das komplette Programm durch und zeigt bei jeder Programminstruktion den Stack an.
