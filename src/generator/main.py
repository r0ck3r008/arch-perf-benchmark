from argparse import ArgumentParser
from importlib import import_module

stream=import_module('stream', '.')

if __name__=='__main__':
    parser=ArgumentParser()
    parser.add_argument('-s', '--stream', required=True, metavar='',
                help='The stream to read from (image/video/network)')
    parser.add_argument('-f', '--fifo', required=True, metavar='',
                help='The FIFO to create/use to push bit stream')
    args=parser.parse_args()
