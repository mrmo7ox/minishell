import os

def combine_text_files(root_dir, output_file):
    with open(output_file, 'w', encoding="utf-8") as out_file:
        for root, dirs, files in os.walk(root_dir):
            for file in files:
                if file:
                    file_path = os.path.join(root, file)
                    try:
                        with open(file_path, 'r', encoding="utf-8", errors='ignore') as in_file:
                            out_file.write(in_file.read()) 
                            out_file.write("\n\n") 
                    except Exception as e:
                        print(f"Could not read {file_path}: {e}")

root_directory = '/home/moel-oua/goinfre/fuzz-dict' 
output_filename = '/home/moel-oua/goinfre/combine.txt'

combine_text_files(root_directory, output_filename)
