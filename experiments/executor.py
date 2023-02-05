import concurrent.futures
import time
import os

def read_files( instances_dir ):
    f = []
    for p, _, files in os.walk( instances_dir ):
        for file in files:
            f.append( os.path.join(p, file) )
    return f

def create_all_combinatitions( files, name, options ):
    args = []
    for op in options:
        for f in files:
            args.append( str( f"{f} {name} {op}" ) )
    return args

def multiply( files, number ):
    n_files = files*number
    n_files.sort()
    return n_files

def execute( args ):
    # just remember that your program should only have one line of output
    print( args )
    res = os.popen(f"./.grasp 1 1 1 {args}")
    result = res.readline().strip() + "\n"
    return result

def create_and_execute_pool( args, max_workers ):
    result = ""
    with concurrent.futures.ProcessPoolExecutor( max_workers ) as executor:
        start_time = time.perf_counter()
        result = list( executor.map( execute, args ) )
        finish_time = time.perf_counter()
        print(f"Program finished in {finish_time-start_time} seconds")
    return result

def write_log( result, LOG_FILE ):
    log_file = open( LOG_FILE, "w" )
    for r in result:
        log_file.write( f"{r}" )
    log_file.close()

if __name__ == "__main__":
    INSTANCES_DIR = "../instances/"
    REPETITIONS = 10
    LOG_FILE = "log.txt"
    MAX_WORKERS = 8

    files = read_files( INSTANCES_DIR )
    args = files
    args = create_all_combinatitions( args, "--alpha", ["0.9"] )
    args = create_all_combinatitions( args, "--iterations", ["50000"] )
    args = create_all_combinatitions( args, "--path", ["y"] )
    args = create_all_combinatitions( args, "--margin", ["1.9"] )
    args = create_all_combinatitions( args, "--removeOperator", ["r"] )
    args = create_all_combinatitions( args, "--removePercentage", ["0.15"] )
    args = create_all_combinatitions( args, "--shuffleOperator", ["e"] )
    args = create_all_combinatitions( args, "--addOperator", ["b"] )
    args = multiply( args, REPETITIONS )
    result = create_and_execute_pool( args, MAX_WORKERS )
    write_log( result, LOG_FILE )
