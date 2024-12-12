from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/esp-data', methods=['GET'])
def get_data():
    return jsonify({"message": "Hello from the Python server!"})

@app.route('/esp-data', methods=['POST'])
def receive_data():
    data = request.json
    print(f"Received data from ESP32: {data}")

    return jsonify({"status": "success", "received": data})


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
