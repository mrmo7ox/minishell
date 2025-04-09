import os
import colorama

colorama.init()
with open("tests/inputs", "r") as f:
    inputs = f.readlines()
color = colorama.Fore
def test(inputs):
    d = 0
    for index, value in enumerate(inputs):
        print(color.GREEN + f"==============[{index}]==============" + color.RESET)
        cmd = f'./minishell "{value.strip()}"'
        process = os.popen(cmd).read().strip()
        print(f"{cmd.strip()} =>\n {process}")

        if "syntax error" not in process:
            print(color.RED + "False" + color.RESET)
            d += 1


    if d != 0:
        print(color.RED + f"Failed {d} test(s)" + color.RESET)
    else:
        print(color.GREEN + "All tests passed!" + color.RESET)

test(inputs)