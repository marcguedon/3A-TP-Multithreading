# Rapport TP Multi-threading

## Exécution des scripts

Exécuter queuemanager.py, puis proxy.py, puis ./build/low_level, puis minion.py, puis boss.py

## Tests de performance

`cmake -B build -S .`:
Tâche identifier: 3 (Python) time: 0.06520618900140107 size: 1000
Tâche identifier: 2 (C++)    time: 0.871263889         size: 1000

`cmake -B build -S . -DCMAKE_BUILD_TYPE=Release`:
Tâche identifier: 3 (Python) time: 0.06021976800002449 size: 1000
Tâche identifier: 2 (C++)    time: 0.510068399         size: 1000
