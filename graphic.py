# Per eseguire da python3:   exec(open('graficoModificato.py').read())

# I add to the theoretical model a basic level of counts to represent a possible background noise independent of the intensity of the photons
#The model is right if there was a constant noise source of about 10 counts

import matplotlib.pyplot as plt
import numpy as np
from scipy import optimize



#MODEL

mean = np.arange(0.0, 1100, 0.1)
sigma = ((1.0*mean**0.5)**2 +10**2)**0.5 #I add +10 in quadrature

fig, ax = plt.subplots()
ax.plot(mean, sigma,label='model: sigma=sqrt((intensity^0.5)^2+10^2)')



#DATA 

file=open('results.txt', 'r')
next(file)

X, Y = [], []
for line in file:
  values = [float(s) for s in line.split()]
  X.append(values[1])
  Y.append(values[2])

plt.plot(X, Y,'.', color='red', label='data')



#BEST FIT

def fit_func(x, a, b):
    return ((x**b)**2+a**2)**0.5

params, params_covariance = optimize.curve_fit(fit_func, X, Y,
                                               p0=[2, 2])

print(params)

ax.plot(X, fit_func(X,params[0], params[1]),label='best fit: sigma=sqrt((intensity^ 0.51)^2+9.13^2)')




ax.set(xlabel='<intensity>', ylabel='sigma',
       title='EXPLORING PHOTONS GRAPH MODIFIED')
ax.grid()
ax.legend()

fig.savefig("graficoFinaleModificato.png")
plt.show()


