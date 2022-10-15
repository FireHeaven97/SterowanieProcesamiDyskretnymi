import numpy
import time
import math


def read_from_file(filename):
    with open(filename) as f:
        number_of_machines, number_of_jobs = [int(x) for x in next(f).split()]
        p_time = numpy.zeros((number_of_machines, number_of_jobs))  #processing time
        for i in range(number_of_machines):
            p_i = f.readline().split()
            for j in range(number_of_jobs):
                p_time[i][j] = p_i[j]
    return number_of_machines, number_of_jobs, p_time


def sum(index_job, data, nb_machines):
    sum_p = 0
    for i in range(nb_machines):
        sum_p += data[i][index_job]
    return sum_p


def order_neh(data, nb_machines, nb_jobs):
    my_seq = []
    for j in range(nb_jobs):
        my_seq.append(j)
    order = sorted(my_seq, key=lambda x: sum(x, data, nb_machines), reverse=True)
    return order


def reorder_array(order, data, nbm, nbj):
    r_data = numpy.zeros((nbm, nbj))
    for j in range(len(order)):
        r_data[:,j] = data[:, order[j]]
    return r_data


def calc_cmax(data, nbm, nbj):
    times = []
    for j in range(0, nbj):
        times.append(0)
    for foo in range(0, nbm):
        times[0] = data[foo, 0] + times[0]
        for moo in range(1, nbj):
            times[moo] = data[foo, moo] + max(times[moo-1], times[moo])
        #print("timespan debug", times)
    return max(times)

def calc_neh(p_ij, nbm, nbj, xs):
    #print("------------------")
    temp = []
    for i in range(0, len(xs)):
        temp.append(xs[i])
    for too in range(1, len(xs)):
        comb = []
        contarr = []
        resarr = []
        #print("moje temparr za ", too, "tym razem na wejsciu to")
        #print(temp)
        for i in range(0, len(xs[:too+1])):
            comb.append(xs[i])
        last = comb[-1]
        #print("moje comb ", comb, "temp", temp)
        for moo in range(0, len(xs[:too+1])):
            comb[moo] = last
            boo = 0
            for foo in range(0, len(comb)):
                if foo == moo:
                    pass
                else:
                    comb[foo] = temp[boo]
                    boo = boo+1
            #print("moje comb ", comb)
            contarr.extend(comb)
            #print("boo i moo i too", boo, moo, too)
            cont = reorder_array(comb, p_ij, nbm, boo+1)
            #print("cont ")
            #print(cont)
            res = calc_cmax(cont, nbm, boo+1)
            #print("res ", res)
            resarr.append(res)
            #print("contarr w budowie ")
            #print(contarr)
        #print("contarr ")
        #print(contarr)
        #print("resarr")
        #print(resarr)
        bestpick = min(range(len(resarr)), key=lambda j: (resarr[j], -j))
        if bestpick == len(resarr)-1:
            pass
        #print("bestpick ", bestpick)
        else:
            for l in range(0, len(resarr)):
                temp[l] = contarr[len(resarr)*bestpick+l]
            #print("len, bestpick, l :", len(resarr), bestpick, l)
            #print("index nr ", l, " = ", len(resarr)*bestpick+l)
            #print("Current permutation ", contarr)
        #print("========================")
    print("Optimal permutation ")
    print(temp)
    p_ij = reorder_array(temp, p_ij, nbm, nbj)
    exec = calc_cmax(p_ij, nbm, nbj)
    print("Execution time ", exec)


nbm, nbj, p_ij = read_from_file("ta050.txt")
#print("Data: \n ", p_ij)
#print("Number of Machines:", nbm)
#print("Number of jobs:", nbj)
print("Non-increasing order of total processing times:")
order_seq = order_neh(p_ij, nbm, nbj)
#print(order_seq)
#ordered_data = reorder_array(order_seq, p_ij, nbm, nbj)
# print("Ordered data: ")
# print(ordered_data)
start = time.time_ns() / 10**6
calc_neh(p_ij, nbm, nbj, order_seq)
stop = time.time_ns() / 10**6 - start
print("Time elapsed:  milliseconds")
print(stop)
print("zakonczylem sie poprawnie:)")