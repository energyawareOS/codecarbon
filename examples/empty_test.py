from codecarbon import EmissionsTracker

tracker = EmissionsTracker()
tracker.start()
emissions: float = tracker.stop()
print(emissions)
