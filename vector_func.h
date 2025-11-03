#ifndef _VECTOR_FUNC_H
#define _VECTOR_FUNC_H

typedef struct {
	float x, y, z, w;
}v4d; // w=0:vector w=1:vertex

v4d vector_plus(v4d P, v4d Q);
v4d vector_minus(v4d P, v4d Q);
float length(v4d P);
v4d normalization(v4d P);
float dot(v4d P, v4d Q);
v4d ProjPQ(v4d P, v4d Q);
v4d cross(v4d P, v4d Q);
v4d PerpPQ(v4d P, v4d Q);

#endif // DEBUG