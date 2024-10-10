#!/bin/bash

# Couleurs pour une meilleure lisibilité
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

wait_for_keypress() {
    echo -e "${BLUE}Appuyez sur une touche pour continuer...${NC}"
    read -n 1 -s -r
    echo
}

# Fonction pour exécuter un test
run_test() {
    test_name="$1"
    num_philo="$2"
    time_die="$3"
    time_eat="$4"
    time_sleep="$5"
    num_eat="$6"
    expected_output="$7"
    timeout="$8"

    echo "Exécution du test : $test_name"
    
    if [ -z "$num_eat" ]; then
        cmd="./philo $num_philo $time_die $time_eat $time_sleep"
    else
        cmd="./philo $num_philo $time_die $time_eat $time_sleep $num_eat"
    fi

    output=$(timeout "$timeout" $cmd 2>&1)
    exit_code=$?

    if [ $exit_code -eq 124 ]; then
        echo -e "${RED}Le test a dépassé le délai de $timeout secondes${NC}"
        return 1
    fi

    if echo "$output" | grep -q "$expected_output"; then
        echo -e "${GREEN}Test réussi${NC}"
        return 0
    else
        echo -e "${RED}Test échoué. Sortie attendue '$expected_output' non trouvée.${NC}"
        echo "Sortie obtenue :"
        echo "$output"
        return 1
    fi
}

echo "Le testeur pourra prendre un certain temps veuillez lancer le test puis faire la correction normalement avant de regarder les resultats"

wait_for_keypress
# Test 1 : Test de base

# Test 2 : Scénario de mort
run_test "Scénario de mort" 4 310 200 200 "" "died" 5

# Test 3 : Avec nombre de repas spécifiéc
run_test "Avec nombre de repas" 5 800 200 200 7 "is eating" 10

# Ajoutez d'autres tests ici

# Test 4 : Test avec un grand nombre de philosophes
run_test "Grand nombre de philosophes" 100 1000 200 200 "" "is eating" 15

# Test 5 : Test avec des temps très courts
run_test "Temps très courts" 4 100 50 50 "" "died" 3

run_test "Test de base" 4 410 200 200 "" "is eating" 5
echo "Tous les tests sont terminés."