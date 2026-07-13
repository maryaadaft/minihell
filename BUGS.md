## Fixed

| # | Bug | Commit |
|---|----|--------|
| 1 | `export VAR` (no `=`) then use → use-after-free / double-free | `d1afc4c` |
| 2 | `cd` with `HOME` unset → SEGV | `e5d9e3c` |
| 3 | Redirection-only pipeline element (`> f \| cat`) → SEGV | `c458670` |
| 4 | SEGV on malloc failure (memset before NULL check) | `371a51b` |
| 5 | Unterminated heredoc at EOF → infinite hang | `b006392` |
| 6 | Relative-path commands (`./x`, `dir/x`) never executed | `1c10485` |
| 7 | Makefile `CFLAGs` typo → no compiler flags applied | `4406e91` |
| 8 | `$?` never updated by builtins / syntax errors | `7e17f5e` |
| 9 | Heredoc delimiter got variable-expanded | `e5ade3a` |
| 10 | Empty unquoted expansion ran as an empty command | `4dcba6a` |
| 11 | Unchecked `pipe()`/`fork()` → silently corrupted pipeline | `97941e4` |
| 12 | Pipeline children ignored SIGQUIT (ctrl-\ dead) | `f932a90` |
| 13 | `exit` with huge argument exited 0 instead of erroring 2 | `a40d08e` |
| 14 | `env` printed `VAR=(null)` for value-less exports | `1301a4c` |
| 15 | Heredoc EOF warning wrote one stray byte | `736021d` |
| 16 | `exit` leaked 2 `dup()` backup fds | `3df0d7e` |
| 17 | `exit > file` still leaked its 2 backup fds | `177e2ab` |
| 18 | `cd` updated `PWD`/`OLDPWD` even when `chdir` failed | `e58b2c7` |
| 19 | `cd a b` (too many args) accepted silently | `37f2cf6` |
| 20 | `echo -nnn hi` didn't collapse combined `-n` flags | `943f805` |
| 21 | `pwd -x` printed an error but left `$?` at 0 | `c10f1fc` |
| 22 | Syntax-error color codes went to stdout, text to stderr | `d1fb27e` |
| 23 | `$$` used `getpid()`, not on the allowed-function list | `93fbc3e` |

### Repro commands

**1** before: heap-use-after-free
```sh
printf 'export PATH\nenv\n' | ./minishell
```

**2** before: SEGV
```sh
printf 'unset HOME\ncd\n' | ./minishell
```

**3** before: SEGV
```sh
printf '> /tmp/f | cat\n' | ./minishell
```

**4** before: SEGV (needs a malloc-failure fault injector)
```sh
LD_PRELOAD=./failmalloc.so FAIL_AT=1 ./minishell
```

**5** before: hangs forever
```sh
printf 'cat << X\nabc\n' | ./minishell
```

**6** before: "command not found"
```sh
printf './rp/go.sh\n' | ./minishell
```

**7** before: objects built with no flags
```sh
make -n | grep -- -Wall
```

**8** before: `$?` = 2 (bash: 0)
```sh
printf 'ls /nope\necho hi\necho $?\n' | ./minishell
```

**9** before: heredoc ends at `X` instead of `$D`
```sh
printf 'export D=X\ncat << $D\nabc\nX\n' | ./minishell
```

**10** before: "command not found", `$?=127`
```sh
printf '$NOSUCHVAR\necho $?\n' | ./minishell
```

**11** before: silent data loss, `$?=0` (needs a fork-failure fault injector)
```sh
LD_PRELOAD=./failfork.so FAIL_FORK=1 ./minishell <<< 'echo a | cat'
```

**12** before: child survives ctrl-\
```sh
./minishell <<< 'cat | cat' &
kill -QUIT $(pgrep -n cat)
```

**13** before: `$?` = 0
```sh
printf 'exit 99999999999999999999\n' | ./minishell; echo $?
```

**14** before: prints `BRANDNEW=(null)`
```sh
printf 'export BRANDNEW\nenv\n' | ./minishell
```

**15** before: 1 stray NUL byte
```sh
printf 'cat << X\nabc\n' | ./minishell 2>err
tr -dc '\0' < err | wc -c
```

**16** before: fds 3/4 left open
```sh
printf 'echo hi\nexit\n' | valgrind --track-fds=yes ./minishell
```

## Not fixed (known, deliberate)

| # | Bug                                                                    |
|---|------------------------------------------------------------------------|
| H | Norminette not done :skull: (style compliance, not a runtime bug)     |
