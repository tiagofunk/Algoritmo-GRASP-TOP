import os
import subprocess
import sys
from pathlib import Path

def read_files( directory ):
    f = []
    for root, _, files in os.walk( directory ):
        for file in files:
            f.append( os.path.join(root, file) )
    return f

def filter_extensions(files,extension):
    return list(filter( lambda x : x.endswith(extension), files ))

def extract_path_and_file(file_path):
    file = file_path[ file_path.rfind("/")+1:file_path.rfind(".") ]
    path = file_path[ 0:file_path.rfind("/")+1 ]
    return path, file

def create_file_compile_command( path, file, arguments ):
    arguments.insert( 0, COMPILER )
    arguments.append( f"{path}{file}.cpp" )
    arguments.append("-o")
    arguments.append(f"{path}{file}.o")
    return arguments

def create_program_compile_command( files ):
    command = [COMPILER,"-o", PROGRAM_PATH]
    for f in files:
        command.append( swap_extension(f) )
    return command

def create_remove_file_command( file ):
    return ["rm", file]

def swap_extension( file ):
    return file[0:-4] + ".o"

def show_command( command ):
    show = ""
    for c in command:
        show += f"{c} "
    return show

def execute( command ):
    print( f"Executando: {show_command(command)}" )
    try:
        output = subprocess.check_output(command)
        return True
    except subprocess.CalledProcessError as e:
        return False

def compile_file( file, arguments ):
    path, file = extract_path_and_file( file )
    command = create_file_compile_command(path, file, arguments)
    return execute( command )

def compile_program(files):
    command = create_program_compile_command( files )
    return execute( command )   
    
def remove_file(file):
    command = create_remove_file_command( file )
    return execute( command )

def remove_program():
    if(os.path.exists( PROGRAM_PATH )):
        command = create_remove_file_command( PROGRAM_PATH )
        execute( command )

def needs_compilation( path, file ):
    dir = Path( f"{path}")
    files = list(dir.glob(f"{file}.*"))
    if len(files) == 1:
        return True
    sorted_files = sorted(files, key=lambda f: f.stat().st_mtime, reverse=True)
    if not sorted_files[0].name.endswith(".o"):
        return True
    return False

def create_arguments( file, file_arguments_exception ):
    arguments = []
    if file in files_arguments_exceptions:
        arguments = ARGUMENTS.copy()
        for a in files_arguments_exceptions[file]:
            arguments.append( a )
    else:
        arguments = ARGUMENTS.copy()
    return arguments
    

def build( files_arguments_exceptions ):
    errors_counts = 0
    files_compiled_count = 0
    files = read_files(FILES_DIR)
    files = filter_extensions(files, ".cpp")

    for f in files:
        path, file = extract_path_and_file( f )
        if not needs_compilation(path, file):
            continue
        files_compiled_count += 1
        if not compile_file( f, create_arguments(file, files_arguments_exceptions) ):
            errors_counts += 1

    if errors_counts == 0 and files_compiled_count > 0:
        compile_program(files)

def clean():
    files = read_files(FILES_DIR)
    files = filter_extensions(files,".o")
    for f in files:
        remove_file( f )
    remove_program()


FILES_DIR = "."
COMPILER = "g++"
ARGUMENTS = ["-c", "-O3", "-Wall", "-fmessage-length=0"]
PROGRAM_NAME = "grasp"
PROGRAM_PATH = f"{FILES_DIR}{PROGRAM_NAME}"

files_arguments_exceptions = {}

if sys.argv[1] == "build":
   build( files_arguments_exceptions )
elif sys.argv[1] == "clean":
    clean()