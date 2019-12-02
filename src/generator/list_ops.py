def list_ops(times):
    s=0.0
    for val in times:
        s+=val
    mean = s/len(times)
    std_dev = 0.0
    for val in times:
        std_dev += (val-mean)**2
    print('Avg: {}, Std: {}, Min: {}, Max: {}'.format(mean, std_dev, min(times), max(times)))
