from flask import Flask, request, render_template, redirect
from modules.db_data import DbData

db = DbData(data_file="text.txt")
app = Flask(__name__)

@app.route('/')
def home():
    return 'dab 420 blaze it OwO'

@app.route("/scoreboard_post", methods=["POST"])
def scoreboard_post():
    if request.method == 'POST':
        request_data = request.get_json()
        db.write_data(request_data)
        return "Success"

@app.route('/demo')
def demo():
    return {"response":db.get_data()}

@app.errorhandler(405)
def err(e):
    return redirect('/')

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0')