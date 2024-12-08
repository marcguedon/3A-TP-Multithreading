from multiprocessing.managers import BaseManager
from multiprocessing import Queue

PORT = 50000
PASSWORD = b"ArielleLeS"

tasks_queue = Queue()
results_queue = Queue()


class QueueManager(BaseManager):
    pass


class QueueClient:
    def __init__(self):
        QueueManager.register("tasks_queue")
        QueueManager.register("results_queue")

        manager = QueueManager(address=("localhost", PORT), authkey=PASSWORD)
        manager.connect()

        self.tasks_queue = manager.tasks_queue()
        self.results_queue = manager.results_queue()


if __name__ == "__main__":
    QueueManager.register("tasks_queue", callable=lambda: tasks_queue)
    QueueManager.register("results_queue", callable=lambda: results_queue)

    manager = QueueManager(address=("", PORT), authkey=PASSWORD)

    server = manager.get_server()
    server.serve_forever()
