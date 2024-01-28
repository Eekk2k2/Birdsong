indices = [];

xLen = 32
yLen = 32

y = 0
while y < yLen:
    x = 0
    while x < xLen:
        if (y < yLen - 1 and x < xLen - 1):
            indices.append(x + (y*xLen))
            indices.append(x + (y*xLen) + 1)
            indices.append(x + (y*xLen) + xLen)

        if (y < yLen -1 and x - 1 != -1):
            indices.append(x + (y*xLen))
            indices.append(x + (y*xLen) + xLen)
            indices.append(x + (y*xLen) + xLen - 1)

        x = x + 1
    y = y + 1


strIndices = "{\n     "
i = 0
while i < len(indices):
    strIndices += '' + str(indices[i]) + ', '
    i += 1
    if i%3 == 0:
        strIndices+= "\n     "

strIndicesLen = len(strIndices) - 8
strIndices = strIndices[:strIndicesLen]

strIndices += "\n};"

text_file = open("OutputIndices.txt", "w")
text_file.write(strIndices)
text_file.close()