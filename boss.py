from task import Task
from queuemanager import QueueClient


class Boss(QueueClient):
    result = None

    def run(self):
        while True:
            self.post_task()
            self.get_results()
            print(self.result)

    def post_task(self):
        task = Task()
        self.tasks_queue.put(task)

    def get_results(self):
        self.result = self.results_queue.get()


if __name__ == "__main__":
    boss = Boss()
    boss.run()