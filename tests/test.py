import subprocess

def run_minishell_command(command):
    process = subprocess.Popen(
        ['/home/moel-oua/Desktop/minishell/minishell'],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )

    # Send the command and exit
    out, err = process.communicate(input=command + "\nexit\n")

    return out.strip(), err.strip(), process.returncode

# Example usage
out, err, code = run_minishell_command("echo hello")
print("STDOUT:", out)
print("STDERR:", err)
print("Exit Code:", code)
