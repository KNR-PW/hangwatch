import time
from flask import Flask, request,  jsonify

app = Flask(__name__, template_folder='template')

lastUpdate = time.time()


state = {}

@app.route('/hooks', methods=['POST','GET'])
def receive_data():
    global lastUpdate
    try:

        content = request.get_json() 
        if 'state' in content:
         received_state = content['state']
         state['miejsce'] = {} 
         state['miejsce']['state'] = received_state
         state['miejsce']=content['miejsce']
         state['state']=content['state']
         lastUpdate = time.time() # Zaktualizuj czas ostatniej aktualizacji
        
         print(f"Miejsce: {state['miejsce']}, Stan: {state['state']}")
        
# Sprawdź, czy czas od ostatniej aktualizacji przekroczył 2 godziny
        if time.time() - lastUpdate > 7200:
            state['state'] = 'offline'
        return jsonify({'success': True})
    except Exception as e:
        print(f"Error receiving state: {str(e)}")
        return jsonify({'success': False, 'error': str(e)})


if time.time() - lastUpdate > 10:
    state['state'] = 'empty'



if __name__ == '__main__':
    app.run(host="0.0.0.0", debug=True)