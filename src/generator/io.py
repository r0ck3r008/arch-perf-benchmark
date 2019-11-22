from os import mkfifo, OSError, _exit
from sys import stderr

def open_fifo(fname):
    try:
        os.mkfifo(fname)
    except OSError as e:
        print(stderr, "[!]Fifo already exists!")
    except Exception as e:
        print(stderr, "[-]Error in creating the fifo: {}".format(e))
        _exit(-1)

def write(fname, data):
    with open(fname, 'r') as f:
        pass
