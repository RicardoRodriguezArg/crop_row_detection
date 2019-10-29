from flask import Flask, render_template, request, send_from_directory

from utils import ServerConfig
from utils import Utils


app = Flask(__name__)
server_config = ServerConfig('./config.ini')
utils = Utils(server_config.configuration_dict)


@app.route("/")
def index():
    return render_template("index.html")


@app.route('/upload', methods=['POST'])
def upload_files():
    section = server_config['UPLOAD_DIRECTORIES']
    directory_to_save = section['RAW_AERIALS_IMAGES']
    for upload in request.files.getlist("file"):
        print("{} is the file name".format(upload.filename))
        filename = upload.filename
        if not (utils.is_file_allowed(filename)):
            print ("Not allowed File: {}".format(filename))
        else:
            print("Save it to:", directory_to_save)
            upload.save(directory_to_save)

    return render_template("image_upload_complete.html")


@app.route('/upload/<filename>')
def send_image(filename):
    return send_from_directory("images", filename)
