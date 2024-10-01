from collections import defaultdict

class AllOne:

    def __init__(self):
        self.map = {}
        self.freq_map = defaultdict(set)
        self.min_freq = float("inf") 
        self.max_freq = 0 

    def inc(self, key: str) -> None:
        if key in self.map:
            freq = self.map[key]
            self.freq_map[freq].remove(key)
            if not self.freq_map[freq]:
                del self.freq_map[freq]

            self.map[key] += 1
        else:
            self.map[key] = 1
            self.min_freq = 1

        freq = self.map[key]
        self.freq_map[freq].add(key)

        self.max_freq = max(self.max_freq, freq)

        if self.min_freq not in self.freq_map:
            self.min_freq = freq

    def dec(self, key: str) -> None:
        if key in self.map:
            freq = self.map[key]
            self.freq_map[freq].remove(key)
            if not self.freq_map[freq]:
                del self.freq_map[freq]

            if freq == 1:
                del self.map[key]
            else:
                self.map[key] -= 1
                new_freq = self.map[key]
                self.freq_map[new_freq].add(key)

            if self.max_freq == freq and not self.freq_map.get(freq):
                self.max_freq -= 1

            if self.min_freq == freq and not self.freq_map.get(freq):
                if self.map:
                    self.min_freq = min(self.freq_map.keys())
                else:
                    self.min_freq = float("inf")

    def getMaxKey(self) -> str:
        if self.max_freq > 0:
            return next(iter(self.freq_map[self.max_freq]))
        return ""

    def getMinKey(self) -> str:
        if self.min_freq < float("inf"):
            return next(iter(self.freq_map[self.min_freq]))
        return ""
