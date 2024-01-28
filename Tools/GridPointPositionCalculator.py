points = [];

xLen = 32
yLen = 32

y = 0
while y < yLen:
    x = 0
    while x < xLen:
        points.append(x + 0.0)
        points.append(y + 0.0)
        points.append(0.0)

        x = x + 1
    y = y + 1


strIndices = "{\n     "
i = 0
while i < len(points):
    strIndices += '' + str(points[i]) + ', '
    i += 1
    if i%3 == 0:
        strIndices+= "\n     "

strIndicesLen = len(strIndices) - 8
strIndices = strIndices[:strIndicesLen]

strIndices += "\n};"

text_file = open("OutputPointPosition.txt", "w")
text_file.write(strIndices)
text_file.close()

print(len(points))