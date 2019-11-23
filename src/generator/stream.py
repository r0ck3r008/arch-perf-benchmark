from importlib import import_module
import cv2

io=import_module('io', '.')

#TODO
#form a packet header to pass numpy.ndarray to the pipe
def to_stream(f, frame):
    for row in frame:
        for col in row:
            for val in col:
                f.write('{};'.format(val))
            f.write("\n")

def to_ndarray_vid(s_file):
    cap_obj=cv2.VideoCapture(s_file)
    f=open('write_file', 'w')
    while True:
        #to numpy.ndarray
        ret, frame=cap_obj.read()
        if ret==False:
            break
        to_stream(f, frame)

    cap_obj.release()
    cv2.destroyAllWindows()
    f.close()

def to_ndarray_img(s_file):
    #to numpy.ndarray
    frame=cv2.imread(s_file)
    f=open('write_file', 'w')
    to_stream(f, frame)
    f.close()

def parse_file_type(s_file):
    if '.jpg' in s_file or '.png' in s_file:
        to_ndarray_img(s_file)
    elif '.mp4' in s_file or 'http' in s_file:
        to_ndarray_vid(s_file)
    else:
        to_ndarray_vid(int(s_file))

