import os
def remove_lab(folder_path):
    files = os.listdir(folder_path)

    for file in files:
        if os.path.isfile(os.path.join(folder_path, file)) and 'lab' in file :
                new_name = file.replace('lab', '')
                os.rename(os.path.join(folder_path, file), os.path.join(folder_path, new_name))
                print(f'Renamed: {file} -> {new_name}')


folder_path = '/home/niranjan/code/OS_assignment/OS_Lab_2'
remove_lab(folder_path)