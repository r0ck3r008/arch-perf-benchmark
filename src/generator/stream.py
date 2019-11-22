from matplotlib.image import imread
from importlib import import_module
import cv2

io=import_module('io', '.')

def parse_file_type(s_file):
    splt=s_file.split('.')
    if len(splt)==2:
        if splt[1]=='jpg' or splt=='png':
            to_stream_img(s_file)
        elif splt[1]=='mp4':
            to_stream_vid(s_file)
    elif len(splt)==0:
        to_stream_vid(int(s_file))

#TODO
#handle networked stream, form a packet header to pass numpy.ndarray to the pipe
def to_stream_vid(s_file):
    cap_obj=cv2.VideoCapture(s_file)
    while True:
        #to numpy.ndarray
        _, frame=cap_obj.read()
        print(type(frame))

        if cv2.waitKey(1) & 0xFF==ord('q'):
            break

    cap_obj.release()
    cv2.destroyAllWindows()

def to_stream_img(s_file):
    #to numpy.ndarray
    pxl_array=imread(s_file)
    print(type(pxl_array))

