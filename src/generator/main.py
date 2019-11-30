from argparse import ArgumentParser
from importlib import import_module

stream=import_module('stream', '.')

if __name__=='__main__':
    parser=ArgumentParser()
    parser.add_argument('-s', '--stream', required=True, metavar='',
                dest='sfile', help='The stream to read from (image/video/network/Webcam)')
    parser.add_argument('-a', '--algo', required=True, metavar='',
                dest='algo', help='Choose from algorithms: Rc4/Chirikov/Vigenere')
    parser.add_argument('-rv', '--riscv', action='store_true',
                dest='riscv', help='Flag if the target is RISCV RV8')
    parser.add_argument('-S', '--size', metavar='', default='240x360',
                dest='size', help="Set the input image size in 'heightxlength' format (Default 240x360)")
    args=parser.parse_args()

    stream.parse_file_type(args)
