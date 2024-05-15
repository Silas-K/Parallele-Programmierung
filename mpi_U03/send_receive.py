from mpi4py import MPI

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

# Blocking

if rank == 0:
    data = {"a": 7, "b": 3.14}
    comm.send(data, dest=1, tag=11)
    print(f"Process {rank} sent data: {data}")
elif rank == 1:
    data = comm.recv(source=0, tag=11)
    print(f"Process {rank} received data: {data}")


# Non-blocking
# if rank == 0:
#     print(f"Process {rank} started.")
#
#     data = {"a": 7, "b": 3.14}
#     req = comm.isend(data, dest=1, tag=11)
#     print(f"Process {rank} sending data...")
#
#     req.wait()
#     print(f"Process {rank} sent data: {data}")
# elif rank == 1:
#     print(f"Process {rank} started.")
#
#     req = comm.irecv(source=0, tag=11)
#
#     print(f"Process {rank} waiting for data...")
#     data = req.wait()
#     print(f"Process {rank} received data: {data}")
