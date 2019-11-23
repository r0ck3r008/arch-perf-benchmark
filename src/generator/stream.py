from importlib import import_module
import cv2

io_helper=import_module('io_helper', '.')

#TODO
#form a packet header to pass numpy.ndarray to the pipe
def to_ndarray_vid(s_file):
    cap_obj=cv2.VideoCapture(s_file)
    while True:
        #to numpy.ndarray
        ret, frame=cap_obj.read()
        if ret==False:
            break
        io_helper.write(frame, fname)

    cap_obj.release()
    cv2.destroyAllWindows()

def to_ndarray_img(s_file):
    #to numpy.ndarray
    frame=cv2.imread(s_file)
    io_helper.write(frame, fname)

def parse_file_type(s_file, fifo):
    global fname
    fname=fifo
    if '.jpg' in s_file or '.png' in s_file:
        to_ndarray_img(s_file)
    elif '.mp4' in s_file or 'http' in s_file:
        to_ndarray_vid(s_file)
    else:
        to_ndarray_vid(int(s_file))

