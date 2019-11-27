from importlib import import_module
import cv2
from multiprocessing import Process
from libnacl import randombytes_uniform as ru
from os import remove

io_helper=import_module('io_helper', '.')

def process_frame(frame):
    fname='/tmp/pipe_{}'.format(ru(1000000))
    io_helper.open_fifo(fname)
    io_helper.write(frame, fname)
    remove(fname)

#TODO
#form a packet header to pass numpy.ndarray to the pipe
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
    frame=cv2.imread(s_file)
    process_frame(frame)

def parse_file_type(s_file):
    global processes
    processes=[]
    if '.jpg' in s_file or '.png' in s_file:
        to_ndarray_img(s_file)
    elif '.mp4' in s_file or 'http' in s_file:
        to_ndarray_vid(s_file)
    else:
        to_ndarray_vid(int(s_file))

    for process in processes:
        process.join()

