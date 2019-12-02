from statistics import stdev

def list_ops(times):
    s=0.0
    for val in times:
        s+=val
    print('Avg: {}, Std: {}, Min: {}, Max: {}'.format(s/len(times), stdev(times), min(times), max(times)))
