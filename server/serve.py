import time
from flask import Flask, request,  jsonify

app = Flask(__name__, template_folder='template')

lastUpdate = time.time()


state = {}

@app.route('/hooks', methods=['POST'])
def receive_data():
    
    try:

        content = request.get_json() 
        if 'state' in content:
         received_state = content['state']
         state['place'] = {} 
         state['place']['state'] = received_state
         state['place']=content['place']
         state['state']=content['state']
          # Zaktualizuj czas ostatniej aktualizacji
        # Zaktualizuj czas ostatniej aktualizacji
      
         
         print(f"place: {state['place']}, State: {state['state']}")
    
        return jsonify({'success': True})
    except Exception as e:
        print(f"Error receiving state: {str(e)}")
        return jsonify({'success': False, 'error': str(e)})


@app.route('/hooks', methods=['GET'])
def check_state():
    
    if time.time() - lastUpdate > 10:
        lastUpdate = time.time()
        state['state'] = 'empty' 
    elif time.time() - lastUpdate > 7200:
        state['state'] = 'offline'
    return jsonify(state)


@app.route('/state', methods=['GET'])
def get_state():
    return jsonify(state)

if __name__ == '__main__':
    app.run(host="0.0.0.0", debug=True)