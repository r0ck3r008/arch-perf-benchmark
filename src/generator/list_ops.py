def list_ops(times):
    s=0.0
    for val in times:
        s+=val
    mean = s/len(times)
    s_dev = 0.0
    for val in times:
        s_dev += (val-mean)**2
    print('Avg: {}, Std: {}, Min: {}, Max: {}'.format(mean, (s_dev/len(times))**.5, min(times), max(times)))
