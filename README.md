# Rapport TP Multi-threading

## Exécution des scripts

Exécuter queuemanager.py, puis proxy.py, puis ./build/low_level, puis minion.py, puis boss.py

## Tests de performance

`cmake -B build -S .` :
Tâche identifier: 3 (Python) time: 0.00043686399999387504 size: 100
Tâche identifier: 2 (C++)    time: 0.000584581            size: 100

Tâche identifier: 3 (Python) time: 0.018299999000191747 size: 500
Tâche identifier: 2 (C++)    time: 0.034083511          size: 500

Tâche identifier: 3 (Python) time: 0.06520618900140107 size: 1000
Tâche identifier: 2 (C++)    time: 0.871263889         size: 1000

Tâche identifier: 3 (Python) time: 0.4005630519998249 size: 2000
Tâche identifier: 2 (C++)    time: 4.502006822        size: 2000

Tâche identifier: 3 (Python) time: 4.669737025000131 size: 5000
Tâche identifier: 2 (C++)    time: 69.98614202       size: 5000

`cmake -B build -S . -DCMAKE_BUILD_TYPE=Release` :
Tâche identifier: 3 (Python) time: 0.0004225420000238955 size: 100
Tâche identifier: 2 (C++)    time: 0.000780551           size: 100

Tâche identifier: 3 (Python) time: 0.010904879000008805 size: 500
Tâche identifier: 2 (C++)    time: 0.041533481          size: 500

Tâche identifier: 3 (Python) time: 0.06021976800002449 size: 1000
Tâche identifier: 2 (C++)    time: 0.510068399         size: 1000

Tâche identifier: 3 (Python) time: 0.34464498799997045 size: 2000
Tâche identifier: 2 (C++)    time: 4.435424932         size: 2000

Tâche identifier: 3 (Python) time: 5.440208376999976 size: 5000
Tâche identifier: 2 (C++)    time: 66.416535247      size: 5000
