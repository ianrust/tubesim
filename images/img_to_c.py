import os
import sys
from PIL import Image

def codeGen(fn_img, start):
    fn = fn_img[:-4]
    fn_code = fn + ".h"
    data = []
    with open(fn_code, "w+") as code:

        with Image.open(fn_img) as image:

            width, height = image.size
            code.write("#pragma once\r\n")
            code.write("const FlashImage " + fn + "(" + str(width*height*3) + ", " + str(width) + ", " + str(height) + ", " + str(start) + ");\r\n")
            for h in range(height):
                for w in range(width):
                    rgb_im = image.convert('RGB')
                    r, g, b = rgb_im.getpixel((w, h))
                    data.append(r)
                    data.append(g)
                    data.append(b)
    return data, fn_code

if __name__ == "__main__":
    data = []
    fns = []
    for fn_img in os.listdir("./"):
        if ".png" in fn_img or ".jpg" in fn_img:
            d, fn = codeGen(fn_img, len(data))
            data += d
            fns += [fn]

    with open("imagedata.h", "w+") as code:
        for fn in fns:
            code.write("#include \"" + fn + "\"\r\n")

        code.write("const uint8_t image_data[" + str(len(data)) + "] = { ");
        for i, datum in enumerate(data):
            code.write(str(datum))
            if (i != len(data)):
                code.write(" , ")
        code.write(" };\r\n")
