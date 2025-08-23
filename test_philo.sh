#!/bin/bash

PHILO=./philo   # caminho do binário

run_test() {
    desc=$1
    cmd=$2
    expect=$3  # "die" ou "no_die"

    echo -n "🔹 $desc ... "

    output=$($cmd 2>&1 | head -n 5)  # pega primeiras 5 linhas
    died=$(echo "$output" | grep -c "died")

    if [[ "$expect" == "die" && $died -gt 0 ]]; then
        echo "✅ (morreu como esperado)"
    elif [[ "$expect" == "no_die" && $died -eq 0 ]]; then
        echo "✅ (ninguém morreu)"
    else
        echo "❌ (resultado inesperado)"
        echo "   comando: $cmd"
        echo "   saída: $output"
    fi
}

echo "======================="
echo " Testes Philosophers 🧵"
echo "======================="

# --- Sem must_eat ---
run_test "1 filósofo deve morrer"      "$PHILO 1 800 200 200" die
run_test "2 filósofos não morrem"      "$PHILO 2 800 200 200" no_die
run_test "5 filósofos não morrem"      "$PHILO 5 800 200 200" no_die
run_test "5 filósofos morrem rápido"   "$PHILO 5 310 200 200" die

# --- Com must_eat ---
run_test "2 filósofos, must_eat=3"     "$PHILO 2 800 200 200 3" no_die
run_test "5 filósofos, must_eat=7"     "$PHILO 5 800 200 200 7" no_die
run_test "5 filósofos, must_eat=1"     "$PHILO 5 800 200 200 1" no_die
run_test "5 filósofos, must_eat=3, morrem" "$PHILO 5 310 200 200 3" die

# --- Stress ---
run_test "100 filósofos must_eat=1"    "$PHILO 100 800 200 200 1" no_die
run_test "200 filósofos sem must_eat"  "$PHILO 200 800 200 200" no_die
run_test "50 filósofos time_to_die curto" "$PHILO 50 300 100 100" die

echo ""
echo "======================="
echo "   Testes concluídos   "
echo "======================="

