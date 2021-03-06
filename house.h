// automatically generated by obj2opengl.py
#ifndef _HOUSE_H_
#define _HOUSE_H_

float houseVertices[] = {
-4.977862, -0.001045, 7.053262,
-4.977862, 3.058158, 7.053262,
-4.977862, -0.001045, 1.146636,
-4.977862, 3.058158, 1.146636,
-2.185013, 5.177294, 1.146636,
-2.185013, 5.177294, 7.053262,
-2.000000, 0.000000, 1.146635,
-2.000000, 2.000000, 1.146635,
-2.000000, 0.000000, -2.000000,
-2.000000, 2.000000, -2.000000,
2.000000, 2.000000, 1.146636,
2.000000, 0.000000, -2.000000,
2.000000, 2.000000, -2.000000,
0.000000, 3.517543, -2.000000,
-0.000000, 3.517543, 1.146635,
2.000000, 2.000000, 1.146636,
2.000000, 2.000000, 7.053262,
2.000000, 0.000000, 7.053262
};

int houseVerticesLength = sizeof(houseVertices) / sizeof(float);

float houseNormals[] = {
-1.000000, 0.000000, 0.000000,
-0.604500, 0.796600, 0.000000,
0.000000, 0.000000, -1.000000,
0.000000, 0.000000, 1.000000,
1.000000, 0.000000, 0.000000,
0.604500, 0.796600, 0.000000,
0.000100, -1.000000, -0.000100,
0.604900, 0.796300, 0.000000,
0.604700, 0.796500, -0.000100,
0.000400, -1.000000, 0.000000,
0.000000, -1.000000, 0.000000
};

int houseNormalsLength = sizeof(houseNormals) / sizeof(float);

int houseElements[] = {
3, 2, 0,
4, 3, 1,
9, 8, 6,
12, 11, 9,
4, 14, 7,
16, 5, 1,
12, 16, 17,
13, 9, 7,
12, 13, 14,
6, 17, 0,
1, 3, 0,
5, 4, 1,
7, 9, 6,
8, 9, 11,
13, 12, 9,
6, 2, 7,
3, 4, 7,
7, 2, 3,
1, 0, 16,
17, 16, 0,
11, 12, 17,
14, 13, 7,
4, 5, 14,
16, 12, 14,
14, 5, 16,
0, 2, 6,
6, 8, 11,
11, 17, 6
};

int houseElementsLength = sizeof(houseElements) / sizeof(int);

int houseNormalIndices[] = {
0, 0, 0,
1, 1, 1,
0, 0, 0,
2, 2, 2,
2, 2, 2,
3, 3, 3,
4, 4, 4,
1, 1, 1,
5, 5, 5,
6, 6, 6,
0, 0, 0,
1, 1, 1,
0, 0, 0,
2, 2, 2,
2, 2, 2,
2, 2, 2,
2, 2, 2,
2, 2, 2,
3, 3, 3,
3, 3, 3,
4, 4, 4,
1, 1, 1,
7, 7, 7,
5, 5, 5,
8, 8, 8,
9, 9, 9,
10, 10, 10,
10, 10, 10
};

int houseNormalIndicesLength = sizeof(houseNormalIndices) / sizeof(int);

#endif // _HOUSE_H_
