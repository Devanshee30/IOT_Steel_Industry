import mysql.connector
import pandas as pd

# Database connection
db = mysql.connector.connect(
    host="192.168.1.100",  # Change this to RPi's IP if running from another system
    user="root",
    password="your_mysql_password",
    database="smart_meter_db"
)
cursor = db.cursor()

# Fetch data
cursor.execute("SELECT * FROM meter_readings")
rows = cursor.fetchall()

# Convert to DataFrame
df = pd.DataFrame(rows, columns=["ID", "Timestamp", "Usage_kWh", "Lagging_kVarh", "Leading_kVarh", "Lagging_PF", "Leading_PF"])

# Save as CSV
df.to_csv("smart_meter_data.csv", index=False)

print("Data exported to smart_meter_data.csv successfully!")
