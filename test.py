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
        # Combine both commands into a single input
        full_input = f"export a=\"1                       4\"\n{command}\nexit\n"
        output, error = process.communicate(input=full_input, timeout=3)
        if(error):
                return "syntax error"
        new = ''
        for line in output.split('\n'):
            if('Minishell$>' not in line and 'exit' not in line):
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
                './minishell',
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
    test_input_path = './export_tests'
    result_output_path = './res'

    input_lines = read_input_lines(test_input_path)
    run_tests(input_lines, result_output_path)

if __name__ == "__main__":
    main()