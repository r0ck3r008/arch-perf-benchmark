echo RC4 320x240
python main.py -s /home/bmj8778/cap-proj/src/samples/vid_samples/videoplayback_320x240.mp4 -a RC4
echo RC4 640x480
python main.py -s /home/bmj8778/cap-proj/src/samples/vid_samples/videoplayback_640x480.mp4 -a RC4 
echo RC4 800x600
python main.py -s /home/bmj8778/cap-proj/src/samples/vid_samples/videoplayback_800x600.mp4 -a RC4 

echo vigenere 320x240
python main.py -s /home/bmj8778/cap-proj/src/samples/vid_samples/videoplayback_320x240.mp4 -a vigenere 
echo vigenere 640x480
python main.py -s /home/bmj8778/cap-proj/src/samples/vid_samples/videoplayback_640x480.mp4 -a vigenere 
echo vigenere 800x600
python main.py -s /home/bmj8778/cap-proj/src/samples/vid_samples/videoplayback_800x600.mp4 -a vigenere 

echo chirikov 320x320
python main.py -s /home/bmj8778/cap-proj/src/samples/vid_samples/videoplayback_320x240.mp4 -a chirikov 
echo chirikov 640x640
python main.py -s /home/bmj8778/cap-proj/src/samples/vid_samples/videoplayback_640x480.mp4 -a chirikov 
echo chirikov 800x800
python main.py -s /home/bmj8778/cap-proj/src/samples/vid_samples/videoplayback_800x600.mp4 -a chirikov 
