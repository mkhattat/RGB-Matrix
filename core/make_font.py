from PIL import Image, ImageFont, ImageDraw
import sys

# First argument: path to the font (ttf)
# Second argument: Size of font
# Third argument: Name of array

#header = ""
offset = 0
data = ""
f = open(str(str(sys.argv[3])) + ".h", "w")
f.write("// Font Name: " + str(sys.argv[3]) + ", Size: " + str(sys.argv[2]) + "\n")
f.write("const uint8_t " + str(sys.argv[3]) + "[] = {\n")
begin = True
for i in range(33, 127):

    im = Image.new("RGB", (64, 32))

    draw = ImageDraw.Draw(im)

    # use a truetype font
    font = ImageFont.truetype(sys.argv[1], int(sys.argv[2]))

    draw.text((0, 0), chr(i), font=font)

    # remove unneccessory whitespaces if needed
    im=im.crop(im.getbbox())

    width, height = im.size
    #print("(width: " + str(width) + ", height: " + str(height) + ")\n")
    #tmp_data += "// width: " + str(width) + ", height: " + str(height) + "\n"

    for y in range(height):
        for x in range(width):
            if begin == False: data += ",\n"
            #data += ","
            line = str(im.getpixel((x,y))).replace("(", "")
            line = line.replace(")", "")
            line = line.split(",")[0]
            data += line
            begin = False

    f.write(str(width) + ", " + str(height) + ", ")
    if (offset <= 255):
        f.write(str(offset) + ", 0,\n")
    else:
        #f.write(str((offset & 0xFF)) + ", " + str(((offset & 0xFF00) >> 4)) + ",\n")
        f.write("{0:#04x}".format((offset & 0xFF)) + ", " + "{0:#04x}".format(((offset & 0xFF00) >> 8)) + ",\n")
    #header += [[{'width' : width, 'height' : height, 'offset' :  offset}]]
    offset += height*width

data += "};\n"

f.write(data)
f.close()
