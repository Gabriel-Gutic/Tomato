import os
import shutil

project_name = input("Project Name: ")

DATA_PATH = os.path.join(os.path.abspath(os.path.join(__file__, "..")), "data")
APPS_PATH = os.path.join(os.path.abspath(os.path.join(__file__, "../../..")), "Apps")
SLN_DIR = os.path.join(APPS_PATH, project_name)
PROJECT_DIR = os.path.join(SLN_DIR, project_name)

if os.path.exists(SLN_DIR):
    print("Project with name '{0}' already exist!".format(SLN_DIR))
    input("Press enter to close")
    exit()

os.mkdir(SLN_DIR)
os.mkdir(PROJECT_DIR)
shutil.copytree(os.path.join(DATA_PATH, "assets"), os.path.join(PROJECT_DIR, "assets"))

premake_template = open(os.path.join(DATA_PATH, "premake/premake.txt"), "r")
premake_file = open(os.path.join(SLN_DIR, "premake5.lua"), "w")

template = premake_template.read()
template = template.replace("{ProjectName}", project_name)
template = template.replace("{PROJECTNAME}", project_name.upper())
premake_file.write(template)

premake_template.close()
premake_file.close()

shutil.copytree(os.path.join(DATA_PATH, "Scripts"), os.path.join(SLN_DIR, "Scripts"))

# src files
SRC_DIR = os.path.join(PROJECT_DIR, "src")
os.mkdir(SRC_DIR)

files = {
    "GUILayer.cpp": "GUILayer.cpp",
    "GUILayer.h": "GUILayer.h",
    "Layer.cpp": "{0}Layer.cpp".format(project_name),
    "Layer.h": "{0}Layer.h".format(project_name),
    "Main.cpp": "Main.cpp",
    "pch.cpp": "pch{0}.cpp".format(project_name),
    "pch.h": "pch{0}.h".format(project_name),
}

SRC_DATA_DIR = os.path.join(DATA_PATH, "src")
for filename in os.listdir(SRC_DATA_DIR):
    filepath = os.path.join(SRC_DATA_DIR, filename)
    
    if os.path.isfile(filepath):
        file = open(filepath, 'r')
        content = file.read()
        file.close()
        content = content.replace("{ProjectName}", project_name)
        file = open(os.path.join(SRC_DIR, files[filename]), 'w')
        file.write(content)
        file.close()

input("Press enter to close")


