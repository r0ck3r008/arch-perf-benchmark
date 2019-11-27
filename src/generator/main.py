from argparse import ArgumentParser
from importlib import import_module

stream=import_module('stream', '.')
io_helper=import_module('io_helper', '.')

if __name__=='__main__':
    parser=ArgumentParser()
    parser.add_argument('-s', '--stream', required=True, metavar='',
                dest='sfile', help='The stream to read from (image/video/network/Webcam)')
    args=parser.parse_args()

    stream.parse_file_type(args.sfile)
