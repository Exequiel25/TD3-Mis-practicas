import os

# Create a pipe
read_pipe, write_pipe = os.pipe()

# Create a child process
child_pid = os.fork()

# Father process
if child_pid > 0:
    # Close the read pipe
    os.close(read_pipe)
    # Read gps data from gps_data.csv and discard the first line
    with open('gps_data.csv', 'r') as f:
        f.readline()
        # For each line in the file
        for line in f:
            # Write the line to the pipe
            os.write(write_pipe, line.encode())
    # Close the write pipe
    os.close(write_pipe)
    # Wait for the child process to finish
    pid, status = os.waitpid(child_pid, 0)
    print(f'Child process {child_pid} finished with status {status}')
# Child process
else:
    # Close the write pipe
    os.close(write_pipe)
    # Read the data from the pipe and calculate the distance using the Harvesine formula
    distance = 0
    prev_lat = None
    prev_lon = None
    while True:
        # Read a data from the pipe
        data = os.read(read_pipe, 1024)
        # If the data is empty, the pipe is closed
        if not data:
            break
        # Decode the data
        data = data.decode()
        # Split the data into lines
        lines = data.splitlines()
        # Split each line into fields
        for line in lines:
            fields = line.split(',')
            # Extract the latitude and longitude
            lat = float(fields[1])
            lon = float(fields[2])
            # If this is not the first line
            if prev_lat is not None:
                # Calculate the distance between the previous and the current point
                dlat = lat - prev_lat
                dlon = lon - prev_lon
                a = (dlat / 2) ** 2 + prev_lat * lat * (dlon / 2) ** 2
                c = 2 * a ** 0.5
                distance += c * 6371
            # Save the current latitude and longitude
            prev_lat = lat
            prev_lon = lon
    # Print the total distance
    print(f'Total distance: {distance:.2f} km')
    # Close the read pipe
    os.close(read_pipe)
    # Exit the child process
    exit(0)
