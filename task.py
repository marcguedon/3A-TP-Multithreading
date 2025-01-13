import time
import json
import numpy as np


class Task:
    def __init__(self, identifier=0, size=None, a=None, b=None, x=None, time=None):
        self.identifier = identifier
        self.size = size or np.random.randint(300, 3000)

        if a is None:
            self.a = np.random.rand(self.size, self.size)
        else:
            self.a = a

        if b is None:
            self.b = np.random.rand(self.size)
        else:
            self.b = b

        if x is None:
            self.x = np.zeros(self.size)
        else:
            self.x = x

        if time is None:
            self.time = 0.0
        else:
            self.time = time

    def work(self):
        start = time.perf_counter()
        self.x = np.linalg.solve(self.a, self.b)
        self.time = time.perf_counter() - start

    def to_json(self) -> str:
        return json.dumps(
            {
                "identifier": self.identifier,
                "size": self.size,
                "a": self.a.tolist(),
                "b": self.b.tolist(),
                "x": self.x.tolist(),
                "time": self.time,
            }
        )

    @staticmethod
    def from_json(text: str) -> "Task":
        json_file = json.loads(text)
        return Task(
            identifier=json_file["identifier"],
            size=json_file["size"],
            a=np.array(json_file["a"]),
            b=np.array(json_file["b"]),
            x=np.array(json_file["x"]),
            time=json_file["time"],
        )

    def __eq__(self, other: "Task") -> bool:
        if not isinstance(other, Task):
            return False

        return (
            self.identifier == other.identifier
            and self.size == other.size
            and np.array_equal(self.a, other.a)
            and np.array_equal(self.b, other.b)
            and np.array_equal(self.x, other.x)
            and np.isclose(self.time, other.time, rtol=1e-5, atol=1e-8)
        )

    def __repr__(self) -> str:
        return str(self.x)
