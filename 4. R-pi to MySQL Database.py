# server.py file to handle incoming data from ESP32
pip install flask mysql-connector-python
from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

# Database connection
db = mysql.connector.connect(
    host="localhost",
    user="root",
    password="your_mysql_password",
    database="smart_meter_db"
)
cursor = db.cursor()

@app.route('/receive_data', methods=['POST'])
def receive_data():
    data = request.json
    sql = "INSERT INTO meter_readings (usage_kWh, lagging_kVarh, leading_kVarh, lagging_pf, leading_pf) VALUES (%s, %s, %s, %s, %s)"
    values = (data["usage_kWh"], data["lagging_kVarh"], data["leading_kVarh"], data["lagging_pf"], data["leading_pf"])
    
    cursor.execute(sql, values)
    db.commit()
    
    return jsonify({"message": "Data stored successfully"}), 200

if __name__ == '__main__':
    app.run(host="0.0.0.0", port=5000, debug=True)


# Bash - To run Flask server and receive data from ESP32
# python3 server.py