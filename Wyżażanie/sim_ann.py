import numpy

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

nbm, nbj, p_ij = read_from_file("ta000.txt")
print("nbm ", nbm)
print("nbj", nbj)
print("pij")
print(p_ij)
czas = timespan(p_ij, nbm, nbj)
print("czas = ", czas)
