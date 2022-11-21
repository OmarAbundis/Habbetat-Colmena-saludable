
# -*- coding: utf-8 -*-
"""
Created on Sun Nov  6 12:41:02 2022

@author: Raymundo Soto Soto
"""
#Instalar las bibliotecas del archivo requeriments.txt

# Instalar con el comando pip installl requeriments.txt

# Se importan las bibliotecas a usar
import pandas as pd
from prophet import Prophet
from prophet.plot import plot_plotly, plot_components_plotly
import matplotlib.pyplot as plt
from prophet.plot import add_changepoints_to_plot
from prophet.serialize import model_to_json, model_from_json  #Sirve para guardar el modelo

# El archivo csv con los datos a procesar debe tener 2 columnas; una llamada ds (datestamp) y otra y (datos del peso de la colmena)
df = pd.read_csv('abejas_datos.csv')  #Se leen los datos del archivo .csv  (provienen de la base de datos)
df.head() # Se leen cabezados del data frame abejas_datos.csv
# plt.plot(df['y'])
# plt.show()

df = df[-5000:]  # Se importan los últimos 5000 datos de la base de datos con el peso

m = Prophet() # Se crea una instancia de la biblioteca Prophet que creará el modelo m para la predicción
m.fit(df)  # Se crea el modelo con los datos leídos en df

future = m.make_future_dataframe(periods=1) #Se realiza la predicción con el modelo ajustado, en este caso el periodo es en días
future.tail()                               # Usar más periodos para más dìas pero el error aumenta

forecast = m.predict(future)
forecast[['ds', 'yhat', 'yhat_lower', 'yhat_upper']]  # Se generan los datos de la predicción y se añaden al final del dataframe

"""Prophet genera el modelo de ajuste de datos y la predicción de en periodos de tiempo hacía adelante,
también genera los analisis del error en los que incurre la predicción y los muestra en un grafico,
yhat_upper es el lìmite superior de error, yhat_lower es el límite inferior, yhat es el valor predicho,
también muestra en la gráfica los valores usados para la predicción.
"""

fig1 = m.plot(forecast, uncertainty=True, xlabel='Fecha', ylabel='Peso colmena, kg').savefig('prediccion_1.png')  # Se grafica en la figura 1 todos los datos de la predicciòn

fig2 = m.plot_components(forecast)  #Graficar Componentes del comportamiento
components_fig = fig2
axes = components_fig.get_axes()
print(axes)
axes[0].set_xlabel('Fecha')
axes[0].set_ylabel('Peso de la colmena, kg')
axes[1].set_ylabel('Cambios del peso')
axes[1].set_xlabel('Hora del día')

fig2.savefig('analisis_tendencia.png')
#print(forecast) #Imprimir los valores dela prediccion

# Añadir donde hay cambios bruscos, añade líneas rojas donde hay cambios bruscos de comportamiento
fig3 = m.plot(forecast, xlabel='Fecha', ylabel='Peso de la colmena, kg')
a = add_changepoints_to_plot(fig3.gca(), m, forecast)
fig3.savefig('zonas_cambios.png')

# Esta sección sirve para hacer una nueva predicción pero un rango para mostrar màs cambios bruscos
# Descomentar y cambiar el valor del (changepoint_range=0.5) a otro valor

# pro_change= Prophet(changepoint_range=0.5)
# forecast = pro_change.fit(df).predict(future)
# fig4= pro_change.plot(forecast);
# a = add_changepoints_to_plot(fig4.gca(), pro_change, forecast)
# fig4.savefig('zonas_cambios.png')




# #plt.plot(forecast(['ds']))
# datos = forecast[:]['trend']
# tiempo = forecast[:]['ds'] 
# #print(forecast[:]['trend'])
# plt.plot(tiempo, datos, 'r')
# plt.plot(forecast['ds'],forecast['yhat'], 'g')
plt.show()


# Se guarda el modelo para ser utilizado posteriormente

with open('serialized_model.json', 'w') as fout:
    fout.write(model_to_json(m))  # Save model

# Instruccciones para cargar el modelo si así se desea
# with open('serialized_model.json', 'r') as fin:
#     m = model_from_json(fin.read())  # Load model