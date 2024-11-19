# sensor_server.py
from flask import Flask

app = Flask(__name__)


@app.route('/sensor', methods=['GET'])
def get_sensor_value():
    # Simular un valor de sensor
    sensor_value = {"temperature": 23.5}
    return sensor_value, 200


if __name__ == '__main__':
    print("http://localhost:5000/sensor")
    app.run(host='localhost', port=5000)
