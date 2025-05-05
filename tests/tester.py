import os
import subprocess

# Open the file in append mode using the 'with' statement
def run_minishell_with_input(input_text):
    with open('res', "a+") as file:  # Open the file for appending
        minishell_process = subprocess.Popen(
            '/home/moel-oua/Desktop/minishell/minishell',  # Replace with the path to your minishell executable
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True  # This ensures we work with strings instead of byte data
        )

        for line in input_text:
            if(line == '' or line is None):
                continue
            print(line)
            if minishell_process.poll() is not None:  
                print("Minishell process exited unexpectedly.")
                break

            # Send the input line to minishell
            minishell_process.stdin.write(line + '\n')
            minishell_process.stdin.flush()  

            # Capture output from minishell
            output = minishell_process.stdout.readline()
            file.write("\n==========================\n")
            file.write(f"output : ")
            while output:
                file.write(f"{output}")  # Write output to the file
                print(output, end='')
                output = minishell_process.stdout.readline()
                if "in the garbage!" in output:
                    break

        # Close the stdin to signal the end of input
        minishell_process.stdin.close()

        # Wait for minishell to finish executing
        minishell_process.wait()

# Read the combined text from the file
def read_combined_text(file_path):
    with open(file_path, 'r', encoding='utf-8', errors='ignore') as file:
        return file.readlines()

# Main function
def main():
    combined_text_file = '/home/moel-oua/Desktop/minishell/tests/l'  # Path to your combined text file
    input_lines = read_combined_text(combined_text_file)
    print(input_lines)
    run_minishell_with_input(input_lines)

if __name__ == "__main__":
    main()
# import os

# def combine_text_files(root_dir, output_file):
#     with open(output_file, 'w', encoding="utf-8") as out_file:
#         for root, dirs, files in os.walk(root_dir):
#             for file in files:
#                 if file:
#                     file_path = os.path.join(root, file)
#                     try:
#                         with open(file_path, 'r', encoding="utf-8", errors='ignore') as in_file:
#                             out_file.write(in_file.read())  # Write contents of text file to output file
#                             out_file.write("\n\n")  # Add a newline between file contents
#                     except Exception as e:
#                         print(f"Could not read {file_path}: {e}")

# Example usage
# root_directory = '/home/moel-oua/goinfre/fuzz-dict' 
# output_filename = '/home/moel-oua/goinfre/combine.txt'

# combine_text_files(root_directory, output_filename)
