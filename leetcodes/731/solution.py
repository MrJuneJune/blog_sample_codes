class MyCalendarTwo(object):

    def __init__(self):
        self.schedules = []
        self.overlaps = []

    def book(self, start, end):
        overlaps = []
        for schedule in self.schedules:
            start_i, end_i = schedule
            if (start < end_i and end > start_i):
                overlaps.append([max(start_i, start), min(end_i, end)])

        for overlap in overlaps:
            for schedule in self.overlaps:
                if (schedule[0] < overlap[1] and overlap[0] < schedule[1] ):
                    return False

        self.schedules.append([start,end])
        for i in overlaps:
            self.overlaps.append(i)
        return True



