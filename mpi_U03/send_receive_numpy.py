from mpi4py import MPI
import numpy as np

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

# explizite Übergabe von MPI-Datentypen

# if rank == 0:
#     data = np.arange(1000, dtype="i")
#     comm.Send([data, MPI.INT], dest=1, tag=77)
#     print(f"Process {rank} sent data: {data[:10]}...")
# elif rank == 1:
#     data = np.empty(1000, dtype="i")
#     comm.Recv([data, MPI.INT], source=0, tag=77)
#     # only print the first 10 elements
#     print(f"Process {rank} received data: {data[:10]}...")


# automatische MPI-Datentyp-Erkennung

if rank == 0:
    data = np.arange(100, dtype=np.float64)
    comm.Send(data, dest=1, tag=13)
    print(f"Process {rank} sent data: {data[:10]}...")
elif rank == 1:
    data = np.empty(100, dtype=np.float64)
    comm.Recv(data, source=0, tag=13)
    print(f"Process {rank} received data: {data[:10]}...")
