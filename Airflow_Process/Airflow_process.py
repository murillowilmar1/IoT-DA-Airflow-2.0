from datetime import timedelta,datetime 
from dateutil.relativedelta import relativedelta
from airflow.utils.dates import days_ago 
from typing import Dict
from airflow import DAG
from airflow.operators.python import PythonOperator 
from airflow.providers.amazon.aws.transfers.local_to_s3 import LocalFilesystemToS3Operator
from airflow.operators.email import EmailOperator
from airflow.models.baseoperator import chain



from dags.funtions.extract import extr_data
from dags.funtions.Transform import transf


default_args = {
    "owner": "wmurillo",
    "depends_on_past":False,
    "email": ["murillowilmar1@gmail.com"], 
    "email_on_failure": False,
    "email_on_retry": False,  
    "retries": 5, 
    "retry_delay":timedelta(minutes=1)
}


with DAG(

     "IoT_Dag", 
     default_args=default_args,
     start_date= datetime(2022,1,12),
     max_active_runs =5, 
     description = " DAG_production",
     schedule_interval="@hourly", 
     tags=["DAG_Production"], 
     catchup =False, 
     template_searchpath = "/usr/local/air_flow/include/"
) as dag: 



  #Task 1 
       extract_data= PythonOperator(task_id="extract_data", python_callable=extr_data)
  #Task 2 
       Transform_data =  PythonOperator(task_id ="Transform_data", python_callable=transf) 
  #Task 3 
       load_data =LocalFilesystemToS3Operator(
        task_id = "load_data",
        filename='/usr/local/airflow/tests/Sales_data_clean.csv',
        dest_key='Sales_data_clean.csv',
        dest_bucket='awswmurillo',
        aws_conn_id="aws_s3",
        replace=True
     )     



       extract_data >> Transform_data >> load_data