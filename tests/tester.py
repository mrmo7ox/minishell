import os
import colorama
with open("tests/inputs", "r") as f:
    inputs = f.readlines()
color = colorama.Fore
def test(inputs):
    for index , value in enumerate(inputs):
        print(color.GREEN + f"==============[{index}]==============" + color.RESET)
        cmd = f'./minishell "{value.strip()}"'
        process = os.popen(cmd).read()
        print(f"{cmd.strip()} =>\n {process.strip()}")

test(inputs)
