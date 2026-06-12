#!/bin/bash

MINISHELL="./minishell"
PASS=0
FAIL=0

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

run_test()
{
	local description="$1"
	local input="$2"
	local expect_error="$3"  # 1 = expect error, 0 = expect success

	output=$(echo "$input" | $MINISHELL 2>&1)
	exit_code=$?

	if [ "$expect_error" -eq 1 ]; then
		# we expect an error message or non-zero exit
		if echo "$output" | grep -qi "syntax error\|unexpected token\|unclosed\|error" || [ $exit_code -ne 0 ]; then
			echo -e "${GREEN}[PASS]${NC} $description"
			PASS=$((PASS + 1))
		else
			echo -e "${RED}[FAIL]${NC} $description"
			echo -e "       input:  '$input'"
			echo -e "       output: '$output'"
			FAIL=$((FAIL + 1))
		fi
	else
		# we expect success (no error)
		if ! echo "$output" | grep -qi "syntax error\|unexpected token\|unclosed\|error"; then
			echo -e "${GREEN}[PASS]${NC} $description"
			PASS=$((PASS + 1))
		else
			echo -e "${RED}[FAIL]${NC} $description"
			echo -e "       input:  '$input'"
			echo -e "       output: '$output'"
			FAIL=$((FAIL + 1))
		fi
	fi
}

echo -e "${YELLOW}========================================${NC}"
echo -e "${YELLOW}       MINISHELL SYNTAX TESTS           ${NC}"
echo -e "${YELLOW}========================================${NC}"

# --- PIPE ERRORS ---
echo ""
echo -e "${YELLOW}--- Pipe Errors ---${NC}"
run_test "pipe at the start"        "| echo"       1
run_test "pipe at the end"          "echo |"       1
run_test "two consecutive pipes"    "echo | | cat" 1
run_test "pipe alone"               "|"            1

# --- REDIRECTION ERRORS ---
echo ""
echo -e "${YELLOW}--- Redirection Errors ---${NC}"
run_test "redirect out alone"           ">"           1
run_test "append alone"                 ">>"          1
run_test "redirect in alone"            "<"           1
run_test "heredoc alone"                "<<"          1
run_test "two redirects no command"     "> > file"   1
run_test "consecutive redirects"        "echo > > file" 1

# --- QUOTE ERRORS ---
echo ""
echo -e "${YELLOW}--- Quote Errors ---${NC}"
run_test "unclosed double quote"    'echo "hello'  1
run_test "unclosed single quote"    "echo 'hello"  1

# --- GENERAL (should NOT error) ---
echo ""
echo -e "${YELLOW}--- General (expect no error) ---${NC}"
run_test "empty input"         ""       0
run_test "only spaces"         "   "    0

# --- VALID COMMANDS (should NOT error) ---
echo ""
echo -e "${YELLOW}--- Valid Commands (expect no error) ---${NC}"
run_test "simple command"           "echo hello"           0
run_test "pipe between commands"    "echo hello | cat"     0
run_test "redirect out"             "echo hello > /dev/null" 0
run_test "redirect in"              "cat < /dev/null"      0
run_test "append"                   "echo hi >> /dev/null" 0
run_test "double quotes"            'echo "hello world"'   0
run_test "single quotes"            "echo 'hello world'"   0

# --- SUMMARY ---
echo ""
echo -e "${YELLOW}========================================${NC}"
echo -e "  ${GREEN}PASSED: $PASS${NC}"
echo -e "  ${RED}FAILED: $FAIL${NC}"
echo -e "${YELLOW}========================================${NC}"