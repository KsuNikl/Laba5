trams_stops = {}
stops_trams = {}

def load_trams():
    print("Загружаю список трамваев для теста...")
    with open("trams.txt", encoding="utf-8") as f:
        tokens = f.read().split()
    i = 0
    while i < len(tokens):
        tram = tokens[i]; i += 1
        stops_count = int(tokens[i]); i += 1
        stops = tokens[i:i + stops_count]; i += stops_count
        create_tram(tram, stops)

def create_tram(tram_name, stops):
    if tram_name in trams_stops:
        print(f"Трамвай №{tram_name} уже существует!")
    else:
        trams_stops[tram_name] = list(stops)
        for stop in stops:
            stops_trams.setdefault(stop, []).append(tram_name)
        print(f"Успешно создан трамвай № {tram_name}")

def trams_in_stop(stop_name):
    if stop_name in stops_trams:
        print(f"Трамваи на остановке {stop_name}:", end="")
        for tram in stops_trams[stop_name]:
            print(f" {tram}", end="")
        print("", end="\n")
    else:
        print(f"Остановки {stop_name} не существует!")

def stops_in_tram(tram_name):
    if tram_name in trams_stops:
        print(f"Остановки трамвая №{tram_name}:", end="")
        c = 1
        for stop in trams_stops[tram_name]:
            print(f"\n{c}. Stop {stop}: ", end="")
            for tram in stops_trams.get(stop, []):
                if tram != tram_name:
                    print(f"{tram} ", end="")
            c += 1
        print("", end="\n")
    else:
        print(f"Трамвая {tram_name} не существует!")

def trams():
    if trams_stops:
        for tram, stops in trams_stops.items():
            print(f"TRAM {tram}:", end="")
            for stop in stops:
                print(f" {stop}", end="")
            print()
    else:
        print("Список трамваев пуст.")

load_trams()
while True:
    cmd = input("   Введите команду > ").split()

    if cmd[0] == "CREATE_TRAM" and len(cmd) > 2:
        tram_name = cmd[1]
        stops_count = int(cmd[2])
        stops = cmd[3:]
        while len(stops) < stops_count:
            stops.extend(input().split())
        stops = stops[:stops_count]
        create_tram(tram_name, stops)
    elif cmd[0] == "TRAMS_IN_STOP" and len(cmd) == 2:
        stop_name = cmd[1]
        trams_in_stop(stop_name)
    elif cmd[0] == "STOPS_IN_TRAM" and len(cmd) == 2:
        tram_name = cmd[1]
        stops_in_tram(tram_name)
    elif cmd[0] == "TRAMS" and len(cmd) == 1:
        trams()
    elif cmd[0] == "EXIT" and len(cmd) == 1:
        break
    else:
        print("Введена неизместная команда!")