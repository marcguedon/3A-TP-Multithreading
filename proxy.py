#!/usr/bin/env python

from http.server import BaseHTTPRequestHandler, HTTPServer
from json import dumps
from queuemanager import QueueClient
from task import Task


class Proxy(BaseHTTPRequestHandler):
    def __init__(self, *args, **kwargs):
        self.client = QueueClient()
        super().__init__(*args, **kwargs)

    def do_GET(self):
        self.send_response(200)
        self.send_header("Content-type", "application/json")
        self.end_headers()
        task = self.client.tasks_queue.get()
        self.wfile.write(bytes(task.to_json(), "utf-8"))

    def do_POST(self):
        self.send_response(200)
        self.send_header("Content-type", "application/json")
        self.end_headers()
        content_length = int(self.headers.get("content-length"))
        content = self.rfile.read(content_length)
        task = Task.from_json(content.decode())
        task = self.client.results_queue.put(task)
        self.wfile.write(bytes(dumps({"status": "ok"}), "utf-8"))


def run(server_class=HTTPServer, handler_class=Proxy):
    server_address = ("", 8000)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()


if __name__ == "__main__":
    run()
