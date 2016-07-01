from PIL import Image
import sys

def iter_frames(gif):
    try:
        i= 0
        while 1:
            gif.seek(i)
            imframe = gif.copy()
            if i == 0: 
                palette = imframe.getpalette()
            else:
                imframe.putpalette(palette)
            yield imframe
            i += 1
    except EOFError:
        pass
    
    

data = ""
counter = 0

gif = Image.open(str(sys.argv[1])) #Can be only gif

f = open(str(sys.argv[2]) + ".h", "w")
f.write("const uint8_t " + str(sys.argv[2]) + "[] = {\n")

for im in iter_frames(gif):
    rgb = im.convert('RGB')
    if counter == 0:
        width, height = rgb.size
        data += (str(width) + ", " + str(height) + ", 0")
        
    counter+=1
    print("(width: " + str(width) + ", height: " + str(height) + ")\n")
    c = 0
    for y in range(height):
        for x in range(width):
            #if c > 0: 
            data += (",")
            line = str(rgb.getpixel((x,y))).replace("(", "")
            line = line.replace(")", "")
            data += ('\n' + line)
            c = 1

data += ("};")
f.write(str(counter) + ", 0, 0,\n")
f.write(data)
f.close()

print("Total frames: ", counter)
