#!/usr/bin/env python3

import argparse
import json
import time

from flask import Flask, request,  jsonify, make_response

app = Flask(__name__, template_folder='template')

ROOMS = None
state={}

class PasswordError(RuntimeError):
    pass

def check_password(board_id, password):
    if board_id not in ROOMS:
        raise PasswordError("Board ID not accepted")
    if ROOMS[board_id] is not None:
        if password != ROOMS[board_id]:
            raise PasswordError("Invalid password")

@app.route('/hooks', methods=['POST'])
def receive_data():
    
    lastUpdate = time.time()
    global state
    try:

        content = request.get_json() 
        received_state = content['state']
        board_id = content['board_id']
        password = content.get('password')
        if ROOMS is not None:
            check_password(board_id, password)

        if board_id not in state:
            state[board_id] = {"state_change_time": lastUpdate}

        if state[board_id].get('state') != received_state:
            state[board_id]['state'] = received_state
            state[board_id]['state_change_time'] = lastUpdate
        state[board_id]['place'] = content['place']
        state[board_id]['last_activity_time'] = lastUpdate
        
        print(f"Board ID: {board_id}, Place: {state[board_id]['place']}, State: {state[board_id]['state']}")
        
        return jsonify({'success': True})
    except PasswordError as e:
        #return 403 Forbidden
        return jsonify({'success': False, 'error': str(e)}), 403
    except Exception as e:
        print(f"Error receiving state: {str(e)}")
        return jsonify({'success': False, 'error': str(e)})


@app.route('/hooks', methods=['GET'])
def check_state():
    global state
    for board_id, board_state in state.items():
        if board_state.get('last_activity_time') is not None:
            if (time.time() - board_state['last_activity_time']) > 7200:
                board_state['state'] = 'offline'
                board_state['state_change_time'] = time.time()

    response = make_response(jsonify(state))
    response.headers['Access-Control-Allow-Origin'] = '*'
    return response

def process_arguments():
    parser = argparse.ArgumentParser(description='Server for receiving state from boards')
    parser.add_argument('--port', type=int, default=5000, help='Port to run the server on')
    parser.add_argument('--debug', action='store_true', help='Enable debug mode')
    parser.add_argument('--rooms', type=str, default=None, help='Path to rooms file if not provided looking for ./rooms.json file if it does not exist every request will be accepted without password')
    args = parser.parse_args()
    if args.rooms is None:
        try:
            with open('./rooms.json') as f:
                print("Default rooms file found")
                args.rooms = './rooms.json'
        except FileNotFoundError:
            print("rooms file not found❗ Now every post request will be accepted without password.")
    return args

def load_rooms(filepath):
    with open(filepath) as f:
        return json.load(f)

if __name__ == '__main__':
    args = process_arguments()
    if args.rooms is not None:
        ROOMS = load_rooms(args.rooms) if args.rooms is not None else None
    app.run(host="0.0.0.0", port=args.port, debug=args.debug)
