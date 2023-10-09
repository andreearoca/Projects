import json
import os
import sys


def create_files_from_dict(path, dictionary, high):
    result = ""
    for element in dictionary:
        if type(dictionary[element]) is dict:
            path1 = os.path.join(path, element)
            os.mkdir(path1)
            result += "---" * high + element + "\n"
            result += create_files_from_dict(path1, dictionary[element], high + 1)
        else:
            path1 = os.path.join(path, element)
            with open(path1, 'w') as f:
                f.write(dictionary[element])
            f.close()
            result += "---" * high + element + ": " + dictionary[element] + "\n"
    return result


if len(sys.argv) < 3:
    raise Exception("Not enough arguments!")
elif len(sys.argv) > 3:
    raise Exception("Too many arguments!")

if not os.path.isfile(sys.argv[2]):
    raise Exception("[ERROR] - file not found")
if not os.path.isdir(sys.argv[1]):
    raise Exception("[ERROR] - directory not found")

with open(sys.argv[2]) as json_file:
    dictionary = json.load(json_file)
json_file.close()

root_folder_path = sys.argv[1]

print(root_folder_path)
print(create_files_from_dict(root_folder_path, dictionary, 1))
