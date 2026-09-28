void MTX_Rot22_02005948(int *mtx, int sinv, int cosv)
{
    mtx[0] = cosv;
    mtx[1] = sinv;
    mtx[2] = -sinv;
    mtx[3] = cosv;
}
