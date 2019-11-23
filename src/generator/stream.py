from importlib import import_module
import cv2

io=import_module('io', '.')

def parse_file_type(s_file):
    if '.jpg' in s_file or '.png' in s_file:
        to_stream_img(s_file)
    elif '.mp4' in s_file or 'http' in s_file:
        to_stream_vid(s_file)
    else:
        to_stream_vid(int(s_file))

#TODO
#handle networked stream, form a packet header to pass numpy.ndarray to the pipe
def to_stream_vid(s_file):
    cap_obj=cv2.VideoCapture(s_file)
    while True:
        #to numpy.ndarray
        ret, frame=cap_obj.read()
        if ret==False:
            break
        print(type(frame))

    cap_obj.release()
    cv2.destroyAllWindows()

def to_stream_img(s_file):
    #to numpy.ndarray
    pxl_array=cv2.imread(s_file)
    print(pxl_array)
