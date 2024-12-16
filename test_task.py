import unittest
import numpy as np
from task import Task


class TestStringMethods(unittest.TestCase):
    def test_work(self):
        size = 10

        task = Task(size=size)
        task.work()

        np.testing.assert_allclose(
            task.a @ task.x,
            task.b,
            rtol=1e-5,
            atol=1e-8,
            err_msg="res n'est pas égal à x",
        )

    def test_json(self):
        task = Task()

        json = task.to_json()
        task2 = Task.from_json(json)

        self.assertEqual(task, task2)


if __name__ == "__main__":
    unittest.main()
