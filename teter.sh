#!/bin/bash

# Couleurs pour une meilleure lisibilité
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Fonction pour exécuter un test
run_test() {
    local test_name=$1
    local args=$2
    local expected_result=$3
    local timeout=$4

    echo -e "${YELLOW}Exécution du test: $test_name${NC}"
    echo "Commande: ./philo $args"
    
    output=$(timeout $timeout ./philo $args 2>&1)
    exit_code=$?
    
    if [ $exit_code -eq 124 ]; then
        echo -e "${RED}Test échoué: Timeout${NC}"
        return 1
    fi
    
    case "$expected_result" in
        "death")
            if echo "$output" | grep -q "died"; then
                local death_time=$(echo "$output" | grep "died" | head -n 1 | awk '{print $1}')
                local last_action_time=$(echo "$output" | tail -n 1 | awk '{print $1}')
                if (( last_action_time - death_time <= 10 )); then
                    echo -e "${GREEN}Test réussi: Un philosophe est mort et le programme s'est arrêté dans les 10ms${NC}"
                    return 0
                else
                    echo -e "${RED}Test échoué: Le programme a continué plus de 10ms après la mort d'un philosophe${NC}"
                    return 1
                fi
            else
                echo -e "${RED}Test échoué: Aucun philosophe n'est mort${NC}"
                return 1
            fi
            ;;
        "no_death")
            if echo "$output" | grep -q "died"; then
                echo -e "${RED}Test échoué: Un philosophe est mort alors qu'il ne devait pas${NC}"
                return 1
            else
                echo -e "${GREEN}Test réussi: Aucun philosophe n'est mort${NC}"
                return 0
            fi
            ;;
        "eat_count")
            local required_meals=$(echo $args | awk '{print $NF}')
            local eat_count=$(echo "$output" | grep -c "is eating")
            if [ $eat_count -ge $((required_meals * $(echo $args | awk '{print $1}') )) ]; then
                echo -e "${GREEN}Test réussi: Tous les philosophes ont mangé au moins $required_meals fois${NC}"
                return 0
            else
                echo -e "${RED}Test échoué: Les philosophes n'ont pas mangé suffisamment${NC}"
                return 1
            fi
            ;;
    esac
}

# Vérification de la présence de l'exécutable
if [ ! -f "./philo" ]; then
    echo -e "${RED}Erreur: L'exécutable 'philo' n'a pas été trouvé${NC}"
    exit 1
fi

# Compteur de tests
total_tests=0
passed_tests=0

# Test 1: Un philosophe doit mourir
((total_tests++))
if run_test "Un philosophe doit mourir" "1 800 200 200" "death" 5; then
    ((passed_tests++))
fi

# Test 2: Pas de mort avec suffisamment de temps
((total_tests++))
if run_test "Pas de mort" "5 800 200 200" "no_death" 5; then
    ((passed_tests++))
fi

# Test 3: Tous les philosophes doivent manger au moins 7 fois
((total_tests++))
if run_test "Tous mangent 7 fois" "6 800 200 300 100" "eat_count" 10; then
    ((passed_tests++))
fi

# Test 4: Test avec des valeurs limites
((total_tests++))
if run_test "Valeurs limites" "4 310 200 100" "death" 5; then
    ((passed_tests++))
fi

# Test 5: Test avec un grand nombre de philosophes
((total_tests++))
if run_test "Grand nombre de philosophes" "20 800 200 200" "no_death" 10; then
    ((passed_tests++))
fi

# Test 6: Test avec un seul repas
((total_tests++))
if run_test "Un seul repas" "5 800 200 200 1" "eat_count" 5; then
    ((passed_tests++))
fi

# Test 7: Test de mort rapide
((total_tests++))
if run_test "Mort rapide" "4 200 205 200" "death" 5; then
    ((passed_tests++))
fi

# Affichage du résultat final
echo -e "${YELLOW}Résumé des tests:${NC}"
echo -e "Tests réussis: ${GREEN}$passed_tests${NC}"
echo -e "Tests échoués: ${RED}$((total_tests - passed_tests))${NC}"
echo -e "Total des tests: ${YELLOW}$total_tests${NC}"

if [ $passed_tests -eq $total_tests ]; then
    echo -e "${GREEN}Tous les tests ont réussi !${NC}"
    exit 0
else
    echo -e "${RED}Certains tests ont échoué.${NC}"
    exit 1
fi