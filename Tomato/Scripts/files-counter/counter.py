import os

SLN_DIR = os.path.dirname(os.path.dirname(os.getcwd()))
EXCLUDE_DIRS = ('Build', '.vs', 'Scripts', 'dependencies')


count = 0
def iterate_through_dir(path):
    global count
    for file in os.listdir(path):
        filepath = os.path.join(path, file)
        if os.path.isdir(filepath):
            if file not in EXCLUDE_DIRS:
                iterate_through_dir(filepath)
        else:
            if file.endswith('.h') or file.endswith('.cpp') or file.endswith('.glsl') or file.endswith('.hlsl'):
                print(file)
                f = open(filepath, 'r')
                lines = f.readlines()
                count += len(lines)
                
iterate_through_dir(SLN_DIR)
print('There are {0} lines in all the .h, .cpp, .glsl and .hlsl files'.format(count))
input("Press enter to close...")