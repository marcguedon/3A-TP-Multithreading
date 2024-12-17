import time
import json
import numpy as np


class Task:
    def __init__(self, identifier=0, size=None, a=None, b=None):
        self.identifier = identifier
        self.size = size or np.random.randint(300, 3_000)

        if a is None:
            self.a = np.random.rand(self.size, self.size)
        else:
            self.a = a

        if b is None:
            self.b = np.random.rand(self.size)
        else:
            self.b = b

        self.x = np.zeros(self.size)
        self.time = None

    def work(self):
        start = time.perf_counter()
        self.x = np.linalg.solve(self.a, self.b)
        self.time = time.perf_counter() - start

    def get_x(self):
        return self.x

    def to_json(self) -> str:
        return json.dumps(
            {
                "identifier": self.identifier,
                "size": self.size,
                "a": self.a.tolist(),
                "b": self.b.tolist(),
            }
        )

    @staticmethod
    def from_json(text: str) -> "Task":
        json_file = json.loads(text)
        return Task(
            json_file["identifier"],
            json_file["size"],
            np.array(json_file["a"]),
            np.array(json_file["b"]),
        )

    def __eq__(self, other: "Task") -> bool:
        if not isinstance(other, Task):
            return False

        return (
            self.identifier == other.identifier
            and self.size == other.size
            and np.array_equal(self.a, other.a)
            and np.array_equal(self.b, other.b)
        )
