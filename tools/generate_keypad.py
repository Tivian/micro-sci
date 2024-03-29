from svgwrite import Drawing
from PIL import ImageFont
import os
import operator

outfile    = 'keypad'
main_color = '#000000'
alp_color  = '#DC143C'
bta_color  = '#3CB371'

web_font = 'Lato'
sys_font = 'LatoWeb-Regular.ttf'
font_main_size = 26
font_sub_size  = 16

str_alp = "\U0001D770"
str_bta = "\U0001D771"
str_dx  = "\U0001D451\U0001D465"
str_ans = "\U0001D5A0\U0001D5C7\U0001D5CC"
str_sci = "\U0001D5D1\U0001D7E3\U0001D7E2\u02E3"
str_clr = "\U0001D5A2\U0001D5AB\U0001D5B1"
str_del = "\U0001D5A3\U0001D5A4\U0001D5AB"
str_on  = "\U0001D5AE\U0001D5AD"
str_off = "\U0001D5AE\U0001D5A5\U0001D5A5"
str_inv = "\U0001D5A8\U0001D5AD\U0001D5B5"
str_hyp = "\U0001D5C1\U0001D5D2\U0001D5C9"
str_sin = "\U0001D5CC\U0001D5C2\U0001D5C7"
str_cos = "\U0001D5BC\U0001D5C8\U0001D5CC"
str_tan = "\U0001D5CD\U0001D5BA\U0001D5C7"
str_log = "\U0001D5C5\U0001D5C8\U0001D5C0"
str_ln  = "\U0001D5C5\U0001D5C7"
str_exp = "\U0001D452\u02E3"
str_10x = "\U0001D7E3\U0001D7E2\u02E3"
str_fac = "\U0001D465\u0021"
str_sto = "\U0001D5B2\U0001D5B3\U0001D5AE"
str_rcl = "\U0001D5B1\U0001D5A2\U0001D5AB"
str_rnd = "\U0001D5B1\U0001D5C7\U0001D5BD\u0023"
str_mod = "\U0001D5C6\U0001D5C8\U0001D5BD"
str_pow = "\U0001D5D2\u02E3"
str_root = "\u02E3\u221A"
str_pow2 = "\U0001D465\u00B2"
str_pow3 = "\U0001D465\u00B3"
str_sqrt = "\u221A"
str_crot = "\u00B3\u221A"
str_perm = "\U0001D5C7\U0001D5E3\U0001D5CB"
str_comb = "\U0001D5C7\U0001D5D6\U0001D5CB"
str_xor = "\U0001D5B7\U0001D5AE\U0001D5B1"
str_or  = "\U0001D5AE\U0001D5B1"
str_and = "\U0001D5A0\U0001D5AD\U0001D5A3"
str_rep = "\U0001D465\u207B\u00B9"
str_abs = "\U0001D5A0\U0001D5BB\U0001D5CC"
str_min = "\U0001D5C6\U0001D5C2\U0001D5C7"
str_max = "\U0001D5C6\U0001D5BA\U0001D5D1"
str_prod = "\u220F"

primary = [
         str_alp,      str_log,     "\u222B",      str_fac,       str_on,
         str_bta,       str_ln,     "\u2211",    "\u25C1 ",    "\u25B7 ",
         str_sto,      str_inv,      str_sin,      str_cos,      str_tan,
         str_rcl,     str_pow2,     str_sqrt,     "\u2768",     "\u2769",
    "\U0001D7E9", "\U0001D7EA", "\U0001D7EB",      str_del,      str_clr,
    "\U0001D7E6", "\U0001D7E7", "\U0001D7E8",     "\u00D7",     "\u00F7",
    "\U0001D7E3", "\U0001D7E4", "\U0001D7E5",     "\u002B",     "\u2212",
    "\U0001D7E2",     "\u00B7",      str_sci,      str_ans,     "\u003D"
]

alpha = [
              "",      str_10x,       str_dx,      str_rep,      str_off,
              "",      str_exp,     str_prod,           "",           "",
              "",      str_hyp,      str_abs,      str_min,      str_max,
              "",     str_pow3,     str_crot,     "\u275F",           "",
              "",           "",           "",           "",           "",
              "",           "",           "",     "\u25CB",      str_mod,
         str_and,       str_or,      str_xor,     str_perm,     str_comb,
              "",      str_rnd, "\U0001D70B",           "",           ""
]

beta = [
              "",           "",           "",           "",           "",
              "",           "",           "",           "",           "",
              "",           "",           "",           "",           "",
              "",      str_pow,     str_root, "\U0001D465", "\U0001D466",
    "\U0001D670", "\U0001D671", "\U0001D672",           "",           "",
    "\U0001D673", "\U0001D674", "\U0001D675",     "\u25CF",           "",
              "",           "",           "",           "",           "",
              "",           "", "\U0001D452",           "",           ""
]

# List of special keys without alpha and beta functions
special_keys = [
    0, 5, 8, 9, 23, 24
]

# Change cwd to the directory of the script
abspath = os.path.abspath(__file__)
dname = os.path.dirname(abspath)
os.chdir(dname)

dwg = Drawing(f'{outfile}.svg', 
            size=(595, 842), # A4 at 72dpi
            profile='full')

px = 2100 / dwg['width'] * (15 / 14)  # pixels per mm horizontally
py = 2970 / dwg['height'] * (15 / 14) # pixels per mm vertically
padding = (100, 100)
key_font = ImageFont.truetype(sys_font, font_main_size)
sec_font = ImageFont.truetype(sys_font, font_sub_size)
key_style = f'font-size: {font_main_size}px; font-family:{web_font}'
sec_style = f'font-size: {font_sub_size}px; font-family:{web_font}'

for y in range(8):
    for x in range(5):
        idx = y * 5 + x
        key = primary[idx]
        alp = alpha[idx]
        bta = beta[idx]
        line_height = 2.5 if idx not in special_keys else 1.5
        key_fill = alp_color if key == str_alp else bta_color if key == str_bta else main_color

        pos = tuple(map(operator.add, padding, (x * 15 * px, y * 15 * py)))
        size = (15 * px, 15 * py)
        button = dwg.add(dwg.g())
        txt_size = key_font.getsize(key)
        alp_size = sec_font.getsize(alp)
        bet_size = sec_font.getsize(bta)
        txt_pos = (pos[0] + (size[0] - txt_size[0]) / 2, pos[1] + size[1] - txt_size[1] / line_height)
        alp_pos = (pos[0] + 5, pos[1] + (size[1] / 3.5) + (alp_size[1] / 10))
        bet_pos = (pos[0] + (size[0] - bet_size[0] - 5), alp_pos[1])
        button.add(dwg.rect(pos, size, fill='white', stroke='black'))
        button.add(dwg.text(key, txt_pos, style=key_style, fill=key_fill))
        button.add(dwg.text(alp, alp_pos, style=sec_style, fill=alp_color))
        button.add(dwg.text(bta, bet_pos, style=sec_style, fill=bta_color))

dwg.save()
