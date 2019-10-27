from flask import Flask, flash, request, redirect, url_for

from utils import ServerConfig
from utils import Utils

from werkzeug.utils import secure_filename

import os

app = Flask(__name__)
server_config = ServerConfig('./config.ini')
utils = Utils(server_config)

@app.route('/', methods=['GET', 'POST'])
def upload_files():
    if request.method == 'POST':
        # check if the post request has the file part
        if 'file' not in request.files:
            flash('No file part')
            return redirect(request.url)
    file = request.files['file']
    # if user does not select file, browser also
    # submit an empty part without filename
    if file.filename == '':
        flash('No selected file')
        return redirect(request.url)
    if file and utils.allowed_file(file.filename):
        filename = secure_filename(file.filename)
        section = server_config['UPLOAD_DIRECTORIES']
        directory_to_save = section['RAW_AERIALS_IMAGES']
        file.save(os.path.join(directory_to_save, filename))
        return redirect(url_for('upload_files', filename=filename))

    return '''
    <!doctype html>
    <title>Upload Raw Images</title>
    <h1>Upload Aerials Images Files</h1>
    <form method=post enctype=multipart/form-data>
      <input type=file name=file>
      <input type=submit value=Upload>
    </form>
    '''
