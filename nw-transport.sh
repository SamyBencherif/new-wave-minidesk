tar -czf new-wave-minidesk.tar.gz new-wave-minidesk

echo copy to external machine A
scp new-wave-minidesk.tar.gz user@ip:path

echo copy to external machine B
scp new-wave-minidesk.tar.gz user@ip:path

# after running this file, run nw-unpack on those machines
# this can be done via ssh so dev and runtime can be done on a single machine
