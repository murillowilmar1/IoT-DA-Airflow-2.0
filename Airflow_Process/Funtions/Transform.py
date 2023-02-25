

import pandas as pd 
import numpy as np 


def transf():
    

     url= "/usr/local/airflow/tests/arduino_table.csv"
     df=pd.read_csv(url)


     # Variable Temperatura 
     mean =df.temperatura.mean()
     df["temperatura"]= df["temperatura"].replace(np.nan, mean)

     
     # Variable Humedad  
     mean =df.hum.mean()
     df["hum"]= df["hum"].replace(np.nan, mean)




     