import sys
from PIL import Image

if __name__ == "__main__":
    fn = sys.argv[1]
    fn_img = fn + ".png"
    fn_code = fn + ".h"
    with open(fn_code, "w+") as code:

        with Image.open(fn_img) as image:

            width, height = image.size
            code.write("size_t " + fn + "_len = " + str(width*height*3) + ";\r\n")
            code.write("size_t " + fn + "_width = " + str(width) + ";\r\n")
            code.write("size_t " + fn + "_height = " + str(height) + ";\r\n")
            code.write("uint8_t " + fn + "[" + str(width*height*3) + "] = { ")
            for h in range(height):
                for w in range(width):
                    rgb_im = image.convert('RGB')
                    r, g, b = rgb_im.getpixel((w, h))
                    if (r > 255 or g > 255 or b > 255):
                        print(r, g, b)
                    code.write(str(r) + " , " + str(g) + " , " + str(b))
                    if ((w != (width-1)) or (h != (height-1))):
                        code.write(" , ")

            code.write(" };\r\n")