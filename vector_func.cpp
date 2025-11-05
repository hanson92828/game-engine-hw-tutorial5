#include <math.h>

typedef struct {
    float x, y, z, w;
}v4d; // w=0:vector w=1:vertex

v4d vector_plus(v4d P, v4d Q) {
    return { P.x + Q.x, P.y + Q.y, P.z + Q.z ,P.w };
}

v4d vector_minus(v4d P, v4d Q) {
    return { P.x - Q.x, P.y - Q.y, P.z - Q.z ,P.w };
}

float length(v4d P) {
    return sqrtf(P.x * P.x + P.y * P.y + P.z * P.z);
}

v4d normalization(v4d P) {
    float l = length(P);
    return { P.x / l, P.y / l, P.z / l, P.w };
}

float dot(v4d P, v4d Q) {
    return P.x * Q.x + P.y * Q.y + P.z * Q.z;
}

v4d ProjPQ(v4d P, v4d Q) { // projection P on Q
    float con = dot(P, Q) / length(Q) / length(Q);
    return { Q.x * con, Q.y * con ,Q.z * con ,Q.w };
}

v4d cross(v4d P, v4d Q) {
    return normalization({ P.y * Q.z - P.z * Q.y, P.z * Q.x - P.x * Q.z, P.x * Q.y - P.y * Q.x ,P.w });
}

v4d PerpPQ(v4d P, v4d Q) {
    v4d temp = ProjPQ(P, Q);
    return { P.x - temp.x, P.y - temp.y, P.z - temp.z, P.w };
}