from queuemanager import QueueClient


class Minion(QueueClient):
    def run(self):
        while True:
            task = self.tasks_queue.get()
            task.work()
            task.identifier = 3
            self.results_queue.put(task)


if __name__ == "__main__":
    minion = Minion()
    minion.run()
