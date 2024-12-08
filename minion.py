from queuemanager import QueueClient


class Minion(QueueClient):
    result = []
    task = []

    def run(self):
        while True:
            self.get_tasks()
            self.process_tasks()
            self.post_results()

    def get_tasks(self):
        self.task = self.tasks_queue.get()

    def process_tasks(self):
        self.task.work()
        self.result = self.task.get_x()

    def post_results(self):
        self.results_queue.put(self.result)


if __name__ == "__main__":
    minion = Minion()
    minion.run()
