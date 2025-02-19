import numpy as np
from time import perf_counter_ns as timer
from numba import jit


def MultFun2(a,b,c,m):
    for i in range(0,m):
        for j in range(0,m):
            acc=0
            for temp in range(0,m):
                acc+=a[i,temp]*b[temp,j]
            c[i,j]=acc
            

@jit
def MultFun(a,b,c,m):
    for i in range(0,m):
        for j in range(0,m):
            acc=0
            for temp in range(0,m):
                acc+=a[i,temp]*b[temp,j]
            c[i,j]=acc


M=1024
K=M
N=M

A=np.arange(M*K)
A=A.reshape(M,K)
B=np.ones((K,N))
C=np.zeros((M,N))

start=timer()
C=np.matmul(A,B)
dt=timer()-start
dt=dt/1000000.0
print("np.matmul time %f ms"%dt)

start=timer()
MultFun(A,B,C,M)
dt=timer()-start
dt=dt/1000000.0
print("jit mul time %f ms"%dt)

start=timer()
MultFun2(A,B,C,M)
dt=timer()-start
dt=dt/1000000.0
print("mul fun time %f ms"%dt)
