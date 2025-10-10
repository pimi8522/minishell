#!/bin/bash

# --- CONFIG ---
MINISHELL_PATH="./minishell"
TEST_FILE="test_suite.txt"
MINISHELL_OUT="minishell_output.log"
BASH_OUT="bash_output.log"
DIFF_OUT="diff_report.log"

# --- COLORS ---
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# --- SETUP ---
# Ensure minishell executable exists
if [ ! -f "$MINISHELL_PATH" ]; then
    echo -e "${RED}Minishell executable not found at $MINISHELL_PATH${NC}"
    echo -e "${YELLOW}Please compile the project first (e.g., 'make').${NC}"
    exit 1
fi

# Clean up previous logs
rm -f "$MINISHELL_OUT" "$BASH_OUT" "$DIFF_OUT"

# --- TESTER ---
run_test() {
    command=$1
    
    echo -e "${YELLOW}Testing command:${NC} $command"

    # Run in minishell
    echo "$command" | "$MINISHELL_PATH" > minishell_stdout.tmp 2> minishell_stderr.tmp
    minishell_status=$?

    # Run in bash
    # We use a subshell to prevent 'exit' from closing the script
    (eval "$command") > bash_stdout.tmp 2> bash_stderr.tmp
    bash_status=$?

    # Combine stdout and stderr for comparison
    cat minishell_stdout.tmp minishell_stderr.tmp > "$MINISHELL_OUT"
    cat bash_stdout.tmp bash_stderr.tmp > "$BASH_OUT"

    # Compare outputs
    diff_output=$(diff -u "$MINISHELL_OUT" "$BASH_OUT")

    # Check results
    if [ "$minishell_status" -eq "$bash_status" ] && [ -z "$diff_output" ]; then
        echo -e "${GREEN}PASS${NC}"
    else
        echo -e "${RED}FAIL${NC}"
        echo "---" >> "$DIFF_OUT"
        echo "COMMAND: $command" >> "$DIFF_OUT"
        echo "  EXIT CODES -> Minishell: $minishell_status | Bash: $bash_status" >> "$DIFF_OUT"
        if [ -n "$diff_output" ]; then
            echo "  OUTPUT DIFF:" >> "$DIFF_OUT"
            echo "$diff_output" >> "$DIFF_OUT"
        fi
        echo "" >> "$DIFF_OUT"
    fi

    # Cleanup temp files
    rm -f minishell_stdout.tmp minishell_stderr.tmp bash_stdout.tmp bash_stderr.tmp
}

# --- MAIN ---
while IFS= read -r line || [[ -n "$line" ]]; do
    # Ignore comments and empty lines
    if [[ "$line" =~ ^\s*# ]] || [[ -z "$line" ]]; then
        continue
    fi
    run_test "$line"
done < "$TEST_FILE"

# --- REPORT ---
if [ -f "$DIFF_OUT" ]; then
    echo -e "\n${RED}--- TEST FAILURES DETECTED ---${NC}"
    echo -e "See ${YELLOW}diff_report.log${NC} for details."
    cat "$DIFF_OUT"
else
    echo -e "\n${GREEN}--- ALL TESTS PASSED ---${NC}"
fi