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


if __name__ == "__main__":
    unittest.main()
