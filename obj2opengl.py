# obj2opengl.py
# author: stephen demos (stphndemos@gmail.com)

# a script that converts obj files to c header files
# one that actually gets the information you need

import sys

# take a [string] that is a wavefront obj file broken on newlines
# return a string that is a c header file with that information
# c header file has 8 things in it, 4 arrays, and 4 array lengths
# the arrays are - 
#   the vertices (thingVertices) with length (thingVerticesLength)
#   the normals (thingNormals) with length (thingNormalsLength)
#   the elements (thingElements) with length (thingElementsLength)
#   the normal indices (thingNormalIndices) with length (thingNormalIndicesLength)
#       this is use to create a single averaged vertex normal across a face
# all of the information for these arrays is in the obj file, it's just a
# matter of the format.
def convert(name, ino):
    out = ""
    # take in all of the lines and sort them into the relevant types
    vs   = []
    vns  = []
    fs   = []
    vnis = []
    for line in ino:
        split_line = line.split()
        # sort the split line into different line types
        if split_line[0] == 'v':
            # we have a vertex
            vs.append(split_line[1:])
            #vs = ', '.join([vs] + split_line[1:]) + '\n'
        elif split_line[0] == 'vn':
            # we have a vertex normal
            vns.append(split_line[1:])
            #vns = ', '.join([vns] + split_line[1:]) + '\n'
        elif split_line[0] == 'f':
            # we have a face statement
            fss = []
            vniss = []
            for p in split_line[1:]:
                sp = p.split('//')
                fss.append(str(int(sp[0])-1))
                vniss.append(str(int(sp[1])-1))
            #fs = ', '.join([fs] + fss) + '\n'
            #vnis = ', '.join([vnis] + vniss) + '\n'
            fs.append(fss)
            vnis.append(vniss)
        else:
            # something else that I don't really care about
            pass
    
    # convert the lists of things into c array style
    vs   = ',\n'.join(map(lambda s: ', '.join(s), vs))   + '\n'
    vns  = ',\n'.join(map(lambda s: ', '.join(s), vns))  + '\n'
    fs   = ',\n'.join(map(lambda s: ', '.join(s), fs))   + '\n'
    vnis = ',\n'.join(map(lambda s: ', '.join(s), vnis)) + '\n'

    out += '// automatically generated by obj2opengl.py\n'
    out += '#ifndef _' + name.upper() + '_H_\n'
    out += '#define _' + name.upper() + '_H_\n\n'
    out += 'float ' + name + 'Vertices[] = {\n'
    out += vs
    out += '};\n\n'
    out += 'int ' + name + 'VerticesLength = sizeof(' + name + 'Vertices) / sizeof(float);\n\n'
    out += 'float ' + name + 'Normals[] = {\n'
    out += vns
    out += '};\n\n'
    out += 'int ' + name + 'NormalsLength = sizeof(' + name + 'Normals) / sizeof(float);\n\n'
    out += 'int ' + name + 'Elements[] = {\n'
    out += fs
    out += '};\n\n'
    out += 'int ' + name + 'ElementsLength = sizeof(' + name + 'Elements) / sizeof(int);\n\n'
    out += 'int ' + name + 'NormalIndices[] = {\n'
    out += vnis
    out += '};\n\n'
    out += 'int ' + name + 'NormalIndicesLength = sizeof(' + name + 'NormalIndices) / sizeof(int);\n\n'
    out += '#endif // _' + name.upper() + '_H_\n'
    return out

if __name__ == '__main__':
    f = open(sys.argv[1])
    name = sys.argv[1].split('.')[0]
    outf = open(name + '.h', 'w')
    outf.write(convert(name, f.readlines()))