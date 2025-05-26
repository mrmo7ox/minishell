# Shell Tests: Pipes, AND, OR, and Redirection (with Error Cases)

## 1. Pipe operator (`|`)

```sh
# Successful pipe
echo "hello" | tr 'a-z' 'A-Z'    # Output: HELLO

# Pipe with a command that fails (grep finds no match)
echo "hello" | grep "notfound"   # Output: (empty), exit code 1

# Pipe with a command that does not exist (error case)
echo "test" | nonexistentcmd     # Output: bash: nonexistentcmd: command not found
```

## 2. Logical AND (`&&`)

```sh
# Both succeed
echo "foo" && echo "bar"         # Output: foo\nbar onditional jump or move depends on uninitialised value(s)==519456==    at 0x406163: echo (in /home/ihamani/Desktop/minishell/minishell)


# First fails, second not executed
cat /nonexistentfile && echo "found"    # Output: cat: /nonexistentfile: No such file or directory

# First succeeds, second fails
echo "hi" && nonexistentcmd      # Output: hi\nbash: nonexistentcmd: command not found
```

## 3. Logical OR (`||`)

```sh
# First fails, second runs
cat /nonexistentfile || echo "fallback" # Output: cat: ... No such file or directory\nfallback

# First succeeds, second not run
echo "success" || echo "won't show"     # Output: success
```

## 4. Redirection (`>`, `>>`, `<`)

```sh
# Redirect stdout to a file
echo "save this" > testfile.txt

# Append to file
echo "add more" >> testfile.txt

# Redirect stdin from a file
cat < testfile.txt

# Error: redirect output to unwritable location (permission denied)
echo "fail" > /root/forbidden.txt      # Output: Permission denied (unless root)
```

## 5. Redirecting stderr (`2>`, `2>>`)

```sh
# Redirect stderr to a file
ls /notfound 2> error.log             # Output: (no stdout), error message in error.log

# Append stderr to file
ls /notfound 2>> error.log
```

## 6. Redirecting both stdout and stderr (`&>`)

```sh
# Both outputs to file
ls /notfound &> all.log               # all.log contains error message

# Pipe both stdout and stderr
(ls /etc /notfound) 2>&1 | tee output.log
```

## 7. Combining operators

```sh
# Pipe and redirect
echo "abc" | tee temp.txt > /dev/null   # temp.txt contains "abc", nothing on stdout

# AND with redirection
echo "ok" && echo "error" 1>&2         # ok to stdout, error to stderr

# OR with redirection (error case)
notfound || echo "ran fallback" > out.txt  # out.txt contains "ran fallback"
```

## 8. Error: File not found/input

```sh
# Input file does not exist
cat < missingfile.txt                # Output: cat: missingfile.txt: No such file or directory

# Try to redirect stdin from directory (error)
cat < /tmp                           # Output: cat: /tmp: Is a directory
```

---

Feel free to copy and adapt these tests for your own shell scripts or CI pipeline!