import numpy
from numpy import genfromtxt
import seaborn
import matplotlib.pylab as plt

#Configure matplot lib
plt.style.use("seaborn")

def generate_heatmap(data):
    plt.figure(figsize=(6,7))
    heat_map = seaborn.heatmap( data, linewidth = 1 , annot = True)
    plt.title( "Heatmap T=10" )
    plt.show()

predicted_temps = genfromtxt('predicted_heatmap.csv', delimiter=',')
generate_heatmap(predicted_temps)