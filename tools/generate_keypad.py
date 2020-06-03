from PIL import Image, ImageDraw
import os
import operator

# Change cwd to the directory of the script
abspath = os.path.abspath(__file__)
dname = os.path.dirname(abspath)
os.chdir(dname)

keypad = Image.new('RGB',
                 (595, 842),   # A4 at 72dpi
                 (255, 255, 255))  # white background
                 
px = 210 / keypad.width * (750 / 93)  # pixels per mm horizontally
py = 297 / keypad.height * (750 / 93) # pixels per mm vertically
padding = (100, 100)
draw = ImageDraw.Draw(keypad)

for y in range(8):
    for x in range(5):
        posx = tuple(map(operator.add, padding, (int(x * 15 * px), int(y * 15 * py))))
        posy = tuple(map(operator.add, padding, (int((x + 1) * 15 * px), int((y + 1) * 15 * py))))
        draw.rectangle((posx, posy), outline="black")

keypad.save('keypad.pdf', 'PDF', quality=100)