
from airflow.hooks.postgres_hook import PostgresHook





def extr_data():
   #  logging.info("scrapping")
   pg_hook = PostgresHook(postgres_conn_id="challenge", schema ="challenge_1")
   with open ("/usr/local/airflow/include/Sales_data.sql", "r") as sqlfile:
    sql_stm= sqlfile.read()
   df = pg_hook.get_pandas_df(sql = f"{sql_stm}") 
   df.to_csv("/usr/local/airflow/tests/Sales_data_dirty.csv")