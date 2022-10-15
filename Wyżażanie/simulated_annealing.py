import numpy
import math
import random
import time

def read_from_file(filename):
    with open(filename) as f:
        number_of_jobs, number_of_machines = [int(x) for x in next(f).split()]
        p_time = numpy.zeros((number_of_jobs, number_of_machines)) #processing time
        for i in range(number_of_jobs):
            p_i = f.readline().split()
            for j in range(number_of_machines):
                p_time[i][j] = p_i[j]
    return number_of_machines, number_of_jobs, p_time

def timespan(data, nbm, nbj):
    cmax = []
    for j in range(0, nbm):
        cmax.append(0)
    for k in range(0, nbj):
        cmax[0] = data[k, 0] + cmax[0]
        for l in range(1, nbm):
            cmax[l] = data[k, l] + max(cmax[l-1], cmax[l])
    return max(cmax)

def probability(C,C_prim,T):
    if C_prim >= C:
        return math.exp((C - C_prim) / T)
    else:
        return 1

def sim_annealig(data, nbm, nbj):
    T0 = 100
    data1 = data
    while 0.0001 < T0:
        random_nb1 = random.randint(0, len(data) - 1)
        random_nb2 = random.randint(0, len(data) - 1)

        Cmax1 = timespan(data, nbm, nbj)

        data1[[random_nb1, random_nb2]] = data1[[random_nb2, random_nb1]]
        Cmax2 = timespan(data1, nbm, nbj)
        p = probability(Cmax1, Cmax2, T0)

        if p < random.random():
            data[[random_nb1, random_nb2]] = data[[random_nb2, random_nb1]]

        T0 *= 0.99


nbm, nbj, p_ij = read_from_file("ta000.txt")
print("Number of machines: ", nbm)
print("Number of jobs: ", nbj)
#print("Data")
#print(p_ij)
czas = timespan(p_ij, nbm, nbj)
print("Cmax  = ", czas)
start = time.time_ns() / 10**6
sim_annealig(p_ij, nbm, nbj)
stop = time.time_ns() / 10**6 - start
print("Time elapsed:  milliseconds")
print(stop)
#print(p_ij)
czas = timespan(p_ij, nbm, nbj)
print("Cmax = ", czas)