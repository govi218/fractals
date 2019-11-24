import numpy as np
# from joblib import Parallel, delayed
import multiprocessing as mp
import matplotlib.pyplot as plt

from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor
import multiprocessing as mp
from multiprocessing import Pool, Value, Array
import time
# from numba import njit
import pickle as pk

m_set = []

class Fractal:

    def __init__(self, step):
        self.step = step

    def mandelbrot_process(self, c, boundary=2, max_iterations=512):
        z = 0+0j
        i = 0
        while np.absolute(z) < np.absolute(boundary):
    #         if i%20 == 0:
    #             print('i:',i,'z:',z)
            if i == max_iterations:
                break
            z = z*z + c
            i += 1
        return i

    def mandelbrot(self, my_arange):
        start = my_arange[0]
        end = my_arange[1]
        step = my_arange[2]
        f = open("m_set.csv", "w")
        f.write("x,y,iters")
        for i in np.arange(start, end, step):
            for j in np.arange(-2.0, 2.0, step):
                iters = self.mandelbrot_process(complex(i,j))
                if int(iters):
                    m_set.append((i,j, iters))
                    print(i+','+j+','+iters)
                    # f.write(i+','+j+','+iters)
        f.close()
        return m_set

    def run(self):
        def arange_calc(num_cores, step):
            arange = []
            arange_step = 4/num_cores
            for i in range(num_cores):
                l = []
                start = i*arange_step - 2
                end=(i+1)*arange_step - 2
                l.append(start)
                l.append(end)
                l.append(step)
                arange.append(l)
            return arange

        my_arange = arange_calc(mp.cpu_count(), self.step)
        pool = mp.Pool()
        # %%time        fractal = Fractal()
        res = pool.map(self.mandelbrot, my_arange)
        m_set = []
        for i in range(len(res)):
            for j in range(len(res[i])):
                m_set.append(res[i][j])
        labels = []
        x_vals = []
        y_vals = []

        for point in m_set:
            labels.append(point[2])
            x_vals.append(point[0])
            y_vals.append(point[1])
        labels = np.array(labels)
        x_vals = np.array(x_vals)
        y_vals = np.array(y_vals)
        # colors = cm.rainbow(colors)
        c_array = {}

        for i in range(len(labels)):
            c_array[labels[i]] = "#"+''.join([np.random.choice(['0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F']) for j in range(6)])

        vars = [labels, x_vals, y_vals, c_array]
        with open("vars", "wb") as f:
            pk.dump(vars, f)

if __name__ == '__main__':
    
    fractal = Fractal(0.001)
    fractal.run()