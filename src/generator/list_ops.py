def list_ops(times):
    s=0.0
    for val in times:
        s+=val

    print('Avg: {}, Min: {}, Max: {}'.format(s/len(times), min(times), max(times)))
