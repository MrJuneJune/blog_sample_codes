class CustomStack:

    def __init__(self, maxSize: int):
        self.life = []
        self.maxSize = maxSize

    def push(self, x: int) -> None:
        if len(self.life) < self.maxSize:
            self.life.append(x)

    def pop(self) -> int:
        return self.life.pop() if self.life else -1

    def increment(self, k: int, val: int) -> None:
        # Increment the first min(k, len(self.life)) elements
        limit = min(k, len(self.life))
        for i in range(limit):
            self.life[i] += val


