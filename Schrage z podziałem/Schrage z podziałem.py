class process:
    def __init__(self,uid,r=0,p=0,q=0):
        self.uid = uid
        self.r=r
        self.p=p
        self.q=q
    def __str__(self):
        return str(self.uid)+' '+str(self.r)+' '+str(self.p)+' '+str(self.q)

from copy import deepcopy

def Schrage(N):
    Cmax=0
    sig=[]
    Ng=[]
    Nn=deepcopy(N)
    t=min(Nn,key=lambda x:x.r).r
    while Ng != [] or Nn != []:
        while Nn != [] and min(Nn,key=lambda x:x.r).r <= t:
            j = min(Nn,key=lambda x:x.r)
            Ng.append(j)
            Nn.remove(j)
        if Ng == []:
            t = min(Nn,key=lambda x:x.r).r
        else:
            j = max(Ng,key=lambda x:x.q)
            Ng.remove(j)
            sig.append(j)
            t=t+j.p
            Cmax = max(t+j.q,Cmax)
    return sig,Cmax

def SchragePmtn(N):
    sig=[]
    Ng=[]
    Nn=deepcopy(N)
    Cmax = 0
    t=0
    l=Nn[0]
    while Ng != [] or Nn != []:
        while Nn != [] and min(Nn,key=lambda x:x.r).r <= t:
            j = min(Nn,key=lambda x:x.r)
            Ng.append(j)
            Nn.remove(j)
            if j.q > l.q:
                nl = deepcopy(l)
                nl.p=t-j.r
                t=j.r
                if nl.p > 0:
                    l.q=0
                    nl.r=0
                    l.p=l.p-nl.p
                    Ng.append(nl) 
        if Ng == []:
            t = min(Nn,key=lambda x:x.r).r
        else:
            j = max(Ng,key=lambda x:x.q)
            Ng.remove(j)
            l=j
            j.start=t
            sig.append(j)
            t=t+j.p
            Cmax = max(Cmax,t+j.q)
    return sig,Cmax

if __name__=='__main__':
    from random import random
    r=[10, 13, 11, 20, 30, 0, 30];
    p=[5, 6, 7, 4, 3, 6, 2];
    q=[7, 26, 24, 21, 8, 17, 0];
    procs = []
    for i in range(len(r)):
        procs.append(process(i+1,r[i],p[i],q[i]))
    
    order,order_cost = Schrage(procs)
    pmtno,pmtnc = SchragePmtn(procs)
    print('Schrage     ',order_cost)
    print('Schrage Pmtn',pmtnc)
    del p;del r;del q;del i;del procs;
