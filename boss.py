import threading
import json

from task import Task
from queuemanager import QueueClient


class Boss(QueueClient):
    def run(self):
        self.post_task()

    def post_task(self):
        task = Task(size=5000)
        self.tasks_queue.put(task)
        self.tasks_queue.put(task)
        print("[BOSS] Envoi Task")

    def print_result(self):
        print("identifier 2 -> C++ / identifier 3 -> python")
        for _ in range(2):
            result_task = self.results_queue.get()
            file = json.loads(result_task.to_json())
            time = file["time"]
            size = file["size"]
            identifier = file["identifier"]
            print(
                "[BOSS] Tâche", "identifier:", identifier, "time:", time, "size:", size
            )


if __name__ == "__main__":
    boss = Boss()

    result_thread = threading.Thread(target=boss.print_result, daemon=True)
    result_thread.start()

    boss.run()

    result_thread.join()
