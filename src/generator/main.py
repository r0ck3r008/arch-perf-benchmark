from argparse import ArgumentParser
from importlib import import_module

stream=import_module('stream', '.')
io_helper=import_module('io_helper', '.')

if __name__=='__main__':
    parser=ArgumentParser()
    parser.add_argument('-s', '--stream', required=True, metavar='',
                dest='sfile', help='The stream to read from (image/video/network/Webcam)')
    parser.add_argument('-f', '--fifo', required=True, metavar='',
                dest='fifo', help='The FIFO to create/use for pushing bit stream')
    args=parser.parse_args()

    io_helper.open_fifo(args.fifo)
    stream.parse_file_type(args.sfile, args.fifo)
