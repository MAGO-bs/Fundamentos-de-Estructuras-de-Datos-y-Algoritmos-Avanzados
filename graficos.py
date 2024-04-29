import matplotlib.pyplot as plt  # Para plotear
import pandas as pd  # Para leer archivo .csv
import sys
import numpy as np

# Generar tablas en latex
exper = pd.read_csv('experimentacion.csv')
latex_exper = exper.to_latex(index=False, escape=False)
print(latex_exper)

# Tamaño del input
n = exper['n_plus_m'].values 
m_1 = exper['time_prom[microseg.]'].values

sd_1 = exper['time_desv_std[microseg.]'].values
lower_limits_1 = [mean - std for mean, std in zip(m_1, sd_1)]
upper_limits_1 = [mean + std for mean, std in zip(m_1, sd_1)]
# Definir la función exponencial de 3^x
def expon_3(x):
    return (1/10000)*(3 ** x)

# Graficar los datos
plt.errorbar(n, m_1, yerr=sd_1, fmt='.', capsize=4, color='blue', label='Edit Distance')
plt.plot(n, m_1, '-o', color='blue', markersize=2)

# Graficar la función 3^x
x_values = np.linspace(min(n), max(n), 100)
plt.plot(x_values, expon_3(x_values), color='red', label='$3^{(n+m)}$')

# Graficar los intervalos de confianza
for x, y, lower, upper in zip(n, m_1, lower_limits_1, upper_limits_1):
    plt.plot([x, x], [lower, upper], color='red')

# Configurar el título y las etiquetas de los ejes
plt.title('Tiempos Experimentación vs $C \cdot 3^{(n+m)}$')
plt.xlabel('Tamaño del Input (n + m)')
plt.ylabel('Tiempo [$\mu$s]')

# Agregar la leyenda
plt.legend()

# Mostrar la gráfica
plt.show()