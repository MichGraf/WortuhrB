# Wortuhr

 Achtung: Dioeser Code ist entstanden aus einem Example der Lib iotwebconf. Diese habe ich um einige Features erweitert aber ohne auf eine ordentliche Modularisierung zu achten. (rein private Anwendung).

 Da dies die Basis für viele Projekte ist habe ich die unveränderlichen Teile in Includes ausgelagert. Nicht die feine Art.
 Deshalb gibt es ein include_init, include_setup, include_main und include_post.
 Diese Dateien müssen / sollen bei Wechsel eines Projektes nicht verändert werden.

 Projektspezifischer Code ausschliesslich in Main bzw. weiteren Includes.
 
