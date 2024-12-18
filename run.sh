#!/bin/bash

# Chemin vers les scripts Python et le fichier exécutable
QUEUE_MANAGER="queuemanager.py"
BOSS="boss.py"
PROXY="proxy.py"
LOW_LEVEL="./build/low_level"  # Assurez-vous que low_level est exécutable

# Fonction pour vérifier si un fichier existe
check_file() {
    if [ ! -f "$1" ]; then
        echo "Erreur : le fichier $1 est introuvable."
        exit 1
    fi
}

# Vérifier les fichiers
check_file "$QUEUE_MANAGER"
check_file "$BOSS"
check_file "$PROXY"
check_file "$LOW_LEVEL"

# Lancer les scripts en parallèle
echo "Démarrage de queuemanager.py"
python3 "$QUEUE_MANAGER" &
PID_QUEUE_MANAGER=$!

echo "Démarrage de boss.py"
python3 "$BOSS" &
PID_BOSS=$!

echo "Démarrage de proxy.py"
python3 "$PROXY" &
PID_PROXY=$!

echo "Démarrage de low_level"
"$LOW_LEVEL" &
PID_LOW_LEVEL=$!

# Attendre que tous les processus se terminent
wait $PID_QUEUE_MANAGER $PID_BOSS $PID_PROXY $PID_LOW_LEVEL

echo "Tous les processus se sont terminés."
