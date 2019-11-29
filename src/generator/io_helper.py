from os import mkfifo, _exit, path
from sys import stderr

def open_fifo(fname):
    if path.exists(fname):
        return True
    try:
        mkfifo(fname)
    except Exception as e:
        print(stderr, "[-]Error in creating the fifo: {}".format(e))
        _exit(-1)

def write(data, fname):
    with open(fname, 'w') as f:
        for row in data:
            for col in row:
                for val in col:
                    f.write('{};'.format(val))
