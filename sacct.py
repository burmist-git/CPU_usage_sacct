import pandas as pd
import datetime

df = pd.read_csv("sacct_output_clean.csv", names=["JobID", "AllocCPUS", "Elapsed"], skiprows=2, delimiter="\s+")
total_cpu_hours = 0
print(df['Elapsed'])                                                                                                                                                                                       

df['Elapsed'] = pd.to_timedelta(df['Elapsed'])

df['Elapsed_x_cpus'] = df['Elapsed'] * df['AllocCPUS']

total_elapsed = df['Elapsed_x_cpus'].sum()
total_hours = total_elapsed.total_seconds() / 3600

print(df) 

print(f"Total CPU hours used: {total_hours} hours")

