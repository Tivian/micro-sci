#from PIL import Image, ImageDraw, ImageFont
from svgwrite import Drawing
from cairosvg import svg2pdf
import os
import operator

# Change cwd to the directory of the script
abspath = os.path.abspath(__file__)
dname = os.path.dirname(abspath)
os.chdir(dname)

dwg = Drawing('keypad.svg', 
            size=(595, 842), # A4 at 72dpi
            profile='tiny')

px = 2100 / dwg['width'] * (15 / 14)  # pixels per mm horizontally
py = 2970 / dwg['height'] * (15 / 14) # pixels per mm vertically
padding = (100, 100)

for y in range(8):
    for x in range(5):
        pos = tuple(map(operator.add, padding, (x * 15 * px, y * 15 * py)))
        size = (15 * px, 15 * py)
        dwg.add(dwg.rect(pos, size, fill='white', stroke='black'))

dwg.save()
svg2pdf(url='keypad.svg', write_to='keypad.pdf')
