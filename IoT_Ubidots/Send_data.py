import serial, time  
import psycopg2
try:
     connection = psycopg2.connect(
     host = "localhost",
     user = "postgres",
     password ="2369115",
     database="challenge")

     print("conexión exitosa")
     cursor = connection.cursor()
except Exception as ex: 

    print(ex)     


puerto =serial.Serial(port = "COM7", 
                       baudrate =115200)
while True: 

    time.sleep(2)
    data =puerto.readline()
    dato= data.split()
    #print(data)
    temperatura = float(dato[1].decode("utf-8"))
    humedad = float(dato[0].decode("utf-8"))
    query = "INSERT INTO arduino_table (temperatura) VALUES(%s)" % temperatura
    print(query)
    cursor.execute(query)
    connection.commit()
    query = "INSERT INTO arduino_table (temperatura) VALUES(%s)" % humedad
    print(query)
    cursor.execute(query)
    connection.commit()
    
connection.close()
puerto.close()



