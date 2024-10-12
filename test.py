import subprocess
import time
import re

class Colors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

def print_colored(text, color):
    print(f"{color}{text}{Colors.ENDC}")

def run_test(test_number, command, expected):
    print_colored(f"\nTest {test_number}", Colors.HEADER)
    print_colored(f"Commande: {command}", Colors.OKBLUE)
    
    start_time = time.time()
    process = subprocess.Popen(command.split(), stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
    
    try:
        stdout, stderr = process.communicate(timeout=60)  # 60 secondes de timeout
    except subprocess.TimeoutExpired:
        process.kill()
        print_colored("ÉCHEC - Le programme n'a pas terminé dans le temps imparti", Colors.FAIL)
        return False
    
    end_time = time.time()
    execution_time = end_time - start_time
    
    print(f"Temps d'exécution: {execution_time:.2f} secondes")
    
    # Compter les occurrences de chaque action
    died_count = stdout.lower().count("died")
    eating_count = stdout.lower().count("is eating")
    sleeping_count = stdout.lower().count("is sleeping")
    thinking_count = stdout.lower().count("is thinking")
    
    # Afficher les résultats obtenus et attendus
    print_colored("Résultats obtenus vs attendus:", Colors.BOLD)
    print(f"Morts     : {died_count:3d} vs {expected['deaths']:3d}")
    print(f"Repas     : {eating_count:3d} vs {expected['meals']:3d}")
    print(f"Sommeils  : {sleeping_count:3d} vs {expected['sleeps']:3d}")
    print(f"Réflexions: {thinking_count:3d} vs {expected['thinks']:3d}")
    
    # Vérifier si les résultats correspondent aux attentes
    success = (died_count == expected['deaths'] and
               eating_count == expected['meals'] and
               sleeping_count == expected['sleeps'] and
               thinking_count == expected['thinks'])
    
    if success:
        print_colored("SUCCÈS - Tous les compteurs correspondent aux attentes", Colors.OKGREEN)
    else:
        print_colored("ÉCHEC - Certains compteurs ne correspondent pas aux attentes", Colors.FAIL)
    
    return success

def main():
    tests = [
        ("1", "./philo 1 800 200 200", {'deaths': 1, 'meals': 0, 'sleeps': 0, 'thinks': 0}),
        ("2", "./philo 5 800 200 200 7", {'deaths': 0, 'meals': 35, 'sleeps': 35, 'thinks': 35}),
        ("3", "./philo 4 410 200 200 20", {'deaths': 0, 'meals': 80, 'sleeps': 80, 'thinks': 80}),
        ("4", "./philo 4 310 200 -100", {'deaths': 0, 'meals': 0, 'sleeps': 0, 'thinks': 0}),
        ("5", "./philo 2 125 60 60 100", {'deaths': 0, 'meals': 200, 'sleeps': 200, 'thinks': 200}),
        ("6", "./philo 5 800 211 600", {'deaths': 1, 'meals': 5, 'sleeps': 5, 'thinks': 0}),
    ]

    successes = 0
    total_tests = len(tests)

    for test in tests:
        if run_test(*test):
            successes += 1

    print_colored(f"\nRésultats finaux: {successes}/{total_tests} tests réussis", Colors.BOLD)
    if successes == total_tests:
        print_colored("Tous les tests ont réussi!", Colors.OKGREEN)
    elif successes == 0:
        print_colored("Tous les tests ont échoué.", Colors.FAIL)
    else:
        print_colored("Certains tests ont échoué.", Colors.WARNING)

if __name__ == "__main__":
    main()