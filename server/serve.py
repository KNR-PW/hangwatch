import time
from flask import Flask, request,  jsonify

app = Flask(__name__, template_folder='template')




state = {}

@app.route('/hooks', methods=['POST'])
def receive_data():
    lastUpdate = time.time()
    try:

        content = request.get_json() 
        if 'state' in content:
         received_state = content['state']
         state['place'] = {} 
         state['place']['state'] = received_state
         state['place']=content['place']
         state['state']=content['state']
         state['time']=lastUpdate
        
         print(f"place: {state['place']}, State: {state['state']}")
    
        return jsonify({'success': True})
    except Exception as e:
        print(f"Error receiving state: {str(e)}")
        return jsonify({'success': False, 'error': str(e)})


@app.route('/hooks', methods=['GET'])
def check_state():
    if (time.time() - state['time']) > 7220:
         state['state'] = 'offline'
    elif (time.time() - state['time']) > 10:
        state['state'] = 'empty'    
    
    
    return jsonify(state)


if __name__ == '__main__':
    app.run(host="0.0.0.0", debug=True)