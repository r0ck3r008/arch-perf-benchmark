from importlib import import_module
import cv2
from multiprocessing import Process, Queue
from threading import Thread
from libnacl import randombytes_uniform as ru
from os import remove
from subprocess import run, PIPE
from time import sleep

io_helper=import_module('io_helper', '.')
list_ops=import_module('list_ops', '.')

def process_frame(frame):
    #arguments
    fname='/tmp/pipe_{}'.format(ru(1000000))
    algonum=0
    prefix=''
    if algo=='chirikov' or algo=='Chirikov':
        algonum=1
    elif algo=='Vigenere' or algo=='vigenere':
        algonum=2

    if riscv==True:
        prefix='rv-jit '

    #pipe
    io_helper.open_fifo(fname)
    t=Thread(target=io_helper.write, args=[frame, fname]).start()
    sleep(10)

    #subprocess
    p=run('{}./engine/engine {} {} {} {}'.format(prefix, fname, algonum, size[0], size[1]),
            shell=True, stdout=PIPE, text=True)
    queue.put(p.stdout)
    remove(fname)

def to_ndarray_vid(s_file):
    cap_obj=cv2.VideoCapture(s_file)
    while True:
        #to numpy.ndarray
        ret, frame=cap_obj.read()
        if ret==False:
            break
        p=Process(target=process_frame, args=[frame,])
        processes.append(p)
        p.start()

    cap_obj.release()
    cv2.destroyAllWindows()

def to_ndarray_img(s_file):
    #to numpy.ndarray
    for i in range(30):
        frame=cv2.imread(s_file)
        p=Process(target=process_frame, args=[frame,])
        processes.append(p)
        p.start()

def parse_args(args):
    global riscv, algo, size
    riscv=args.riscv
    algo=args.algo
    size=args.size.split('x')

    return args.sfile

def parse_file_type(args):
    s_file=parse_args(args)
    global processes, queue
    processes=[]
    queue=Queue()
    if '.jpg' in s_file or '.png' in s_file:
        to_ndarray_img(s_file)
    elif '.mp4' in s_file or 'http' in s_file:
        to_ndarray_vid(s_file)
    else:
        to_ndarray_vid(int(s_file))

    for process in processes:
        process.join()

    enc_times=[]
    dec_times=[]
    while queue.empty()!=True:
        enc_time, dec_time=queue.get().split(':')
        enc_times.append(float(enc_time))
        dec_times.append(float(dec_time))
    list_ops.list_ops(enc_times)
    list_ops.list_ops(dec_times)
