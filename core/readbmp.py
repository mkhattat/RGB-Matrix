from PIL import Image
import sys

im = Image.open(str(sys.argv[1])) #Can be many different formats.
rgb = im.convert('RGB')
width, height = rgb.size
print("(width: " + str(width) + ", height: " + str(height) + ")\n")
f = open(str(sys.argv[2]) + ".h", "w")
f.write("// width: " + str(width) + ", height: " + str(height) + "\n")
f.write("const uint8_t " + str(sys.argv[2]) + "[] = {\n")
f.write(str(width) + ", " + str(height) + ", 0,")
c = 0
#bar = True
for y in range(height):
    for x in range(width):
        if c > 0: f.write(",")
        #if bar : f.write("{"); bar = False
        line = str(rgb.getpixel((x,y))).replace("(", "")
        line = line.replace(")", "")
        f.write('\n' + line)
        c+=1
    #f.write("}")
    #bar = True


f.write("};")
f.close()
