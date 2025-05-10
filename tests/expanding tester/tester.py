import subprocess

def run_command_with_shell(shell_path, command):
    process = subprocess.Popen(
        shell_path,
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )

    try:
        output, error = process.communicate(input=command + '\nexit\n', timeout=3)
        if( ">" in output or error):
                return "syntax error"
        new = ''
        for line in output.split('\n'):
            if('Minishell' not in line and 'exit' not in line):
                new += line
        return (new)
    except subprocess.TimeoutExpired:
        process.kill()
        return "[timeout]"

def run_tests(commands, result_file_path):
    with open(result_file_path, "w") as result_file:
        res = []
        for line in commands:
            line = line.strip()
            if not line:
                continue

            result_file.write(f"{line.strip()}")
            line = f"echo {line}"
            minishell_output = run_command_with_shell(
                '/home/moel-oua/Desktop/minishell/minishell',
                line
            )
            res.append(minishell_output)
            result_file.write(f":[{minishell_output.strip()}]")

            bash_output = run_command_with_shell('bash', line)
            res.append(bash_output)
            result_file.write(f":[{bash_output.strip()}]")
            if(res[0] == res[1]):
                result_file.write("[✅]\n")
            else:
                result_file.write("[❌]\n")
            res.clear()
            result_file.write("-" * 40 + "\n")

def read_input_lines(file_path):
    with open(file_path, "r", encoding="utf-8", errors="ignore") as f:
        return f.readlines()

def main():
    test_input_path = '/home/moel-oua/Desktop/minishell/tests/export_tests'
    result_output_path = '/home/moel-oua/Desktop/minishell/tests/res'

    input_lines = read_input_lines(test_input_path)
    run_tests(input_lines, result_output_path)

if __name__ == "__main__":
    main()
