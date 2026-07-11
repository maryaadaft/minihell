#!/bin/bash

echo "===== BASIC COMMANDS ====="

{
	echo "echo hello world"
	echo "pwd"
	echo "ls"
	echo "not_a_command"
	echo "echo \$?"
} | ./minishell


echo
echo "===== ENVIRONMENT ====="

{
	echo "env | grep PATH"
	echo "echo \$USER"
	echo "echo \$HOME"
} | ./minishell


echo
echo "===== EXIT STATUS ====="

{
	echo "ls"
	echo "echo \$?"
	echo "ls nonexistent"
	echo "echo \$?"
	echo "notfound"
	echo "echo \$?"
} | ./minishell


echo
echo "===== REDIRECTIONS ====="

{
	echo "echo hello > test_file"
	echo "cat test_file"
	echo "echo append >> test_file"
	echo "cat test_file"
	echo "rm test_file"
} | ./minishell


echo
echo "===== INPUT REDIRECTION ====="

{
	echo "echo input_test > input_file"
	echo "cat < input_file"
	echo "rm input_file"
} | ./minishell


echo
echo "===== PIPES ====="

{
	echo "echo hello | cat"
	echo "ls | wc -l"
	echo "cat /etc/passwd | grep root"
} | ./minishell


echo
echo "===== HEREDOC ====="

{
	echo "cat << EOF"
	echo "hello"
	echo "world"
	echo "EOF"
} | ./minishell


echo
echo "===== HEREDOC EXPANSION ====="

{
	echo "cat << EOF"
	echo "\$USER"
	echo "\$HOME"
	echo "EOF"
} | ./minishell


echo
echo "===== HEREDOC NO EXPANSION ====="

{
	echo "cat << 'EOF'"
	echo "\$USER"
	echo "\$HOME"
	echo "EOF"
} | ./minishell


echo
echo "===== MULTIPLE HEREDOC ====="

{
	echo "cat << A << B"
	echo "first"
	echo "A"
	echo "second"
	echo "B"
} | ./minishell


echo
echo "===== BUILTINS ====="

{
	echo "echo hello"
	echo "pwd"
	echo "env"
	echo "export TEST=value"
	echo "echo \$TEST"
	echo "unset TEST"
	echo "echo \$TEST"
} | ./minishell


echo
echo "===== QUOTES ====="

{
	echo "echo 'hello world'"
	echo 'echo "hello world"'
	echo "echo \"\$USER\""
} | ./minishell


echo
echo "===== EXIT ====="

echo "exit" | ./minishell

echo
echo "DONE"