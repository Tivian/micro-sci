from PIL import Image
import os

# Change cwd to the directory of the script
abspath = os.path.abspath(__file__)
dname = os.path.dirname(abspath)
os.chdir(dname)

#im = Image.open('test.jpg')
keypad = Image.new('RGB',
                 (595, 842),   # A4 at 72dpi
                 (255, 255, 255))  # White
#keypad.paste(im, im.getbbox())  # Not centered, top-left corner
keypad.save('keypad.pdf', 'PDF', quality=100)