from PIL import Image
img = Image.open('binary.ppm')
img.save('binary.bmp')
img.show()