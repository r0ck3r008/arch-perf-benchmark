echo RC4 320x240
python main.py -s 320_240.jpg -a RC4 -S 240x320
echo RC4 640x480
python main.py -s 320_240.jpg -a RC4 -S 480x640
echo RC4 800x600
python main.py -s 320_240.jpg -a RC4 -S 600x800

echo vigenere 320x240
python main.py -s 320_240.jpg -a vigenere -S 240x320
echo vigenere 640x480
python main.py -s 320_240.jpg -a vigenere -S 480x640
echo vigenere 800x600
python main.py -s 320_240.jpg -a vigenere -S 600x800

echo chirikov 320x320
python main.py -s 320_240.jpg -a chirikov -S 320x320
echo chirikov 640x640
python main.py -s 320_240.jpg -a chirikov -S 640x640
echo chirikov 800x800
python main.py -s 320_240.jpg -a chirikov -S 800x800
