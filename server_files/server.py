from flask import Flask, request, jsonify
import socket
import threading
import time
import struct

app = Flask(__name__)

coordinates = {'x': 0.0, 'y': 0.0, 'z': 0.0}
lock = threading.Lock()

def send_coordinates():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect(('localhost', 65432))
        while True:
            with lock:
                data = struct.pack('fff', coordinates['x'], coordinates['y'], coordinates['z'])
            s.sendall(data)
            time.sleep(1)  # Update coordinates every second

@app.route('/update_coordinates', methods=['POST'])
def update_coordinates():
    data = request.json
    x = data.get('x')
    y = data.get('y')
    z = data.get('z')
    if x is not None and y is not None and z is not None:
        with lock:
            coordinates['x'] = float(x)
            coordinates['y'] = float(y)
            coordinates['z'] = float(z)
        return jsonify({"status": "success"}), 200
    else:
        return jsonify({"status": "failure", "message": "Invalid coordinates"}), 400

if __name__ == '__main__':
    threading.Thread(target=send_coordinates, daemon=True).start()
    app.run(debug=True)