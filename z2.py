def distribute(clients, windows_count):
    clients.sort(key=lambda a: a[1], reverse=True)
    windows_load = [0] * windows_count
    windows_clients = [[] for _ in range(windows_count)]

    for talon, time in clients:
        min_idx = 0
        for i in range(1, windows_count):
            if windows_load[i] < windows_load[min_idx]:
                min_idx = i
        windows_load[min_idx] += time
        windows_clients[min_idx].append(talon)

    for i in range(windows_count):
        print(f"Окно {i + 1} ({windows_load[i]} минут): ", end="")
        for j, t in enumerate(windows_clients[i]):
            print(t, end="")
            if j != len(windows_clients[i]) - 1:
                print(", ", end="")
        print("", end="\n")


windows_count = int(input("Введите кол-во окон: "))
talon_count = 0
clients = []

while True:
    cmd = input("   Введите команду > ").split()

    if cmd[0] == "ENQUEUE" and len(cmd) == 2:
        time = int(cmd[1])
        talon_count += 1
        talon = f"T{talon_count:03d}"
        clients.append((talon, time))
        print(talon)

    elif cmd[0] == "DISTRIBUTE" and len(cmd) == 1:
        distribute(clients, windows_count)

    else:
        print("Введена неверная команда!")