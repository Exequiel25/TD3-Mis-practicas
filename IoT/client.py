# client.py
import requests


def get_sensor_data():
    response = requests.get('http://127.0.0.1:5000/sensor')
    if response.status_code == 200:
        sensor_data = response.json()
        print(f"Sensor Data: {sensor_data}")
    else:
        print("Failed to retrieve sensor data")


if __name__ == '__main__':
    get_sensor_data()
