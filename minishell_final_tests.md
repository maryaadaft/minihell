# Minishell Final Test Suite

---

## SECTION 1 — Prompt and Basic Input

```
(just press enter)
```
Expected: prompt reappears, no error

```
echo hello
```
Expected: `hello`

---

## SECTION 2 — echo

```
echo hello
```
`hello`

```
echo hello world
```
`hello world`

```
echo -n hello
```
`hello` (no newline after)

```
echo -n
```
(nothing printed, no newline)

```
echo
```
(empty line)

```
echo ""
```
(empty line)

```
echo ''
```
(empty line)

```
echo "hello world"
```
`hello world`

```
echo 'hello world'
```
`hello world`

```
echo "hello"world
```
`helloworld`

```
echo 'hello'"world"
```
`helloworld`

```
echo "it's a test"
```
`it's a test`

```
echo 'it"s a test'
```
`it"s a test`

```
echo "   spaces   "
```
`   spaces   `

```
echo '   spaces   '
```
`   spaces   `

---

## SECTION 3 — pwd

```
pwd
```
Expected: your current directory

```
pwd ignored_arg
```
Expected: your current directory (arg silently ignored)

---

## SECTION 4 — cd

```
cd /tmp
pwd
```
`/tmp`

```
cd /
pwd
```
`/`

```
cd
pwd
```
`/home/maryaada`

```
cd /nonexistent_path_xyz
```
Expected: error message, no such file or directory

```
cd /tmp
cd ..
pwd
```
`/`

---

## SECTION 5 — env

```
env
```
Expected: all environment variables in KEY=VALUE format

---

## SECTION 6 — export

```
export
```
Expected: all vars as `declare -x KEY="VALUE"` sorted alphabetically

```
export TESTVAR=hello
```
(no output)

```
export
```
Expected: TESTVAR appears in list

```
export TESTVAR=newvalue
export | grep TESTVAR
```
`declare -x TESTVAR="newvalue"`

```
export EMPTYVAR=
export | grep EMPTYVAR
```
`declare -x EMPTYVAR=""`

```
export NOVALUE
export | grep NOVALUE
```
`declare -x NOVALUE`

```
export A=1 B=2 C=3
export | grep -E "^declare -x [ABC]="
```
```
declare -x A="1"
declare -x B="2"
declare -x C="3"
```

```
export 1INVALID=foo
```
`minishell: export: '1INVALID=foo': not a valid identifier`

```
export =foo
```
`minishell: export: '=foo': not a valid identifier`

```
export _VALID=yes
export | grep _VALID
```
`declare -x _VALID="yes"`

```
unset TESTVAR EMPTYVAR NOVALUE A B C _VALID
```
(no output, all removed)

---

## SECTION 7 — unset

```
export FOO=bar
env | grep FOO
```
`FOO=bar`

```
unset FOO
env | grep FOO
```
(no output)

```
unset NONEXISTENT
```
(no output, no error)

```
unset PATH
env | grep PATH
```
(no output — PATH gone)

```
export PATH=/usr/bin:/bin
env | grep PATH
```
`PATH=/usr/bin:/bin`

---

## SECTION 8 — exit

```
exit 0
```
Shell exits. In outer terminal: `echo $?` shows `0`

```
exit 42
```
Shell exits. In outer terminal: `echo $?` shows `42`

```
exit 1 2 3
pwd
```
```
exit
minishell: exit: too many arguments
/your/path
```
Shell does NOT exit

```
exit abc
```
```
exit
minishell: exit: abc: numeric argument required
```
Exits with code 2

```
exit 256
```
Shell exits. In outer terminal: `echo $?` shows `0` (wraps around)

---

## SECTION 9 — external commands

```
ls
```
Expected: directory listing

```
ls -la
```
Expected: long listing

```
/bin/ls
```
Expected: directory listing via absolute path

```
whoami
```
Expected: your username

```
nonexistentcommand
```
`minishell: command not found`

```
/nonexistent/path/binary
```
`minishell: command not found`

---

## SECTION 10 — exit status

```
ls > /dev/null
echo $?
```
`0`

```
nonexistentcommand
echo $?
```
`127`

```
ls /nonexistent_path_xyz
echo $?
```
`2`

```
echo $?
echo $?
```
Both print `0`

---

## SECTION 11 — $VAR expansion

```
echo $HOME
```
`/home/maryaada`

```
echo $USER
```
`maryaada`

```
echo $NONEXISTENT
```
(empty line)

```
echo "$HOME"
```
`/home/maryaada`

```
echo '$HOME'
```
`$HOME`

```
echo "home is $HOME yes"
```
`home is /home/maryaada yes`

```
export MYVAR=hello
echo $MYVAR
```
`hello`

```
echo "$MYVAR world"
```
`hello world`

```
echo '$MYVAR world'
```
`$MYVAR world`

```
unset MYVAR
echo $MYVAR
```
(empty line)

```
ls > /dev/null
echo $?
echo "$?"
echo '$?'
```
```
0
0
$?
```

---

## SECTION 12 — quotes with expansion

```
echo "hello $USER"
```
`hello maryaada`

```
echo 'hello $USER'
```
`hello $USER`

```
echo "$HOME/$USER"
```
`/home/maryaada/maryaada`

```
export VAR="hello world"
echo $VAR
echo "$VAR"
echo '$VAR'
unset VAR
```
```
hello world
hello world
$VAR
```

```
echo ""$HOME
```
`/home/maryaada`

```
echo "$HOME""$USER"
```
`/home/maryaadamaryaada`

---

## SECTION 13 — output redirection

```
echo hello > /tmp/ms_test.txt
cat /tmp/ms_test.txt
```
`hello`

```
echo world > /tmp/ms_test.txt
cat /tmp/ms_test.txt
```
`world` (overwritten)

```
echo test > /nonexistent_dir/file.txt
```
`minishell: /nonexistent_dir/file.txt: No such file or directory`

```
> /tmp/ms_empty.txt
ls -la /tmp/ms_empty.txt
```
Expected: file exists, 0 bytes

---

## SECTION 14 — append redirection

```
echo line1 > /tmp/ms_append.txt
echo line2 >> /tmp/ms_append.txt
echo line3 >> /tmp/ms_append.txt
cat /tmp/ms_append.txt
```
```
line1
line2
line3
```

```
>> /tmp/ms_append.txt
cat /tmp/ms_append.txt
```
(content unchanged)

---

## SECTION 15 — input redirection

```
echo "hello world" > /tmp/ms_in.txt
cat < /tmp/ms_in.txt
```
`hello world`

```
wc -w < /tmp/ms_in.txt
```
`2`

```
< /tmp/ms_in.txt
```
(no output, exit 0)

```
< /tmp/ms_nonexistent_xyz.txt
echo $?
```
```
minishell: /tmp/ms_nonexistent_xyz.txt: No such file or directory
1
```

---

## SECTION 16 — combined redirections

```
echo "combined" > /tmp/ms_in.txt
cat < /tmp/ms_in.txt > /tmp/ms_out.txt
cat /tmp/ms_out.txt
```
`combined`

```
echo hello > /tmp/ms_a.txt > /tmp/ms_b.txt
cat /tmp/ms_a.txt
cat /tmp/ms_b.txt
```
```
(empty)
hello
```

---

## SECTION 17 — pipes

```
echo hello | cat
```
`hello`

```
echo hello | cat | cat | cat
```
`hello`

```
echo hello world | wc -w
```
`2`

```
echo hello | grep hello
echo $?
```
```
hello
0
```

```
echo hello | grep nonexistent
echo $?
```
```
(no output)
1
```

```
ls | wc -l
```
Expected: number of items in current directory

```
ls | sort | head -3
```
Expected: first 3 items alphabetically

```
echo hello | cat > /tmp/ms_pipe_out.txt
cat /tmp/ms_pipe_out.txt
```
`hello`

---

## SECTION 18 — pipes with builtins

```
env | grep PATH
```
Expected: PATH line

```
env | grep HOME
```
Expected: HOME line

```
env | sort | head -5
```
Expected: first 5 env vars alphabetically

```
echo hello | wc -c
```
`6`

---

## SECTION 19 — heredoc

```
cat << EOF
hello
world
EOF
```
```
hello
world
```

```
wc -l << EOF
a
b
c
EOF
```
`3`

```
cat << 'EOF'
$HOME
$USER
EOF
```
```
$HOME
$USER
```
(no expansion — quoted delimiter)

```
cat << EOF
$HOME
$USER
EOF
```
```
/home/maryaada
maryaada
```
(expansion — unquoted delimiter)

```
export A=newjeans
cat << $A
hi
there
$A
```
```
hi
there
```
(delimiter is literal `$A`, stops on `$A` not `newjeans`)

```
cat << EOF | grep hello
hello
world
EOF
```
`hello`

```
cat << EOF > /tmp/ms_heredoc.txt
content here
EOF
cat /tmp/ms_heredoc.txt
```
`content here`

---

## SECTION 20 — heredoc ctrl-C

```
cat << EOF
(press ctrl-C here)
```
Expected: cancels heredoc, returns to prompt

```
echo $?
```
`1` or `130`

---

## SECTION 21 — syntax errors

```
|
```
`minishell: syntax error near unexpected token '|'`

```
| ls
```
`minishell: syntax error near unexpected token '|'`

```
ls |
```
`minishell: syntax error near unexpected token '|'`

```
ls | | grep foo
```
`minishell: syntax error near unexpected token '||'`

```
>
```
`minishell: syntax error near unexpected token`

```
<
```
`minishell: syntax error near unexpected token`

```
ls >>
```
`minishell: syntax error near unexpected token`

```
echo "unclosed
```
`minishell: syntax error: unclosed quote`

```
echo 'unclosed
```
`minishell: syntax error: unclosed quote`

---

## SECTION 22 — signals

```
sleep 5
(press ctrl-C during sleep)
echo $?
```
```
^C
130
```

```
(press ctrl-D at empty prompt)
```
Expected: prints `exit` and shell closes cleanly

```
(press ctrl-\ at empty prompt)
```
Expected: nothing happens, prompt stays

---

## SECTION 23 — edge cases

```
echo $HOME$USER
```
`/home/maryaadamaryaada`

```
echo $HOME/$USER
```
`/home/maryaada/maryaada`

```
cd $HOME
pwd
```
`/home/maryaada`

```
ls | grep nonexistent
echo $?
```
```
(no output)
1
```

```
echo hello | cat > /tmp/ms_edge.txt
cat /tmp/ms_edge.txt
rm /tmp/ms_edge.txt
```
```
hello
(file removed)
```

---

## SECTION 24 — cleanup

```
rm -f /tmp/ms_test.txt /tmp/ms_in.txt /tmp/ms_out.txt
rm -f /tmp/ms_a.txt /tmp/ms_b.txt /tmp/ms_empty.txt
rm -f /tmp/ms_append.txt /tmp/ms_heredoc.txt /tmp/ms_pipe_out.txt
```

---

## AUTOMATED SCRIPT

Save as `test.sh` then run:

```
./minishell < test.sh
```

Compare with:

```
bash --norc --noprofile < test.sh
```

Output should be identical.

```bash
echo hello
echo $HOME
echo $USER
ls /tmp > /dev/null
echo $?
nonexistentcmd
echo $?
echo hello > /tmp/ms_auto.txt
cat /tmp/ms_auto.txt
echo append >> /tmp/ms_auto.txt
cat /tmp/ms_auto.txt
cat < /tmp/ms_auto.txt
echo hello | cat
echo hello | wc -w
export MSTEST=working
echo $MSTEST
unset MSTEST
echo $MSTEST
pwd
cd /tmp
pwd
cd -
pwd
ls | wc -l
env | grep HOME
exit 42
```

---

## VALGRIND CHECK

```
echo "echo hello
ls
exit" | valgrind --leak-check=full --show-leak-kinds=definite ./minishell 2>&1 | grep -E "definitely lost|ERROR SUMMARY"
```

Expected:
```
ERROR SUMMARY: 0 errors from 0 contexts
```
